/**
  ******************************************************************************
  * @file    system_stm32l1xx.c
  * @author  MCD Application Team
  * @version V1.2.0
  * @date    14-March-2014
  * @brief   CMSIS Cortex-M3 Device Peripheral Access Layer System Source File.
  *          This file contains the system clock configuration for STM32L1xx Ultra
  *          Low power devices, and is generated by the clock configuration 
  *          tool  STM32L1xx_Clock_Configuration_V1.2.0.xls
  *             
  * 1.  This file provides two functions and one global variable to be called from 
  *     user application:
  *      - SystemInit(): Setups the system clock (System clock source, PLL Multiplier
  *                      and Divider factors, AHB/APBx prescalers and Flash settings),
  *                      depending on the configuration made in the clock xls tool. 
  *                      This function is called at startup just after reset and 
  *                      before branch to main program. This call is made inside
  *                      the "startup_stm32l1xx_xx.s" file.
  *                        
  *      - SystemCoreClock variable: Contains the core clock (HCLK), it can be used
  *                                  by the user application to setup the SysTick 
  *                                  timer or configure other parameters.
  *                                     
  *      - SystemCoreClockUpdate(): Updates the variable SystemCoreClock and must
  *                                 be called whenever the core clock is changed
  *                                 during program execution.   
  *      
  * 2. After each device reset the MSI (2.1 MHz Range) is used as system clock source.
  *    Then SystemInit() function is called, in "startup_stm32l1xx_xx.s" file, to
  *    configure the system clock before to branch to main program.    
  *    
  * 3. If the system clock source selected by user fails to startup, the SystemInit()
  *    function will do nothing and MSI still used as system clock source. User can 
  *    add some code to deal with this issue inside the SetSysClock() function.       
  * 
  * 4. The default value of HSE crystal is set to 8MHz, refer to "HSE_VALUE" define
  *    in "stm32l1xx.h" file. When HSE is used as system clock source, directly or
  *    through PLL, and you are using different crystal you have to adapt the HSE
  *    value to your own configuration.
  *
  * 5. This file configures the system clock as follows:
  *-----------------------------------------------------------------------------
  * System clock source                | 1- PLL_HSE_EXTC        | 3- PLL_HSI
  *                                    | (external 8 MHz clock) | (internal 16 MHz)
  *                                    | 2- PLL_HSE_XTAL        |
  *                                    | (external 8 MHz xtal)  |
  *-----------------------------------------------------------------------------
  * SYSCLK(MHz)                        | 24                     | 32
  *-----------------------------------------------------------------------------
  * AHBCLK (MHz)                       | 24                     | 32
  *-----------------------------------------------------------------------------
  * APB1CLK (MHz)                      | 24                     | 32
  *-----------------------------------------------------------------------------
  * APB2CLK (MHz)                      | 24                     | 32
  *-----------------------------------------------------------------------------
  * USB capable (48 MHz precise clock) | YES                    | NO
  *-----------------------------------------------------------------------------  
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2014 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/** @addtogroup CMSIS
  * @{
  */

/** @addtogroup stm32l1xx_system
  * @{
  */  
  
/** @addtogroup STM32L1xx_System_Private_Includes
  * @{
  */

#include "stm32l1xx.h"

/**
  * @}
  */

/** @addtogroup STM32L1xx_System_Private_TypesDefinitions
  * @{
  */

/**
  * @}
  */

/** @addtogroup STM32L1xx_System_Private_Defines
  * @{
  */

/*!< Uncomment the following line if you need to relocate your vector Table in
     Internal SRAM. */ 
/* #define VECT_TAB_SRAM */
#define VECT_TAB_OFFSET  0x0 /*!< Vector Table base offset field. 
                                  This value must be a multiple of 0x200. */
/**
  * @}
  */

/** @addtogroup STM32L1xx_System_Private_Macros
  * @{
  */

/* Select the clock sources (other than HSI) to start with (0=OFF, 1=ON) */
#define USE_PLL_HSE_EXTC (1) /* Use external clock */
#define USE_PLL_HSE_XTAL (1) /* Use external xtal */

/**
  * @}
  */

/** @addtogroup STM32L1xx_System_Private_Variables
  * @{
  */

uint32_t SystemCoreClock = 32000000; /* Default with HSI. Will be updated if HSE is used */

__I uint8_t PLLMulTable[9] = {3, 4, 6, 8, 12, 16, 24, 32, 48};
__I uint8_t AHBPrescTable[16] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 6, 7, 8, 9};

/**
  * @}
  */

