#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QList>
#include "frame.h"

class TcpServer : public QTcpServer
{
    Q_OBJECT
public:
    TcpServer(int port_ = 6001);
    ~TcpServer();
    void start();
    QString description();
private:
    int port_;
    QTcpSocket* client_;
public slots:
    void sendResponse(QString frame);
private slots:
    void newClient();
    void removeClient();
    void grabFrame();
signals:
    void frameContent(QString);
    void info(QString);
};

#endif // TCPSERVER_H
