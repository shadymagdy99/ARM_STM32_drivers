/*
   Author : Shady Magdy

   Version: V1
*/
/***
 *      ________   _________ _____            _____  _____  _______      __  _______ ______ 
 *     |  ____\ \ / /__   __|_   _|          |  __ \|  __ \|_   _\ \    / /\|__   __|  ____|
 *     | |__   \ V /   | |    | |    ______  | |__) | |__) | | |  \ \  / /  \  | |  | |__   
 *     |  __|   > <    | |    | |   |______| |  ___/|  _  /  | |   \ \/ / /\ \ | |  |  __|  
 *     | |____ / . \   | |   _| |_           | |    | | \ \ _| |_   \  / ____ \| |  | |____ 
 *     |______/_/ \_\  |_|  |_____|          |_|    |_|  \_\_____|   \/_/    \_\_|  |______|
 *                                                                                          
 *                                                                                          
 */

#ifndef EXTI_PRIVATE_H
#define EXTI_PRIVATE_H



typedef struct
{
	volatile u32   IMR;
    volatile u32   EMR;
    volatile u32   RTSR;
    volatile u32   FTSR;
    volatile u32   SWIER;
    volatile u32   PR;
}EXTI_t;


#define EXTI  ((volatile EXTI_t*)0x40013C00)







#endif
