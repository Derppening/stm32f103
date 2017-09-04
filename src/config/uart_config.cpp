#include "uart_config.h"

UART COM1(USART1, RCC_APB2Periph_USART1, &PA9, &PA10, RCC_APB2Periph_GPIOA, RCC_APB2Periph_GPIOA, USART1_IRQn);

void USART1_IRQHandler() {
    if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) {
        if (COM1.listener != 0) {
            COM1.listener(USART_ReceiveData(USART1));
        }
        USART_ClearITPendingBit(USART1, USART_IT_RXNE);
    }
}
