/****
	*STM32F4DISCOVERY
	*wait until the buttom was pushed,the orange LED light 
	*
	*
****/

#include<stdint.h>

#define SET_BIT(addr, bit) *((volatile uint32_t *)(addr)) |= (uint32_t)1 << bit
#define CLEAR_BIT(addr, bit) *((volatile uint32_t *)(addr)) &= ~((uint32_t)1 << bit)
#define READ_BIT(addr,bit) *(volatile uint32_t *)(addr) &((uint32_t)1 << bit)
//#define READ_BIT(addr,bit) (((uint32_t)1 == (*(uint32_t *)(addr) & (uint32_t)1 << bit))?1:0)

//RCC BUTTOM AND ORANGE LED

#define RCC_BASE 0x40023800				
#define RCC_AHB1ENR_OFFSET 0X30
#define GPIODEN_BIT 3
#define GPIOAEN_BIT 0

//GPIO SET
#define GPIOx_MODER_OFFSET 0X00
#define GPIOx_OTYPER_OFFSET 0x04
#define GPIOx_OSPEEDR_OFFSET 0x08
#define GPIOx_PUPDR_OFFSET 0x0C
#define GPIOx_BSRR_OFFSET 0x18
#define GPIOx_IDR_OFFSET 0X10
//LED SET

#define GPIOD_BASE 0x40020C00


#define MODER13_1_BIT 27
#define MODER13_0_BIT 26


#define OT13_BIT 13


#define OSPEEDR13_1_BIT 27
#define OSPEEDR13_0_BIT 26


#define PUPDR13_1_BIT 27
#define PUPDR13_0_BIT 26

#define BR13_BIT 29
#define BS13_BIT 13


//Buttom set
#define GPIOA_BASE 0x40020000

#define IDR_0_BIT  0

#define MODER0_1_BIT 1
#define MODER0_0_BIT 0

//#define OT0_BIT 0



//#define OSPEEDR0_1_BIT 1
//#define OSPEEDR0_0_BIT 0


#define PUPDR0_1_BIT 1
#define PUPDR0_0_BIT 0


#define BR0_BIT 16
#define BS0_BIT 0

void homework(void)
{
	///////////////////
	//set the led bit//
	///////////////////
	
	SET_BIT(RCC_BASE+RCC_AHB1ENR_OFFSET,GPIODEN_BIT);

	//SET MODER13 = 01 =>General purpose output mode
	CLEAR_BIT(GPIOD_BASE+GPIOx_MODER_OFFSET,MODER13_1_BIT);
	SET_BIT(GPIOD_BASE+GPIOx_MODER_OFFSET,MODER13_0_BIT);
    
	//OT15 = 0 => Output push-pull
	CLEAR_BIT(GPIOD_BASE+GPIOx_OTYPER_OFFSET,OT13_BIT);

	//OSPEEDR15 = 00 => Low speed
	CLEAR_BIT(GPIOD_BASE+GPIOx_OSPEEDR_OFFSET,OSPEEDR13_1_BIT);
	CLEAR_BIT(GPIOD_BASE+GPIOx_OSPEEDR_OFFSET,OSPEEDR13_0_BIT);

	//PUPDR15 = 00 => No pull-up, pull-down
	CLEAR_BIT(GPIOD_BASE+GPIOx_PUPDR_OFFSET,PUPDR13_1_BIT);
	CLEAR_BIT(GPIOD_BASE+GPIOx_PUPDR_OFFSET,PUPDR13_0_BIT);


	//////////////////////
	//set the buttom bit// 
	//////////////////////
	
	SET_BIT(RCC_BASE+RCC_AHB1ENR_OFFSET,GPIOAEN_BIT);

	//SET MODER = 00 => buttom input
	CLEAR_BIT(GPIOA_BASE+GPIOx_MODER_OFFSET,MODER0_1_BIT);
	CLEAR_BIT(GPIOA_BASE+GPIOx_MODER_OFFSET,MODER0_0_BIT);

	//SET PUPDR = 11 => RESERVED I/O CONFIGURATION  
	SET_BIT(GPIOA_BASE+GPIOx_PUPDR_OFFSET,PUPDR0_1_BIT);
	SET_BIT(GPIOA_BASE+GPIOx_PUPDR_OFFSET,PUPDR0_0_BIT);


	unsigned int i;
	while(!READ_BIT(GPIOA_BASE+GPIOx_IDR_OFFSET,IDR_0_BIT));
	while(1)
	{	

		if(READ_BIT(GPIOA_BASE+GPIOx_IDR_OFFSET,IDR_0_BIT))
		{
			///reset orange led light

			SET_BIT(GPIOD_BASE+GPIOx_BSRR_OFFSET,BR13_BIT);

			for(i=0;i<100000;i++)
			;
			
			///set orange led light	

			SET_BIT(GPIOD_BASE+GPIOx_BSRR_OFFSET,BS13_BIT);

			for(i=0;i<100000;i++)
			;  
		}	

			
    }
}






