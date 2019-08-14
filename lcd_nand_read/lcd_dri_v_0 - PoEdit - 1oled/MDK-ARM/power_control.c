#include "power_cotrol.h"
/* Private defines -----------------------------------------------------------*/
#define keepOpen_Pin GPIO_PIN_15
#define keepOpen_GPIO_Port GPIOC
#define power_Pin GPIO_PIN_0
#define power_GPIO_Port GPIOA
#define power PAin(0)
#define keepOpen PCin(15)
/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
void MX_Power_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(keepOpen_GPIO_Port, keepOpen_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : keepOpen_Pin */
  GPIO_InitStruct.Pin = keepOpen_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(keepOpen_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : power_Pin */
  GPIO_InitStruct.Pin = power_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(power_GPIO_Port, &GPIO_InitStruct);
}
	
uint8_t Check_power_down(void) 
  {
	 static uint8_t bit=0,down=0;
	 static uint16_t temp = 0xFFFF;
		bit = power;
 temp=(temp<<1)|bit;
 if((temp&0x0f)==0x0f)
     {
		   down = 1;
		 }
 if((down==1)&&(temp&0x0f)==0x00)
     {
    down = 0;
    return 1;
     }
    return 0;
} 
void keepOpen_OFF(void)
{
  HAL_GPIO_WritePin(keepOpen_GPIO_Port, keepOpen_Pin, GPIO_PIN_RESET);
}
void keepOpen_ON(void)
{
  HAL_GPIO_WritePin(keepOpen_GPIO_Port, keepOpen_Pin, GPIO_PIN_SET);
}