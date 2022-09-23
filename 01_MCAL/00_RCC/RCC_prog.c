/*=======================================================================================
============================   - RCC_program.c				 ============================
============================   - Created: 6/9/2022			 ============================
============================   - Author: Shady_Magdy   ============================
============================   - Version : _1_				 ============================
============================   - Note :  
									     *-
									     *-
=======================================================================================*/ 
/***
 *      _____   _____ _____            _____  _____   ____   _____ _____            __  __ 
 *     |  __ \ / ____/ ____|          |  __ \|  __ \ / __ \ / ____|  __ \     /\   |  \/  |
 *     | |__) | |   | |       ______  | |__) | |__) | |  | | |  __| |__) |   /  \  | \  / |
 *     |  _  /| |   | |      |______| |  ___/|  _  /| |  | | | |_ |  _  /   / /\ \ | |\/| |
 *     | | \ \| |___| |____           | |    | | \ \| |__| | |__| | | \ \  / ____ \| |  | |
 *     |_|  \_\\_____\_____|          |_|    |_|  \_\\____/ \_____|_|  \_\/_/    \_\_|  |_|
 *                                                                                         
 *                                                                                         
 */
/*=======================================================================================
============================   The Foundation Of Function   ============================= 
=========================================================================================*/

/*===========   INCLUDE LIB   ===========*/
		 #include "STD_TYPES.h"
		 #include "BIT_MATH.h"
/*======================================*/	 
/*===========  INCLUDE MCAL  ===========*/
		#include "RCC_private.h"
		#include "RCC_interface.h"
		#include "RCC_config.h"
/*======================================*/	
/*===========  INCLUDE HAL   ===========*/
			

/*======================================*/	

/*===========  INCLUDEAPP   ===========*/

/*=====================================*/	




/*====================================================   Start_FUNCTION   ====================================================*/
 /*
	- Function To Enable Prepheral :
	
							       - BusName_t      :  The Bus Of The Prepheral ( AHB1 , AHB2 , APB1 , APB2 ) Every One Detect Which REG To Choice Pripheral From It
							       - Copy_u8PerName :  The Order Of Prepheral On The Selected Reg 
	
*/


void MRCC_vEnableClock(BusName_t BusName , u8 Copy_u8PerNum )
{
	
	switch(BusName)
	{
		case AHB1_BUS:  SET_BIT(RCC_AHB1ENR,Copy_u8PerNum );         break ;
		case AHB2_BUS:  SET_BIT(RCC_AHB2ENR,Copy_u8PerNum );         break ;
		case APB1_BUS:  SET_BIT(RCC_APB1ENR,Copy_u8PerNum );         break ;
		case APB2_BUS:  SET_BIT(RCC_APB2ENR,Copy_u8PerNum );         break ;
		default :     /*   ERROR   */          break ;
		
	}
	
	
}
/*====================================================   END_ FUNCTION   ====================================================*/
/*====================================================   Start_FUNCTION   ====================================================*/

 /*
	- Function To Disable Prepheral :
	
							       - BusName_t      :  The Bus Of The Prepheral ( AHB1 , AHB2  , APB1 , APB2 ) Every One Detect Which REG To Choice Pripheral From It
							       - Copy_u8PerName :  The Order Of Prepheral On The Selected Reg 
	
*/

void MRCC_vDisableClock(BusName_t BusName , u8 Copy_u8PerNum )
{
	switch(BusName)
	{
		case AHB1_BUS:  CLR_BIT(RCC_AHB1ENR,Copy_u8PerNum );         break ; 
		case AHB2_BUS:  CLR_BIT(RCC_AHB2ENR,Copy_u8PerNum );         break ; 
		case APB1_BUS:  CLR_BIT(RCC_APB1ENR,Copy_u8PerNum );         break ; 
		case APB2_BUS:  CLR_BIT(RCC_APB2ENR,Copy_u8PerNum );         break ; 
		default :     /* ERROR */          break ;
		
	}
}
/*====================================================   END_ FUNCTION   ====================================================*/
/*====================================================   Start_FUNCTION   ====================================================*/

/*
* Function To Enable Security System
*/

void MRCC_vEnableSecuritySystem(void)
{
	SET_BIT( RCC_CR  , 19U);
	
}
/*====================================================   END_ FUNCTION   ====================================================*/
/*====================================================   Start_FUNCTION   ====================================================*/
/*
* Function To Disable Security System
*/

void MRCC_vDisableSecuritySystem(void)
{
	CLR_BIT( RCC_CR  , 19U);
	
}
/*====================================================   END_ FUNCTION   ====================================================*/
/*====================================================   Start_FUNCTION   ====================================================*/
/* About The Function :
	
				- CLK		: HSE | HSI |PLL	
				- PLLSrc	:PLL_HSE | PLL_HSI
				- HSESrc    :HSE_Crystal ,HSE_RC 
 */

