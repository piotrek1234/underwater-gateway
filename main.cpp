#include <QCoreApplication>
#include "tcpserver.h"
#include "frameparser.h"
#include "axishandler.h"
#include "temphandler.h"
#include "pressurehandler.h"
#include "motorhandler.h"
#include "outputhandler.h"
#include "camerahandler.h"
#include "servicehandler.h"
#include "modbusmaster.h"
#include "modbus_regs.h"
#include "logger.h"

//todo:
// - dopracować kamery: zrobić delay pomiędzy ramkami dla kamer, problem analogiczny jak przy modbusie (niepotwierdzone)
// - sprawdzić poprawność wątków przy kamerach (włączenie, wyłączenie, włączenie -> warningi)
// - dodać underwater-gateway do autostartu + ewentualnie niech chodzi jako usługa
// - program zawiesza się po wykonaniu zapytania do modbusa bez aktywnego połączenia z nim
// - sprawdzić czy wytrzyma zalew ramek (np. 8-9-20 na sekundę)
// - sprawdzić optymalny delay modbusa (przy 50ms jest dobrze, być może można zejść niżej)
// - ustawić urządzenie modbusa jako pierwsze pasujące do /dev/ttyUSB{d} (jeśli ma być USB, jeśli SAC to nie ruszać)
// - pauzować kolejkę modbusa dopóki nie odzyska się połączenia

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    TcpServer s_cam1(6001), s_cam2(6002), s_mod1(6003), s_mod2(6004), s_log(6005);
    FrameParser fp1, fp2, fp3, fp4, fp5;
    Logger* lh = new Logger();

    //QObject::connect(&s_cam1, SIGNAL(info(QString)), lh, SLOT(log(QString)));
    //QObject::connect(&s_cam2, SIGNAL(info(QString)), lh, SLOT(log(QString)));
    //QObject::connect(&s_mod1, SIGNAL(info(QString)), lh, SLOT(log(QString)));
    //QObject::connect(&s_mod2, SIGNAL(info(QString)), lh, SLOT(log(QString)));

    QObject::connect(&s_cam1, SIGNAL(frameContent(QString)), &fp1, SLOT(parseFrame(QString)));
    QObject::connect(&fp1, SIGNAL(sendFrame(QString)), &s_cam1, SLOT(sendResponse(QString)));
    QObject::connect(&s_cam2, SIGNAL(frameContent(QString)), &fp2, SLOT(parseFrame(QString)));
    QObject::connect(&fp2, SIGNAL(sendFrame(QString)), &s_cam2, SLOT(sendResponse(QString)));
    QObject::connect(&s_mod1, SIGNAL(frameContent(QString)), &fp3, SLOT(parseFrame(QString)));
    QObject::connect(&fp3, SIGNAL(sendFrame(QString)), &s_mod1, SLOT(sendResponse(QString)));
    QObject::connect(&s_mod2, SIGNAL(frameContent(QString)), &fp4, SLOT(parseFrame(QString)));
    QObject::connect(&fp4, SIGNAL(sendFrame(QString)), &s_mod2, SLOT(sendResponse(QString)));
    //QObject::connect(&s_log, SIGNAL(frameContent(QString)), &fp5, SLOT(parseFrame(QString)));
    //QObject::connect(&fp5, SIGNAL(sendFrame(QString)), &s_log, SLOT(sendResponse(QString)));

    //QObject::connect(&fp1, SIGNAL(sendFrame(QString)), lh, SLOT(log(QString)));
    //QObject::connect(&fp2, SIGNAL(sendFrame(QString)), lh, SLOT(log(QString)));
    //QObject::connect(&fp3, SIGNAL(sendFrame(QString)), lh, SLOT(log(QString)));
    //QObject::connect(&fp4, SIGNAL(sendFrame(QString)), lh, SLOT(log(QString)));

    MotorHandler* mh = new MotorHandler(6);
    mh->assignRegister(0, MB_CTRL_BLDC_1);
    mh->assignRegister(1, MB_CTRL_BLDC_2);
    mh->assignRegister(2, MB_CTRL_BLDC_3);
    mh->assignRegister(3, MB_CTRL_BLDC_4);
    mh->assignRegister(4, MB_CTRL_BLDC_5);
    mh->assignRegister(5, MB_CTRL_BLDC_6);
    //QObject::connect(mh, SIGNAL(info(QString)), lh, SLOT(log(QString)));

    AxisHandler* ah = new AxisHandler(4);
    ah->assignRegister(0, regType::read, MB_STAT_STEPPER_1_POS);
    ah->assignRegister(1, regType::read, MB_STAT_STEPPER_2_POS);
    ah->assignRegister(2, regType::read, MB_STAT_STEPPER_3_POS);
    ah->assignRegister(3, regType::read, MB_STAT_STEPPER_4_POS);
    ah->assignRegister(0, regType::write, MB_CTRL_STEPPER_1_POS);
    ah->assignRegister(1, regType::write, MB_CTRL_STEPPER_2_POS);
    ah->assignRegister(2, regType::write, MB_CTRL_STEPPER_3_POS);
    ah->assignRegister(3, regType::write, MB_CTRL_STEPPER_4_POS);
    ah->assignRegister(0, regType::speed, MB_CTRL_STEPPER_1_SPEED);
    ah->assignRegister(1, regType::speed, MB_CTRL_STEPPER_2_SPEED);
    ah->assignRegister(2, regType::speed, MB_CTRL_STEPPER_3_SPEED);
    ah->assignRegister(3, regType::speed, MB_CTRL_STEPPER_4_SPEED);
    ah->assignRegister(0, regType::gear, MB_CTRL_STEPPER_1_GEAR);
    ah->assignRegister(1, regType::gear, MB_CTRL_STEPPER_2_GEAR);
    ah->assignRegister(2, regType::gear, MB_CTRL_STEPPER_3_GEAR);
    ah->assignRegister(3, regType::gear, MB_CTRL_STEPPER_4_GEAR);
    //QObject::connect(ah, SIGNAL(info(QString)), lh, SLOT(log(QString)));

    CameraHandler* ch1 = new CameraHandler(2);
    CameraHandler* ch2 = new CameraHandler(2);
    //QObject::connect(ch1, SIGNAL(info(QString)), lh, SLOT(log(QString)));
   // QObject::connect(ch2, SIGNAL(info(QString)), lh, SLOT(log(QString)));

    TempHandler *th = new TempHandler();
    th->assignRegister(9);
    //QObject::connect(th, SIGNAL(info(QString)), lh, SLOT(log(QString)));

    PressureHandler* ph = new PressureHandler();
    ph->assignRegister(8);
    QObject::connect(ph, SIGNAL(info(QString)), lh, SLOT(log(QString)));

    OutputHandler* oh = new OutputHandler(3);
    oh->assignRegister(0, MB_CTRL_POWER_1);
    oh->assignRegister(1, MB_CTRL_POWER_2);
    oh->assignRegister(1, MB_CTRL_POWER_3);
    //QObject::connect(oh, SIGNAL(info(QString)), lh, SLOT(log(QString)));

    ServiceHandler* sh = new ServiceHandler();
    //QObject::connect(sh, SIGNAL(info(QString)), lh, SLOT(log(QString)));

    fp3.addHandler(ah);
    fp4.addHandler(th);
    fp4.addHandler(ph);
    fp1.addHandler(ch1);
    fp2.addHandler(ch2);
    fp3.addHandler(mh);
    fp3.addHandler(oh);
    fp3.addHandler(sh);
    //fp5.addHandler(lh);

    /*lh->addHandler(ah);
    lh->addHandler(th);
    lh->addHandler(ph);
    lh->addHandler(ch1);
    lh->addHandler(ch2);
    lh->addHandler(mh);
    lh->addHandler(oh);
    lh->addHandler(sh);

    lh->addServer(&s_cam1);
    lh->addServer(&s_cam2);
    lh->addServer(&s_mod1);
    lh->addServer(&s_mod2);*/

    //ModbusMaster* modbus1 = new ModbusMaster("/dev/ttyUSB0", 100, 38400);
    ModbusMaster* modbus1 = new ModbusMaster("/dev/ttyUSB0", 100);
    //ModbusMaster* modbus2 = new ModbusMaster("/dev/ttySAC0", 100);

    //QObject::connect(modbus1, SIGNAL(error(QString)), &fp3, SLOT(buildErrorFrame(QString)));
    //QObject::connect(modbus2, SIGNAL(error(QString)), &fp3, SLOT(buildErrorFrame(QString)));

    ah->setModbus(modbus1);
    mh->setModbus(modbus1);
    th->setModbus(modbus1);
    ph->setModbus(modbus1);
    oh->setModbus(modbus1);
    sh->setModbus(modbus1);

    s_cam1.start();
    s_cam2.start();
    s_mod1.start();
    s_mod2.start();
    //s_log.start();

    return a.exec();
}
