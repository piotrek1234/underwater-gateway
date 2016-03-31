#include <QCoreApplication>
#include "tcpserver.h"
#include "frameparser.h"
#include "axishandler.h"
#include "temphandler.h"
#include "pressurehandler.h"
#include "motorhandler.h"
#include "outputhandler.h"
#include "camerahandler.h"
#include "modbusmaster.h"
#include "modbus_regs.h"

//todo:
// sprawdzić czy konwersja int-u_int16_t-int16_t nie sypie się na odroidzie
// dopracować kamery: zrobić delay pomiędzy ramkami dla kamer, problem analogiczny jak przy modbusie

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    TcpServer s_cam1(6001), s_cam2(6002), s_mod1(6003);
    FrameParser fp1, fp2, fp3;

    //QObject::connect(&s, SIGNAL(frameContent(QString)), &fp, SLOT(parseFrame(QString)));
    //QObject::connect(&s, SIGNAL(frameContent(QString)), &fp, SLOT(printFrame(QString)));
    //QObject::connect(&fp, SIGNAL(sendFrame(QString)), &s, SLOT(sendResponse(QString)));

    QObject::connect(&s_cam1, SIGNAL(frameContent(QString)), &fp1, SLOT(parseFrame(QString)));
    QObject::connect(&fp1, SIGNAL(sendFrame(QString)), &s_cam1, SLOT(sendResponse(QString)));
    QObject::connect(&s_cam2, SIGNAL(frameContent(QString)), &fp2, SLOT(parseFrame(QString)));
    QObject::connect(&fp2, SIGNAL(sendFrame(QString)), &s_cam2, SLOT(sendResponse(QString)));
    QObject::connect(&s_mod1, SIGNAL(frameContent(QString)), &fp3, SLOT(parseFrame(QString)));
    QObject::connect(&fp3, SIGNAL(sendFrame(QString)), &s_mod1, SLOT(sendResponse(QString)));

    MotorHandler* mh = new MotorHandler(6);
    mh->assignRegister(0, MB_CTRL_BLDC_1);
    mh->assignRegister(1, MB_CTRL_BLDC_2);
    mh->assignRegister(2, MB_CTRL_BLDC_3);
    mh->assignRegister(3, MB_CTRL_BLDC_4);
    mh->assignRegister(4, MB_CTRL_BLDC_5);
    mh->assignRegister(5, MB_CTRL_BLDC_6);

    AxisHandler* ah = new AxisHandler(3);
    ah->assignRegister(0, regType::read, MB_STAT_STEPPER_1);
    ah->assignRegister(1, regType::read, MB_STAT_STEPPER_2);
    ah->assignRegister(2, regType::read, MB_STAT_STEPPER_3);
    ah->assignRegister(0, regType::write, MB_CTRL_STEPPER_1_POS);
    ah->assignRegister(1, regType::write, MB_CTRL_STEPPER_2_POS);
    ah->assignRegister(2, regType::write, MB_CTRL_STEPPER_3_POS);
    ah->assignRegister(0, regType::speed, MB_CTRL_STEPPER_1_SPEED);
    ah->assignRegister(1, regType::speed, MB_CTRL_STEPPER_2_SPEED);
    ah->assignRegister(2, regType::speed, MB_CTRL_STEPPER_3_SPEED);

    CameraHandler* ch1 = new CameraHandler(2);
    CameraHandler* ch2 = new CameraHandler(2);

    TempHandler *th = new TempHandler();
    th->assignRegister(9);

    PressureHandler* ph = new PressureHandler();
    ph->assignRegister(8);

    OutputHandler* oh = new OutputHandler(2);
    oh->assignRegister(0, MB_CTRL_POWER_1);
    oh->assignRegister(1, MB_CTRL_POWER_2);

    fp3.addHandler(ah);
    fp3.addHandler(th);
    fp3.addHandler(ph);
    fp1.addHandler(ch1);
    fp2.addHandler(ch2);
    fp3.addHandler(mh);
    fp3.addHandler(oh);

    ModbusMaster* modbus1 = new ModbusMaster("/dev/ttyUSB0", 100);
    //ModbusMaster* modbus2 = new ModbusMaster("/dev/ttySAC1", 101);
    ah->setModbus(modbus1);
    mh->setModbus(modbus1);
    th->setModbus(modbus1);
    ph->setModbus(modbus1);
    oh->setModbus(modbus1);

    s_cam1.start();
    s_cam2.start();
    s_mod1.start();

    return a.exec();
}
