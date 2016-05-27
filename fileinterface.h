#ifndef FILEINTERFACE_H
#define FILEINTERFACE_H

#include "measureinterface.h"
#include <QFile>
#include <QTextStream>

class FileInterface : public MeasureInterface
{
    Q_OBJECT
public:
    FileInterface(QString file) { file_ = file; }
    virtual double read();
private:
    QString file_;
};

#endif // FILEINTERFACE_H
