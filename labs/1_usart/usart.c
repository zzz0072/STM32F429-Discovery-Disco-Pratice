#include "stm32f4xx_conf.h"
#include <stm32f4xx.h>
#include <stm32f4xx_gpio.h>
#include <stm32f4xx_usart.h>

void setupUSART(void);

/* helper functions */
void print(char *str);
char getchar(void);
void putchar(char c);

int main(int argc, char **argv)
{
    /* Setup USART */
    setupUSART();

    /* Greeting */
    print("Hello World\n");
    print("\r> ");
    while(1) {
        /* Echo a character */
        char c = getchar();
        putchar(c);

        /* Show prompt with enter */
        if (c == '\n') {
            print("\r> ");
        }
    }

    return 0;
}

void setupUSART(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    /* Enable GPIOC clock */
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);

    /* Connect USART6_Tx instead of PC6 */
    GPIO_PinAFConfig(GPIOC, GPIO_PinSource6, GPIO_AF_USART6);

    /* Connect USART6_Rx instead of PC7 */
    GPIO_PinAFConfig(GPIOC, GPIO_PinSource7, GPIO_AF_USART6);

    /* Configure USART Tx (PC6) and Rx (PC7) as alternate function  */
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;

    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;

    GPIO_Init(GPIOC, &GPIO_InitStructure);

    /********************************************
     * USART set started here
     ********************************************/
    USART_InitTypeDef USART_InitStruct;

    /* Enable USART6 clock */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART6, ENABLE);

    /* 115200, N81  */
    USART_InitStruct.USART_BaudRate = 115200;
    USART_InitStruct.USART_WordLength = USART_WordLength_8b;
    USART_InitStruct.USART_StopBits = USART_StopBits_1;
    USART_InitStruct.USART_Parity = USART_Parity_No;
    USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

    /* Apply USART settings */
    USART_Init(USART6, &USART_InitStruct);

    /* Enable USART */
    USART_Cmd(USART6, ENABLE);
}

char getchar(void)
{
    while(USART_GetFlagStatus(USART6, USART_FLAG_RXNE) == RESET);
    return USART6->DR & 0xff;
}

void putchar(char c)
{
    /* Wait until data was tranferred */
    while(USART_GetFlagStatus(USART6, USART_FLAG_TXE) == RESET);

    USART6->DR = (c & 0xff);
}

void print(char *str)
{
    assert_param(str != 0);
    while(*str) {
        putchar(*str);
        str++;
    }
}

/* Trap here for gdb if asserted */
void assert_failed(uint8_t* file, uint32_t line)
{
    while(1);
}
