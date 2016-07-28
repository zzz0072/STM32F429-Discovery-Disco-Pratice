#include "stm32f4xx_conf.h"
#include <stm32f4xx.h>
#include <stm32f4xx_gpio.h>
#include <stm32f4xx_usart.h>

/* Hello world from USART */

void setupUSART(void);
void print(char *str);

int main(int argc, char **argv)
{
    char my_str[]="Hello World\n";

    /* Setup USART */
    setupUSART();

    /* Print Hello World Repeatly */
    while(1) {
        print(my_str);
    }

    return 0;
}

void setupUSART(void)
{
    USART_InitTypeDef USART_InitStruct;

    /* 115200, N81  */
    USART_InitStruct.USART_BaudRate = 115200;
    USART_InitStruct.USART_WordLength = USART_WordLength_8b;
    USART_InitStruct.USART_StopBits = USART_StopBits_1;
    USART_InitStruct.USART_Parity = USART_Parity_No;
    USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

    GPIO_InitTypeDef GPIO_InitStructure;

    /* Enable UART clock */
    RCC_AHB1PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

    /* Connect USART1_Tx*/
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource9 ,GPIO_AF_USART1);

    /* Connect USART1_Rx*/
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);

    /* Configure USART Tx as alternate function  */
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;

    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* Configure USART Rx as alternate function  */
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_10;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* USART configuration */
    USART_Init(USART1, &USART_InitStruct);

    /* Enable USART */
    USART_Cmd(USART1, ENABLE);
}

int putchar(int c)
{
    /* Wait until data was tranferred */
    while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);

    USART1->DR = (c & 0xff);
    return 0;
}

void print(char *str)
{
    assert_param(str != 0);
    while(*str != 0) {
        putchar(*str);
        str++;
    }
}

/* Trap here for gdb if asserted */
void assert_failed(uint8_t* file, uint32_t line)
{
    while(1);
}
