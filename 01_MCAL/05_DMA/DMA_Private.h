/*
 * DMA_Private.h
 *
 *  Created on: Jul 20, 2022
 *      Author: Shady Magdy
 */

#ifndef MCAL_DMA_PRIVATE_H_
#define MCAL_DMA_PRIVATE_H_

#include "STD_TYPES.h"
/***********************************************************************************
	-----> Macros
			*
************************************************************************************/

/* Struct For DMA Stream We Have 8 Stream  Every one have This Register*/
typedef struct
{
	volatile u32 CR;
	volatile u32 NDTR;
	volatile u32* PAR;
	volatile u32* M0AR;
	volatile u32* M1AR;
	volatile u32 FCR;

}DMA_Stream_t ;

/* DMA_Register */
typedef struct
{
	volatile u32 LISR 		 ;
	volatile u32 HISR		 ;
	volatile u32 LIFCR 		 ;
	volatile u32 HIFCR 		 ;
	DMA_Stream_t StreamID[8]  ; /* We Have 8 Copy of  Stream*/
}DMA_CFG_t;


#define DMA2		((volatile DMA_CFG_t *)0X40026400)  /* Pointer To Struct Of DMA Type*/
#define DMA1		((volatile DMA_CFG_t *)0X40026000)  /* Pointer To Struct Of DMA Type*/





#endif /* MCAL_DMA_PRIVATE_H_ */
