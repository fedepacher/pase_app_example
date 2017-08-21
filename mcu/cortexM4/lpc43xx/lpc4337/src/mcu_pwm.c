/*
 * mcu_pwm.c
 *
 *  Created on: 7/7/2017
 *      Author: Fede
 */
/* Copyright 2017, Gustavo Muro
 * All rights reserved.
 *
 * This file is part of CIAA Firmware.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

/** \brief source para MCU
 **
 ** archivo de inicilización del microcontrolador
 **
 **/

/** \addtogroup PASE_APP_EXAMPLE
 ** @{ */
/** \addtogroup MCU
 ** @{ */

/*==================[inclusions]=============================================*/
#include "mcu.h"
#include "stdint.h"
#include "chip.h"
#include "os.h"
#include "mcu_pwm.h"

/*==================[internal functions declaration]=========================*/
/*typedef struct
{
   uint8_t port;
   uint8_t pin;
}portPin_type;*/

#define index 1
#define port 2
#define pin 10

#define SCT_PWM_PIN_LED_AMARILLO    2        /* COUT2 [index 2] Controls LED */
#define SCT_PWM_PIN_LED_ROJO    5        /* COUT5 [index 2] Controls LED */
#define SCT_PWM_PIN_LED_VERDE    4        /* COUT4 [index 2] Controls LED */
#define SCT_PWM_LED        2        /* Index of LED PWM */

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/


extern void mcu_pwm_init(void)
{
	Chip_SCTPWM_Init(LPC_SCT);
}

extern void mcu_pwm_config(mcu_pwm_channel_enum channel, uint32_t frecuencia)
{
	Chip_SCTPWM_SetRate(LPC_SCT, frecuencia);

	//LED AMARILLO
	//Chip_SCU_PinMuxSet(2, 10, FUNC1);//LED AMARILLO
	//Chip_SCTPWM_SetOutPin(LPC_SCT, SCT_PWM_LED, SCT_PWM_PIN_LED_AMARILLO);

	//LED ROJO
	//Chip_SCU_PinMuxSet(2, 0xB, FUNC1);//LED ROJO
	//Chip_SCTPWM_SetOutPin(LPC_SCT, SCT_PWM_LED, SCT_PWM_PIN_LED_ROJO);

	//LED VERDE
	//Chip_SCU_PinMuxSet(2, 0xC, FUNC1);//LED VERDE
	//Chip_SCTPWM_SetOutPin(LPC_SCT, SCT_PWM_LED, SCT_PWM_PIN_LED_VERDE);

	Chip_SCTPWM_SetDutyCycle(LPC_SCT, SCT_PWM_LED, 0);

	//Chip_SCTPWM_SetOutPin(LPC_SCT, index, pin);

}

extern void mcu_pwm_setDutyCicle(uint32_t d,uint32_t d1,uint32_t d2, uint16_t f)
{
	Chip_SCU_PinMuxSet(2, d1, f);
	Chip_SCTPWM_SetOutPin(LPC_SCT, SCT_PWM_LED, d2);
	Chip_SCTPWM_SetDutyCycle(LPC_SCT, SCT_PWM_LED, Chip_SCTPWM_PercentageToTicks(LPC_SCT, d));
}

extern void mcu_pwm_start(void)
{
	Chip_SCTPWM_Start(LPC_SCT);

}

extern void mcu_pwm_stop(void)
{
	Chip_SCTPWM_Stop(LPC_SCT);
}