/** @addtogroup STM32L1xx_System_Private_FunctionPrototypes
  * @{
  */

void SetSysClock(void);

#if (USE_PLL_HSE_XTAL != 0) || (USE_PLL_HSE_EXTC != 0)
uint8_t SetSysClock_PLL_HSE(uint8_t bypass);
#endif

uint8_t SetSysClock_PLL_HSI(void);

/**
  * @}
  */

/** @addtogroup STM32L1xx_System_Private_Functions
  * @{
  */

/**
  * @brief  Setup the microcontroller system.
  *         Initialize the Embedded Flash Interface, the PLL and update the 
  *         SystemCoreClock variable.
  * @param  None
  * @retval None
  */
void SystemInit (void)
{
  /*!< Set MSION bit */
  RCC->CR |= (uint32_t)0x00000100;

  /*!< Reset SW[1:0], HPRE[3:0], PPRE1[2:0], PPRE2[2:0], MCOSEL[2:0] and MCOPRE[2:0] bits */
  RCC->CFGR &= (uint32_t)0x88FFC00C;
  
  /*!< Reset HSION, HSEON, CSSON and PLLON bits */
  RCC->CR &= (uint32_t)0xEEFEFFFE;

  /*!< Reset HSEBYP bit */
  RCC->CR &= (uint32_t)0xFFFBFFFF;

  /*!< Reset PLLSRC, PLLMUL[3:0] and PLLDIV[1:0] bits */
  RCC->CFGR &= (uint32_t)0xFF02FFFF;

  /*!< Disable all interrupts */
  RCC->CIR = 0x00000000;

  /* Configure the System clock source, PLL Multiplier and Divider factors, 
     AHB/APBx prescalers and Flash settings */
  SetSysClock();

  /* Configure the Vector Table location add offset address ------------------*/
#ifdef VECT_TAB_SRAM
  SCB->VTOR = SRAM_BASE | VECT_TAB_OFFSET; /* Vector Table Relocation in Internal SRAM */
#else
  SCB->VTOR = FLASH_BASE | VECT_TAB_OFFSET; /* Vector Table Relocation in Internal FLASH */
#endif
}

/**
   * @brief  Update SystemCoreClock variable according to Clock Register Values.
  *         The SystemCoreClock variable contains the core clock (HCLK), it can
  *         be used by the user application to setup the SysTick timer or configure
  *         other parameters.
  *           
  * @note   Each time the core clock (HCLK) changes, this function must be called
  *         to update SystemCoreClock variable value. Otherwise, any configuration
  *         based on this variable will be incorrect.         
  *     
  * @note   - The system frequency computed by this function is not the real 
  *           frequency in the chip. It is calculated based on the predefined 
  *           constant and the selected clock source:
  *             
  *           - If SYSCLK source is MSI, SystemCoreClock will contain the MSI 
  *             value as defined by the MSI range.
  *                                   
  *           - If SYSCLK source is HSI, SystemCoreClock will contain the HSI_VALUE(*)
  *                                              
  *           - If SYSCLK source is HSE, SystemCoreClock will contain the HSE_VALUE(**)
  *                          
  *           - If SYSCLK source is PLL, SystemCoreClock will contain the HSE_VALUE(**) 
  *             or HSI_VALUE(*) multiplied/divided by the PLL factors.
  *         
  *         (*) HSI_VALUE is a constant defined in stm32l1xx.h file (default value
  *             16 MHz) but the real value may vary depending on the variations
  *             in voltage and temperature.   
  *    
  *         (**) HSE_VALUE is a constant defined in stm32l1xx.h file (default value
  *              8 MHz), user has to ensure that HSE_VALUE is same as the real
  *              frequency of the crystal used. Otherwise, this function may
  *              have wrong result.
  *                
  *         - The result of this function could be not correct when using fractional
  *           value for HSE crystal.  
  * @param  None
  * @retval None
  */
