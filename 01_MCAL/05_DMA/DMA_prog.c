/*
 * DMA_prog.c
 *
 *  Created on: Jul 20, 2022
 *      Author: Shady Magdy
 */


#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DMA_interface.h"
#include "DMA_Private.h"
#include "DMA.config.h"

/********************************************************** Start_FUNCTION  **********************************************************/
/*		Function :
					*/
void (*DMA2_CallBack)(void)=NULL;

void MDMA_2_u8StreamInit(void)
{

	/* 1- Before Any Config The Bit Of EN Must = 0 ,It must Be Disable*/
	/* Use Stream NUM = 0 */
	/* If Enable Bit == 1 */

	if( GET_BIT(DMA2 ->StreamID[0].CR  , 0U) )
	{
		CLR_BIT(DMA2 ->StreamID[0].CR  , 0U);
		/* 2) Wait */
		while( GET_BIT(DMA2 ->StreamID[0].CR  , 0U)) ;


	}
	//DMA2 ->StreamID[0].CR =0X35680;
	/* 3. Select the DMA channel (request) using CHSEL[2:0] in the DMA_SxCR register */

	/* 4-SoftWare Priority Stream :{ LOW , Medium , High , VeryHigh} BIT(16 , 17)---> VeryHigh  */

	SET_BIT(DMA2 ->StreamID[0].CR  , 16U);
	SET_BIT(DMA2 ->StreamID[0].CR  , 17U);


	/* 5- Set DIR Mode :{ MTM ,PTM ,MTP} BIT (6,7)  -- >MTM */

	SET_BIT(DMA2 ->StreamID[0].CR  , 7U);
	CLR_BIT(DMA2 ->StreamID[0].CR  , 6U);

	/* 6- Set M & M SIZE BIT(13,14) ,(11,12) :{Byte , HaveWord , Word}*/
	/* 	As Word 32 For Source	*/

	SET_BIT(DMA2 ->StreamID[0].CR  , 12U);
	CLR_BIT(DMA2 ->StreamID[0].CR  , 11U);
	SET_BIT(DMA2 ->StreamID[0].CR  , 14U);
	CLR_BIT(DMA2 ->StreamID[0].CR  , 13U);


	/* 7- Disable Direct Mode */
	SET_BIT(DMA2 ->StreamID[0].FCR  , 2U);


	/* 8-Set FIFO Threshold {(1/4),(1/2),(3/4),full} */
	/* Use FULL*/
	SET_BIT(DMA2 ->StreamID[0].FCR  , 1U);
	SET_BIT(DMA2 ->StreamID[0].FCR  , 0U);


	/* 9-SRC & DIS Increament For Both */
	CLR_BIT(DMA2 ->StreamID[0].CR  , 15U);
	SET_BIT(DMA2 ->StreamID[0].CR  , 10U);
	SET_BIT(DMA2 ->StreamID[0].CR  , 9U);


	/* 10- EN Interrput Of Transfer Complete */
	//SET_BIT(DMA2 ->StreamID[0].CR  , 4U);



}

/*********************************************************** END_ FUNCTION   *********************************************************/


/********************************************************** Start_FUNCTION  **********************************************************/
/*		Function :	To Set Addrese Of Source & Distination
					*/
void MDMA_2_voidSetAdresses(u32* const Ptr_SrcAdd ,u32* const Ptr_DisAdd ,u16 Copy_u32Size  )
{
	/* Source Add */
	DMA2 ->StreamID[0].PAR=Ptr_SrcAdd;

	/* Distination Add */
	DMA2 ->StreamID[0].M0AR=Ptr_DisAdd;

	/* Size */
	DMA2 ->StreamID[0].NDTR=Copy_u32Size;

}
/*********************************************************** END_ FUNCTION   *********************************************************/


/********************************************************** Start_FUNCTION  **********************************************************/
/*		Function :	Enable DMA
					*/
void MDMA_2_voidEnable(void)
{
	/* All Flag == 0 or make them =0 */
	DMA2->LIFCR|=((1<<0)|(1<<2)|(1<<3)|(1<<4)|(1<<5));
	/* EN Bit One Way To Stearm */


	SET_BIT(DMA2 ->StreamID[0].CR  , 4U);
	SET_BIT(DMA2 ->StreamID[0].CR  , 0U);


}

void MDMA_2_Stream0_CallBack(void(*ptr)(void))
{
	DMA2_CallBack=ptr;
}



void DMA2_Stream0_IRQHandler(void)
{
	DMA2->LIFCR|=((1<<0)|(1<<2)|(1<<3)|(1<<4)|(1<<5));
	DMA2_CallBack();
}
