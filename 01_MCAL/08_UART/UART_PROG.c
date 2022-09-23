/*=======================================================================================
==========================  - UART_program.c				 ============================
==========================  - Created: 3/22/2022			 ============================
==========================  - Author: Shady_Magdy      ============================
==========================  - Version : _1_				     ============================
==========================  - Note :
									*-
									*-
=======================================================================================*/


/*=======================================================================================
============================   The Foundation Of Function   =============================
=========================================================================================*/

/*===========   INCLUDE LIB   ===========*/
		 #include "STD_TYPES.h"
		 #include "BIT_MATH.h"
/*======================================*/
/*===========  INCLUDE MCAL  ===========*/
		#include "UART_PRIVATE.h"
		#include "UART_INTERFACE.h"
		#include "UART_CFG.h"
		#include "UART_ENUMS.h"
/*======================================*/
/*===========  INCLUDE HAL   ===========*/


/*======================================*/

/*===========  INCLUDEAPP   ===========*/

/*=====================================*/



/* */
void (*MUSART1_CallBack)(void);

/*====================================================   Start_FUNCTION   ====================================================*/
/******************************************************************************
* \Syntax          : void MUART_vInit(void)
* \Description     :
* \Sync\Async      :
* \Reentrancy      :
* \Parameters (in) :
* \Parameters (out):
* \Return value:   :
*******************************************************************************/
void MUART_vInit(void){

	/*===========	UART_1	 ===========*/
#if (UART1_USED == U_ENABLE)
	UART1_REG ->CR1.SBK 	= 	UART1_SEND_BREAK;
	UART1_REG ->CR1.RE 		= 	UART1_RECEIVER;
	UART1_REG ->CR1.TE 		= 	UART1_TRANSMITTER;
	UART1_REG ->CR1.RXNEIE 	= 	UART1_RX_INT;
	UART1_REG ->CR1.TCIE 	= 	UART1_T_COMP_INT;
	UART1_REG ->CR1.PCE 	= 	UART1_PARITY_ENABLE;
	UART1_REG ->CR1.PS 		= 	UART1_PARITY_MODE;
	UART1_REG ->CR1.M 		= 	UART1_WORD_LEN;
	UART1_REG ->CR1.OVER8 	= 	UART1_OVER_SAMPLING;
	UART1_REG ->BRR 		= 	UART1_BUAD_RATE;
	UART1_REG ->CR2 		|= (UART1_STOP_BITS <<12);
#endif

   /*===========	UART_2	 ===========*/
#if (UART2_USED == U_ENABLE)
	UART2_REG ->CR1.SBK 	= 	UART2_SEND_BREAK;
	UART2_REG ->CR1.TE 		= 	UART2_TRANSMITTER;
	UART2_REG ->CR1.RXNEIE 	= 	UART2_RX_INT;
	UART2_REG ->CR1.RE 		= 	UART2_RECEIVER;
	UART2_REG ->CR1.TCIE 	= 	UART2_T_COMP_INT;
	UART2_REG ->CR1.PCE 	= 	UART2_PARITY_ENABLE;
	UART2_REG ->CR1.PS 		= 	UART2_PARITY_MODE;
	UART2_REG ->CR1.M 		= 	UART2_WORD_LEN;
	UART2_REG ->CR1.OVER8 	= 	UART2_OVER_SAMPLING;
	UART2_REG ->BRR 		= 	UART2_BUAD_RATE;
	UART2_REG ->CR2 		|= (UART2_STOP_BITS <<12);
#endif

   /*===========	UART_6	 ===========*/
#if (UART6_USED == U_ENABLE)
	UART6_REG ->CR1.SBK 	= 	UART6_SEND_BREAK;
	UART6_REG ->CR1.TE 		= 	UART6_TRANSMITTER;
	UART6_REG ->CR1.RXNEIE 	= 	UART6_RX_INT;
	UART6_REG ->CR1.RE 		= 	UART6_RECEIVER;
	UART6_REG ->CR1.TCIE 	= 	UART6_T_COMP_INT;
	UART6_REG ->CR1.PCE 	= 	UART6_PARITY_ENABLE;
	UART6_REG ->CR1.PS 		= 	UART6_PARITY_MODE;
	UART6_REG ->CR1.M 		= 	UART6_WORD_LEN;
	UART6_REG ->CR1.OVER8 	= 	UART6_OVER_SAMPLING;
	UART6_REG ->BRR 		= 	(0x3)|(0x68<<4);;;;;;;;;;;;;;;;
	UART6_REG ->CR2 		|= (UART6_STOP_BITS <<12);
#endif
}

/*====================================================   END_ FUNCTION   ====================================================*/
/*====================================================   Start_FUNCTION   ====================================================*/
/*	Function :
*
*/
void MUART_vEnable(u8 copy_u8Index)
{
	UART_REG ptr = MUART_GetHandler(copy_u8Index);
	ptr ->CR1.UE = 1;
}
/*====================================================   END_ FUNCTION   ====================================================*/
/*====================================================   Start_FUNCTION   ====================================================*/
/*	Function :
*
*/
void MUART_vDisable(u8 copy_u8Index){
	UART_REG ptr = MUART_GetHandler(copy_u8Index);
	ptr ->CR1.UE = 0;
}
/*====================================================   END_ FUNCTION   ====================================================*/
/*====================================================   Start_FUNCTION   ====================================================*/
/*	Function :
*
*/
void MUART_u8SendData(u8 copy_u8Index, u8* copy_u8Data){
	UART_REG ptr = MUART_GetHandler(copy_u8Index);
	ptr->CR1.UE = 1;
	while(GET_BIT(ptr->SR,7)==0);
	ptr ->DR = *copy_u8Data;
	while(GET_BIT(ptr->SR,6)==0);

}
/*====================================================   END_ FUNCTION   ====================================================*/
/*====================================================   Start_FUNCTION   ====================================================*/
/*	Function :
*
*/
u8 MUART_u8ReadData(u8 copy_u8Index){
	UART_REG ptr = MUART_GetHandler(copy_u8Index);
	ptr->CR1.UE = 1;
	u8 Local_u8data = 0;
	while(!GET_BIT(ptr->SR,5));
	Local_u8data = ptr->DR;
	return Local_u8data;
}
/*====================================================   END_ FUNCTION   ====================================================*/
/*====================================================   Start_FUNCTION   ====================================================*/
/*	Function :
*
*/
UART_REG MUART_GetHandler(u8 copy_u8Index){
	UART_REG ptr =0;
	switch (copy_u8Index)
	{
		case UART_1 : ptr = (UART_REG) UART1_BASE_ADDRESS; 		break;
		case UART_2 : ptr = (UART_REG) UART2_BASE_ADDRESS; 		break;
		case UART_6 : ptr = (UART_REG) UART6_BASE_ADDRESS; 		break;
		default:break;
	}
	return ptr;
}
/*====================================================   END_ FUNCTION   ====================================================*/

/*====================================================   Start_FUNCTION   ====================================================*/
/*	Function :
*
*/

void MUSART1_VidSetCallBack( void (*ptr) (void) ){
    /* */
	MUSART1_CallBack = ptr ;

}
/*====================================================   END_ FUNCTION   ====================================================*/
/*====================================================   Start_FUNCTION   ====================================================*/
/*	Function :
*
*/
void USART1_IRQHandler(void){
    /* */
	UART1_REG -> SR = 0 ;
	/* */
	MUSART1_CallBack();

}
/*====================================================   END_ FUNCTION   ====================================================*/
/*====================================================   Start_FUNCTION   ====================================================*/


