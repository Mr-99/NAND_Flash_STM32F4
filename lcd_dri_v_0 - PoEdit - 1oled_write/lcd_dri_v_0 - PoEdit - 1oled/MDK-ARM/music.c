#include "delay.h"
#include "stm32f4xx_hal.h"
#include "music.h" 
#define music_Pin GPIO_PIN_7
#define music_GPIO_Port GPIOE
//
#define MUSIC_SET  PEout(7)=1
#define MUSIC_CLR  PEout(7)=0
void music_init(void)
     {		 
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  __HAL_RCC_GPIOC_CLK_ENABLE();
	  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(music_GPIO_Port, music_Pin, GPIO_PIN_RESET);
	 /*Configure GPIO pin : back_Pin */
  GPIO_InitStruct.Pin = music_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(music_GPIO_Port, &GPIO_InitStruct);
     }
void music_on(unsigned char n)
			 {
			unsigned char i;
			MUSIC_CLR;
			MUSIC_SET;	
			delay_ms(6);
for(i=0x01;i!=0;i=i<<1)
		 {
			if(n&i)
			   {
			MUSIC_CLR;
      delay_us(500);
      MUSIC_SET;	
			delay_ms(1);
			delay_us(500);
					 
				 }
				 else
			   {
			MUSIC_CLR;
      delay_ms(1);
			delay_us(500);
      MUSIC_SET;
      delay_us(500);
				 }
		 }
		 	MUSIC_CLR;
			 }