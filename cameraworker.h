#ifndef CAMERAWORKER_H
#define CAMERAWORKER_H

#include <QObject>
#include <QTimer>
#include "udp-stream/PracticalSocket.h"
#include <opencv2/opencv.hpp>

// pozmieniać:
#define PACK_SIZE 4096 //udp pack size; note that OSX limits < 8100 bytes
#define ENCODE_QUALITY 80

class CameraWorker : public QObject
{
    Q_OBJECT
public:
    explicit CameraWorker();
    CameraWorker(QString* host) : device(0), res_w(640), res_h(480), fps(30), turnedOn(false), port(6002), host_(host) {}
    //CameraInfo() : device(0), res_w(640), res_h(480), fps(30), turnedOn(false), port(1234) {}
public:
    unsigned int device;
    unsigned int res_w;
    unsigned int res_h;
    unsigned int fps;
    bool turnedOn;
    unsigned int port;
    void setHost(QString* host);
signals:
    void streamEnded();
private:
    QString* host_;
private slots:
    void moveOn() {}
public slots:
    void stream();
    void stop();
};

#endif // CAMERAWORKER_H
