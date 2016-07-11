#ifndef MEASUREINTERFACE_H
#define MEASUREINTERFACE_H

#include <QObject>

class MeasureInterface : public QObject
{
    Q_OBJECT
public:
    explicit MeasureInterface(QObject *parent = 0);
    virtual ~MeasureInterface() {}
    virtual double read() = 0;
signals:

public slots:

};

#endif // MEASUREINTERFACE_H
