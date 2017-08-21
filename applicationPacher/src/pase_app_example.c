/* Copyright 2017, Gustavo Muro
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

/** \brief PASE APP EXAMPLE
 **
 ** ejemplo de aplicación usando CIAA Firmware
 **
 **/

/** \addtogroup
 ** @{ */
/** \addtogroup
 ** @{ */
/** \addtogroup
 ** @{ */

/*==================[inclusions]=============================================*/
#include "os.h"
#include "pase_app_example.h"
#include "bsp.h"
#include "mcu.h"


/*==================[macros and definitions]=================================*/
#define FIRST_START_DELAY_MS 200
#define PERIOD_MS 20
#define PERIOD_4SEG 1000
#define PERIODO_PTO_SERIE 1000


#define SCT_PWM_RATE   10000        /* PWM frequency 10 KHz */
#define LED_STEP_CNT      20        /* Change LED duty cycle every 20ms */
#define OUT_STEP_CNT    1000        /* Change duty cycle every 1 second */

#define BAUD_RATE	115200

#define BUFFER_SIZE  512

#define TICKRATE_HZ     1000        /* 1 ms Tick rate */

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/
int32_t pausa = 1;
estado_secuencia secuencia = 0;
led_on led_encendido = 0;
uint8_t arranque = 0;
double tiempo = 0;

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/
static void eventInput1_callBack(mcu_gpio_pinId_enum id, mcu_gpio_eventTypeInput_enum evType)
{
   ActivateTask(InputEvTask1);
}

static void eventInput2_callBack(mcu_gpio_pinId_enum id, mcu_gpio_eventTypeInput_enum evType)
{
   ActivateTask(InputEvTask2);
}

/*==================[external functions definition]==========================*/
/** \brief Main function
 *
 * This is the main entry point of the software.
 *
 * \returns 0
 *
 * \remarks This function never returns. Return value is only to avoid compiler
 *          warnings or errors.
 */
int main(void)
{
   /* Starts the operating system in the Application Mode 1 */
   /* This example has only one Application Mode */
   StartOS(AppMode1);

   /* StartOs shall never returns, but to avoid compiler warnings or errors
    * 0 is returned */
   return 0;
}

/** \brief Error Hook function
 *
 * This fucntion is called from the os if an os interface (API) returns an
 * error. Is for debugging proposes. If called this function triggers a
 * ShutdownOs which ends in a while(1).
 *
 * The values:
 *    OSErrorGetServiceId
 *    OSErrorGetParam1
 *    OSErrorGetParam2
 *    OSErrorGetParam3
 *    OSErrorGetRet
 *
 * will provide you the interface, the input parameters and the returned value.
 * For more details see the OSEK specification:
 * http://portal.osek-vdx.org/files/pdf/specs/os223.pdf
 *
 */
void ErrorHook(void)
{
   ShutdownOS(0);
}

/** \brief Initial task
 *
 * This task is started automatically in the application mode 1.
 */
TASK(InitTask)
{
   bsp_init();


  /* mcu_pwm_init();
   mcu_pwm_config(0,SCT_PWM_RATE);*/


   //ACTIVA EVENTO BOTON 1, FALLING EDGE
   mcu_gpio_setEventInput(MCU_GPIO_PIN_ID_38,
           MCU_GPIO_EVENT_TYPE_INPUT_FALLING_EDGE,
           eventInput1_callBack);
   //ACTIVA EVENTO BOTON 2, RISING EDGE
   mcu_gpio_setEventInput(MCU_GPIO_PIN_ID_42,
           MCU_GPIO_EVENT_TYPE_INPUT_RISING_EDGE,
           eventInput2_callBack);

   //inicia uart
  // mcu_uart_init(BAUD_RATE);



   TerminateTask();
}


static int32_t contador = 0;
static char flag_cambio = 0;
TASK(PeriodicTask)
{
	/*tiempo = tiempo + 0.2;
	if(pausa == 0)
	{
		if(flag_cambio == 0)
		{
			if(contador < 100)
			{
				contador = contador + 1;
				secuencia = INICIO_SECUENCIA;
			}
			else
			{
				flag_cambio = 1;
				switch(led_encendido)
				{
					case 0:
						secuencia = MAXIMO_1;
					break;
					case 1:
						secuencia = MAXIMO_2;
					break;
					case 2:
						secuencia = MAXIMO_3;
					break;

				}
				ChainTask(WriteSerialTask);
			}
		}
		else
		{
			if(contador > 1)
			{
				contador = contador - 1;
			}
			else
			{
				flag_cambio = 0;
				ChainTask(PeriodicTask4Seg);
			}
		}

		switch(led_encendido)
		{
			case 0:
				mcu_pwm_setDutyCicle(contador,10,2,1);
				mcu_pwm_setDutyCicle(contador,11,5,0);//CAMBIO EN VALOR DE LA FUNC, ULTIMO PARAMETRO PARA APAGAR LED
				mcu_pwm_setDutyCicle(contador,12,4,0);
			break;
			case 1:
				mcu_pwm_setDutyCicle(contador,10,2,0);
				mcu_pwm_setDutyCicle(contador,11,5,1);
				mcu_pwm_setDutyCicle(contador,12,4,0);
			break;
			case 2:
				mcu_pwm_setDutyCicle(contador,10,2,0);
				mcu_pwm_setDutyCicle(contador,11,5,0);
				mcu_pwm_setDutyCicle(contador,12,4,1);
			break;
		}
	}*/
	TerminateTask();
}

