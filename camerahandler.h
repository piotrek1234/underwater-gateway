#ifndef CAMERAHANDLER_H
#define CAMERAHANDLER_H

#include <QString>
#include <QVector>
#include <QPair>
#include <QThread>
#include "handler.h"
#include "cameraworker.h"

struct CameraInfo{
    CameraInfo() : device(0), res_w(640), res_h(480), fps(30), turnedOn(false), port(1234) {}
    unsigned int device;
    unsigned int res_w;
    unsigned int res_h;
    unsigned int fps;
    bool turnedOn;
    unsigned int port;
};

class CameraHandler : public Handler
{
public:
    CameraHandler() : camerasCount_(0), host("127.0.0.1") {}
    CameraHandler(unsigned int camerasCount);
    virtual ~CameraHandler();
    virtual void get(QStringList frame);
    virtual void set(QStringList frame);
    void setCamerasCount(unsigned int count);
    unsigned int getCamerasCount() { return camerasCount_; }
    void setParameters(unsigned int camNr, CameraInfo params);
    CameraInfo getParameters(unsigned int camNr);
    void setHostAddress(QString address);
    virtual char handlerType() const { return 'C'; }
private:
    QVector<QPair<CameraWorker*, QThread*> > cams;
    unsigned int camerasCount_;
    QString host;
};

#endif // CAMERAHANDLER_H
