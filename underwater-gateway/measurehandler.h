#ifndef MEASUREHANDLER_H
#define MEASUREHANDLER_H

#include <QMap>
#include <QVector>
#include <QTimer>
#include "handler.h"
#include "measure.h"

class MeasureHandler : public Handler
{
    Q_OBJECT
public:
    MeasureHandler(int interval);
    virtual void get(QStringList frame);
    virtual void set(QStringList frame);
    virtual char handlerType() const { return 'm'; }
    virtual QString description();
    void addMeasure(char type, Measure* measure);
private:
    QTimer timer;
    QMap<char, QVector<Measure*> > measures;
private slots:
    void updateMeasures();
};

#endif // MEASUREHANDLER_H
