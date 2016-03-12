#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QList>
#include <frame.h>

class TcpServer : public QTcpServer
{
    Q_OBJECT
public:
    TcpServer(int port = 6001);
    ~TcpServer();
    void start();
private:
    int port;
    QTcpSocket* client;
private slots:
    void newClient();
    void removeClient();
    void grabFrame();
public slots:
    void sendResponse(QString frame);
signals:
    void frameContent(QString);
};

#endif // TCPSERVER_H
