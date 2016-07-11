#ifndef WIRING_H
#define WIRING_H

//zaślepka, nie wrzucać do gotowego projektu

int wiringPiI2CReadReg8(int, int);
int wiringPiI2CSetup(int);
void wiringPiI2CWriteReg8(int, int, int);

#endif
