/*

 * mcu_pwm.c
 *
 *  Created on: 7 jul. 2017
 *      Author: lucho
 */
/*==================[inclusions]=============================================*/
#include "mcu.h"
#include "mcu_timer.h"
#include "chip.h"


/*==================[macros and definitions]=================================*/


/*==================[external functions definition]==========================*/

extern void mcu_timer_init(){

	   Chip_TIMER_PrescaleSet(LPC_TIMER1, SystemCoreClock/1000);
	   Chip_TIMER_Reset(LPC_TIMER1);
}


extern uint32_t mcu_timer_read(){

	return Chip_TIMER_ReadCount(LPC_TIMER1);
}

extern void mcu_timer_start(){
	Chip_TIMER_Enable(LPC_TIMER1);
}




