/*
 * ADC_Private.h
 *
 *  Created on: Sep 21, 2022
 *      Author: Shady Magdy
 */

#ifndef MCAL_ADC_ADC_PRIVATE_H_
#define MCAL_ADC_ADC_PRIVATE_H_

#define ADC1_BASE_ADDRESS 				0x40012000
typedef struct
{
	volatile u32 SR   ;
	volatile u32 CR1  ;
	volatile u32 CR2  ;
	volatile u32 SMPR1;
	volatile u32 SMPR2;
	volatile u32 JOFR1;
	volatile u32 JOFR2;
	volatile u32 JOFR3;
	volatile u32 JOFR4;
	volatile u32 HTR  ;
	volatile u32 LTR  ;
	volatile u32 SQR1 ;
	volatile u32 SQR2 ;
	volatile u32 SQR3 ;
	volatile u32 JSQR ;
	volatile u32 JDR[4] ;
	volatile u32 DR   ;
}ADC_TypeDef;

#define    ADC1						   ((ADC_TypeDef*)(ADC1_BASE_ADDRESS))


#define    ADC1_CCR                    (*((volatile u32 *)(ADC1_BASE_ADDRESS)(ADC1_BASE_ADDRESS+ 0x300+0x04)))
#endif /* MCAL_ADC_ADC_PRIVATE_H_ */
