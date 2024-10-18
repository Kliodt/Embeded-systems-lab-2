/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "i2c.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "kb.h"
#include "sdk_uart.h"
#include "pca9538.h"
#include "oled.h"
#include "fonts.h"

#include "controller.h"
#include "handlers.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
int initCalculator();
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */
  

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C1_Init();
  MX_USART6_UART_Init();
  /* USER CODE BEGIN 2 */
  oled_Init();

  /* USER CODE END 2 */
 
 

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  initCalculator();

  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage 
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 25;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
int initCalculator() {
    initController ();

    struct HandlerInfo btnSym0 = {appendCharHandler, {.symbol = '0'}};
    struct HandlerInfo btnSym1 = {appendCharHandler, {.symbol = '1'}};
    struct HandlerInfo btnSym2 = {appendCharHandler, {.symbol = '2'}};
    struct HandlerInfo btnSym3 = {appendCharHandler, {.symbol = '3'}};
    struct HandlerInfo btnSym4 = {appendCharHandler, {.symbol = '4'}};
    struct HandlerInfo btnSym5 = {appendCharHandler, {.symbol = '5'}};
    struct HandlerInfo btnSym6 = {appendCharHandler, {.symbol = '6'}};
    struct HandlerInfo btnSym7 = {appendCharHandler, {.symbol = '7'}};
    struct HandlerInfo btnSym8 = {appendCharHandler, {.symbol = '8'}};
    struct HandlerInfo btnSym9 = {appendCharHandler, {.symbol = '9'}};
    
    struct HandlerInfo btnSymPlus = {appendCharHandler, {.symbol = '+'}};
    struct HandlerInfo btnSymMinus = {appendCharHandler, {.symbol = '-'}};
    struct HandlerInfo btnSymMultiply = {appendCharHandler, {.symbol = '*'}};
    struct HandlerInfo btnSymDivide = {appendCharHandler, {.symbol = '/'}};

    struct HandlerInfo btnSymPoint = {appendCharHandler, {.symbol = '.'}};
    struct HandlerInfo btnSymBracketLeft = {appendCharHandler, {.symbol = '('}};
    struct HandlerInfo btnSymBracketRight = {appendCharHandler, {.symbol = ')'}};

    struct HandlerInfo btnEquals = {equalsHandler};
    struct HandlerInfo btnClearOne = {clearOneHandler};
    struct HandlerInfo btnClearAll = {clearAllHandler};

    struct HandlerInfo btnSwitchLayout = {switchLayout};

    // layout 1
    setHandler(BUTTON_SYMBOL_0, btnSym0);
    setHandler(BUTTON_SYMBOL_1, btnSym1);
    setHandler(BUTTON_SYMBOL_2, btnSym2);
    setHandler(BUTTON_SYMBOL_3, btnSym3);
    setHandler(BUTTON_SYMBOL_4, btnSym4);
    setHandler(BUTTON_SYMBOL_5, btnSym5);
    setHandler(BUTTON_SYMBOL_6, btnSym6);
    setHandler(BUTTON_SYMBOL_7, btnSym7);
    setHandler(BUTTON_SYMBOL_8, btnSym8);
    setHandler(BUTTON_SYMBOL_9, btnSym9);
    setHandler(BUTTON_POINT, btnSymPoint);
    setHandler(BUTTON_SWITCH_LAYOUT_1, btnSwitchLayout);
    
    // layout 2
    setHandler(BUTTON_PLUS, btnSymPlus);
    setHandler(BUTTON_MINUS, btnSymMinus);
    setHandler(BUTTON_MULTIPLY, btnSymMultiply);
    setHandler(BUTTON_DIVIDE, btnSymDivide);
    setHandler(BUTTON_LEFT_BRACKET, btnSymBracketLeft);
    setHandler(BUTTON_RIGHT_BRACKET, btnSymBracketRight);

    setHandler(BUTTON_EQUALS, btnEquals);
    setHandler(BUTTON_CLEAR_ONE, btnClearOne);
    setHandler(BUTTON_CLEAR_ALL, btnClearAll);
    setHandler(BUTTON_SWITCH_LAYOUT_2, btnSwitchLayout);

    startListening ();
    return 0;
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
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
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
