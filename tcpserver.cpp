#include "tcpserver.h"
#include <iostream>

TcpServer::TcpServer(int port)
{
    this->port = port;
    this->client = nullptr;
    connect(this, SIGNAL(newConnection()), this, SLOT(newClient()));
}

TcpServer::~TcpServer()
{

}

void TcpServer::start()
{
    listen(QHostAddress::Any, port);
}

void TcpServer::newClient()
{
    while(hasPendingConnections())
    {
        QTcpSocket* socket = nextPendingConnection();
        if(!client) client = socket;
        connect(socket, SIGNAL(readyRead()), this, SLOT(grabFrame()));
        connect(socket, SIGNAL(disconnected()), this, SLOT(removeClient()));
    }
}

void TcpServer::removeClient()
{
    QTcpSocket* who = qobject_cast<QTcpSocket*>(sender());
    if(who == client)
        client = nullptr;
}

void TcpServer::grabFrame()
{
    QTcpSocket* socket = qobject_cast<QTcpSocket*>(sender());
    if(socket)
    {
        QString frame(socket->readAll());
        if(frame.at(0) == Frame::FRAME_START)   //przemyśleć czy nie lepiej szukać pozycji nawiasu (
        {
            int len = frame.indexOf(Frame::FRAME_END)-1;
            if(len > 0)
                emit frameContent(frame.mid(1, len));
            //std::cout << frame.mid(1, len).toStdString() << std::endl;
        }
    }
}

void TcpServer::sendResponse(QString frame)
{
    client->write(frame.toStdString().c_str());
    //client->waitForBytesWritten(3000);
}

