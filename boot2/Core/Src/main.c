/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "ethernet.h"
#include "stm32f1xx_it.h"
#include "flash_if.h"
#include "stm32f1xx_hal_wwdg.h"

RTC_HandleTypeDef hrtc;

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_RTC_Init(void);
static void MX_ETH_Init(void);
void DeSystemClock_Config(void);
static void MX_WWDG_Init(void);
static void MX_CRC_Init(void);
static uint32_t TimeoutCalculation(uint32_t timevalue);

WWDG_HandleTypeDef hwwdg;

int main(void)
{
 MX_GPIO_Init();

 

 FLASH_If_Init();
 HAL_Init();
 SystemClock_Config();

 load_struct_flash_data();
 MX_GPIO_Init();
 MX_DMA_Init();
 MX_ETH_Init();
 BOOT_EthernetInit();
//  MX_RTC_Init();
  step_boot=1;
  if (HAL_RTCEx_BKUPRead(&hrtc,2)!=0)
  {
   step_boot=4;
   timer_to_app=0;
   flag_app_start=0;
   HAL_RTCEx_BKUPWrite(&hrtc,2,1);
  }
 while (1)
  {
   uIP_PeriodicFunc();
   if (flag_app_start==1)
    {
     jamp_to_app();
     
    }
  }
}

void SystemClock_Config(void)
{
 RCC_OscInitTypeDef RCC_OscInitStruct = {0};
 RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
 RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};
 RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE|RCC_OSCILLATORTYPE_LSE;
 RCC_OscInitStruct.HSEState = RCC_HSE_ON;
 RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV6;
 RCC_OscInitStruct.LSEState = RCC_LSE_ON;
 RCC_OscInitStruct.HSIState = RCC_HSI_ON;
 RCC_OscInitStruct.Prediv1Source = RCC_PREDIV1_SOURCE_PLL2;
 RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
 RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
 RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL5;
 RCC_OscInitStruct.PLL2.PLL2State = RCC_PLL2_ON;
 RCC_OscInitStruct.PLL2.PLL2MUL = RCC_PLL2_MUL16;
 RCC_OscInitStruct.PLL2.HSEPrediv2Value = RCC_HSE_PREDIV2_DIV4;
 if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_RTC;
  PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSE;
  PeriphClkInit.PLLI2S.PLLI2SMUL = RCC_PLLI2S_MUL16;
  PeriphClkInit.PLLI2S.HSEPrediv2Value = RCC_HSE_PREDIV2_DIV4;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
  HAL_RCC_MCOConfig(RCC_MCO, RCC_MCO1SOURCE_PLL3CLK, RCC_MCODIV_1);
  /** Configure the Systick interrupt time
  */
  __HAL_RCC_HSE_PREDIV2_CONFIG(RCC_HSE_PREDIV2_DIV4);
  /** Configure the Systick interrupt time
  */
  __HAL_RCC_PLLI2S_CONFIG(RCC_PLLI2S_MUL16);
  /** Configure the Systick interrupt time
  */
  __HAL_RCC_PLLI2S_ENABLE();
}
void MX_RTC_Init(void)
{

  /* USER CODE BEGIN RTC_Init 0 */

  /* USER CODE END RTC_Init 0 */

  RTC_TimeTypeDef sTime = {0};
  RTC_DateTypeDef DateToUpdate = {0};

  /* USER CODE BEGIN RTC_Init 1 */

  /* USER CODE END RTC_Init 1 */
  /** Initialize RTC Only
  */
  hrtc.Instance = RTC;
  hrtc.Init.AsynchPrediv = RTC_AUTO_1_SECOND;
  hrtc.Init.OutPut = RTC_OUTPUTSOURCE_NONE;
  if (HAL_RTC_Init(&hrtc) != HAL_OK)
  {
    Error_Handler();
  }

  /* USER CODE BEGIN Check_RTC_BKUP */

  /* USER CODE END Check_RTC_BKUP */

  /** Initialize RTC and set the Time and Date
  */
  
  
  
  HAL_RTC_GetTime (&hrtc,&sTime,RTC_FORMAT_BIN);
  
  
//  sTime.Hours = 0x10;
//  sTime.Minutes = 0x12;
//  sTime.Seconds = 0x22;

  if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN) != HAL_OK)
  {
    Error_Handler();
  }
  
  
  HAL_RTC_GetDate (&hrtc,&DateToUpdate,RTC_FORMAT_BIN);
