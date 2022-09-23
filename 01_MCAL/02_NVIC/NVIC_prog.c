/*
  Author : Shady Magdy
  Date   : 15-5-2022
  Version: V1  
*/
/***
 *      _   ___      _______ _____            _____  _____   ____   _____ 
 *     | \ | \ \    / /_   _/ ____|          |  __ \|  __ \ / __ \ / ____|
 *     |  \| |\ \  / /  | || |       ______  | |__) | |__) | |  | | |  __ 
 *     | . ` | \ \/ /   | || |      |______| |  ___/|  _  /| |  | | | |_ |
 *     | |\  |  \  /   _| || |____           | |    | | \ \| |__| | |__| |
 *     |_| \_|   \/   |_____\_____|          |_|    |_|  \_\\____/ \_____|
 *                                                                        
 *                                                                        
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "NVIC_interface.h"
#include "NVIC_private.h"
#include "NVIC_config.h"


void MNVIC_vEnableIRQ(IRQn_t Copy_tIRQ)
{
	if(Copy_tIRQ<=31)
	{
		NVIC->ISER[0]=(1U<<Copy_tIRQ);
	}
	else if(Copy_tIRQ<=63)
	{
		Copy_tIRQ-=32;
		NVIC->ISER[1]=(1U<<Copy_tIRQ);
	}
	else if(Copy_tIRQ<=84)
	{
		Copy_tIRQ-=64;
		NVIC->ISER[1]=(1U<<Copy_tIRQ);
	}
	else 
	{
		/*return error*/
	}
}
void MNVIC_vDisableIRQ(IRQn_t Copy_tIRQ)
{
	if(Copy_tIRQ<=31)
	{
		NVIC->ICER[0]=(1U<<Copy_tIRQ);
	}
	else if(Copy_tIRQ<=63)
	{
		Copy_tIRQ-=32;
		NVIC->ICER[1]=(1U<<Copy_tIRQ);
	}
	else if(Copy_tIRQ<=84)
	{
		Copy_tIRQ-=64;
		NVIC->ICER[1]=(1U<<Copy_tIRQ);
	}
	else 
	{
		/*return error*/
	}
}
void MNVIC_vSetPindeng(IRQn_t Copy_tIRQ)
{
	if(Copy_tIRQ<=31)
	{
		NVIC->ISPR[0]=(1U<<Copy_tIRQ);
	}
	else if(Copy_tIRQ<=63)
	{
		Copy_tIRQ-=32;
		NVIC->ISPR[1]=(1U<<Copy_tIRQ);
	}
	else if(Copy_tIRQ<=84)
	{
		Copy_tIRQ-=64;
		NVIC->ISPR[1]=(1U<<Copy_tIRQ);
	}
	else 
	{
		/*return error*/
	}
	
}
void MNVIC_vClearSetPindeng(IRQn_t Copy_tIRQ)
{
	if(Copy_tIRQ<=31)
	{
		NVIC->ICPR[0]=(1U<<Copy_tIRQ);
	}
	else if(Copy_tIRQ<=63)
	{
		Copy_tIRQ-=32;
		NVIC->ICPR[1]=(1U<<Copy_tIRQ);
	}
	else if(Copy_tIRQ<=84)
	{
		Copy_tIRQ-=64;
		NVIC->ICPR[1]=(1U<<Copy_tIRQ);
	}
	else 
	{
		/*return error*/
	}
}

u8 MNVIC_u8GetActiveFlag(IRQn_t Copy_tIRQ)
{
	u8 L_u8GetActiveFlag = 0U;
	if(Copy_tIRQ<=31)
	{
		L_u8GetActiveFlag = GET_BIT(NVIC->IABR[0],Copy_tIRQ);
	}
	else if(Copy_tIRQ<=63)		
	{
		Copy_tIRQ-=32;
		L_u8GetActiveFlag = GET_BIT(NVIC->IABR[1],Copy_tIRQ);
	}
	else if(Copy_tIRQ<=84)
	{
		Copy_tIRQ-=64;
		L_u8GetActiveFlag = GET_BIT(NVIC->IABR[2],Copy_tIRQ);
	}
	else 
	{
		/*return error*/
	}
	return L_u8GetActiveFlag;
}
void MNVIC_vSetGroupPriority(IRQn_t Copy_tIRQ,u8 Copy_u8Group,u8 Copy_u8Sub)
{
	
	SCB_AIRCR=PRI_GROUP;
	#if PRI_GROUP==GROUP16_SUB0
	NVIC->IP[Copy_tIRQ]=((Copy_u8Group<<0)<<(4));
	#elif PRI_GROUP==GROUP8_SUB2            
	NVIC->IP[Copy_tIRQ]=(((Copy_u8Group<<1)|(Copy_u8Sub))<<(4));
	#elif PRI_GROUP==GROUP4_SUB4                                            
	NVIC->IP[Copy_tIRQ]=(((Copy_u8Group<<2)|(Copy_u8Sub))<<(4));
	#elif PRI_GROUP==GROUP2_SUB8                                            
	NVIC->IP[Copy_tIRQ]=(((Copy_u8Group<<3)|(Copy_u8Sub))<<(4));
	#elif PRI_GROUP==GROUP0_SUB16        
	NVIC->IP[Copy_tIRQ]=((Copy_u8Sub)<<(4));
	#endif
	
	
}
