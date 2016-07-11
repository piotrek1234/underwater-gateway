#include <QCoreApplication>
#include "../underwater-gateway/tcpserver.h"
#include "../underwater-gateway/frameparser.h"
#include "../underwater-gateway/camerahandler.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    TcpServer s_cam1(6001);
    FrameParser fp1;

    QObject::connect(&s_cam1, SIGNAL(frameContent(QString)), &fp1, SLOT(parseFrame(QString)));
    QObject::connect(&fp1, SIGNAL(sendFrame(QString)), &s_cam1, SLOT(sendResponse(QString)));

    CameraHandler* ch1 = new CameraHandler(3);

    fp1.addHandler(ch1);

    s_cam1.start();

    return a.exec();
}
