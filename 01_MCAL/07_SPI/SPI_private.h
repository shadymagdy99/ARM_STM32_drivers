#ifndef _SPI_PRIVATE_H
#define _SPI_PRIVATE_H


#define  SPI1_BASE_ADDRESS         0x40013000


typedef struct{
	volatile u32 SPI_CR1;
	volatile u32 Reserved;
	volatile u32 SPI_SR;
	volatile u32 SPI_DR;
	volatile u32 SPI_CRCPR;
	volatile u32 SPI_RXCRCR;
	volatile u32 SPI_TXCRCR;
	volatile u32 SPI_I2SCFGR;
	volatile u32 SPI_I2SPR;
	
}SPI_t;

#defne MSPI1         ((SPI_t    *)(SPI1_BASE_ADDRESS))


























#endif