//  DateToUpdate.WeekDay = RTC_WEEKDAY_FRIDAY;
//  DateToUpdate.Month = RTC_MONTH_DECEMBER;
//  DateToUpdate.Date = 0x12;
if (DateToUpdate.Year <20)
{
  DateToUpdate.Year = 20;
}
  if (HAL_RTC_SetDate(&hrtc, &DateToUpdate, RTC_FORMAT_BIN) != HAL_OK)
  {
    Error_Handler();
  }
}
/**
  * @brief ETH Initialization Function
  * @param None
  * @retval None
  */
static void MX_ETH_Init(void)
{
  hetho.Instance = ETH;
  hetho.Init.AutoNegotiation = ETH_AUTONEGOTIATION_ENABLE;
  hetho.Init.Speed = ETH_SPEED_100M;
  hetho.Init.DuplexMode = ETH_MODE_FULLDUPLEX;
  hetho.Init.PhyAddress = LAN8742A_PHY_ADDRESS;
  hetho.Init.MACAddr[0] =   00;
  hetho.Init.MACAddr[1] =   ((uint16_t)idBase0[0])>>8;
  hetho.Init.MACAddr[2] =   (uint16_t)idBase1[0];
  hetho.Init.MACAddr[3] =   ((uint16_t)idBase1[0])>>8;
  hetho.Init.MACAddr[4] =   (uint16_t)idBase2[0];
  hetho.Init.MACAddr[5] =   ((uint16_t)idBase2[0])>>8;  
  hetho.Init.RxMode = ETH_RXINTERRUPT_MODE;
  hetho.Init.ChecksumMode = ETH_CHECKSUM_BY_SOFTWARE;
  hetho.Init.MediaInterface = ETH_MEDIA_INTERFACE_RMII;
  if (HAL_ETH_Init(&hetho) != HAL_OK)
  {
    Error_Handler();
  }
}

static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* Configure DMA request hdma_ETHtomem_dma1_channel1 on DMA1_Channel1 */
  hdma_ETHtomem_dma1_channel1.Instance = DMA1_Channel1;
  hdma_ETHtomem_dma1_channel1.Init.Direction = DMA_PERIPH_TO_MEMORY;
  hdma_ETHtomem_dma1_channel1.Init.PeriphInc = DMA_PINC_ENABLE;
  hdma_ETHtomem_dma1_channel1.Init.MemInc = DMA_MINC_ENABLE;
  hdma_ETHtomem_dma1_channel1.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
  hdma_ETHtomem_dma1_channel1.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
  hdma_ETHtomem_dma1_channel1.Init.Mode = DMA_NORMAL;
  hdma_ETHtomem_dma1_channel1.Init.Priority = DMA_PRIORITY_HIGH;
  if (HAL_DMA_Init(&hdma_ETHtomem_dma1_channel1) != HAL_OK)
  {
    Error_Handler( );
  }

}


static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  uint32_t pvalue = 0U;
  uint32_t backupregister = 0U;
  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(PHY_RST_GPIO_Port, PHY_RST_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, LED_RED_Pin, GPIO_PIN_RESET);
  
/* USER CODE BEGIN ETH_MspInit 0 */

  /* USER CODE END ETH_MspInit 0 */
    /* Enable Peripheral clock */
    __HAL_RCC_ETH_CLK_ENABLE();

    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**ETH GPIO Configuration
    PC1     ------> ETH_MDC
    PA1     ------> ETH_REF_CLK
    PA2     ------> ETH_MDIO
    PA7     ------> ETH_CRS_DV
    PC4     ------> ETH_RXD0
    PC5     ------> ETH_RXD1
    PB10     ------> ETH_RX_ER
    PB11     ------> ETH_TX_EN
    PB12     ------> ETH_TXD0
    PB13     ------> ETH_TXD1
    */
    GPIO_InitStruct.Pin = GPIO_PIN_1;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_1|GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_2;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_4|GPIO_PIN_5;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  
  
   /*Configure GPIO pins : LED_GREEN_Pin LED_RED_Pin */
  GPIO_InitStruct.Pin = LED_RED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : PA8 */
  GPIO_InitStruct.Pin = GPIO_PIN_8;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
void DeSystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  RCC_OscInitStruct.PLL2.PLL2State = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure the Systick interrupt time
  */
  __HAL_RCC_PLLI2S_ENABLE();
}

/* USER CODE END 4 */

 /**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM1 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
 if (htim->Instance == TIM1) 
 {
  HAL_IncTick();
  timer_uip++;
  if((timer_uip%500)==0)
   {
    fPassed500ms=true;
    if(timer_uip >= 10000)
     {
      fPassed10s=true;
      timer_uip=0;
     }
//    HAL_GPIO_TogglePin (LED_RED_GPIO_Port, LED_RED_Pin);
   }
  
  if (step_boot==4)
    {
     if (ct_led_timer>3000)
      {
        HAL_GPIO_TogglePin (LED_RED_GPIO_Port, LED_RED_Pin);
        ct_led_timer=0;
      }
     else
     {
      ct_led_timer++;
     }
    }
  else
    {
      if (ct_led_timer>500)
      {
        HAL_GPIO_TogglePin (LED_RED_GPIO_Port, LED_RED_Pin);
        ct_led_timer=0;
      }
       else
     {
      ct_led_timer++;
     }
    }
  
  if((HAL_GPIO_ReadPin(IN_SWICH_GPIO_Port,IN_SWICH_Pin)==1)&&(step_boot==1))
    {
      timer_to_app=0;
      flag_app_start=1;
    }
   if((HAL_GPIO_ReadPin(IN_SWICH_GPIO_Port,IN_SWICH_Pin)==0)&&(step_boot==1))
    {
      step_boot=2;
      timer_start_app++;
    }
    if((HAL_GPIO_ReadPin(IN_SWICH_GPIO_Port,IN_SWICH_Pin)==0)&&(step_boot==2))
    {      
      timer_start_app++;
    }
   if((HAL_GPIO_ReadPin(IN_SWICH_GPIO_Port,IN_SWICH_Pin)==1)&&(step_boot==2))
    {
      if(timer_start_app<5000)
        {
          step_boot=4;
          timer_to_app=0;
        }
      else
        {
          step_boot=3;
          load_def_data();
          flag_app_start=1;
          timer_to_app=0;
        }
      
    }
 
    
  
  
  if (step_boot==4)
  {
    if (timer_to_app<TIME_TO_APP)
      {
        timer_to_app++;
      }
    else
      {
        timer_to_app=0;
        flag_app_start=1;
      }
  }
 }
}
static void MX_WWDG_Init(void)
{

  /* USER CODE BEGIN WWDG_Init 0 */

  /* USER CODE END WWDG_Init 0 */

  /* USER CODE BEGIN WWDG_Init 1 */

  /* USER CODE END WWDG_Init 1 */
  hwwdg.Instance = WWDG;
  hwwdg.Init.Prescaler = WWDG_PRESCALER_1;
  hwwdg.Init.Window = 16;//fghm
  hwwdg.Init.Counter = 0xc0;
  hwwdg.Init.EWIMode = WWDG_EWI_DISABLE;
  if (HAL_WWDG_Init(&hwwdg) != HAL_OK)
  {
    Error_Handler();
  }
  
  /* USER CODE BEGIN WWDG_Init 2 */

  /* USER CODE END WWDG_Init 2 */

}


/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
static uint32_t TimeoutCalculation(uint32_t timevalue)
{
  uint32_t timeoutvalue = 0;
  uint32_t pclk1 = 0;
  uint32_t wdgtb = 0;

  /* considering APB divider is still 1, use HCLK value */
  pclk1 = HAL_RCC_GetPCLK1Freq();

  /* get prescaler */
  wdgtb = (1 << ((hwwdg.Init.Prescaler) >> 7)); /* 2^WDGTB[1:0] */

  /* calculate timeout */
  timeoutvalue = ((4096 * wdgtb * timevalue) / (pclk1 / 1000));

  return timeoutvalue;
}
#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
