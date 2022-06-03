/*
    By : Fayssal Chokri <fayssalchokri@symantec.com>
    2021-2022 MIT Licence
*/



/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F4xx_FLASH_RAMFUNC_H
#define __STM32F4xx_FLASH_RAMFUNC_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"

/** @addtogroup STM32F4xx_StdPeriph_Driver
  * @{
  */

/** @addtogroup FLASH RAMFUNC
  * @{
  */ 

/* Exported types ------------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/** 
  * @brief  __RAM_FUNC definition
  */ 
#if defined ( __CC_ARM   )
/* ARM Compiler
   ------------
   RAM functions are defined using the toolchain options. 
   Functions that are executed in RAM should reside in a separate source module.
   Using the 'Options for File' dialog you can simply change the 'Code / Const' 
   area of a module to a memory space in physical RAM.
   Available memory areas are declared in the 'Target' tab of the 'Options for Target'
   dialog. 
*/
#define __RAM_FUNC void 

#elif defined ( __ICCARM__ )
/* ICCARM Compiler
   ---------------
   RAM functions are defined using a specific toolchain keyword "__ramfunc". 
*/
#define __RAM_FUNC __ramfunc void

#elif defined   (  __GNUC__  )
/* GNU Compiler
   ------------
  RAM functions are defined using a specific toolchain attribute 
   "__attribute__((section(".RamFunc")))".
*/
#define __RAM_FUNC void  __attribute__((section(".RamFunc")))

#endif
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
__RAM_FUNC FLASH_FlashInterfaceCmd(FunctionalState NewState);
__RAM_FUNC FLASH_FlashSleepModeCmd(FunctionalState NewState);


#ifdef __cplusplus
}
#endif

#endif /* __STM32F4xx_FLASH_RAMFUNC_H */

/**
  * @}
  */ 

/**
  * @}
  */ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

