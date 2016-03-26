#ifndef FRAMEPARSER_H
#define FRAMEPARSER_H

#include <QObject>
#include <QStringList>
#include <QMap>
#include "frame.h"
#include "handler.h"
#include <iostream>

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
    QMap<QString, Handler*> handlers_;
public slots:
    void parseFrame(QString frame);
    void buildFrame(QStringList args);  //dla faktycznych odpowiedzi
    void buildErrorFrame(QString content);   //dla błędów
    void printFrame(QString frame); //dla debuga
};

#endif // FRAMEPARSER_H
