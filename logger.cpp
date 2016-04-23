#include "logger.h"

Logger::Logger()
{

}

void Logger::get(QStringList)
{
    for(Handler* h : handlers_)
    {
        if(h->description() != QString())
            emit response(QStringList(h->description()));
    }

    for(TcpServer* s : servers_)
    {
        if(s->description() != QString())
            emit response(QStringList(s->description()));
    }
}

void Logger::addHandler(Handler *handler)
{
    handlers_.push_back(handler);
}

void Logger::addServer(TcpServer *server)
{
    servers_.push_back(server);
}

void Logger::set(QStringList)
{
    emit error("Logger is not setable");
}

void Logger::log(QString message)
{
    emit response(QStringList(message));
}
