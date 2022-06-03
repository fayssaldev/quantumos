/*
    By : Fayssal Chokri <fayssalchokri@symantec.com>
    2021-2022 MIT Licence
*/

#include "HardwareSerial.h"


HardwareSerial::HardwareSerial(USART_TypeDef *_USARTx)
{
    this->USARTx = _USARTx;
    USART_Function = 0;
    _rx_buffer_head = _rx_buffer_tail = 0;
}


void HardwareSerial::IRQHandler()
{
    if(USART_GetITStatus(USARTx, USART_IT_RXNE) != RESET)
    {
        uint8_t c = USART_ReceiveData(USARTx);
        uint16_t i = (uint16_t)(_rx_buffer_head + 1) % SERIAL_RX_BUFFER_SIZE;
        if (i != _rx_buffer_tail)
        {
            _rx_buffer[_rx_buffer_head] = c;
            _rx_buffer_head = i;
        }

        if(USART_Function)
        {
            USART_Function();
        }

        USART_ClearITPendingBit(USARTx, USART_IT_RXNE);
    }
}


void HardwareSerial::begin(uint32_t BaudRate)
{
    begin(BaudRate, SERIAL_Config_Default);
}


void HardwareSerial::begin(uint32_t BaudRate, SERIAL_Config Config)
{
    begin(BaudRate, Config, USART_PreemptionPriority_Default, USART_SubPriority_Default);
}


void HardwareSerial::begin(uint32_t BaudRate, SERIAL_Config Config, uint8_t PreemptionPriority, uint8_t SubPriority)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    uint16_t Tx_Pin, Rx_Pin;
    uint16_t ItChannel;
    uint32_t RCC_AHB1Periph_GPIOx;
    GPIO_TypeDef *GPIOx;
    uint8_t GPIO_AF_USARTx;

    if(USARTx == USART1)
    {
        Tx_Pin = GPIO_Pin_9;
        Rx_Pin = GPIO_Pin_10;
        GPIOx = GPIOA;
        GPIO_AF_USARTx = GPIO_AF_USART1;
        RCC_AHB1Periph_GPIOx = RCC_AHB1Periph_GPIOA;
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
        ItChannel = USART1_IRQn;
    }
    else if(USARTx == USART2)
    {
        Tx_Pin = GPIO_Pin_2;
        Rx_Pin = GPIO_Pin_3;
        GPIOx = GPIOA;
        GPIO_AF_USARTx = GPIO_AF_USART2;
        RCC_AHB1Periph_GPIOx = RCC_AHB1Periph_GPIOA;
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
        ItChannel = USART2_IRQn;
    }
    else if(USARTx == USART3)
    {
        Tx_Pin = GPIO_Pin_10;
        Rx_Pin = GPIO_Pin_11;
        GPIOx = GPIOB;
        GPIO_AF_USARTx = GPIO_AF_USART3;
        RCC_AHB1Periph_GPIOx = RCC_AHB1Periph_GPIOB;
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
#if defined (STM32F40_41xxx) || defined (STM32F427_437xx) || defined (STM32F429_439xx)
        ItChannel = USART3_IRQn;
#endif
    }
    else return;

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOx, ENABLE);

    GPIO_PinAFConfig(GPIOx, GPIO_GetPinSource(Tx_Pin), GPIO_AF_USARTx);
    GPIO_PinAFConfig(GPIOx, GPIO_GetPinSource(Rx_Pin), GPIO_AF_USARTx);

    GPIO_InitStructure.GPIO_Pin =  Tx_Pin | Rx_Pin;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOx, &GPIO_InitStructure);

    //Usart NVIC 
    NVIC_InitStructure.NVIC_IRQChannel = ItChannel;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = PreemptionPriority ;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = SubPriority;        
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;         
    NVIC_Init(&NVIC_InitStructure); 

    //USART 
    USART_InitStructure.USART_BaudRate = BaudRate;
    USART_InitStructure.USART_WordLength = USART_GetWordLength(Config);
    USART_InitStructure.USART_StopBits = USART_GetParity(Config);
    USART_InitStructure.USART_Parity = USART_GetStopBits(Config);
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; 

    USART_Init(USARTx, &USART_InitStructure); 
    USART_ITConfig(USARTx, USART_IT_RXNE, ENABLE);
    USART_Cmd(USARTx, ENABLE);                    
}


void HardwareSerial::end(void)
{
    USART_Cmd(USARTx, DISABLE);
}


void HardwareSerial::attachInterrupt(USART_CallbackFunction_t Function)
{
    USART_Function = Function;
}


int HardwareSerial::available(void)
{
    return ((unsigned int)(SERIAL_RX_BUFFER_SIZE + _rx_buffer_head - _rx_buffer_tail)) % SERIAL_RX_BUFFER_SIZE;
}


int HardwareSerial::read(void)
{
    // if the head isn't ahead of the tail, we don't have any characters
    if (_rx_buffer_head == _rx_buffer_tail)
    {
        return -1;
    }
    else
    {
        unsigned char c = _rx_buffer[_rx_buffer_tail];
        _rx_buffer_tail = (rx_buffer_index_t)(_rx_buffer_tail + 1) % SERIAL_RX_BUFFER_SIZE;
        return c;
    }
}


int HardwareSerial::peek(void)
{
    if (_rx_buffer_head == _rx_buffer_tail)
    {
        return -1;
    }
    else
    {
        return _rx_buffer[_rx_buffer_tail];
    }
}


void HardwareSerial::flush(void)
{
    _rx_buffer_head = _rx_buffer_tail;
}


size_t HardwareSerial::write(uint8_t n)
{
    while(!USART_GetFlagStatus(USARTx, USART_FLAG_TXE)){};
    USART_SendData(USARTx, n);
    return n;
}

//Creat Object For User
HardwareSerial Serial(USART1);//TX-PA9 RX-PA10
HardwareSerial Serial2(USART2);//TX-PA2 RX-PA3
HardwareSerial Serial3(USART3);//TX-PB10 RX-PB11

//USARTx_IRQHandler
extern "C" {
    void USART1_IRQHandler(void)
    {
        Serial.IRQHandler();
    }

    void USART2_IRQHandler(void)
    {
        Serial2.IRQHandler();
    }

    void USART3_IRQHandler(void)
    {
        Serial3.IRQHandler();
    }
}
