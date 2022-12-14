/*
 * ADC.h
 *
 *  Created on: sep 21, 2022
 *      Author: Shady Magdy
 */

#ifndef MCAL_ADC_ADC_H_
#define MCAL_ADC_ADC_H_

#define ADC_SR_EOC						(1U<<1)

#define ADC_CR1_EOCIE					(1U<<5)
#define ADC_CR1_RES_12						(0U<<24)
#define ADC_CR1_RES_10						(1U<<24)
#define ADC_CR1_RES_8						(2U<<24)
#define ADC_CR1_RES_6						(3U<<24)
#define ADC_CR2_ADON						(1U<<0)
#define ADC_CR2_CONT						(1U<<1)
#define ADC_CR2_SWSTART						(1U<<30)
#define ADC_SQ1_ADC_L_1						(0<<20)
void ADC_Init(void);
u16 ADC_Read(void);



#endif /* MCAL_ADC_ADC_H_ */
