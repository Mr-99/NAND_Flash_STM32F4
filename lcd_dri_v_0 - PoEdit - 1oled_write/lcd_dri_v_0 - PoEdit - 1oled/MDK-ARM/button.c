#include "button.h" 
#define key0_Pin GPIO_PIN_4
#define key0_GPIO_Port GPIOD
#define key1_Pin GPIO_PIN_5
#define key1_GPIO_Port GPIOD
#define key2_Pin GPIO_PIN_0
#define key2_GPIO_Port GPIOA
#define key3_Pin GPIO_PIN_2
#define key3_GPIO_Port GPIOE
#define key4_Pin GPIO_PIN_3
#define key4_GPIO_Port GPIOE
//°´¼ü
#define key0 PDin(4)
#define key1 PDin(5)
#define key2 PAin(0)
#define key3 PEin(2)
#define key4 PEin(3)
void botton_init(void)
		 {
 GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  /*Configure GPIO pins : PEPin PEPin */
  GPIO_InitStruct.Pin = key3_Pin|key4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = key0_Pin|key1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(key0_GPIO_Port, &GPIO_InitStruct);
		}
//°´¼ü¼ì²â0
uint8_t key0_in(void)
   {
	 static uint8_t temp=0,bit=0,down=0;
		bit = key0;
 temp=(temp<<1)|bit;
 if((temp&0x0f)==0x00)
     {
		   down = 1;
		 }
 if((down==1)&&((temp&0x0f)==0x0f))
     {
    down = 0;
    return 1;
     }
return 0;
	 }	
	 //°´¼ü¼ì²â1
uint8_t key1_in(void)
   {
	 static uint8_t temp=0,bit=0,down=0;
		bit = key1;
 temp=(temp<<1)|bit;
 if((temp&0x0f)==0x00)
     {
		   down = 1;
		 }
 if((down==1)&&((temp&0x0f)==0x0f))
     {
    down = 0;
    return 2;
     }
return 0;
	 }	
 //°´¼ü¼ì²â3
uint8_t key3_in(void)
   {
	 static uint8_t temp=0,bit=0,down=0;
		bit = key3;
 temp=(temp<<1)|bit;
 if((temp&0x0f)==0x00)
     {
		   down = 1;
		 }
 if((down==1)&&((temp&0x0f)==0x0f))
     {
    down = 0;
    return 3;
     }
return 0;
	 }	
  //°´¼ü¼ì²â4
uint8_t key4_in(void)
   {
	 static uint8_t temp=0,bit=0,down=0;
		bit = key4;
 temp=(temp<<1)|bit;
 if((temp&0x0f)==0x00)
     {
		   down = 1;
		 }
 if((down==1)&&((temp&0x0f)==0x0f))
     {
    down = 0;
    return 4;
     }
return 0;
	 }