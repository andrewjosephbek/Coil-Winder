/* USER CODE BEGIN Header */
#define _USE_MATH_DEFINES
#include <math.h>
#include "liquidcrystal_i2c.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ArborParameters.h"

#include "DRV8825_Stepper.h"
#include "Button.h"
#include "CoilParameters.h"
#include "EyeParameters.h"
#include "Field.h"
#include "UserInput.h"
#include <CoilWinderUtils.h>

/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2023 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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
I2C_HandleTypeDef hi2c1;

TIM_HandleTypeDef htim1;

/* Definitions for UITask */
osThreadId_t UITaskHandle;
const osThreadAttr_t UITask_attributes = {
  .name = "UITask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for motorTask */
osThreadId_t motorTaskHandle;
const osThreadAttr_t motorTask_attributes = {
  .name = "motorTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityAboveNormal,
};
/* USER CODE BEGIN PV */

CoilParameters_t Coil0;
Button_t IncrementButton;
Button_t DecrementButton;
Button_t SelectButton;
UserInput_t UserInput0;

UIField_t WireField;
UIField_t DiamField;
UIField_t WidthField;
UIField_t LayersField;

UIField_t * UIFields[] = {&WireField, &DiamField, &WidthField, &LayersField};

DRV8825_Stepper_t ArborStepper;
DRV8825_Stepper_t EyeStepper;
EyeParameters_t Eye0;
ArborParameters_t Arbor0;

bool redrawUI = true;



/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);
static void MX_TIM1_Init(void);
void StartDefaultTask(void *argument);
void StartTask02(void *argument);

