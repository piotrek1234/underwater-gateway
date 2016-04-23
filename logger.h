#ifndef LOGGER_H
#define LOGGER_H

#include <handler.h>
#include <tcpserver.h>
#include <QVector>

class Logger : public Handler
{
    Q_OBJECT
public:
    Logger();
    virtual void set(QStringList);
    virtual void get(QStringList);
    virtual char handlerType() const { return 'L'; }
    void addHandler(Handler* handler);
    void addServer(TcpServer* server);
public slots:
    void log(QString message);
private:
    QVector<Handler*> handlers_;
    QVector<TcpServer*> servers_;
};

#endif // LOGGER_H
