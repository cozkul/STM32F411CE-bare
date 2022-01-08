#ifndef REGISTER_ADRDRESSES_H
#define REGISTER_ADRDRESSES_H

#include "Types.h"

#define ACCESS(memory)    *((uint32_t volatile *) (memory))
#define ACCESS_16(memory) *((uint16_t volatile *) (memory))
#define ACCESS_8(memory)  *((uint8_t volatile *) (memory))

#define SCB_BASE 0xE000E008UL // (section 4.4 pg 221 of Programming Manual)
#define SCB_CFSR        ACCESS(SCB_BASE + 0x28UL) // (section 4.4.10 pg 237 of Programming Manual)
#define SCB_CPACR       ACCESS(SCB_BASE + 0x88UL) // (section 4.6.1 pg 253 of Programming Manual)

#define FLASH_INTERFACE_BASE 0x40023C00U // (section 2.3 pg 38)
#define FLASH_ACR       ACCESS(FLASH_INTERFACE_BASE + 0x00UL)

#define RCC_BASE 0x40023800UL // (section 2.3 pg 38)
#define RCC_CR          ACCESS(RCC_BASE + 0x00UL)
#define RCC_PLLCFGR     ACCESS(RCC_BASE + 0x04UL)
#define RCC_CFGR        ACCESS(RCC_BASE + 0x08UL)
#define RCC_AHB1ENR     ACCESS(RCC_BASE + 0x30UL)
#define RCC_APB1ENR     ACCESS(RCC_BASE + 0x40UL)

#define PWR_BASE 0x40007000UL // (section 2.3 pg 38)
#define PWR_CR          ACCESS(PWR_BASE + 0x00UL)

#define GPIOC_BASE 0x40020800UL // (section 2.3 pg 38)
#define GPIOC_MODER     ACCESS(GPIOC_BASE + 0x00UL)
#define GPIOC_OTYPER    ACCESS(GPIOC_BASE + 0x04UL)
#define GPIOC_OSPEEDR   ACCESS(GPIOC_BASE + 0x08UL)
#define GPIOC_PUPDR     ACCESS(GPIOC_BASE + 0x0CUL)
#define GPIOC_BSRR      ACCESS(GPIOC_BASE + 0x18UL)

#define TIM2_BASE 0x40000000UL // (section 2.3 pg 38)
#define TIM2_CR1        ACCESS_16(TIM2_BASE + 0x00UL)
#define TIM2_SR         ACCESS_16(TIM2_BASE + 0x10UL)
#define TIM2_CNT        ACCESS(TIM2_BASE + 0x24UL)
#define TIM2_PSC        ACCESS_16(TIM2_BASE + 0x28UL)
#define TIM2_ARR        ACCESS(TIM2_BASE + 0x2CUL)

#endif