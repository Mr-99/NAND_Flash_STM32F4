#include "h_spi.h"
#include "delay.h"
#define LCD1_CS_SET (HAL_GPIO_WritePin(lcd1_cs_GPIO_Port,lcd1_cs_Pin,GPIO_PIN_SET))
#define LCD1_CS_CLR (HAL_GPIO_WritePin(lcd1_cs_GPIO_Port,lcd1_cs_Pin,GPIO_PIN_RESET))
#define LCD1_RS_SET (HAL_GPIO_WritePin(lcd1_dc_GPIO_Port,lcd1_dc_Pin,GPIO_PIN_SET))
#define LCD1_RS_CLR (HAL_GPIO_WritePin(lcd1_dc_GPIO_Port,lcd1_dc_Pin,GPIO_PIN_RESET))
#define LCD1_RST_SET (HAL_GPIO_WritePin(lcd1_res_GPIO_Port,lcd1_res_Pin,GPIO_PIN_SET))
#define LCD1_RST_CLR (HAL_GPIO_WritePin(lcd1_res_GPIO_Port,lcd1_res_Pin,GPIO_PIN_RESET))
SPI_HandleTypeDef hspi1;
//对应的spi的GPIO口
void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, lcd1_res_Pin|lcd1_cs_Pin|lcd1_dc_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(Contact_PinA7_GPIO_Port, Contact_PinA7_Pin, GPIO_PIN_SET);

  /*Configure GPIO pins : PAPin PAPin PAPin */
  GPIO_InitStruct.Pin = lcd1_res_Pin|lcd1_cs_Pin|lcd1_dc_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = Contact_PinA7_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(Contact_PinA7_GPIO_Port, &GPIO_InitStruct);

}
//END
/* SPI1 init function */
void MX_SPI1_Init(void)
{

  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_HIGH;
  hspi1.Init.CLKPhase = SPI_PHASE_2EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_256;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_LSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 7;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
//    Error_Handler();
  }

}

void HAL_SPI_MspInit(SPI_HandleTypeDef* spiHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(spiHandle->Instance==SPI1)
  {
  /* USER CODE BEGIN SPI1_MspInit 0 */

  /* USER CODE END SPI1_MspInit 0 */
    /* SPI1 clock enable */
    __HAL_RCC_SPI1_CLK_ENABLE();
  
    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**SPI1 GPIO Configuration    
    PA5     ------> SPI1_SCK
    PA7     ------> SPI1_MOSI 
    */
    GPIO_InitStruct.Pin = GPIO_PIN_5|GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF5_SPI1;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* USER CODE BEGIN SPI1_MspInit 1 */

  /* USER CODE END SPI1_MspInit 1 */
  }
}

void HAL_SPI_MspDeInit(SPI_HandleTypeDef* spiHandle)
{

  if(spiHandle->Instance==SPI1)
  {
  /* USER CODE BEGIN SPI1_MspDeInit 0 */

  /* USER CODE END SPI1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_SPI1_CLK_DISABLE();
  
    /**SPI1 GPIO Configuration    
    PA5     ------> SPI1_SCK
    PA7     ------> SPI1_MOSI 
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_5|GPIO_PIN_7);

  /* USER CODE BEGIN SPI1_MspDeInit 1 */

  /* USER CODE END SPI1_MspDeInit 1 */
  }
} 

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
//上面是基础结构
//下面是对上面函数的组织
uint8_t SPI1_ReadWriteByte(uint8_t TxData)
{
    uint8_t Rxdata;
//    HAL_SPI_TransmitReceive(&hspi1,&TxData,&Rxdata,1, 0);      
        HAL_SPI_Transmit(&hspi1,&TxData,1, 0); 	
 	return Rxdata;          		    //返回收到的数据		
}
/****************************************************************************
* 名    称：Lcd1_WriteData(uint8_t Data)
* 功    能：向液晶屏写一个8位数据
* 入口参数：dat     寄存器数据
* 出口参数：无
* 说    明：向控制器指定地址写入数据，内部函数
****************************************************************************/

