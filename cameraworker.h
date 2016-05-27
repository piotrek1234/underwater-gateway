#ifndef CAMERAWORKER_H
#define CAMERAWORKER_H

#include <QObject>
#include <QTimer>
#include "udp-stream/PracticalSocket.h"
#include <opencv2/opencv.hpp>

#define PACK_SIZE 4096 //udp pack size; note that OSX limits < 8100 bytes

class CameraWorker : public QObject
{
    Q_OBJECT
public:
    explicit CameraWorker();
    CameraWorker(QString* host) : device(0), res_w(640), res_h(480), fps(30), turnedOn(false), \
        port(6002), jpg_quality(50), saveFrame(false), host_(host) {}
    unsigned int device;
    unsigned int res_w;
    unsigned int res_h;
    unsigned int fps;
    bool turnedOn;
    unsigned int port;
    int jpg_quality;
    bool saveFrame;
    void setHost(QString* host);
private:
    QString* host_;
    bool waiting;
    QTimer* t1;
public slots:
    void stream();
    void stop();
private slots:
    void moveOn() { }
signals:
    void streamEnded();
    void info(QString message);
};

#endif // CAMERAWORKER_H
