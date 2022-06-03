/*
    By : Fayssal Chokri <fayssalchokri@symantec.com>
    2021-2022 MIT Licence
*/


/** @addtogroup CMSIS
  * @{
  */

/** @addtogroup stm32f0xx_system
  * @{
  */  
  
/**
  * @brief Define to prevent recursive inclusion
  */
#ifndef __SYSTEM_STM32F0XX_H
#define __SYSTEM_STM32F0XX_H

#ifdef __cplusplus
 extern "C" {
#endif 

/** @addtogroup STM32F0xx_System_Includes
  * @{
  */

/**
  * @}
  */


/** @addtogroup STM32F0xx_System_Exported_types
  * @{
  */

extern uint32_t SystemCoreClock;          /*!< System Clock Frequency (Core Clock) */

/**
  * @}
  */

/** @addtogroup STM32F0xx_System_Exported_Constants
  * @{
  */

/**
  * @}
  */

/** @addtogroup STM32F0xx_System_Exported_Macros
  * @{
  */

/**
  * @}
  */

/** @addtogroup STM32F0xx_System_Exported_Functions
  * @{
  */
  
extern void SystemInit(void);
extern void SystemCoreClockUpdate(void);
/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /*__SYSTEM_STM32F0XX_H */

/**
  * @}
  */
  
/**
  * @}
  */  
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
