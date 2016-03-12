#ifndef FRAMEPARSER_H
#define FRAMEPARSER_H

#include <QObject>
#include <QStringList>
#include <QMap>
#include "frame.h"
#include "handler.h"

class FrameParser : public QObject
{
    Q_OBJECT
public:
    explicit FrameParser(QObject *parent = 0);
    ~FrameParser();
    void addHandler(Handler* handler);
    Handler* getHandler(char type);
signals:
    void sendFrame(QString);
private:
    QMap<QString, Handler*> handlers;

public slots:
    void parseFrame(QString frame);
    void buildFrame(QStringList args);  //dla faktycznych odpowiedzi
    void buildErrorFrame(QString content);   //dla błędów
};

#endif // FRAMEPARSER_H
