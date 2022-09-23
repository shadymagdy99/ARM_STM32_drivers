/*
   Author : Shady Magdy
   
   Version: V1
*/

#ifndef SYSCFG_PRIVATE_H
#define SYSCFG_PRIVATE_H 

#define SYSCFG_BASE_ADDRESS     0x40013800



typedef struct
{
	volatile u32 MEMRMP ;
	volatile u32 PMC    ;
	volatile u32 EXTICR[4];
	volatile u32 RESERVED[2];
	volatile u32 CMPCR;
}SYSCFG_t;


#define MSYSCFG       ((  SYSCFG_t *) SYSCFG_BASE_ADDRESS)



#endif
