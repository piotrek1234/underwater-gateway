#include "camerahandler.h"
#include <iostream>

CameraHandler::CameraHandler(unsigned int camerasCount) : host_("127.0.0.1")
{
    camerasCount_ = 0;
    setCamerasCount(camerasCount);
}

CameraHandler::~CameraHandler()
{
    for(int i=0; i<cams_.size(); ++i)
    {
        cams_.at(i).first->stop();
    }
}
void CameraHandler::get(QStringList frame)
{
    if(frame.length() == 1)
    {
        if(frame.at(0) == "H")
        {
            emit response(QStringList() << QString(handlerType()) << "H" << host_);
            return;
        }
        else if(frame.at(0) == "Q") //przerobić na niezależne sterowanie jakością dla każdej kamery
        {
            emit response(QStringList() << QString(handlerType()) << "Q" << QString::number(cams_.at(0).first->jpg_quality));
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
                emit error("C/1/Camera index out of range");
                return;
            }
        }
        emit error("C/2/Wrong parameters format. Valid options: H, number.");
    }
    emit error("C/3/Wrong parameters count. Required 1, given "+QString::number(frame.length()));
}

void CameraHandler::set(QStringList frame)
{
    //2 parametry - on/off: {indeks}, {włączona:1,0}
    //6 - wszystko: {indeks},{szerokość},{wysokość},{fps},{włączona:1,0},{port}
    if(frame.length() > 1)
    {
        if(frame.at(0) == "H")
        {
            if(frame.length() == 2)
            {
                if(setHostAddress(frame.at(1)))
                    emit response(QStringList() << QString(handlerType()) << "H" << host_);
                else
                    emit error("C/4/Wrong IP address for host");
                return;
            }
            else
            {
                emit error("C/3/Wrong parameters count for camera:set_host. Required 2, given "+QString::number(frame.length()));
                return;
            }
        }
        else if(frame.at(0) == "Q")/*todo todo*/
        {
            if(frame.length() == 2)
            {
                bool ok;
                int quality = frame.at(1).toInt(&ok);
                if(quality>100 || quality<1)
                    ok = false;

                if(ok)
                {
                    for(int i=0; i<camerasCount_; ++i)
                        cams_.at(i).first->jpg_quality = quality;
                    emit response(QStringList() << QString(handlerType()) << "Q" << QString::number(quality));
                }
                else
                    emit error("C/10/Invalid quality for camera");
                return;
            }
            else
            {
                emit error("C/3/Wrong parameters count for camera:quality. Required 2, given "+QString::number(frame.length()));
                return;
            }
        }
        else if(frame.at(0) == "S")
        {
            if(frame.length() == 2)
            {
                int num = frame.at(1).toInt();
                cams_.at(num).first->saveFrame = true;
                    emit response(QStringList() << QString(handlerType()) << "S" << QString::number(num));
                return;
            }
            else
            {
                emit error("C/3/Wrong parameters count for camera:saveFrame. Required 2, given "+QString::number(frame.length()));
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
                    emit error("C/3/Wrong parameters count. Required 2 or 6, given "+QString::number(frame.length()));
                    return;
                }

                emit response(QStringList() << QString(handlerType()) << QString::number(cam->device) << \
                              QString::number(cam->res_w) << QString::number(cam->res_h) << \
                              QString::number(cam->fps) << \
                              QString::number(static_cast<unsigned int>(turnOn)) << \
                              QString::number(cam->port));


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
                            //std::cout << "przesuwanie do wątku\n";
                            cam->moveToThread(th);
                            connect(th, SIGNAL(started()), cam, SLOT(stream()));
                            connect(cam, SIGNAL(streamEnded()), th, SLOT(quit()));
                            connect(th, SIGNAL(finished()), th, SLOT(deleteLater()));
                            //std::cout << "startowanie wątku\n";
                            th->start();
                        }
                    }
                }
                else
                {
                    cam->stop();
                }
            }
            else
            {
                emit error("C/1/Camera index out of range");
                return;
            }
        }
    }
    else
        emit error("C/3/Wrong parameters count. Required 2 or 8, given "+QString::number(frame.length()));

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
            connect(cw, SIGNAL(info(QString)), this, SLOT(passInfo(QString)));
            cw->device = i;
            cams_.append(QPair<CameraWorker*, QThread*>(cw, nullptr));
        }

    }
    camerasCount_ = count;
}

bool CameraHandler::setHostAddress(QString address)
{
    QHostAddress adr;
    bool ok = adr.setAddress(address);

    if(ok)
        host_ = address;
    return ok;
}

QString CameraHandler::description()
{
    QString info(host_+"/"+QString::number(camerasCount_)+"/");

    for(int i=0; i<camerasCount_; ++i)
    {
        CameraWorker* cam = cams_.at(i).first;
        info += QString::number(cam->device) + ","+QString::number(cam->res_w)+","+QString::number(cam->res_h)\
                +","+QString::number(cam->fps)+","+QString::number(cam->port)+","+\
                QString::number(static_cast<int>(cam->turnedOn));
        if(i < camerasCount_-1)
            info += "/";

    }

    return QString(handlerType())+"/"+info;
}

void CameraHandler::passInfo(QString message)
{
    emit info(message);
}


