/****************************************************************
 ************   - STK_program.c                ******************
 ***********    - Created: 5/19/2022		   ******************
 ***********    - Author: Shady_Magdy    ******************
 ***********    - Version : _1_				   ******************
 ***********  -								   ******************
 ****************************************************************/ 
#include "STD_TYPES.h"
#include "BIT_MATH.h"


#include "STK_interface.h"
#include "STK_private.h"
#include "STK_config.h"

/* Global Var Take Function address */
void (  * MSTK_CallBack )(void) = 0U;
/* Global Var To set Mode */
volatile u8 G_u8Set_Mode   = 0U;
volatile u8 G_GetFlag =0;
/* ProtoType of Handler of SysTick */
void SysTick_Handler(void);

/********************************************************** Start_FUNCTION  **********************************************************/
/*
	Function Only Apply The Clock From Configer (AHB or( AHB/8---> 1MHZ) So 1 = 1Msec & Disable SysTick Interrupt & Disa-ble SysTick
*/
void MSTK_vInit(void)
{
	

	#if _MSTK_CLK_SRC == _MSTK_CLK_AHB   
		/*  Disable Counter , CLK_SRC --> AHB ,  Disable INT */
		CLR_BIT( MSTK -> CTRL , 0  ) ;
		CLR_BIT( MSTK -> CTRL , 1  ) ;
		SET_BIT( MSTK -> CTRL , 2  ) ;
	
	#elif _MSTK_CLK_SRC == _MSTK_CLK_AHB_8
		/*  Disable Counter , CLK_SRC --> AHB/8 ,  Disable INT */
		CLR_BIT( MSTK -> CTRL , 0  ) ;
		CLR_BIT( MSTK -> CTRL , 1  ) ;
		CLR_BIT( MSTK -> CTRL , 2  ) ;
	#endif
	
	
}
/*********************************************************** END_ FUNCTION   *********************************************************/


/********************************************************** Start_FUNCTION  **********************************************************/
void MSTK_vBusyWait(u32 Copy_u32TicksNUM)
{
	
	/* 1) Load val in Load REG */
	MSTK -> LOAD = (Copy_u32TicksNUM*5000) ;
	/* 2) Start Timer  */
	MSTK ->CTRL |=1<<0;
	/* 3) Wait Flag = 1*/
	while( GET_BIT(MSTK ->CTRL,16 )  == 0){}
	/* 4) Stop Timer */
	MSTK -> LOAD = 0;
	MSTK -> VAL = 0;
	CLR_BIT( MSTK -> CTRL , 0);
	
	
}

/*********************************************************** END_ FUNCTION   *********************************************************/


/********************************************************** Start_FUNCTION  **********************************************************/

u32 MSTK_u32GetRemainingTime(void)
{
	
	u32 L_u32Remaning = 0 ;
	L_u32Remaning = MSTK ->VAL ;
	return L_u32Remaning ;

}
/*********************************************************** END_ FUNCTION   *********************************************************/


/********************************************************** Start_FUNCTION  **********************************************************/
u32 MSTK_u32GetElapsedTime(void)
{
	
	u32 L_u32Elapsed = 0 ;
	L_u32Elapsed = ((MSTK ->LOAD) - (MSTK -> VAL)) ;
	return L_u32Elapsed ;
	
	
}
/*********************************************************** END_ FUNCTION   *********************************************************/


/********************************************************** Start_FUNCTION  **********************************************************/


/*  5- Function To Enable Interrupt */
void MSTK_vEnableINT(void)
{
	SET_BIT( MSTK -> CTRL , 1);
	
}

/*********************************************************** END_ FUNCTION   *********************************************************/


/********************************************************** Start_FUNCTION  **********************************************************/


/*  6- Function To Disable Interrupt */
void MSTK_vDisableINT(void)
{
	
	CLR_BIT( MSTK -> CTRL , 1);
	
}

/*********************************************************** END_ FUNCTION   *********************************************************/


/********************************************************** Start_FUNCTION  **********************************************************/






/* - The Same Of Function (3) But Only Differant At ISR Will Not Mack Load And Value = 0 */
			 /*  Send Time To Clock it And What Will Call After Time Finsh   */						
		      /* Global Var Take Adress Of Function And
										After Time Out ISR Call The Global_Var Which Point To Function  
*/
void MSTK_vSetIntervalPeriodic(u32 Copy_u32TicksNUM , void (* ptr)(void))
{
	/* 1) Load ptr in MSTK_CallBack */
	MSTK_CallBack=ptr;
	
	/* 2) Choose Mode PERIODIC  */
	G_u8Set_Mode=_MODE_PERIODIC;

	/* 3) Enable The Interrupt */
	SET_BIT( MSTK -> CTRL , 1);

	/* 4) Load val in Load REG */
	MSTK -> LOAD = (Copy_u32TicksNUM*5000) ;
	
	/* 5) Start Timer  */
	MSTK ->CTRL |=1<<0;
	
}

/*********************************************************** END_ FUNCTION   *********************************************************/


/********************************************************** Start_FUNCTION  **********************************************************/

/* 	- Function Asynchronous Take Tick And Start To Count Them , Give Flag And Work One Time ,
		And Give Me Function And i Will Resive In Pointer To Function To Call it After Counting Ticks .
		I Will Tick The Adress Of Function And Give It To Global Var ( Call back )  And ISR D o this Func */				
			/* Only One Time */	
void MSTK_vSetIntervalSingle(u32 Copy_u32TicksNUM , void (* ptr)(void))
{
	/* 1) Load ptr in MSTK_CallBack */
	MSTK_CallBack=ptr;
	
	/* 2) Choose Mode SINGLE  */
	G_u8Set_Mode=_MODE_SINGLE;

	/* 3) Enable The Interrupt */
	SET_BIT( MSTK -> CTRL , 1);

	/* 4) Load val in Load REG */
	MSTK -> LOAD = (Copy_u32TicksNUM*5000) ;
	
	/* 5) Start Timer  */
	MSTK ->CTRL |=1<<0;
	

}


/*********************************************************** END_ FUNCTION   *********************************************************/


/********************************************************** Start_FUNCTION  **********************************************************/


/*  9-  Function Will Stop The Interval If It Was Periodic Or Single*/
void MSTK_voidStopInterval(void) 
{

	/* 1) Disable The Interrupt */
	CLR_BIT( MSTK -> CTRL , 1);	
	
	/* 2) Stop Timer */
	MSTK -> LOAD = 0;
	MSTK -> VAL = 0;
	CLR_BIT( MSTK -> CTRL , 0);
	
	
}

/*********************************************************** END_ FUNCTION   *********************************************************/

/********************************************************** Start_FUNCTION  **********************************************************/

void SysTick_Handler(void)
{
	G_GetFlag = GET_BIT(MSTK ->CTRL,16 );
	if (G_u8Set_Mode==_MODE_SINGLE)
	{
	    /* 1) Disable The Interrupt */
	    CLR_BIT( MSTK -> CTRL , 1);	
	    
	    /* 2) Stop Timer */
		MSTK -> LOAD = 0;
		MSTK -> VAL = 0;
	    CLR_BIT( MSTK -> CTRL , 0);
	}
	MSTK_CallBack();
}

/*********************************************************** END_ FUNCTION   *********************************************************/