TASK(PeriodicTask4Seg)
{
	/*if(led_encendido<2)
	{
		led_encendido++;
	}
	else
	{
		led_encendido = 0;
	}
	ChainTask(WriteSerialTask2);*/
	TerminateTask();
}

/*TASK(PruebaSerialTask)
{
	//GetResource(POSIXR);
	bsp_ledAction(BOARD_LED_ID_0_B, BSP_LED_ACTION_TOGGLE);

	char* message1 = "Hola";
	char message2[] = " Puto\n\r";

	const char* name = "hello";
	const char* extension = ".txt\n\r";

	char name_with_extension[11];
	//name_with_extension = malloc(sizeof(name)+1+4); /* make space for the new string (should check the return value ...) */
/*	strcpy(name_with_extension, name); /* copy name into the new var */
/*	strcat(name_with_extension, extension); /* add the extension */

/*	mcu_uart_write(name_with_extension, sizeof(name_with_extension));


	TerminateTask();
}*/




TASK(WriteSerialTask)
{

	/*bsp_ledAction(BOARD_LED_ID_0_R, BSP_LED_ACTION_TOGGLE);

	char message1[] = "Maximo Amarillo\n\r";
	char message2[] = "Maximo Rojo\n\r";
	char message3[] = "Maximo Verde\n\r";
	char message4[] = "Secuencia Stop\n\r";
	char message5[] = "Inicio Secuencia - Iniciando Amarillo\n\r";
	char message6[] = "Secuencia Pausada\n\r";
	char message7[] = "Secuencia Reanudada\n\r";

		 switch(secuencia)
	 	 {
		 	 	 case STOP:
		 			 mcu_uart_write(message4, sizeof(message4));
		 			 break;
		 		case INICIO_SECUENCIA:
		 			 mcu_uart_write(message5, sizeof(message5));
		 			 break;
		 		case PAUSA:
		 			 mcu_uart_write(message6, sizeof(message6));
		 			 break;
		 		case REANUDA_SECUENCIA:
		 			mcu_uart_write(message7, sizeof(message7));
		 			break;
			 	 case MAXIMO_1:
			 		mcu_uart_write(message1, sizeof(message1));
			 		 break;
			 	 case MAXIMO_2:
			 		 mcu_uart_write(message2, sizeof(message2));
			 		 break;
			 	 case MAXIMO_3:
			 		 mcu_uart_write(message3, sizeof(message3));
			 		 break;

		}*/


	TerminateTask();
}

TASK(WriteSerialTask2)
{
/*	char message8[] = "Iniciando Amarillo\n\r";
	char message9[] = "Iniciando Rojo\n\r";
	char message10[] = "Iniciando Verde\n\r";

	switch(led_encendido)
			 {
			 	 case lED_1:
			 		mcu_uart_write(message8, sizeof(message8));
					break;
				case lED_2:
					mcu_uart_write(message9, sizeof(message9));
					break;
				case lED_3:
			 		mcu_uart_write(message10, sizeof(message10));
			 		break;
			 }*/
	TerminateTask();
}
//TECLA 1
TASK(InputEvTask1)
{
	bsp_ledAction(BOARD_LED_ID_0_R, BSP_LED_ACTION_TOGGLE);
	/*if(arranque ==0)
	{
		arranque = 1;
		 //activo tarea pwm
		   SetRelAlarm(ActivatePeriodicTask, FIRST_START_DELAY_MS, PERIOD_MS);
	}

	bsp_ledAction(BOARD_LED_ID_1, BSP_LED_ACTION_OFF);
	bsp_ledAction(BOARD_LED_ID_2, BSP_LED_ACTION_OFF);
	bsp_ledAction(BOARD_LED_ID_3, BSP_LED_ACTION_OFF);
	if(pausa == 0)
	{
	   pausa = 1;
	   mcu_pwm_stop();
	   secuencia = STOP;
	   ChainTask(WriteSerialTask);
	}
	else
	{
		tiempo = 0;
		pausa = 0;
		led_encendido = 0;
		contador = 0;
		flag_cambio = 0;
		secuencia = INICIO_SECUENCIA;
		mcu_pwm_start();
		ChainTask(WriteSerialTask);

	}*/


   TerminateTask();
}


//TECLA 2 PAUSA
TASK(InputEvTask2)
{

   bsp_ledAction(BOARD_LED_ID_0_B, BSP_LED_ACTION_TOGGLE);
/*   if(pausa == 0)
   {
	   pausa = 1;
	   secuencia = PAUSA;
   }
   else
   {
	   pausa = 0;
	   secuencia = REANUDA_SECUENCIA;
   }
   ChainTask(WriteSerialTask);*/
   TerminateTask();
}



/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

