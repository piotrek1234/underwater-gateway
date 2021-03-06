#include <QCoreApplication>
#include "tcpserver.h"
#include "frameparser.h"
#include "axishandler.h"
#include "motorhandler.h"
#include "outputhandler.h"
#include "camerahandler.h"
#include "servicehandler.h"
#include "modbusmaster.h"
#include "modbus_regs.h"
#include "measurehandler.h"
#include "fileinterface.h"
#include "imuinterface.h"
#include "onewireinterface.h"
#include "adcinterface.h"
#include "i2c.h"
#include "computedmeasure.h"
//#include "logger.h"

//todo:
// - sprawdzić poprawność wątków przy kamerach (włączenie, wyłączenie, włączenie -> warningi)
// - program zawiesza się po wykonaniu zapytania do modbusa bez aktywnego połączenia z nim
// - pauzować kolejkę modbusa dopóki nie odzyska się połączenia

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    TcpServer s_cam1(6001), s_cam2(6002), s_mod1(6003), s_mod2(6004), s_mod3(6005)/*, s_log(6005)*/;
    FrameParser fp1, fp2, fp3, fp4, fp5/*, fp5*/;
    //Logger* lh = new Logger();

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
    QObject::connect(&s_mod3, SIGNAL(frameContent(QString)), &fp5, SLOT(parseFrame(QString)));
    QObject::connect(&fp5, SIGNAL(sendFrame(QString)), &s_mod3, SLOT(sendResponse(QString)));
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

    CameraHandler* ch1 = new CameraHandler(3);
    CameraHandler* ch2 = new CameraHandler(3);
    //QObject::connect(ch1, SIGNAL(info(QString)), lh, SLOT(log(QString)));
   // QObject::connect(ch2, SIGNAL(info(QString)), lh, SLOT(log(QString)));

    OutputHandler* oh = new OutputHandler(3);
    oh->assignRegister(0, MB_CTRL_POWER_1);
    oh->assignRegister(1, MB_CTRL_POWER_2);
    oh->assignRegister(2, MB_CTRL_POWER_3);
    //QObject::connect(oh, SIGNAL(info(QString)), lh, SLOT(log(QString)));

    ServiceHandler* sh = new ServiceHandler();
    //QObject::connect(sh, SIGNAL(info(QString)), lh, SLOT(log(QString)));

    MeasureHandler* Mh1 = new MeasureHandler(500);
    MeasureHandler* Mh2 = new MeasureHandler(500);

    I2C* i2c1 = new I2C(0x28);
    i2c1->prepare();

    ImuInterface* imu_roll = new ImuInterface(i2c1, 0x1c, 360, 2048);
    ImuInterface* imu_pitch = new ImuInterface(i2c1, 0x1e, 360, 2048);
    imu_roll->prepare();

    Mh1->addMeasure('T', new Measure(new FileInterface("/sys/class/thermal/thermal_zone0/temp"), 0.001, 0.0));
    Mh2->addMeasure('A', new Measure(imu_roll, 1.0, 0.0));
    Mh2->addMeasure('A', new Measure(imu_pitch, 1.0, 0.0));
    MeasureInterface* adc_press = new AdcInterface("1-0068", 0);
    Measure* adcMeasure = new Measure(adc_press, 21.23333333, -11731.2);
    Mh1->addMeasure('P', adcMeasure);  //
    Mh1->addMeasure('T', new Measure(new OneWireInterface("28-021562ba7dff"), 0.001, 0.0)); //gotowe (1-wire)
    Mh1->addMeasure('H', new Measure(new AdcInterface("1-0068", 3), 1.0, 0.0));  //wilgotność, gotowe
    Mh1->addMeasure('T', new Measure(new AdcInterface("1-0068", 1), 0.0356506, -293.725));
    Mh1->addMeasure('T', new Measure(new AdcInterface("1-0068", 2), 0.0356506, -293.725));
    Mh1->addMeasure('x', new Measure(new ComputedMeasure(adcMeasure), 1.0, 0.0));

    fp1.addHandler(ch1);
    fp2.addHandler(ch2);

    fp3.addHandler(mh);
    fp3.addHandler(oh);
    fp3.addHandler(ah);
    fp3.addHandler(sh);

    fp4.addHandler(Mh1);
    fp5.addHandler(Mh2);
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

    //QObject::connect(modbus1, SIGNAL(error(QString)), &fp3, SLOT(buildErrorFrame(QString)));
    //QObject::connect(modbus2, SIGNAL(error(QString)), &fp3, SLOT(buildErrorFrame(QString)));

    ah->setModbus(modbus1);
    mh->setModbus(modbus1);
    oh->setModbus(modbus1);
    sh->setModbus(modbus1);

    s_cam1.start();
    s_cam2.start();
    s_mod1.start();
    s_mod2.start();
    s_mod3.start();
    //s_log.start();

    return a.exec();
}
