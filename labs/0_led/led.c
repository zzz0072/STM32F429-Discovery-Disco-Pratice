#include "stm32f4xx_conf.h"
#include <stm32f4xx.h>
#include <stm32f4xx_gpio.h>

/* A Led blink lab for STM32 Discovry Disco                   *
 * Based on:                                                  *
 *   Discovering the STM32 Microcontroller by Geoffrey Brown. */

void setupLED(GPIO_InitTypeDef *LED_InitStruct);
void sleep(uint32_t nSec);

int main(int argc, char **argv)
{
    static int LEDVal = 0;
    GPIO_InitTypeDef LED_InitStruct;

    /* Setup LED */
    setupLED(&LED_InitStruct);

    /* Setup timer interrupt interval to nano second */
    if(SysTick_Config(SystemCoreClock / 1000)) {
        while(1); /* Trap here if failed */
    }

    /* Blinking LED3 and LED4 */
    while(1) {
        GPIO_WriteBit(GPIOG, GPIO_Pin_13 , LEDVal);
        GPIO_WriteBit(GPIOG, GPIO_Pin_14 , !LEDVal);

        sleep(250);
        LEDVal = !LEDVal;
    }

    return 0;
}

void setupLED(GPIO_InitTypeDef *LED_InitStruct)
{
    /* Setup LED GPIO */
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);

    GPIO_StructInit(LED_InitStruct);
    LED_InitStruct->GPIO_Pin   = GPIO_Pin_13 | GPIO_Pin_14 ;
    LED_InitStruct->GPIO_Mode  = GPIO_Mode_OUT;
    LED_InitStruct->GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOG, LED_InitStruct);
}

static __IO uint32_t g_timeToWakeUp;
void sleep(uint32_t nSec)
{
    g_timeToWakeUp = nSec;

    /* Busy waiting */
    while(g_timeToWakeUp != 0);
}

/* ISR for system tick */
void SysTick_Handler(void)
{
    if (g_timeToWakeUp != 0x00) {
        g_timeToWakeUp--;
    }
}

/* Trap here for gdb if asserted */
void assert_failed(uint8_t* file, uint32_t line)
{
    while(1);
}
