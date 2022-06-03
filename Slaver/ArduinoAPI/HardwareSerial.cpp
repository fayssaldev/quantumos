/*
    By : Fayssal Chokri <fayssalchokri@symantec.com>
    2021-2022 MIT Licence
*/

#include "HardwareSerial.h"

/**
  * @brief  
  * @param  
  * @retval 
  */
HardwareSerial::HardwareSerial(USART_TypeDef *_USARTx)
{
    this->USARTx = _USARTx;
    USART_Function = 0;
}

/**
  * @brief  
  * @param  
  * @retval 
  */
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
    
    if(USART_GetITStatus(USARTx, USART_IT_ORE) != RESET)
    {
        USART_ClearITPendingBit(USARTx, USART_IT_ORE);
    }
}

/**
  * @brief  
  * @param  
  * @retval 
  */
void HardwareSerial::begin(uint32_t BaudRate)
{
    begin(BaudRate, SERIAL_Config_Default);
}

/**
  * @brief  
  * @param  
  * @param  
  * @retval 
  */
void HardwareSerial::begin(uint32_t BaudRate, SERIAL_Config Config)
{
    begin(BaudRate, Config, USART_ChannelPriority_Default);
}

/**
  * @brief  
  * @param  
  * @param  
  * @param  
  * @retval 
  */
void HardwareSerial::begin(uint32_t BaudRate, SERIAL_Config Config, uint8_t ChannelPriority)
{
    
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    uint16_t Tx_Pin, Rx_Pin;
    uint16_t ItChannel;
    uint32_t RCC_AHBPeriph_GPIOx;
    GPIO_TypeDef *GPIOx;

    if(USARTx == USART1)
    {
        Tx_Pin = GPIO_Pin_9;
        Rx_Pin = GPIO_Pin_10;

        GPIOx = GPIOA;
        RCC_AHBPeriph_GPIOx = RCC_AHBPeriph_GPIOA;
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
        ItChannel = USART1_IRQn;
    }
    else if(USARTx == USART2)
    {
        Tx_Pin = GPIO_Pin_2;
        Rx_Pin = GPIO_Pin_3;
        
        GPIOx = GPIOA;
        RCC_AHBPeriph_GPIOx = RCC_AHBPeriph_GPIOA;
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
        ItChannel = USART2_IRQn;
    }

    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOx, ENABLE);

    GPIO_PinAFConfig(GPIOx, Get_GPIO_PinSource(Tx_Pin), GPIO_AF_1);
    GPIO_PinAFConfig(GPIOx, Get_GPIO_PinSource(Rx_Pin), GPIO_AF_1);

    GPIO_InitStructure.GPIO_Pin =  Tx_Pin | Rx_Pin;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOx, &GPIO_InitStructure);

    //Usart NVIC 
    NVIC_InitStructure.NVIC_IRQChannel = ItChannel;
    NVIC_InitStructure.NVIC_IRQChannelPriority = ChannelPriority;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    //USART 
    USART_InitStructure.USART_BaudRate = BaudRate;
    USART_InitStructure.USART_WordLength = Get_USART_WordLength_x(Config);
    USART_InitStructure.USART_StopBits = Get_USART_StopBits_x(Config);
    USART_InitStructure.USART_Parity = Get_USART_Parity_x(Config);
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	
    USART_Init(USARTx, &USART_InitStructure); 

    USART_ITConfig(USARTx, USART_IT_RXNE, ENABLE);
    USART_Cmd(USARTx, ENABLE);                   
}

/**
  * @brief  
  * @param  
  * @retval 
  */
void HardwareSerial::end(void)
{
    USART_Cmd(USARTx, DISABLE);
}

/**
  * @brief  
  * @param  Function: 
  * @retval 
  */
void HardwareSerial::attachInterrupt(USART_CallbackFunction_t Function)
{
    USART_Function = Function;
}

/**
  * @brief  
  * @param  
  * @retval 
  */
int HardwareSerial::available(void)
{
    return ((unsigned int)(SERIAL_RX_BUFFER_SIZE + _rx_buffer_head - _rx_buffer_tail)) % SERIAL_RX_BUFFER_SIZE;
}

/**
  * @brief  
  * @param  
  * @retval 
  */
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

/**
  * @brief  
  * @param  
  * @retval 
  */
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

/**
  * @brief  
  * @param  
  * @retval 
  */
void HardwareSerial::flush(void)
{
    _rx_buffer_head = _rx_buffer_tail;
}

/**
  * @brief  
  * @param 
  * @retval 
  */
size_t HardwareSerial::write(uint8_t n)
{
    while(!IS_USARTx_SendDone(USARTx)) {}; 
    USART_SendData(USARTx, n);
    return n;
}

//Creat Object For User
HardwareSerial Serial(USART1);//TX-PA9 RX-PA10
HardwareSerial Serial2(USART2);//TX-PA2 RX-PA3

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
}