void SystemCoreClockUpdate (void)
{
  uint32_t tmp = 0, pllmul = 0, plldiv = 0, pllsource = 0, msirange = 0;

  /* Get SYSCLK source -------------------------------------------------------*/
  tmp = RCC->CFGR & RCC_CFGR_SWS;
  
  switch (tmp)
  {
    case 0x00:  /* MSI used as system clock */
      msirange = (RCC->ICSCR & RCC_ICSCR_MSIRANGE) >> 13;
      SystemCoreClock = (32768 * (1 << (msirange + 1)));
      break;
    case 0x04:  /* HSI used as system clock */
      SystemCoreClock = HSI_VALUE;
      break;
    case 0x08:  /* HSE used as system clock */
      SystemCoreClock = HSE_VALUE;
      break;
    case 0x0C:  /* PLL used as system clock */
      /* Get PLL clock source and multiplication factor ----------------------*/
      pllmul = RCC->CFGR & RCC_CFGR_PLLMUL;
      plldiv = RCC->CFGR & RCC_CFGR_PLLDIV;
      pllmul = PLLMulTable[(pllmul >> 18)];
      plldiv = (plldiv >> 22) + 1;
      
      pllsource = RCC->CFGR & RCC_CFGR_PLLSRC;

      if (pllsource == 0x00)
      {
        /* HSI oscillator clock selected as PLL clock entry */
        SystemCoreClock = (((HSI_VALUE) * pllmul) / plldiv);
      }
      else
      {
        /* HSE selected as PLL clock entry */
        SystemCoreClock = (((HSE_VALUE) * pllmul) / plldiv);
      }
      break;
    default: /* MSI used as system clock */
      msirange = (RCC->ICSCR & RCC_ICSCR_MSIRANGE) >> 13;
      SystemCoreClock = (32768 * (1 << (msirange + 1)));
      break;
  }
  /* Compute HCLK clock frequency --------------------------------------------*/
  /* Get HCLK prescaler */
  tmp = AHBPrescTable[((RCC->CFGR & RCC_CFGR_HPRE) >> 4)];
  /* HCLK clock frequency */
  SystemCoreClock >>= tmp;
}

/**
  * @brief  Configures the System clock source, PLL Multiplier and Divider factors,
  *               AHB/APBx prescalers and Flash settings
  * @note   This function should be called only once the RCC clock configuration  
  *         is reset to the default reset state (done in SystemInit() function).             
  * @param  None
  * @retval None
  */
void SetSysClock(void)
{
  /* 1- Try to start with HSE and external clock */
#if USE_PLL_HSE_EXTC != 0
  if (SetSysClock_PLL_HSE(1) == 0)
#endif
  {
    /* 2- If fail try to start with HSE and external xtal */
    #if USE_PLL_HSE_XTAL != 0
    if (SetSysClock_PLL_HSE(0) == 0)
    #endif
    {
      /* 3- If fail start with HSI clock */
      if (SetSysClock_PLL_HSI() == 0)
      {
        while(1)
        {
          // [TODO] Put something here to tell the user that a problem occured...
        }
      }
    }
  }
  
  /* Output SYSCLK on MCO pin(PA8) for debugging purpose */
  /*
  // Enable GPIOA clock
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
  // Configure MCO pin (PA8)
  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_8;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;  
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  // Select the clock to output
  RCC_MCOConfig(RCC_MCOSource_SYSCLK, RCC_MCODiv_1);
  */
}

#if (USE_PLL_HSE_XTAL != 0) || (USE_PLL_HSE_EXTC != 0)
/******************************************************************************/
/*            PLL (clocked by HSE) used as System clock source                */
/******************************************************************************/
uint8_t SetSysClock_PLL_HSE(uint8_t bypass)
{
  __IO uint32_t StartUpCounter = 0;
  __IO uint32_t HSEStatus = 0;

  /* Bypass HSE: can be done only if HSE is OFF */
  RCC->CR &= ((uint32_t)~RCC_CR_HSEON); /* To be sure HSE is OFF */  
  if (bypass != 0)
  {
    RCC->CR |= ((uint32_t)RCC_CR_HSEBYP);
  }
  else
  {
    RCC->CR &= ((uint32_t)~RCC_CR_HSEBYP);
  }
  
  /* Enable HSE */
  RCC->CR |= ((uint32_t)RCC_CR_HSEON);
  
  /* Wait till HSE is ready */
  do
  {
    HSEStatus = RCC->CR & RCC_CR_HSERDY;
    StartUpCounter++;
  } while((HSEStatus == 0) && (StartUpCounter != HSE_STARTUP_TIMEOUT));

  /* Check if HSE has started correctly */
  if ((RCC->CR & RCC_CR_HSERDY) != RESET)
  {
    /* Enable 64-bit access */
    FLASH->ACR |= FLASH_ACR_ACC64;

    /* Enable Prefetch Buffer */
    FLASH->ACR |= FLASH_ACR_PRFTEN;

    /* Flash 1 wait state (latency) */
    FLASH->ACR |= FLASH_ACR_LATENCY;

    /* Power enable */
    RCC->APB1ENR |= RCC_APB1ENR_PWREN;

    /* Select the Voltage Range 1 (1.8 V) */
    PWR->CR = PWR_CR_VOS_0;

    /* Wait Until the Voltage Regulator is ready */
    while((PWR->CSR & PWR_CSR_VOSF) != RESET)
    {
    }

    /* PLL configuration */
    /* SYSCLK = 24 MHz ((8 MHz * 6) / 2) */
    /* USBCLK = 48 MHz (8 MHz * 6) --> USB OK */
    RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_PLLSRC | RCC_CFGR_PLLMUL | RCC_CFGR_PLLDIV));
    RCC->CFGR |= (uint32_t)(RCC_CFGR_PLLSRC_HSE | RCC_CFGR_PLLMUL6 | RCC_CFGR_PLLDIV2   
                          | RCC_CFGR_HPRE_DIV1    /* HCLK   = 24 MHz */
                          | RCC_CFGR_PPRE2_DIV1   /* PCLK2  = 24 MHz */
                          | RCC_CFGR_PPRE1_DIV1); /* PCLK1  = 24 MHz */

    /* Enable PLL */
    RCC->CR |= RCC_CR_PLLON;

    /* Wait till PLL is ready */
    while((RCC->CR & RCC_CR_PLLRDY) == 0)
    {
    }
    
    /* Select PLL as system clock source */
    RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));
    RCC->CFGR |= (uint32_t)RCC_CFGR_SW_PLL;

    /* Wait till PLL is used as system clock source */
    while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS) != (uint32_t)RCC_CFGR_SWS_PLL)
    {
    }

    return 1; // OK
  }
  else
  {
    return 0; // FAIL
  }
}
#endif

