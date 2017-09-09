/* Copyright 2017, Luciano Rumin
 *
 *
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

/** \brief UTIL
 **
 ** Aplicación usando CIAA Firmware
 **
 **/

/** \addtogroup
 ** @{ */
/** \addtogroup
 ** @{ */
/** \addtogroup
 ** @{ */

/*==================[inclusions]=============================================*/

#include "util.h"


/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/


/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/


/*==================[internal functions definition]==========================*/

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
extern void Binario_to_BCD(uint32_t Valor_Convertir, uint8_t* Buffer, uint32_t offset, uint32_t length){

	uint32_t Valor_BCD;
	uint32_t Desplazar;
	uint32_t D;
	uint32_t Auxiliar_Calculo;
	uint32_t Valor_Posicion, Valor_Comparar, Limpiar_Valor, Valor_Sumar;

	Valor_BCD=0;
	Desplazar=31;


	while(Desplazar){
		D = 1 << (Desplazar);
		Valor_BCD |= (Valor_Convertir & D)>>Desplazar;
		Valor_Posicion=0x0000000F;
		Valor_Comparar=0x00000004;
		Limpiar_Valor=0xFFFFFFF0;
		Valor_Sumar=0x00000003;

		for(D=0;D<8;D++){
			Auxiliar_Calculo = Valor_BCD & Valor_Posicion;
			if(Auxiliar_Calculo > Valor_Comparar) {
				Valor_BCD &= Limpiar_Valor;
				Auxiliar_Calculo = Auxiliar_Calculo + Valor_Sumar;
				Valor_BCD |= Auxiliar_Calculo & Valor_Posicion;
			}
			Valor_Comparar = Valor_Comparar <<4;
			Limpiar_Valor = (Limpiar_Valor <<4) | 0x0000000F;
			Valor_Posicion= Valor_Posicion <<4;
			Valor_Sumar = Valor_Sumar <<4;
		}

		Valor_BCD = Valor_BCD << 1;
		Desplazar--;
	}
	Valor_BCD |= (Valor_Convertir & 1);

	for (Auxiliar_Calculo=(offset+length); Auxiliar_Calculo>offset; Auxiliar_Calculo--){
		Buffer[Auxiliar_Calculo-1]=((Valor_BCD & 0x0000000F) + '0');
		Valor_BCD=Valor_BCD>>4;
	}
}
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

