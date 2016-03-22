#ifndef MODBUS_REGS_H_
#define MODBUS_REGS_H_

/*****************************************************MODBUS REGISTERS*******************************************/

/* Control section					*/
#define MB_SECTION_CTRL_ADDR	0	/* Control section start address											*/
#define MB_SECTION_CTRL_SIZE	15	/* Control section number of registers										*/

#define MB_CTRL_BLDC_1			0	/* BLDC 1 power to set (0 on reset); Range: <-1000,1000>					*/
#define MB_CTRL_BLDC_2			1	/* BLDC 2 power to set (0 on reset); Range: <-1000,1000>					*/
#define MB_CTRL_BLDC_3			2	/* BLDC 3 power to set (0 on reset); Range: <-1000,1000>					*/
#define MB_CTRL_BLDC_4			3	/* BLDC 4 power to set (0 on reset); Range: <-1000,1000>					*/
#define MB_CTRL_BLDC_5			4	/* BLDC 5 power to set (0 on reset); Range: <-1000,1000>					*/
#define MB_CTRL_BLDC_6			5	/* BLDC 6 power to set (0 on reset); Range: <-1000,1000>					*/

#define MB_CTRL_STEPPER_1		6	/* Stepper Motor 1 position to set (0 on reset); Range: <-18000,18000>		*/
#define MB_CTRL_STEPPER_2		7	/* Stepper Motor 2 position to set (0 on reset); Range: <-18000,18000>		*/
#define MB_CTRL_STEPPER_3		8	/* Stepper Motor 3 position to set (0 on reset); Range: <-18000,18000>		*/
#define MB_CTRL_STEPPER_4		9	/* Stepper Motor 4 position to set (0 on reset); Range: <-18000,18000>		*/

#define MB_CTRL_POWER_1			10	/* Power Output 1 control register (0 on reset); Range <0,1>				*/
#define MB_CTRL_POWER_2			11	/* Power Output 2 control register (0 on reset); Range <0,1>				*/
#define MB_CTRL_POWER_3			12	/* Power Output 3 control register (0 on reset); Range <0,1>				*/

#define MB_CTRL_MODE			13	/* Driver Mode Register (0 on reset); Range: Specified bit flags (below)	*/
#define MB_CTRL_CMD				14	/* Driver Command Register (0 on reset); Range: Specified bit flags (below)	*/

/* Status section (READ ONLY!)		*/
#define MB_SECTION_STAT_ADDR	15	/* Status section start address												*/
#define MB_SECTION_STAT_SIZE	6	/* Status section number of registers										*/

#define MB_STAT_STEPPER_1		15	/* Stepper Motor 1 current position (0 on reset); Range: <-18000,18000>		*/
#define MB_STAT_STEPPER_2		16	/* Stepper Motor 2 current position (0 on reset); Range: <-18000,18000>		*/
#define MB_STAT_STEPPER_3		17	/* Stepper Motor 3 current position (0 on reset); Range: <-18000,18000>		*/
#define MB_STAT_STEPPER_4		18	/* Stepper Motor 4 current position (0 on reset); Range: <-18000,18000>		*/

#define MB_STAT_DRIVER			19	/* Driver Status Register (0 on reset); Range: Specified bit flags (below)	*/
#define MB_STAT_RUNTIME			20	/* Time from last power on (in seconds)										*/

/**************************************************END OF MODBUS REGISTERS***************************************/

/*************************************************REGISTERS SPECIFIED FLAGS**************************************/
/* MB_CTRL_MODE		*/
#define MB_CTRL_MODE_STOP			0x0000	/* Driver stop mode (all outputs off)							*/
#define MB_CTRL_MODE_NORMAL			0x0001	/* Driver normal mode (all function active)						*/
/* MB_CTRL_CMD		*/
#define MB_CTRL_CMD_DRIVER_RESET	0x0001	/* Reset driver to 'power on' state								*/
#define MB_CTRL_CMD_RESET_STEPPERS	0x0002	/* Reset all stepper's registers (control & status)				*/
/* MB_STAT_DRIVER	*/
#define MB_STAT_DRIVER_STOPPED		0x0001	/* Driver was stopped due to user action or connection timeout	*/

#endif /* MODBUS_REGS_H_ */
