#include "cameraworker.h"

CameraWorker::CameraWorker()
{
}

void CameraWorker::stream()
{
    std::cout << "CW::stream()\n";
    // na podstawie https://github.com/chenxiaoqino/udp-image-streaming/blob/master/Client.cpp

    using namespace cv;

    string servAddress = host_->toStdString();
    unsigned short servPort = Socket::resolveService(QString::number(port).toStdString(), "udp");

    try
    {
        UDPSocket sock;
        int jpegqual =  ENCODE_QUALITY;

        Mat frame, send;
        vector < uchar > encoded;
        VideoCapture cap(device);

        if (!cap.isOpened())
        {
            cerr << "OpenCV Failed to open camera\n";
            turnedOn = false;
        }

        while (turnedOn)
        {
            std::cout << "w pętli\n";
            cap >> frame;
            resize(frame, send, Size(res_w, res_h), 0, 0, INTER_LINEAR);
            vector < int > compression_params;
            compression_params.push_back(CV_IMWRITE_JPEG_QUALITY);
            compression_params.push_back(jpegqual);

            imencode(".jpg", send, encoded, compression_params);
            //imshow("send", send);
            int total_pack = 1 + (encoded.size() - 1) / PACK_SIZE;

            int ibuf[1];
            ibuf[0] = total_pack;
            sock.sendTo(ibuf, sizeof(int), servAddress, servPort);

            for (int i = 0; i < total_pack; i++)
                sock.sendTo( & encoded[i * PACK_SIZE], PACK_SIZE, servAddress, servPort);

            //waitKey(1000/fps);
            QTimer timer;
            timer.singleShot(1000/fps, this, SLOT(moveOn()));
        }
        emit streamEnded();
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
    std::cout << "CameraWorker::stop(). setting turnedOn to false.\n";
}

void CameraWorker::setHost(QString *host)
{
    host_ = host;
}


