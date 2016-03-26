#include "camerahandler.h"
#include <iostream>

CameraHandler::CameraHandler(unsigned int camerasCount) : host_("127.0.0.1")
{
    camerasCount_ = 0;
    setCamerasCount(camerasCount);
}

CameraHandler::~CameraHandler()
{
    //powyłączać kamery
    for(int i=0; i<cams_.size(); ++i)
    {
        //cams_.at(i).first->turnedOn = false;
        cams_.at(i).first->stop();
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
    //2 parametry - on/off:
    // {indeks}, {włączona:1,0}
    //6 - wszystko
    // {indeks},{szerokość},{wysokość},{fps},{włączona:1,0},{port}
    if(frame.length() > 1)
    {
        if(frame.at(0) == "H")
        {
            if(frame.length() == 2)
            {
                if(setHostAddress(frame.at(1)))
                    emit response(QStringList() << QString(handlerType()) << "H" << host_);
                else
                    emit error("Wrong IP address for host");
                return;
            }
            else
            {
                emit error("Wrong parameters count for camera:set_host. Required 2, given "+QString::number(frame.length()));
                return;
            }
        }
        else
        {
            unsigned int nr = frame.at(0).toUInt();

            bool turnOn = false;

            if(nr < cams_.size())
            {
                CameraWorker* cam = cams_.at(nr).first;

                if(frame.length() == 6)
                {
                    //cam->device = nr;
                    cam->res_w = frame.at(1).toUInt();
                    cam->res_h = frame.at(2).toUInt();
                    cam->fps = frame.at(3).toUInt();
                    turnOn = static_cast<bool>(frame.at(4).toInt());
                    cam->port = frame.at(5).toUInt();
                }
                else if(frame.length() == 2)
                {
                    turnOn = static_cast<bool>(frame.at(1).toInt());
                }
                else
                {
                    emit error("Wrong parameters count. Required 2 or 6, given "+QString::number(frame.length()));
                    return;
                }

                emit response(QStringList() << QString(handlerType()) << QString::number(cam->device) << \
                              QString::number(cam->res_w) << QString::number(cam->res_h) << \
                              QString::number(cam->fps) << \
                              /*QString::number(static_cast<unsigned int>(cam->turnedOn)) << \*/
                              QString::number(static_cast<unsigned int>(turnOn)) << \
                              host_ << QString::number(cam->port));

                if(turnOn)
                {
                    if(!cam->turnedOn)
                    {
                        //włącz stream
                        cam->turnedOn = true;
                        QThread* th = cams_.at(frame.at(0).toUInt()).second;
                        if(!th)
                        {
                            th = new QThread;
                            std::cout << "przesuwanie do wątku\n";
                            cam->moveToThread(th);
                            //connect(th, &QThread::finished, cam, &QObject::deleteLater);
                            //cam->stream();
                            connect(th, SIGNAL(started()), cam, SLOT(stream()));
                            connect(cam, SIGNAL(streamEnded()), th, SLOT(quit()));
                            connect(th, SIGNAL(finished()), th, SLOT(deleteLater()));
                            std::cout << "startowanie wątku\n";
                            th->start();
                        }
                    }

                }
                else
                {
                    //QThread* th = cams_.at(frame.at(0).toUInt()).second;
                    //cam = qobject_cast<CameraWorker*>(th);
                    std::cout << "CameraHandler::set(). Calling CameraWorker::stop().\n";
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
        for(unsigned int i=camerasCount_; i<count; ++i)
        {
            CameraWorker* cw = new CameraWorker(&host_);
            cw->device = i;
            cams_.append(QPair<CameraWorker*, QThread*>(cw, nullptr));
        }

    }
    camerasCount_ = count;
}

/*void CameraHandler::setParameters(unsigned int camNr, CameraWorker *params)
{
    if((camNr <= camerasCount_) && (camNr <= cams.size()))
        cams[camNr] = params;
}

CameraWorker *CameraHandler::getParameters(unsigned int camNr)
{
   if((camNr <= camerasCount_) && (camNr <= cams.size()))
        return cams.at(camNr);
}*/

bool CameraHandler::setHostAddress(QString address)
{
    QHostAddress adr;
    bool ok = adr.setAddress(address);

    if(ok)
        host_ = address;
    return ok;
}


