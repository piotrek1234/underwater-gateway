#ifndef I2C_H
#define I2C_H

#include <QObject>
#include <wiringPiI2C.h>

class I2C : public QObject
{
    Q_OBJECT
public:
    explicit I2C(int address);
    void prepare();
    int getHandle() { return handle; }
signals:

public slots:
private:
    int handle;
    int address;

};

#endif // I2C_H
