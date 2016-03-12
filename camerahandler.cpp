#include "camerahandler.h"
#include <iostream>

CameraHandler::CameraHandler(unsigned int camerasCount)
{
    camerasCount_ = 0;
    setCamerasCount(camerasCount);
}

CameraHandler::~CameraHandler()
{
    //powyłączać kamery
    for(int i=0; i<cams_.size(); ++i)
    {
        cams_.at(i).first->turnedOn = false;
    }
}
void CameraHandler::get(QStringList frame)
{
    if(frame.length() == 1)
    {
        if(frame.at(0) == "H")
        {
            emit response(QStringList() << host_);
            return;
        }
        else if(true /* czy jest cyfra */)
        {
            int i = frame.at(0).toInt();
            if(i < camerasCount_ && i >= 0)
            {
                CameraWorker* cam = cams_.at(i).first;
                emit response(QStringList() << QString(handlerType()) << QString::number(cam->device) << \
                              QString::number(cam->res_w) << QString::number(cam->res_h) << \
                              QString::number(cam->fps) << \
                              QString::number(static_cast<unsigned int>(cam->turnedOn)) << \
                              QString::number(cam->port));
                return;
            }
            else
            {
                emit error("Camera index out of range");
                return;
            }
        }
        emit error("Wrong parameters format. Valid options: H, number.");
    }
    emit error("Wrong parameters count. Required 1, given "+QString::number(frame.length()));
}

void CameraHandler::set(QStringList frame)
{
    //1+
    //1 - on/off:
    // {indeks}, {włączona:1,0}
    //5 - wszystko
    // {indeks},{szerokość},{wysokość},{fps},{włączona:1,0},{port}
    if(frame.length() > 1)
    {
        if(frame.at(0) == "H")
        {
            if(frame.length() == 2)
            {
                host_ = frame.at(1);
                emit response(QStringList() << QString(handlerType()) << "H" << host_);
                return;
            }
            else
            {
                emit error("Wrong parameters count for camera:set-host. Required 2, given "+QString::number(frame.length()));
                return;
            }
        }
        else if(true /* czy jest liczba */)
        {
            if(frame.at(0).toUInt() < cams_.size())
            {
                CameraWorker* cam = cams_.at(frame.at(0).toUInt()).first;

                if(frame.length() == 6)
                {
                    cam->device = frame.at(0).toUInt();
                    cam->res_w = frame.at(1).toUInt();
                    cam->res_h = frame.at(2).toUInt();
                    cam->fps = frame.at(3).toUInt();
                    cam->turnedOn = static_cast<bool>(frame.at(4).toInt());
                    cam->port = frame.at(5).toUInt();
                }
                else if(frame.length() == 2)
                {
                    cam->turnedOn = static_cast<bool>(frame.at(1).toUInt());
                }
                else
                {
                    emit error("Wrong parameters count. Required 2 or 6, given "+QString::number(frame.length()));
                    return;
                }

                emit response(QStringList() << QString(handlerType()) << QString::number(cam->device) << \
                              QString::number(cam->res_w) << QString::number(cam->res_h) << \
                              QString::number(cam->fps) << \
                              QString::number(static_cast<unsigned int>(cam->turnedOn)) << \
                              host_ << QString::number(cam->port));

                if(cam->turnedOn)
                {
                    //włącz stream
                    QThread* th = cams_.at(frame.at(0).toUInt()).second;
                    if(!th)
                        th = new QThread;
                    cam->moveToThread(th);
                    //connect(th, &QThread::finished, cam, &QObject::deleteLater);
                    cam->stream();
                    th->start();
                }
                else
                {
                    cam->stop();
                }
            }
            else
            {
                emit error("Camera index out of range");
                return;
            }
        }
    }
    else
        emit error("Wrong parameters count. Required 2 or 8, given "+QString::number(frame.length()));

}

void CameraHandler::setCamerasCount(unsigned int count)
{
    if(count < camerasCount_)
    {
        cams_.erase(cams_.begin()+count, cams_.end());
    }
    else if(count > camerasCount_)
    {
        for(unsigned int i=0; i<count-camerasCount_; ++i)
        {
            CameraWorker* cw = new CameraWorker(&host_);
            cams_.append(QPair<CameraWorker*, QThread*>(cw, nullptr));
        }

    }
    camerasCount_ = count;
}

void CameraHandler::setParameters(unsigned int camNr, CameraInfo params)
{
    /*if((camNr <= camerasCount_) && (camNr <= cams.size()))
        cams[camNr] = params;
    else
        emit error("Camera index out of range");*/
}

CameraInfo CameraHandler::getParameters(unsigned int camNr)
{
   /* if((camNr <= camerasCount_) && (camNr <= cams.size()))
        return cams.at(camNr);
    emit error("Camera index out of range");*/
}

void CameraHandler::setHostAddress(QString address)
{
    host_ = address;
}


