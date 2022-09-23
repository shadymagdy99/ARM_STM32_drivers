
/*=======================================================================================
============================   The Foundation Of Function   =============================
=========================================================================================*/

/*===========   INCLUDE LIB   ===========*/
		 #include "LIB/Std_Types.h"
		 #include "LIB/Bit_Math.h"
/*======================================*/
/*===========  INCLUDE MCAL  ===========*/
		#include "MCAL/ADC/ADC_Private.h"
		#include "MCAL/ADC/ADC.h"
		#include "MCAL/ADC/ADC_Config.h"
/*======================================*/
/*===========  INCLUDE HAL   ===========*/


/*======================================*/

/*===========  INCLUDEAPP   ===========*/

/*=====================================*/


/*====================================================   Start_FUNCTION   ====================================================*/
void ADC_Init(void)
{
	//ADC1->CR1 |= ADC_CR1_EOCIE;		//interrupt enable on end of conv.
	//ADC1->CR1 |= ADC_CR1_RES_12;	//Resolution
	//ADC1->CR2 |= (1U<<1); //Cont. Conv.
	ADC1->SQR1 = 0; //Sequence Length
	ADC1->SQR3 |=(1U<<0);	//channel 1 is first in sequence
	//ADC1->CR1  |= (1U<<8);
	ADC1->CR2 |= 1U ;	//adc ON

}
u16 ADC_Read(void)
{
	ADC1->CR2 |= (1U<<30);//start
	while(!((ADC1->SR) & (1U<<1)));
	return (ADC1->DR);
}
