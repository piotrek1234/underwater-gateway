#include <QCoreApplication>
#include "tcpserver.h"
#include "frameparser.h"
#include "axishandler.h"
#include "temphandler.h"
#include "pressurehandler.h"
#include "motorhandler.h"
#include "camerahandler.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    TcpServer s;
    FrameParser fp;

    QObject::connect(&s, SIGNAL(frameContent(QString)), &fp, SLOT(parseFrame(QString)));
    QObject::connect(&fp, SIGNAL(sendFrame(QString)), &s, SLOT(sendResponse(QString)));
    AxisHandler* ah = new AxisHandler();
    ah->setAxesCount(1);

    CameraHandler* ch = new CameraHandler(1);

    fp.addHandler(ah);
    fp.addHandler(new TempHandler());
    fp.addHandler(new PressureHandler());
    fp.addHandler(ch);


    s.start();

    return a.exec();
}