void Lcd1_WriteData(uint8_t Data)
{
   LCD1_CS_CLR;
	//delay_us(50);
	LCD1_RS_SET;//Cmmand:0 Data:1
		delay_us(50);
   SPI1_ReadWriteByte(Data);
//   Lcd1_CS_SET;
}
/****************************************************************************
* 名    称：Lcd1_WriteIndex(uint8_t Index)
* 功    能：向液晶屏写一个8位指令
* 入口参数：Index   寄存器地址
* 出口参数：无
* 说    明：调用前需先选中控制器，内部函数
****************************************************************************/
void Lcd1_WriteIndex(uint8_t Index)
{
   LCD1_CS_CLR;
	//delay_us(50);
   LCD1_RS_CLR;  
	delay_us(50);
   SPI1_ReadWriteByte(Index);
//   Lcd1_CS_SET;
}
/****************************************************************************
* 名    称：void Lcd1_WriteData_16Bit(uint16_t Data)
* 功    能：向液晶屏写一个16位数据
* 入口参数：Data
* 出口参数：无
* 说    明：向控制器指定地址写入一个16位数据
****************************************************************************/
void Lcd1_WriteData_16Bit(uint16_t Data)
{	
	Lcd1_WriteData(Data>>8);
	Lcd1_WriteData(Data);	
}
/****************************************************************************
* 名    称：void Lcd1_WriteReg(uint8_t Index,uint16_t Data)
* 功    能：写寄存器数据
* 入口参数：Index,Data
* 出口参数：无
* 说    明：本函数为组合函数，向Index地址的寄存器写入Data值
****************************************************************************/
void Lcd1_WriteReg(uint8_t Index,uint16_t Data)
{
	  Lcd1_WriteIndex(Index);
  	Lcd1_WriteData_16Bit(Data);
}
/****************************************************************************
* 名    称：void Lcd1_Reset(void)
* 功    能：液晶硬复位函数
* 入口参数：无
* 出口参数：无
* 说    明：液晶初始化前需执行一次复位操作
****************************************************************************/
void Lcd1_Reset(void)
{
	LCD1_RST_CLR;
	delay_ms(100);
	LCD1_RST_SET;
	delay_ms(50);
}
/****************************************************************************
* 名    称：void Lcd1_Init(void)
* 功    能：液晶初始化函数
* 入口参数：无
* 出口参数：无
* 说    明：液晶初始化_ILI9225_176X220
****************************************************************************/
void Lcd1_Init(void)
{	
	//2.2inch TM2.2-G2.2 Init 20171020 
	Lcd1_WriteIndex(0x11);  
	Lcd1_WriteData(0x00); 

	Lcd1_WriteIndex(0xCF);  
	Lcd1_WriteData(0X00); 
	Lcd1_WriteData(0XC1); 
	Lcd1_WriteData(0X30);

	Lcd1_WriteIndex(0xED);  
	Lcd1_WriteData(0X64); 
	Lcd1_WriteData(0X03); 
	Lcd1_WriteData(0X12);
	Lcd1_WriteData(0X81);

	Lcd1_WriteIndex(0xE8);  
	Lcd1_WriteData(0X85); 
	Lcd1_WriteData(0X11); 
	Lcd1_WriteData(0X78);

	Lcd1_WriteIndex(0xF6);  
	Lcd1_WriteData(0X01); 
	Lcd1_WriteData(0X30); 
	Lcd1_WriteData(0X00);

	Lcd1_WriteIndex(0xCB);  
	Lcd1_WriteData(0X39); 
	Lcd1_WriteData(0X2C); 
	Lcd1_WriteData(0X00);
	Lcd1_WriteData(0X34);
	Lcd1_WriteData(0X05);

	Lcd1_WriteIndex(0xF7);  
	Lcd1_WriteData(0X20); 

	Lcd1_WriteIndex(0xEA);  
	Lcd1_WriteData(0X00); 
	Lcd1_WriteData(0X00); 

	Lcd1_WriteIndex(0xC0);  
	Lcd1_WriteData(0X20); 

	Lcd1_WriteIndex(0xC1);  
	Lcd1_WriteData(0X11); 

	Lcd1_WriteIndex(0xC5);  
	Lcd1_WriteData(0X31); 
	Lcd1_WriteData(0X3C); 

	Lcd1_WriteIndex(0xC7);  
	Lcd1_WriteData(0XA9); 

	Lcd1_WriteIndex(0x3A);  
	Lcd1_WriteData(0X55); 
	
  Lcd1_WriteIndex(0x36);  
	#if USE_HORIZONTAL
		 Lcd1_WriteData(0xE8);//横屏参数
	#else
		 Lcd1_WriteData(0x48);//竖屏参数 
	#endif

	Lcd1_WriteIndex(0xB1);  
	Lcd1_WriteData(0X00); 
	Lcd1_WriteData(0X18); 

	Lcd1_WriteIndex(0xB4);  
	Lcd1_WriteData(0X00); 
	Lcd1_WriteData(0X00); 

	Lcd1_WriteIndex(0xF2);  
	Lcd1_WriteData(0X00); 

	Lcd1_WriteIndex(0x26);  
	Lcd1_WriteData(0X01); 

	Lcd1_WriteIndex(0xE0);  
	Lcd1_WriteData(0X0F); 
	Lcd1_WriteData(0X17); 
	Lcd1_WriteData(0X14); 
	Lcd1_WriteData(0X09); 
	Lcd1_WriteData(0X0C); 
	Lcd1_WriteData(0X06); 
	Lcd1_WriteData(0X43); 
	Lcd1_WriteData(0X75); 
	Lcd1_WriteData(0X36); 
	Lcd1_WriteData(0X08); 
	Lcd1_WriteData(0X13); 
	Lcd1_WriteData(0X05); 
	Lcd1_WriteData(0X10); 
	Lcd1_WriteData(0X0B); 
	Lcd1_WriteData(0X08); 


	Lcd1_WriteIndex(0xE1);  
	Lcd1_WriteData(0X00); 
	Lcd1_WriteData(0X1F); 
	Lcd1_WriteData(0X23); 
	Lcd1_WriteData(0X03); 
	Lcd1_WriteData(0X0E); 
	Lcd1_WriteData(0X04); 
	Lcd1_WriteData(0X39); 
	Lcd1_WriteData(0X25); 
	Lcd1_WriteData(0X4D); 
	Lcd1_WriteData(0X06); 
	Lcd1_WriteData(0X0D); 
	Lcd1_WriteData(0X0B); 
	Lcd1_WriteData(0X33); 
	Lcd1_WriteData(0X37); 
	Lcd1_WriteData(0X0F); 

	Lcd1_WriteIndex(0x29);  	
}
/*************************************************
函数名：Lcd1_Set_XY
功能：设置Lcd1显示起始点
入口参数：xy坐标
返回值：无
*************************************************/
void Lcd1_SetXY(uint16_t Xpos, uint16_t Ypos)
{	
	Lcd1_WriteIndex(0x2A);
	Lcd1_WriteData_16Bit(Xpos);
	Lcd1_WriteIndex(0x2B);
	Lcd1_WriteData_16Bit(Ypos);
	Lcd1_WriteIndex(0x2c);	
} 
