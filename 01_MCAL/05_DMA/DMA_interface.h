/*
 * DMA_interface.h
 *
 *  Created on: Jul 20, 2022
 *      Author: Shady Magdy
 */

#ifndef MCAL_DMA_INTERFACE_H_
#define MCAL_DMA_INTERFACE_H_

#include "STD_TYPES.h"

/* Function To Init DMA : */
void MDMA_2_u8StreamInit(void);

/* Function :	To Set Addrese Of Source & Distination*/
void MDMA_2_voidSetAdresses(u32* const Ptr_SrcAdd ,u32* const Ptr_DisAdd ,u16 Copy_u32Size  );

/* Function :	To EN_DMA */
void MDMA_2_voidEnable(void) ;

void MDMA_2_Stream0_CallBack (void(*ptr)(void));

#endif /* MCAL_DMA_INTERFACE_H_ */