/******************************************************************************/
/*            PLL (clocked by HSI) used as System clock source                */
/******************************************************************************/
uint8_t SetSysClock_PLL_HSI(void)
{
  __IO uint32_t StartUpCounter = 0;
  __IO uint32_t HSIStatus = 0;

  /* Enable HSI */
  RCC->CR |= ((uint32_t)RCC_CR_HSION);

  /* Wait till HSI is ready */
  do
  {
    HSIStatus = RCC->CR & RCC_CR_HSIRDY;
    StartUpCounter++;
  } while((HSIStatus == 0) && (StartUpCounter != HSI_STARTUP_TIMEOUT));

  if ((RCC->CR & RCC_CR_HSIRDY) != RESET)
  {
    /* Enable 64-bit access */
    FLASH->ACR |= FLASH_ACR_ACC64;

    /* Enable Prefetch Buffer */
    FLASH->ACR |= FLASH_ACR_PRFTEN;

    /* Flash 1 wait state (latency) */
    FLASH->ACR |= FLASH_ACR_LATENCY;

    /* Power enable */
    RCC->APB1ENR |= RCC_APB1ENR_PWREN;

    /* Select the Voltage Range 1 (1.8 V) */
    PWR->CR = PWR_CR_VOS_0;

    /* Wait Until the Voltage Regulator is ready */
    while((PWR->CSR & PWR_CSR_VOSF) != RESET)
    {
    }

    /* PLL configuration */
    /* SYSCLK = 32 MHz ((16 MHz * 4) / 2) */
    /* USBCLK = 64 MHz (16 MHz * 4) --> USB not possible */
    RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_PLLSRC | RCC_CFGR_PLLMUL | RCC_CFGR_PLLDIV));
    RCC->CFGR |= (uint32_t)(RCC_CFGR_PLLSRC_HSI | RCC_CFGR_PLLMUL4 | RCC_CFGR_PLLDIV2   
                          | RCC_CFGR_HPRE_DIV1    /* HCLK   = 32 MHz */
                          | RCC_CFGR_PPRE2_DIV1   /* PCLK2  = 32 MHz */
                          | RCC_CFGR_PPRE1_DIV1); /* PCLK1  = 32 MHz */

    /* Enable PLL */
    RCC->CR |= RCC_CR_PLLON;

    /* Wait till PLL is ready */
    while((RCC->CR & RCC_CR_PLLRDY) == 0)
    {
    }
    
    /* Select PLL as system clock source */
    RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));
    RCC->CFGR |= (uint32_t)RCC_CFGR_SW_PLL;

    /* Wait till PLL is used as system clock source */
    while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS) != (uint32_t)RCC_CFGR_SWS_PLL)
    {
    }

    return 1; // OK
  }
  else
  {
    return 0; // FAIL
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

/******************* (C) COPYRIGHT 2013 STMicroelectronics *****END OF FILE****/
