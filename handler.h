#ifndef HANDLER_H
#define HANDLER_H

#include <QObject>
#include <QStringList>

class Handler : public QObject
{
    Q_OBJECT
public:
    Handler();
    virtual ~Handler();
    virtual void set(QStringList frame) = 0;
    virtual void get(QStringList frame) = 0;
    virtual char handlerType() const = 0;
protected slots:
    virtual void finish(QStringList context, QStringList args);
    void failure(QString content);
signals:
    void response(QStringList);
    void error(QString);
};

#endif // HANDLER_H
