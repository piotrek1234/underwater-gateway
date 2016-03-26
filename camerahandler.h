#ifndef CAMERAHANDLER_H
#define CAMERAHANDLER_H

#include <QString>
#include <QVector>
#include <QPair>
#include <QThread>
#include <QHostAddress>
#include "handler.h"
#include "cameraworker.h"

class CameraHandler : public Handler
{
public:
    CameraHandler() : camerasCount_(0), host_("127.0.0.1") {}
    CameraHandler(unsigned int camerasCount);
    virtual ~CameraHandler();
    virtual void get(QStringList frame);
    virtual void set(QStringList frame);
    void setCamerasCount(unsigned int count);
    unsigned int getCamerasCount() { return camerasCount_; }
    bool setHostAddress(QString address);
    virtual char handlerType() const { return 'C'; }
private:
    QVector<QPair<CameraWorker*, QThread*> > cams_;
    unsigned int camerasCount_;
    QString host_;
};

#endif // CAMERAHANDLER_H
