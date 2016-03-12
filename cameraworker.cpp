#include "cameraworker.h"

CameraWorker::CameraWorker(QObject *parent) :
    QObject(parent)
{
}

void CameraWorker::stream()
{
    using namespace cv;
    string servAddress = host_->toStdString(); // First arg: server address
    unsigned short servPort = Socket::resolveService(QString::number(port).toStdString(), "udp");

    try {
        UDPSocket sock;
        int jpegqual =  ENCODE_QUALITY; // Compression Parameter

        Mat frame, send;
        vector < uchar > encoded;
        VideoCapture cap(device); // Grab the camera
        //namedWindow("send", CV_WINDOW_AUTOSIZE);
        if (!cap.isOpened()) {
            cerr << "OpenCV Failed to open camera";
            exit(1);
        }

        //clock_t last_cycle = clock();
        while (turnedOn) {
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

            waitKey(FRAME_INTERVAL);

            //clock_t next_cycle = clock();
            //double duration = (next_cycle - last_cycle) / (double) CLOCKS_PER_SEC;
            //cout << "\teffective FPS:" << (1 / duration) << " \tkbps:" << (PACK_SIZE * total_pack / duration / 1024 * 8) << endl;

            //cout << next_cycle - last_cycle;
            //last_cycle = next_cycle;
        }
        // Destructor closes the socket

    } catch (SocketException & e) {
        cerr << e.what() << endl;
        exit(1);
    }
}

void CameraWorker::stop()
{
    turnedOn = false;
}

void CameraWorker::restart()
{

}

void CameraWorker::setHost(QString *host)
{
    host_ = host;
}
