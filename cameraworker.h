#ifndef CAMERAWORKER_H
#define CAMERAWORKER_H

#include <QObject>
#include "udp-stream/PracticalSocket.h"
#include <opencv2/opencv.hpp>

// pozmieniać:
#define FRAME_INTERVAL (1000/30)
#define PACK_SIZE 4096 //udp pack size; note that OSX limits < 8100 bytes
#define ENCODE_QUALITY 80

class CameraWorker : public QObject
{
    Q_OBJECT
public:
    explicit CameraWorker(QObject *parent = 0);
    CameraWorker(QString* host) : device(0), res_w(640), res_h(480), fps(30), turnedOn(false), port(1234), host_(host) {}
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

public slots:
    void stream();
    void restart();
    void stop();
};

#endif // CAMERAWORKER_H
