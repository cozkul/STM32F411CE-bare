#include "Types.h"
#include "RegisterAddresses.h"

extern uint32_t SystemCoreClock;
void delay(uint32_t ms);
void PC13Config(void);
void TIM2Config(void);

int main(void)
{
    PC13Config();
    TIM2Config();

    while (1)
    {
        // Reset pin PC13 (section 8.4.7 pg 160)
        GPIOC_BSRR |= (1UL << 13) << 16;
        delay(1000);
        GPIOC_BSRR |= 1UL << 13;
        delay(1000);
    }
    return 0;
}

void PC13Config(void)
{
    // Enable AHB1 clock (section 6.3.9 pg 117)
    RCC_AHB1ENR |= 1UL << 2;
    // Set PC13 no pull-down or pull-up (section 8.4.4 pg 158)
    GPIOC_PUPDR &= ~((1UL << 26) | (1UL << 26));
    // Set PC13 push-pull (section 8.4.2 pg 157)
    GPIOC_OTYPER &= ~(1UL << 13);
    // Set PC13 low (section 8.4.6 pg 159)
    GPIOC_BSRR |= 1UL << 13; // BSRR is for atomic write.
    // ODR can be used for for read and write |= or &=
    // Set PC13 speed high (section 8.4.3 pg 158)
    GPIOC_OSPEEDR &= ~((1UL << 26) | (1UL << 26));
    GPIOC_OSPEEDR |= 1U << 27;
    // Set PC13 as output (section 8.4.1 pg 157)
    GPIOC_MODER &= ~((1UL << 26) | (1UL << 26));
    GPIOC_MODER |= 1UL << 26;
}

void TIM2Config(void)
{
    // Enable timer clock TIM2EN (section 6.3.11 pg 118)
    RCC_APB1ENR |= 1;
    // APB1 peripheral clock was set to 48MHz
    // APB1 timer clock was set to 48MHz
    // Configure TIM2 prescaler (section 13.4.11 pg 367)
    TIM2_PSC = 48 - 1; // 1us
    // Configure TIM2 auto reload register (section 13.4.12 pg 367)
    TIM2_ARR = 0xFFFFFFFF; // TIM2 is 32bit counter
    // Enable timer (CEN) on control register (section 13.4.1 pg 353)
    TIM2_CR1 |= 1;
    // Wait for update on update interrupt flag (section 13.4.5 pg 358)
    while (TIM2_SR & 1);
}

void delay(uint32_t ms)
{
    for (uint32_t i = 0; i < ms; i++)
    {
        TIM2_CNT = 0; // (section 13.4.10 pg 367)
        while (TIM2_CNT < 100000);
        // TODO: figure out discrepancy on order of magnitude (100000us != 1ms)
    }
}