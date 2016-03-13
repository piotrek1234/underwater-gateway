#include <QCoreApplication>
#include "tcpserver.h"
#include "frameparser.h"
#include "axishandler.h"
#include "temphandler.h"
#include "pressurehandler.h"
#include "motorhandler.h"
#include "camerahandler.h"
#include "modbusmaster.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    TcpServer s;
    FrameParser fp;

    QObject::connect(&s, SIGNAL(frameContent(QString)), &fp, SLOT(parseFrame(QString)));
    //QObject::connect(&s, SIGNAL(frameContent(QString)), &fp, SLOT(printFrame(QString)));
    QObject::connect(&fp, SIGNAL(sendFrame(QString)), &s, SLOT(sendResponse(QString)));

    MotorHandler* mh = new MotorHandler(6);
    mh->assignRegister(0, 110);
    mh->assignRegister(1, 111);
    mh->assignRegister(2, 112);
    mh->assignRegister(3, 113);
    mh->assignRegister(4, 114);
    mh->assignRegister(5, 115);

    AxisHandler* ah = new AxisHandler(3);
    ah->assignRegister(0, 100);
    ah->assignRegister(1, 101);
    ah->assignRegister(2, 102);

    CameraHandler* ch = new CameraHandler(1);

    TempHandler *th = new TempHandler();
    th->assignRegister(100);

    PressureHandler* ph = new PressureHandler();
    ph->assignRegister(110);

    fp.addHandler(ah);
    fp.addHandler(th);
    fp.addHandler(ph);
    fp.addHandler(ch);
    fp.addHandler(mh);

    ModbusMaster* modbus1 = new ModbusMaster("/dev/ttyUSB0", 100, 115200);
    ah->setModbus(modbus1);
    th->setModbus(modbus1);
    ph->setModbus(modbus1);
    mh->setModbus(modbus1);

    s.start();

    return a.exec();
}
