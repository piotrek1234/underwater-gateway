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
// problem z usuwaniem cmd po jego wykonaniu
// dopracować kamery

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    TcpServer s;
    FrameParser fp;

    QObject::connect(&s, SIGNAL(frameContent(QString)), &fp, SLOT(parseFrame(QString)));
    //QObject::connect(&s, SIGNAL(frameContent(QString)), &fp, SLOT(printFrame(QString)));
    QObject::connect(&fp, SIGNAL(sendFrame(QString)), &s, SLOT(sendResponse(QString)));

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

    CameraHandler* ch = new CameraHandler(1);

    TempHandler *th = new TempHandler();
    th->assignRegister(9);

    PressureHandler* ph = new PressureHandler();
    ph->assignRegister(8);

    OutputHandler* oh = new OutputHandler(2);
    oh->assignRegister(0, MB_CTRL_POWER_1);
    oh->assignRegister(1, MB_CTRL_POWER_2);

    fp.addHandler(ah);
    fp.addHandler(th);
    fp.addHandler(ph);
    fp.addHandler(ch);
    fp.addHandler(mh);
    fp.addHandler(oh);

    ModbusMaster* modbus1 = new ModbusMaster("/dev/ttyUSB0", 100);
    //ModbusMaster* modbus2 = new ModbusMaster("/dev/ttySAC1", 101);
    ah->setModbus(modbus1);
    mh->setModbus(modbus1);
    th->setModbus(modbus1);
    ph->setModbus(modbus1);
    oh->setModbus(modbus1);

    s.start();

    return a.exec();
}
