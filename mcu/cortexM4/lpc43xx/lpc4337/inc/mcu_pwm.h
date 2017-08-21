/*
 * mcu_pwm.h
 *
 *  Created on: 7/7/2017
 *      Author: Fede
 */

#ifndef MCU_PWM_H_
#define MCU_PWM_H_
/** \brief Header para MCU
 **
 ** archivo de inicilización del microcontrolador
 **
 **/

/** \addtogroup PASE_APP_EXAMPLE
 ** @{ */
/** \addtogroup MCU GPIO
 ** @{ */

/*==================[inclusions]=============================================*/
#include "stdbool.h"
#include "stdint.h"

/*==================[cplusplus]==============================================*/
#ifdef __cplusplus
extern "C" {
#endif

/*==================[macros]=================================================*/

/*==================[typedef]================================================*/
typedef enum
{
   MCU_PWM_CHANNEL0 = 0,
   MCU_PWM_CHANNEL1,
   MCU_PWM_CHANNEL2,
   MCU_PWM_CHANNEL3,
   MCU_PWM_CHANNEL4,
   MCU_PWM_CHANNEL5,

}mcu_pwm_channel_enum;


/*==================[external functions declaration]=========================*/
extern void mcu_pwm_init(void);
extern void mcu_pwm_config(mcu_pwm_channel_enum, uint32_t);
extern void mcu_pwm_setDutyCicle(uint32_t,uint32_t,uint32_t, uint16_t f);
extern void mcu_pwm_start(void);
extern void mcu_pwm_stop(void);
/*==================[cplusplus]==============================================*/
#ifdef __cplusplus
}
#endif
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
#endif /* MCU_PWM_H_ */