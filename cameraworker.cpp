#include "cameraworker.h"
#include <QTime>

CameraWorker::CameraWorker()
{
}

void CameraWorker::stream()
{
    // na podstawie https://github.com/chenxiaoqino/udp-image-streaming/blob/master/Client.cpp

    using namespace cv;

    emit info("C/8/Starting stream/"+QString::number(device)+"/"+QString::number(res_w)+"/"+QString::number(res_h)+"/" \
              +QString::number(fps)+"/"+QString::number(port));

    string servAddress = host_->toStdString();
    unsigned short servPort = Socket::resolveService(QString::number(port).toStdString(), "udp");

    try
    {
        UDPSocket sock;

        Mat frame, send;
        vector < uchar > encoded;
        VideoCapture cap(device);
        cap.set(CV_CAP_PROP_FRAME_WIDTH, res_w);
        cap.set(CV_CAP_PROP_FRAME_HEIGHT, res_h);
        cap.set(CV_CAP_PROP_FPS, fps);

        if (!cap.isOpened())
        {
            cerr << "OpenCV Failed to open camera\n";
            emit info("C/5/Could not open camera");
            turnedOn = false;
        }

        while (turnedOn)
        {
            //std::cout << ".\n";
            QTime dieTime = QTime::currentTime().addMSecs(1000/fps);
            while(QTime::currentTime() < dieTime);

            //cap >> frame;
            if(!cap.read(frame))
            {
                std::cout << "Problem reading frame from camera " << device << std::endl;
                continue;
            }
            if(frame.size().area() <= 0)
                continue;

            resize(frame, send, Size(res_w, res_h), 0, 0, INTER_LINEAR);
            vector < int > compression_params;
            compression_params.push_back(CV_IMWRITE_JPEG_QUALITY);
            compression_params.push_back(ENCODE_QUALITY);

            imencode(".jpg", send, encoded, compression_params);
            //imshow("send", send);
            int total_pack = 1 + (encoded.size() - 1) / PACK_SIZE;

            int ibuf[1];
            ibuf[0] = total_pack;
            sock.sendTo(ibuf, sizeof(int), servAddress, servPort);

            for (int i = 0; i < total_pack; i++)
                sock.sendTo( & encoded[i * PACK_SIZE], PACK_SIZE, servAddress, servPort);
        }
        emit streamEnded();
        emit info("C/6/Stream ended/"+QString::number(device));
    }
    catch (SocketException & e)
    {
        cerr << e.what() << endl;
        turnedOn = false;
    }
}

void CameraWorker::stop()
{
    turnedOn = false;
    emit info("C/9/Stopping stream/"+QString::number(device));
}

void CameraWorker::setHost(QString *host)
{
    host_ = host;
    emit info("C/7/Host set/"+(*host));
}


