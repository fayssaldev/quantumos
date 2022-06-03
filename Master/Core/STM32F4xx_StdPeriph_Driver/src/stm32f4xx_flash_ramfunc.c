/*
    By : Fayssal Chokri <fayssalchokri@symantec.com>
    2021-2022 MIT Licence
*/

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_flash_ramfunc.h"

/** @addtogroup STM32F4xx_StdPeriph_Driver
  * @{
  */

/** @defgroup FLASH RAMFUNC 
  * @brief FLASH RAMFUNC driver modules
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup FLASH_RAMFUNC_Private_Functions
  * @{
  */

/** @defgroup FLASH_RAMFUNC_Group1 Peripheral features functions executed from internal RAM 
  *  @brief Peripheral Extended features functions 
  *
@verbatim   

 ===============================================================================
                      ##### ramfunc functions #####
 ===============================================================================
    [..]
    This subsection provides a set of functions that should be executed from RAM 
    transfers.
    
@endverbatim
  * @{
  */

/**
  * @brief Start/Stop the flash interface while System Run
  * @note  This mode is only available for STM32F411xx devices. 
  * @note  This mode could n't be set while executing with the flash itself. 
  *        It should be done with specific routine executed from RAM.     
  * @param  NewState: new state of the Smart Card mode.
  *          This parameter can be: ENABLE or DISABLE.  
  * @retval None
  */
__RAM_FUNC FLASH_FlashInterfaceCmd(FunctionalState NewState)
{
  if (NewState != DISABLE)
  {
    /* Start the flash interface while System Run */
    CLEAR_BIT(PWR->CR, PWR_CR_FISSR);
  }
  else
  {
    /* Stop the flash interface while System Run */  
    SET_BIT(PWR->CR, PWR_CR_FISSR);
  }
}

/**
  * @brief Enable/Disable the flash sleep while System Run
  * @note  This mode is only available for STM32F411xx devices. 
  * @note  This mode could n't be set while executing with the flash itself. 
  *        It should be done with specific routine executed from RAM.     
  * @param  NewState: new state of the Smart Card mode.
  *          This parameter can be: ENABLE or DISABLE.  
  * @retval None
  */
__RAM_FUNC FLASH_FlashSleepModeCmd(FunctionalState NewState)
{
  if (NewState != DISABLE)
  {
    /* Enable the flash sleep while System Run */
    SET_BIT(PWR->CR, PWR_CR_FMSSR);
  }
  else
  {
    /* Disable the flash sleep while System Run */
    CLEAR_BIT(PWR->CR, PWR_CR_FMSSR);
  }
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