/* USER CODE BEGIN PFP */

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


	Coil_Init(&Coil0, 20, 5000, 100, 1);

    Button_Init(&DecrementButton, GPIOA, DEC_BTN_Pin, 1, 1);
    Button_Init(&IncrementButton, GPIOA, INC_BTN_Pin, 1, 1);
    Button_Init(&SelectButton, GPIOA, SEL_BTN_Pin, 0, 1);

    UserInput_Init(&UserInput0, &DecrementButton, &IncrementButton, &SelectButton);

    UIField_Init(	&WireField,
    					UI_1_X, UI_1_Y, UI_FIELD_OFFSET, UI_1_MULT, FIXED_POINT_PRECISION,
    					"Wire[mm]",
    					&UserInput0,
    					Coil_getWireDiam_10um, Coil_incWireDiam_10um);

    	UIField_Init(	&DiamField,
    					UI_2_X, UI_2_Y, UI_FIELD_OFFSET, UI_2_MULT, FIXED_POINT_PRECISION,
    					"Diam[mm]",
    					&UserInput0,
    					Coil_getCoilDiam_10um, Coil_incCoilDiam_10um);

    	UIField_Init(	&WidthField,
    					UI_3_X, UI_3_Y, UI_FIELD_OFFSET, UI_3_MULT, FIXED_POINT_PRECISION,
    					"Width[mm]",
    					&UserInput0,
    					Coil_getCoilWidth_10um, Coil_incCoilWidth_10um);

    	UIField_Init(	&LayersField,
    					UI_4_X, UI_4_Y, UI_FIELD_OFFSET, UI_4_MULT, 0,
    					"Layers",
    					&UserInput0,
    					Coil_getCoilLayers, Coil_incCoilLayers);

    	DRV8825_Init(	&ArborStepper,
    					GPIOA, STEPPER_ARBOR_STP_Pin,
    					GPIOA, STEPPER_A_DIR_Pin,
    					GPIOB, STEPPER_A_SLP_Pin,
    					NULL, -1,
    					NULL, -1,
    					NULL, -1,
    					NULL, -1,
    					NULL, -1, MICROSTEP_LEVEL);

    	DRV8825_Init(	&EyeStepper,
    					GPIOA, STEPPER_B_STP_Pin,
    					GPIOB, STEPPER_B_DIR_Pin,
    					GPIOB, STEPPER_B_SLP_Pin,
    					NULL, -1,
    					NULL, -1,
    					NULL, -1,
    					NULL, -1,
    					NULL, -1, MICROSTEP_LEVEL);

    	Eye_Init(&Eye0, &EyeStepper, EYE_LENGTH, 0.0, EYE_STEPS, GPIOA, LIMIT_SW_Pin);
    	Arbor_Init(&Arbor0, &ArborStepper, 100, ARBOR_STEPS);

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C1_Init();
  MX_TIM1_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Init scheduler */
  osKernelInitialize();

  /* USER CODE BEGIN RTOS_MUTEX */
    /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
    /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
    /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
    /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of UITask */
  UITaskHandle = osThreadNew(StartDefaultTask, NULL, &UITask_attributes);

  /* creation of motorTask */
  motorTaskHandle = osThreadNew(StartTask02, NULL, &motorTask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
    /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
    /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

  /* Start scheduler */
  osKernelStart();

  /* We should never get here as control is now taken by the scheduler */
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
    while (1) {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
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
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 10;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV7;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.Timing = 0x10909CEC;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Analogue filter
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Digital filter
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief TIM1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM1_Init(void)
{

  /* USER CODE BEGIN TIM1_Init 0 */

  /* USER CODE END TIM1_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM1_Init 1 */

  /* USER CODE END TIM1_Init 1 */
  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 80-1;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 0xffff-1;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterOutputTrigger2 = TIM_TRGO2_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM1_Init 2 */

  /* USER CODE END TIM1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, STEPPER_ARBOR_STP_Pin|STEPPER_A_DIR_Pin|MICROSTEP_M1_Pin|MICROSTEP_M0_Pin
                          |STEPPER_B_STP_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, STEPPER_A_SLP_Pin|MICROSTEP_M2_Pin|STEPPER_ENABLE_Pin|STEPPER_B_DIR_Pin
                          |STEPPER_B_SLP_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : LIMIT_SW_Pin INC_BTN_Pin SEL_BTN_Pin DEC_BTN_Pin */
  GPIO_InitStruct.Pin = LIMIT_SW_Pin|INC_BTN_Pin|SEL_BTN_Pin|DEC_BTN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : STEPPER_ARBOR_STP_Pin STEPPER_B_STP_Pin */
  GPIO_InitStruct.Pin = STEPPER_ARBOR_STP_Pin|STEPPER_B_STP_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : STEPPER_A_DIR_Pin MICROSTEP_M1_Pin MICROSTEP_M0_Pin */
  GPIO_InitStruct.Pin = STEPPER_A_DIR_Pin|MICROSTEP_M1_Pin|MICROSTEP_M0_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : STEPPER_A_SLP_Pin MICROSTEP_M2_Pin STEPPER_ENABLE_Pin STEPPER_B_DIR_Pin
                           STEPPER_B_SLP_Pin */
  GPIO_InitStruct.Pin = STEPPER_A_SLP_Pin|MICROSTEP_M2_Pin|STEPPER_ENABLE_Pin|STEPPER_B_DIR_Pin
                          |STEPPER_B_SLP_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
/* USER CODE END 4 */

/* USER CODE BEGIN Header_StartDefaultTask */
/**
 * @brief  Function implementing the defaultTask thread.
 * @param  argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN 5 */

    unsigned int uiMaster = HALF_UINT_MAX;
    uint8_t uiControl = 0;


    HD44780_Init(4);

    HAL_Delay(1000);

	HD44780_Clear();

    /* Infinite loop */
    for (;;) {

    	if(redrawUI) {
			for(int ii = 0; ii < 4; ii++) {
				UIField_PrintTitle(UIFields[ii]);
				UIField_Print(UIFields[ii], &Coil0);
			}

			HD44780_SetCursor(UI_5_X, UI_5_Y);
            HD44780_PrintStr("~");

			redrawUI = false;
    	}



    	UserInput_Update(&UserInput0);

        uiMaster += (UserInput_Get(&UserInput0) == Select);

        uiControl = (uiMaster) % 5;



        bool field_modified = ! (UserInput_Get(&UserInput0) == Select || UserInput_Get(&UserInput0) == None);

        if (field_modified)
            HD44780_NoCursor();
        else
            HD44780_Cursor();



        switch (uiControl) {

        case 0:
        case 1:
        case 2:
        case 3:
        	UIField_SetCursorOnField(UIFields[uiControl]);
        	UIField_UpdateValue(UIFields[uiControl], &Coil0);
        	UIField_RePrint(UIFields[uiControl], &Coil0);

            break;

        case 4:
            HD44780_SetCursor(UI_5_X, UI_5_Y);

            if (field_modified && Coil_isValid(&Coil0))
            	vTaskResume(motorTaskHandle);

            break;

        }

        osDelay(10);

    }
  /* USER CODE END 5 */
}

/* USER CODE BEGIN Header_StartTask02 */
/**
 * @brief Function implementing the motorTask thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartTask02 */
void StartTask02(void *argument)
{
  /* USER CODE BEGIN StartTask02 */


	int nCoils, nLayers;
	char str[20];





	vTaskSuspend(motorTaskHandle);


    /* Infinite loop */
    for (;;) {

        	HD44780_Clear();

            nCoils = Coil_getCoilWidth_10um(&Coil0) /  Coil_getWireDiam_10um(&Coil0);
            nLayers = Coil_getCoilLayers(&Coil0);

            Arbor_Start(&Arbor0);
            Eye_Start(&Eye0);

            HAL_Delay(3000);
            HD44780_PrintTitle("Homing E Axis...", 0);

            if(Eye_FindHome(&Eye0) == 0) {


            	HD44780_PrintTitle("Set Arbor Position", 0);
            	HD44780_PrintTitle("[SELECT] to cont.", 1);

                while (UserInput_Get(&UserInput0) != Select);

            	HD44780_Clear();
            	HD44780_PrintTitle("Winding coil...", 0);

				//Coil winding starts here
				for (int layersWound = 0; layersWound < nLayers; layersWound++) {

					//alternate the direction of the winding with each layer
					int dir = (-1 * (layersWound % 2)) | ((layersWound+1) % 2);

					//Once a layer of coils has been wound, advance the eye a half coil distance
					//too ensure that the next layer is wound in the root of the previous layer
					if(layersWound)
						Eye_MoveWireDiameters(&Eye0, &Coil0, 0.5*dir);


					//Each iteration winds a single wrap of coil
					for (int coilsWound = 0; coilsWound < nCoils; coilsWound++) {

						//Print percent completion
		                sprintf(str, "%d", (100*(layersWound * nCoils + coilsWound)) / (nLayers * nCoils));
		                strcat(str, "% Complete");
		                HD44780_PrintTitle(str, 1);

		                //odd bug, initializes GPIO pins for some reason, need to fix
						GPIOB->BRR = (uint32_t)STEPPER_ARBOR_STP_Pin;
						GPIOB->BRR = (uint32_t)STEPPER_B_STP_Pin;

						Arbor_SingleRevolution(&Arbor0, &Coil0);
						Eye_MoveWireDiameters(&Eye0, &Coil0, 1*dir);

					}
				}

            } else {
                HD44780_Clear();
            	HD44780_PrintTitle("Homing Failed :(", 0);
            }

            Arbor_End(&Arbor0);
            Eye_End(&Eye0);
            redrawUI = true;
            vTaskSuspend(motorTaskHandle);
    }
  /* USER CODE END StartTask02 */
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
    while (1) {}
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
       ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