void MRCC_vInitSystemCLK(void)
{
	
	/********** HSI **********/
#if CLKSRC == HSI 
	
	/* 1- CLK SYS --> HSI */
	CLR_BIT(MRCC->CFGR, 0U);
	CLR_BIT(MRCC->CFGR, 1U);
	/* 2- EN HSI */
	SET_BIT(MRCC->CR , 0U);
	/* 3- Wait */
	/*
		while( ( ( GET_BIT( MRCC->CR , 1 ) ) == 0 ) && ( LOC_u32TimeOut < 100000 ) ){ LOC_u32TimeOut++; }
		if( LOC_u32TimeOut >= 100000 ){ TimeOut }*/
		
	/********** HSE **********/
#elif CLKSRC == HSE

	#if HSE_SRC == CRYSTAL 
		/* 1- CLK SYS --> HSE */
		 SET_BIT(MRCC->CFGR, 0U);
		 CLR_BIT(MRCC->CFGR, 1U);
		 /*2_ CNFG HSE Crystal */
		 CLR_BIT(MRCC->CR, 18U);
		 /* 3- Enable HSE */
		 SET_BIT(MRCC->CR , 16U);
		 /*4- Wait */
		while((( GET_BIT( MRCC->CR , 17 ) ) == 0 )) {}

/*****************************************************************/
	#elif HSE_SRC == RC 
		/* 1- CLK SYS --> HSE */
		 SET_BIT(MRCC->CFGR, 0U);
		 CLR_BIT(MRCC->CFGR, 1U);
		 /*2_ CNFG HSE RC */
		SET_BIT(MRCC->CR, 18U);
		 /* 3- Enable HSE */
		 SET_BIT(MRCC->CR , 16U);
		 /*4- Wait */
		while( ( ( GET_BIT( MRCC->CR , 17 ) ) == 0 ) ;

	#else 
    /* Error*/
	#endif
	

	/********** PLL **********/
#elif CLKSRC == PLL	
  /*****************************************************************/
    #if PLL_SRC == _HSE_PLL 
			/*1-Enable HSE */
			SET_BIT(MRCC->CR,16U);
			/* while ( GET_BIT(RCC_CR, 17)==0);*/
			/*2- Disable PLL*/
			CLR_BIT(MRCC->CR,24U);
			/* while ( GET_BIT(RCC_CR, 25)==0);*/
			/* 3- PLL From HSE */
			SET_BIT(MRCC->PLLCFGR, 22U);
			
			/* 4- System Clk  PLL */
			CLR_BIT(MRCC->CFGR,0U);
			SET_BIT(MRCC->CFGR,1U);
			/*5- Enable PLL*/
			SET_BIT(MRCC->CR,24U);
			/*************************/
				#if HSE_SRC == RC
					/* - Enable BYP */
					SET_BIT(MRCC->CR,18U);
				#elif HSE_SRC == CRYSTAL
					/*- Disable BYP */
					CLR_BIT(MRCC->CR,18U);
				#else
					/*	ERROR	*/
				#endif
 /*****************************************************************/
    #elif PLL_SRC == _HSI_PLL  
            /*Enable HSI */
		     SET_BIT(MRCC->CR,0U);
		     /*2- Disable PLL*/
		     CLR_BIT(MRCC->CR,24U);
			/* 3- PLL From HSI */
			CLR_BIT(MRCC->PLLCFGR, 22U);
			/*4- Enable PLL*/
			SET_BIT(MRCC->CR,24U);
			/* 5- System Clk  PLL */
			CLR_BIT(MRCC->CFGR,0U);
			SET_BIT(MRCC->CFGR,1U);
    #else 
            /* Error*/
	#endif
/****************************************************/

#else 
/* Error*/
#endif // The End Of Big IF	
}
/*====================================================   END_ FUNCTION   ====================================================*/

/*====================================================   Start_FUNCTION   ====================================================*/


 void MRCC_vOutMCO_1(u8 Copy_u8MC1_0SRC )
{
 switch(Copy_u8MC1_0SRC)
 {
		case MC0_1_LSE : 
				CLR_BIT(RCC_CFGR , 22);
				SET_BIT(RCC_CFGR , 21);
		break  ;
		/*********/
		case MC0_1_HSE  :
		
				CLR_BIT(RCC_CFGR , 21);
				SET_BIT(RCC_CFGR , 22);
		break  ;
		/*********/
		case MC0_1_HSI  :
				CLR_BIT(RCC_CFGR , 21);
				CLR_BIT(RCC_CFGR , 22);
		break  ;
		/*********/
		case  MC0_1_PLL :
				SET_BIT(RCC_CFGR , 21);
				SET_BIT(RCC_CFGR , 22);
		break  ;
		default :   /* ERROR*/ break ;
	
	
 }

}



/*====================================================   END_ FUNCTION   ====================================================*/
/*====================================================   Start_FUNCTION   ====================================================*/


void MRCC_vOutMCO_1Pre(MCO_1_Pre_t Copy_tPreMco_1 )
{
	switch (Copy_tPreMco_1 )
	{
	 case MCO_1_Div_1 :	 
	       CLR_BIT(RCC_CFGR , 26);
	 break ; 
	 case MCO_1_Div_2 :	 
		   CLR_BIT(RCC_CFGR , 24);
		   CLR_BIT(RCC_CFGR , 25);
	       SET_BIT(RCC_CFGR , 26);
	 break ; 
	 case MCO_1_Div_3 :	 
		   SET_BIT(RCC_CFGR , 24);
		   CLR_BIT(RCC_CFGR , 25);
	       SET_BIT(RCC_CFGR , 26);
	 break ; 
	  case MCO_1_Div_4 :	 
		   CLR_BIT(RCC_CFGR , 24);
		   SET_BIT(RCC_CFGR , 25);
	       SET_BIT(RCC_CFGR , 26);
	 break ; 
	  case MCO_1_Div_5 :	 
		   SET_BIT(RCC_CFGR , 24);
		   SET_BIT(RCC_CFGR , 25);
	       SET_BIT(RCC_CFGR , 26);
	 break ; 
		
	}

}

/*====================================================   END_ FUNCTION   ====================================================*/


/*
Function to prescale AHB/2

*/
void MRCC_vAHBdiv2(void )
{
	//select AHB prescaller by 2
	SET_BIT(MRCC->CFGR,7U);
	CLR_BIT(MRCC->CFGR,6U);
	CLR_BIT(MRCC->CFGR,5U);
	CLR_BIT(MRCC->CFGR,4U);
	
}

