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
    AxisHandler* ah = new AxisHandler(1);
    //ah->setAxesCount(1);

    CameraHandler* ch = new CameraHandler(1);
    TempHandler *th = new TempHandler();
    PressureHandler* ph = new PressureHandler();

    fp.addHandler(ah);
    fp.addHandler(th);
    fp.addHandler(ph);
    fp.addHandler(ch);

    ModbusMaster* modbus1 = new ModbusMaster("/dev/ttyUSB0", 100, 115200);
    ah->setModbus(modbus1);
    th->setModbus(modbus1);
    ph->setModbus(modbus1);

    s.start();

    return a.exec();
}
