#ifndef MODBUS_REGS_H_
#define MODBUS_REGS_H_

/*****************************************************MODBUS REGISTERS*******************************************/

/* Control section					*/
#define MB_SECTION_CTRL_ADDR	0	/* Control section start address											*/
#define MB_SECTION_CTRL_SIZE	19	/* Control section number of registers										*/

#define MB_CTRL_BLDC_1			0	/* BLDC 1 power to set (0 on reset); Range: <-1000,1000>					*/
#define MB_CTRL_BLDC_2			1	/* BLDC 2 power to set (0 on reset); Range: <-1000,1000>					*/
#define MB_CTRL_BLDC_3			2	/* BLDC 3 power to set (0 on reset); Range: <-1000,1000>					*/
#define MB_CTRL_BLDC_4			3	/* BLDC 4 power to set (0 on reset); Range: <-1000,1000>					*/
#define MB_CTRL_BLDC_5			4	/* BLDC 5 power to set (0 on reset); Range: <-1000,1000>					*/
#define MB_CTRL_BLDC_6			5	/* BLDC 6 power to set (0 on reset); Range: <-1000,1000>					*/

#define MB_CTRL_STEPPER_1_POS	6	/* Stepper Motor 1 position to set (0 on reset); Range: <-18000,18000>		*/
#define MB_CTRL_STEPPER_2_POS	7	/* Stepper Motor 2 position to set (0 on reset); Range: <-18000,18000>		*/
#define MB_CTRL_STEPPER_3_POS	8	/* Stepper Motor 3 position to set (0 on reset); Range: <-18000,18000>		*/
#define MB_CTRL_STEPPER_4_POS	9	/* Stepper Motor 4 position to set (0 on reset); Range: <-18000,18000>		*/

#define MB_CTRL_STEPPER_1_SPEED	10	/* Stepper Motor 1 speed to set (360 on reset); Range: <360,3600>			*/
#define MB_CTRL_STEPPER_2_SPEED	11	/* Stepper Motor 1 speed to set (360 on reset); Range: <360,3600>			*/
#define MB_CTRL_STEPPER_3_SPEED	12	/* Stepper Motor 1 speed to set (360 on reset); Range: <360,3600>			*/
#define MB_CTRL_STEPPER_4_SPEED	13	/* Stepper Motor 1 speed to set (360 on reset); Range: <360,3600>			*/

#define MB_CTRL_POWER_1			14	/* Power Output 1 control register (0 on reset); Range <0,1>				*/
#define MB_CTRL_POWER_2			15	/* Power Output 2 control register (0 on reset); Range <0,1>				*/
#define MB_CTRL_POWER_3			16	/* Power Output 3 control register (0 on reset); Range <0,1>				*/

#define MB_CTRL_MODE			17	/* Driver Mode Register (0 on reset); Range: Specified bit flags (below)	*/
#define MB_CTRL_CMD				18	/* Driver Command Register (0 on reset); Range: Specified bit flags (below)	*/

/* Status section (READ ONLY!)		*/
#define MB_SECTION_STAT_ADDR	20	/* Status section start address												*/
#define MB_SECTION_STAT_SIZE	6	/* Status section number of registers										*/

#define MB_STAT_STEPPER_1		20	/* Stepper Motor 1 current position (0 on reset); Range: <-18000,18000>		*/
#define MB_STAT_STEPPER_2		21	/* Stepper Motor 2 current position (0 on reset); Range: <-18000,18000>		*/
#define MB_STAT_STEPPER_3		22	/* Stepper Motor 3 current position (0 on reset); Range: <-18000,18000>		*/
#define MB_STAT_STEPPER_4		23	/* Stepper Motor 4 current position (0 on reset); Range: <-18000,18000>		*/

#define MB_STAT_DRIVER			24	/* Driver Status Register (0 on reset); Range: Specified bit flags (below)	*/
#define MB_STAT_RUNTIME			25	/* Time from last power on (in seconds)										*/

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
