#include <QCoreApplication>
#include "../underwater-gateway/tcpserver.h"
#include "../underwater-gateway/frameparser.h"
#include "../underwater-gateway/measurehandler.h"
#include "../underwater-gateway/fileinterface.h"
#include "../underwater-gateway/imuinterface.h"
#include "../underwater-gateway/onewireinterface.h"
#include "../underwater-gateway/adcinterface.h"
#include "../underwater-gateway/i2c.h"
#include "../underwater-gateway/computedmeasure.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    TcpServer s_mod3(6004);
    FrameParser fp5;

    QObject::connect(&s_mod3, SIGNAL(frameContent(QString)), &fp5, SLOT(parseFrame(QString)));
    QObject::connect(&fp5, SIGNAL(sendFrame(QString)), &s_mod3, SLOT(sendResponse(QString)));

    MeasureHandler* Mh1 = new MeasureHandler(500);
    //MeasureHandler* Mh2 = new MeasureHandler(500);

    //I2C* i2c1 = new I2C(0x28);
    //i2c1->prepare();

    //ImuInterface* imu_roll = new ImuInterface(i2c1, 0x1c, 360, 2048);
    //ImuInterface* imu_pitch = new ImuInterface(i2c1, 0x1e, 360, 2048);
    //imu_roll->prepare();

    Mh1->addMeasure('T', new Measure(new FileInterface("/sys/class/thermal/thermal_zone0/temp"), 0.001, 0.0));
    //Mh2->addMeasure('A', new Measure(imu_roll, 1.0, 0.0));
    //Mh2->addMeasure('A', new Measure(imu_pitch, 1.0, 0.0));
    MeasureInterface* adc_press = new AdcInterface("1-0068", 0);
    Measure* adcMeasure = new Measure(adc_press, 21.23333333, -11731.2);
    Mh1->addMeasure('P', adcMeasure);  //
    Mh1->addMeasure('T', new Measure(new OneWireInterface("28-021562ba7dff"), 0.001, 0.0)); //gotowe (1-wire)
    Mh1->addMeasure('H', new Measure(new AdcInterface("1-0068", 3), 1.0, 0.0));  //wilgotność, gotowe
    Mh1->addMeasure('T', new Measure(new AdcInterface("1-0068", 1), 0.0356506, -293.725));
    Mh1->addMeasure('T', new Measure(new AdcInterface("1-0068", 2), 0.0356506, -293.725));
    Mh1->addMeasure('x', new Measure(new ComputedMeasure(adcMeasure), 1.0/9810, 0.0));

    fp5.addHandler(Mh1);
    //fp5.addHandler(Mh2);

    s_mod3.start();

    return a.exec();
}
