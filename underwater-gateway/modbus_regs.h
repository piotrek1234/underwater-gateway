#ifndef MODBUS_REGS_H_
#define MODBUS_REGS_H_

/*****************************************************MODBUS REGISTERS*******************************************/

/* Control section					*/
#define MB_SECTION_CTRL_ADDR	0	/* Control section start address											*/
#define MB_SECTION_CTRL_SIZE	23	/* Control section number of registers										*/

#define MB_CTRL_BLDC_1			0	/* BLDC 1 power to set (0 on reset); Unit: %								*/
#define MB_CTRL_BLDC_2			1	/* BLDC 2 power to set (0 on reset); Unit: %								*/
#define MB_CTRL_BLDC_3			2	/* BLDC 3 power to set (0 on reset); Unit: %								*/
#define MB_CTRL_BLDC_4			3	/* BLDC 4 power to set (0 on reset); Unit: %								*/
#define MB_CTRL_BLDC_5			4	/* BLDC 5 power to set (0 on reset); Unit: %								*/
#define MB_CTRL_BLDC_6			5	/* BLDC 6 power to set (0 on reset); Unit: %								*/

#define MB_CTRL_STEPPER_1_POS	6	/* Stepper Motor 1 position to set (0 on reset); Unit: deg					*/
#define MB_CTRL_STEPPER_2_POS	7	/* Stepper Motor 2 position to set (0 on reset); Unit: deg					*/
#define MB_CTRL_STEPPER_3_POS	8	/* Stepper Motor 3 position to set (0 on reset); Unit: deg					*/
#define MB_CTRL_STEPPER_4_POS	9	/* Stepper Motor 4 position to set (0 on reset); Unit: deg					*/

#define MB_CTRL_STEPPER_1_SPEED	10	/* Stepper Motor 1 speed to set (36 on reset); Unit: deg					*/
#define MB_CTRL_STEPPER_2_SPEED	11	/* Stepper Motor 1 speed to set (36 on reset); Unit: deg					*/
#define MB_CTRL_STEPPER_3_SPEED	12	/* Stepper Motor 1 speed to set (36 on reset); Unit: deg					*/
#define MB_CTRL_STEPPER_4_SPEED	13	/* Stepper Motor 1 speed to set (36 on reset); Unit: deg					*/

#define MB_CTRL_STEPPER_1_GEAR	14
#define MB_CTRL_STEPPER_2_GEAR	15
#define MB_CTRL_STEPPER_3_GEAR	16
#define MB_CTRL_STEPPER_4_GEAR	17

#define MB_CTRL_POWER_1			18	/* Power Output 1 control register (0 on reset); Unit: on/off				*/
#define MB_CTRL_POWER_2			19	/* Power Output 2 control register (0 on reset); Unit: on/off				*/
#define MB_CTRL_POWER_3			20	/* Power Output 3 control register (0 on reset); Unit: on/off				*/

#define MB_CTRL_MODE			21	/* Driver Mode Register (0 on reset); Unit: Specified flags (below)			*/
#define MB_CTRL_CMD				22	/* Driver Command Register (0 on reset); Unit: Specified flags (below)		*/

/* Status section (READ ONLY!)		*/
#define MB_SECTION_STAT_ADDR	25	/* Status section start address												*/
#define MB_SECTION_STAT_SIZE	6	/* Status section number of registers										*/

#define MB_STAT_STEPPER_1_POS	25	/* Stepper Motor 1 current position (0 on reset); Unit: deg					*/
#define MB_STAT_STEPPER_2_POS	26	/* Stepper Motor 2 current position (0 on reset); Unit: deg					*/
#define MB_STAT_STEPPER_3_POS	27	/* Stepper Motor 3 current position (0 on reset); Unit: deg					*/
#define MB_STAT_STEPPER_4_POS	28	/* Stepper Motor 4 current position (0 on reset); Unit: deg					*/

#define MB_STAT_DRIVER			29	/* Driver Status Register (0 on reset); Range: Specified bit flags (below)	*/
#define MB_STAT_RUNTIME			30	/* Time from last power on (in seconds)										*/

/* Debug							*/

#define MB_DEBUG_1				35
#define MB_DEBUG_2				36
#define MB_DEBUG_3				37
#define MB_DEBUG_4				38
#define MB_DEBUG_5				39

/**************************************************END OF MODBUS REGISTERS***************************************/

/*************************************************REGISTERS SPECIFIED FLAGS**************************************/
/* MB_CTRL_MODE		*/
#define MB_CTRL_MODE_STOP			0x0000	/* Driver stop mode (all outputs off)								*/
#define MB_CTRL_MODE_NORMAL			0x0001	/* Driver normal mode (all function active)							*/
/* MB_CTRL_CMD		*/
#define MB_CTRL_CMD_NONE			0x0000	/* Empty command													*/
#define MB_CTRL_CMD_DRIVER_RESET	0x0001	/* Reset driver to 'power on' state									*/
#define MB_CTRL_CMD_RESET_STEPPERS	0x0002	/* Reset all stepper's registers (control & status)					*/
/* MB_STAT_DRIVER	*/
#define MB_STAT_DRIVER_STOPPED		0x0000	/* Driver normal operating mode										*/
#define MB_STAT_DRIVER_NORMAL		0x0001	/* Driver was stopped due to user action or connection timeout		*/
#define MB_STAT_DRIVER_BLDC_INIT	0x0002	/* Driver bldc initialization										*/

/**********************************************END OF REGISTERS SPECIFIED FLAGS**********************************/

/***************************************************REGISTERS CONSTRAINS*****************************************/
#define MB_CTRL_BLDC_MIN			-100
#define MB_CTRL_BLDC_MAX			100

#define MB_CTRL_STEPPER_POS_MIN		-1800
#define MB_CTRL_STEPPER_POS_MAX		1800

#define MB_CTRL_STEPPER_SPEED_MIN	36
#define MB_CTRL_STEPPER_SPEED_MAX	1080

#define MB_CTRL_STEPPER_GEAR_MIN	1
#define MB_CTRL_STEPPER_GEAR_MAX	1000

#define MB_CTRL_POWER_MIN			0
#define MB_CTRL_POWER_MAX			1

#define MB_CTRL_MODE_MIN			0
#define MB_CTRL_MODE_MAX			1

#define MB_CTRL_CMD_MIN				1
#define MB_CTRL_CMD_MAX				2
/************************************************END OF REGISTERS CONSTRAINS*************************************/

#endif /* MODBUS_REGS_H_ */
