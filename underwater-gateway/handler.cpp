#include "handler.h"

Handler::Handler()
{

}

Handler::~Handler()
{

}

void Handler::finish(QStringList context, QStringList args)
{
    emit response(QStringList() << context << args);
}

void Handler::failure(QString content)
{
    emit error(content);
}
