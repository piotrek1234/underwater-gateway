#include <QCoreApplication>
#include "../underwater-gateway/tcpserver.h"
#include "../underwater-gateway/frameparser.h"
#include "../underwater-gateway/axishandler.h"
#include "../underwater-gateway/motorhandler.h"
#include "../underwater-gateway/outputhandler.h"
#include "../underwater-gateway/servicehandler.h"
#include "../underwater-gateway/modbusmaster.h"
#include "../underwater-gateway/modbus_regs.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    TcpServer s_mod1(6003);
    FrameParser fp3;

    QObject::connect(&s_mod1, SIGNAL(frameContent(QString)), &fp3, SLOT(parseFrame(QString)));
    QObject::connect(&fp3, SIGNAL(sendFrame(QString)), &s_mod1, SLOT(sendResponse(QString)));

    MotorHandler* mh = new MotorHandler(6);
    mh->assignRegister(0, MB_CTRL_BLDC_1);
    mh->assignRegister(1, MB_CTRL_BLDC_2);
    mh->assignRegister(2, MB_CTRL_BLDC_3);
    mh->assignRegister(3, MB_CTRL_BLDC_4);
    mh->assignRegister(4, MB_CTRL_BLDC_5);
    mh->assignRegister(5, MB_CTRL_BLDC_6);

    AxisHandler* ah = new AxisHandler(4);
    ah->assignRegister(0, regType::read, MB_STAT_STEPPER_1_POS);
    ah->assignRegister(1, regType::read, MB_STAT_STEPPER_2_POS);
    ah->assignRegister(2, regType::read, MB_STAT_STEPPER_3_POS);
    ah->assignRegister(3, regType::read, MB_STAT_STEPPER_4_POS);
    ah->assignRegister(0, regType::write, MB_CTRL_STEPPER_1_POS);
    ah->assignRegister(1, regType::write, MB_CTRL_STEPPER_2_POS);
    ah->assignRegister(2, regType::write, MB_CTRL_STEPPER_3_POS);
    ah->assignRegister(3, regType::write, MB_CTRL_STEPPER_4_POS);
    ah->assignRegister(0, regType::speed, MB_CTRL_STEPPER_1_SPEED);
    ah->assignRegister(1, regType::speed, MB_CTRL_STEPPER_2_SPEED);
    ah->assignRegister(2, regType::speed, MB_CTRL_STEPPER_3_SPEED);
    ah->assignRegister(3, regType::speed, MB_CTRL_STEPPER_4_SPEED);
    ah->assignRegister(0, regType::gear, MB_CTRL_STEPPER_1_GEAR);
    ah->assignRegister(1, regType::gear, MB_CTRL_STEPPER_2_GEAR);
    ah->assignRegister(2, regType::gear, MB_CTRL_STEPPER_3_GEAR);
    ah->assignRegister(3, regType::gear, MB_CTRL_STEPPER_4_GEAR);

    OutputHandler* oh = new OutputHandler(3);
    oh->assignRegister(0, MB_CTRL_POWER_1);
    oh->assignRegister(1, MB_CTRL_POWER_2);
    oh->assignRegister(1, MB_CTRL_POWER_3);

    ServiceHandler* sh = new ServiceHandler();

    fp3.addHandler(ah);
    fp3.addHandler(mh);
    fp3.addHandler(oh);
    fp3.addHandler(sh);

    ModbusMaster* modbus1 = new ModbusMaster("/dev/ttyUSB0", 100);
    //ModbusMaster* modbus2 = new ModbusMaster("/dev/ttySAC0", 100);

    ah->setModbus(modbus1);
    mh->setModbus(modbus1);
    oh->setModbus(modbus1);
    sh->setModbus(modbus1);

    s_mod1.start();

    return a.exec();
}
