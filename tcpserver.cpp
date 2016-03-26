#include "tcpserver.h"
#include <iostream>

TcpServer::TcpServer(int port)
{
    this->port_ = port;
    this->client_ = nullptr;
    connect(this, SIGNAL(newConnection()), this, SLOT(newClient()));
}

TcpServer::~TcpServer()
{

}

void TcpServer::start()
{
    listen(QHostAddress::Any, port_);
}

void TcpServer::newClient()
{
    while(hasPendingConnections())
    {
        QTcpSocket* socket = nextPendingConnection();
        if(!client_) client_ = socket;
        connect(socket, SIGNAL(readyRead()), this, SLOT(grabFrame()));
        connect(socket, SIGNAL(disconnected()), this, SLOT(removeClient()));
    }
}

void TcpServer::removeClient()
{
    QTcpSocket* who = qobject_cast<QTcpSocket*>(sender());
    if(who == client_)
        client_ = nullptr;
}

void TcpServer::grabFrame()
{
    QTcpSocket* socket = qobject_cast<QTcpSocket*>(sender());
    if(socket)
    {
        QString frame(socket->readAll());

        bool nadal = true;
        int pos1=0, pos2=0;
        while(nadal)
        {
            pos1 = frame.indexOf(Frame::FRAME_START, pos1);
            pos2 = frame.indexOf(Frame::FRAME_END, pos2);
            int len = pos2-pos1-1;
            if(len > 0)
                emit frameContent(frame.mid(pos1+1, len));
            if(pos1 == -1 || pos2 == -1)
                nadal = false;
            pos1++;
            pos2++;
        }

        /*if(frame.at(0) == Frame::FRAME_START)   //przemyśleć czy nie lepiej szukać pozycji nawiasu (
        {
            int len = frame.indexOf(Frame::FRAME_END)-1;
            if(len > 0)
                emit frameContent(frame.mid(1, len));
            //std::cout << frame.mid(1, len).toStdString() << std::endl;
        }*/
    }
}

void TcpServer::sendResponse(QString frame)
{
    client_->write(frame.toStdString().c_str());
    //client->waitForBytesWritten(3000);
}

