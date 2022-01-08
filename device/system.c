#include "Types.h"
#include "RegisterAddresses.h"

uint32_t SystemCoreClock = 96000000;

void system_init(void)
{
      /* FPU settings ------------------------------------------------------------*/
    // Enable FPU  (section 4.6.1 pg 253 of Programming Manual)
    SCB_CPACR |= (0xFUL << 20);  /* set CP10 and CP11 Full Access */

    // Enable HSE (HSEON) (section 6.3.1 pg 103) HSE clock frequency is 25Mhz, declared in compiler options HSE_VALUE.
    RCC_CR |= 1UL << 16;
    // Wait until HSE is ready (HSERDY) (section 6.2.1 pg 95)
    while ((RCC_CR & (1UL << 17)) == 0);

    // Enable PWREN clock on APB1 where power control registers reside (section 6.3.11 pg 118)
    RCC_APB1ENR |= 1UL << 28;
    // Set internal voltage regulator scale: scale 1 (84MHz to 100MHz) (VOS) (section 5.4.1 pg 86)
    PWR_CR |= ((1UL << 14) | (1UL << 15));
    
    // Set AHB high speed prescaler (HPRE): system clock undivided (section 6.3.3 pg 108)
    RCC_CFGR &= ~(1UL << 7);
    // Set APB1 low speed prescaler (PPRE1): AHB clock divided by 2 (<=50MHz) (section 6.3.3 pg 107)
    RCC_CFGR &= ~((1UL << 12) | (1UL << 11) | (1UL << 10));
    RCC_CFGR |= ((1UL << 12));
    // Set APB2 high speed prescaler (PPRE2): AHB clock undivided (section 6.3.3 pg 107)
    RCC_CFGR &= ~((1UL << 15) | (1UL << 14) | (1UL << 13));

    // Set PLL source to be HSE
    RCC_PLLCFGR |= (1UL << 22);
    // Set main PLL division factor for VCO (PLLM) (1MHz to 2MHz) (section 6.3.2 pg 105)
    RCC_PLLCFGR &= ~(0x3FUL << 0);
    RCC_PLLCFGR |= (25UL << 0);
    // Set main PLL multiplication factor for VCO (PLLN) (100MHz to 432MHz) (section 6.3.2 pg 105)
    RCC_PLLCFGR &= ~(0xFFUL << 6);
    RCC_PLLCFGR |= (192UL << 6);
    // Set main PLL division factor for main system clock (PLLP): VCO divided by 2 (<=100MHz) (section 6.3.2 pg 105)
    RCC_PLLCFGR &= ~(0x3UL << 16);
    // Set main PLL division factor (PLLQ) for USB and SDIO: VCO divided by 4 (=48MHz) (section 6.3.2 pg 104)
    RCC_PLLCFGR &= ~(0xFUL << 24);
    RCC_PLLCFGR |= (1UL << 26);

    // Enable PLL (PLLON) (section 6.3.1 pg 102)
    RCC_CR |= (1UL << 24);
    // Wait until PLL is ready (PLLRDY) (section 6.2.6 pg 97)
    while ((RCC_CR & (1UL << 25)) == 0);

    // Configure flash memory (section 3.8.1 pg 59)
    FLASH_ACR = 0x0; // Reset flash
    FLASH_ACR |= (5UL << 0); // LATENCY: 5 WS (section 3.4.1 pg 45)
    FLASH_ACR |= (1UL << 8); // PRFTEN: Prefetch enable (section 3.4.1 pg 45)
    FLASH_ACR |= (1UL << 9); // ICEN: Instruction chache enable  (section 3.8.1 pg 59)
    FLASH_ACR |= (1UL << 10); // DCEN: Data cache enable  (section 3.8.1 pg 59)

    // Select main PLL as system clock source (SW) (section 6.3.3 pg 108)
    RCC_CFGR &= ~((1UL << 1) | (1UL << 0));
    RCC_CFGR |= 1UL << 1;
    // Wait until system clock switch status is set (SWS) (section 6.3.3 pg 108)
    while ((RCC_CFGR & 0xC) != 0x8);
}