#include "delay.h"
#include "lcd144_dri.h"
#include "oled.h" //����oled�ӿ�
#define lcd_res_Pin GPIO_PIN_13
#define lcd_res_GPIO_Port GPIOD
#define lcd_clk_Pin GPIO_PIN_6
#define lcd_clk_GPIO_Port GPIOC
#define lcd_sda_Pin GPIO_PIN_7
#define lcd_sda_GPIO_Port GPIOC
#define lcd_cs_Pin GPIO_PIN_8
#define lcd_cs_GPIO_Port GPIOC
#define lcd_dc_Pin GPIO_PIN_9
#define lcd_dc_GPIO_Port GPIOC

//#define LCD_SDA_SET (HAL_GPIO_WritePin(lcd_sda_GPIO_Port,lcd_sda_Pin,GPIO_PIN_SET))
//#define LCD_SDA_CLR (HAL_GPIO_WritePin(lcd_sda_GPIO_Port,lcd_sda_Pin,GPIO_PIN_RESET))
//#define LCD_SCL_SET (HAL_GPIO_WritePin(lcd_clk_GPIO_Port,lcd_clk_Pin,GPIO_PIN_SET))
//#define LCD_SCL_CLR (HAL_GPIO_WritePin(lcd_clk_GPIO_Port,lcd_clk_Pin,GPIO_PIN_RESET))
//#define LCD_CS_SET (HAL_GPIO_WritePin(lcd_cs_GPIO_Port,lcd_cs_Pin,GPIO_PIN_SET))
//#define LCD_CS_CLR (HAL_GPIO_WritePin(lcd_cs_GPIO_Port,lcd_cs_Pin,GPIO_PIN_RESET))
//#define LCD_RS_SET (HAL_GPIO_WritePin(lcd_dc_GPIO_Port,lcd_dc_Pin,GPIO_PIN_SET))
//#define LCD_RS_CLR (HAL_GPIO_WritePin(lcd_dc_GPIO_Port,lcd_dc_Pin,GPIO_PIN_RESET))
//#define LCD_RST_SET (HAL_GPIO_WritePin(lcd_res_GPIO_Port,lcd_res_Pin,GPIO_PIN_SET))
//#define LCD_RST_CLR (HAL_GPIO_WritePin(lcd_res_GPIO_Port,lcd_res_Pin,GPIO_PIN_RESET))


#define LCD_SDA_SET PCout(7)=1
#define LCD_SDA_CLR PCout(7)=0
#define LCD_SCL_SET PCout(6)=1
#define LCD_SCL_CLR PCout(6)=0
#define LCD_CS_SET  PCout(8)=1
#define LCD_CS_CLR  PCout(8)=0
#define LCD_RS_SET  PCout(9)=1
#define LCD_RS_CLR  PCout(9)=0
#define LCD_RST_SET  PDout(13)=1
#define LCD_RST_CLR  PDout(13)=0

/****************************************************************************
* ��    �ƣ�void LCD_GPIO_Init(void)
* ��    �ܣ�STM32_ģ��SPI���õ���GPIO��ʼ��
* ��ڲ�������
* ���ڲ�������
* ˵    ������ʼ��ģ��SPI���õ�GPIO
****************************************************************************/
void LCD_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(lcd_res_GPIO_Port, lcd_res_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, lcd_clk_Pin|lcd_sda_Pin|lcd_cs_Pin|lcd_dc_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : lcd_res_Pin */
  GPIO_InitStruct.Pin = lcd_res_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
  HAL_GPIO_Init(lcd_res_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : lcd_clk_Pin lcd_sda_Pin lcd_cs_Pin lcd_dc_Pin */
  GPIO_InitStruct.Pin = lcd_clk_Pin|lcd_sda_Pin|lcd_cs_Pin|lcd_dc_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);  
}
/****************************************************************************
* ��    �ƣ�void  SPIv_WriteData(uint8_t Data)
* ��    �ܣ�STM32_ģ��SPIдһ���ֽ����ݵײ㺯��
* ��ڲ�����Data
* ���ڲ�������
* ˵    ����STM32_ģ��SPI��дһ���ֽ����ݵײ㺯��
****************************************************************************/
void  SPIv_WriteData(uint8_t Data)
{
	unsigned char i=0;
	for(i=8;i>0;i--)
	{
		if(Data&0x80)	
	  LCD_SDA_SET; //�������
      else LCD_SDA_CLR;
	   
      LCD_SCL_CLR;       
      LCD_SCL_SET;
      Data<<=1; 
	}
}
/****************************************************************************
* ��    �ƣ�Lcd_WriteIndex(uint8_t Index)
* ��    �ܣ���Һ����дһ��8λָ��
* ��ڲ�����Index   �Ĵ�����ַ
* ���ڲ�������
* ˵    ��������ǰ����ѡ�п��������ڲ�����
****************************************************************************/
void Lcd_WriteIndex(uint8_t Index)
{
   LCD_CS_CLR;
   LCD_RS_CLR;
   SPIv_WriteData(Index);
   LCD_CS_SET;
}

/****************************************************************************
* ��    �ƣ�Lcd_WriteData(uint8_t Data)
* ��    �ܣ���Һ����дһ��8λ����
* ��ڲ�����dat     �Ĵ�������
* ���ڲ�������
* ˵    �����������ָ����ַд�����ݣ��ڲ�����
****************************************************************************/
void Lcd_WriteData(uint8_t Data)
{
   LCD_CS_CLR;
   LCD_RS_SET;
   SPIv_WriteData(Data);
   LCD_CS_SET;
}
/****************************************************************************
* ��    �ƣ�void Lcd_WriteData_16Bit(uint16_t Data)
* ��    �ܣ���Һ����дһ��16λ����
* ��ڲ�����Data
* ���ڲ�������
* ˵    �����������ָ����ַд��һ��16λ����
****************************************************************************/
void Lcd_WriteData_16Bit(uint16_t Data)
{	
	Lcd_WriteData(Data>>8);
	Lcd_WriteData(Data);	
}
/****************************************************************************
* ��    �ƣ�void LCD_WriteReg(uint8_t Index,uint16_t Data)
* ��    �ܣ�д�Ĵ�������
* ��ڲ�����Index,Data
* ���ڲ�������
* ˵    ����������Ϊ��Ϻ�������Index��ַ�ļĴ���д��Dataֵ
****************************************************************************/
void LCD_WriteReg(uint8_t Index,uint16_t Data)
{
	  Lcd_WriteIndex(Index);
  	Lcd_WriteData_16Bit(Data);
}


/****************************************************************************
1
* ��    �ƣ�void Lcd_Reset(void)
* ��    �ܣ�Һ��Ӳ��λ����
* ��ڲ�������
* ���ڲ�������
* ˵    ����Һ����ʼ��ǰ��ִ��һ�θ�λ����
****************************************************************************/
void Lcd_Reset(void)
{
	LCD_GPIO_Init();
	LCD_RST_CLR;
	delay_ms(100);
	LCD_RST_SET;
	delay_ms(50);
}
void DISP_WINDOWS(void)
{
Lcd_WriteIndex(0x2A);
Lcd_WriteData(0x00);
Lcd_WriteData(0x02);
Lcd_WriteData(0x00);
Lcd_WriteData(0x81);


Lcd_WriteIndex(0x2B);
Lcd_WriteData(0x00);
Lcd_WriteData(0x03);
Lcd_WriteData(0x00);
Lcd_WriteData(0x82);


Lcd_WriteIndex(0x2C);
}
/****************************************************************************
2
* ��    �ƣ�void Lcd_Init(void)
* ��    �ܣ�Һ����ʼ������
* ��ڲ�������
* ���ڲ�������
* ˵    ����Һ����ʼ��_ILI9225_176X220
****************************************************************************/
void Lcd_Init(void)
{	
	LCD_GPIO_Init();//ʹ��ģ��SPI
	Lcd_Reset(); //Reset before LCD Init.

	//2.2inch TM2.2-G2.2 Init 20171020 
	Lcd_WriteIndex(0x11);  
	Lcd_WriteData(0x00); 

	Lcd_WriteIndex(0xCF);  
	Lcd_WriteData(0X00); 
	Lcd_WriteData(0XC1); 
	Lcd_WriteData(0X30);

	Lcd_WriteIndex(0xED);  
	Lcd_WriteData(0X64); 
	Lcd_WriteData(0X03); 
	Lcd_WriteData(0X12);
	Lcd_WriteData(0X81);

	Lcd_WriteIndex(0xE8);  
	Lcd_WriteData(0X85); 
	Lcd_WriteData(0X11); 
	Lcd_WriteData(0X78);

	Lcd_WriteIndex(0xF6);  
	Lcd_WriteData(0X01); 
	Lcd_WriteData(0X30); 
	Lcd_WriteData(0X00);

	Lcd_WriteIndex(0xCB);  
	Lcd_WriteData(0X39); 
	Lcd_WriteData(0X2C); 
	Lcd_WriteData(0X00);
	Lcd_WriteData(0X34);
	Lcd_WriteData(0X05);

	Lcd_WriteIndex(0xF7);  
	Lcd_WriteData(0X20); 

	Lcd_WriteIndex(0xEA);  
	Lcd_WriteData(0X00); 
	Lcd_WriteData(0X00); 

	Lcd_WriteIndex(0xC0);  
	Lcd_WriteData(0X20); 

	Lcd_WriteIndex(0xC1);  
	Lcd_WriteData(0X11); 

	Lcd_WriteIndex(0xC5);  
	Lcd_WriteData(0X31); 
	Lcd_WriteData(0X3C); 

	Lcd_WriteIndex(0xC7);  
	Lcd_WriteData(0XA9); 

	Lcd_WriteIndex(0x3A);  
	Lcd_WriteData(0X55); 
	
  Lcd_WriteIndex(0x36);  
	#if USE_HORIZONTAL
		 Lcd_WriteData(0xE8);//��������
	#else
		 Lcd_WriteData(0x48);//�������� 
	#endif

	Lcd_WriteIndex(0xB1);  
	Lcd_WriteData(0X00); 
	Lcd_WriteData(0X18); 

	Lcd_WriteIndex(0xB4);  
	Lcd_WriteData(0X00); 
	Lcd_WriteData(0X00); 

	Lcd_WriteIndex(0xF2);  
	Lcd_WriteData(0X00); 

	Lcd_WriteIndex(0x26);  
	Lcd_WriteData(0X01); 

	Lcd_WriteIndex(0xE0);  
	Lcd_WriteData(0X0F); 
	Lcd_WriteData(0X17); 
	Lcd_WriteData(0X14); 
	Lcd_WriteData(0X09); 
	Lcd_WriteData(0X0C); 
	Lcd_WriteData(0X06); 
	Lcd_WriteData(0X43); 
	Lcd_WriteData(0X75); 
	Lcd_WriteData(0X36); 
	Lcd_WriteData(0X08); 
	Lcd_WriteData(0X13); 
	Lcd_WriteData(0X05); 
	Lcd_WriteData(0X10); 
	Lcd_WriteData(0X0B); 
	Lcd_WriteData(0X08); 
	
	
	Lcd_WriteIndex(0xE1);  
	Lcd_WriteData(0X00); 
	Lcd_WriteData(0X1F); 
	Lcd_WriteData(0X23); 
	Lcd_WriteData(0X03); 
	Lcd_WriteData(0X0E); 
	Lcd_WriteData(0X04); 
	Lcd_WriteData(0X39); 
	Lcd_WriteData(0X25); 
	Lcd_WriteData(0X4D); 
	Lcd_WriteData(0X06); 
	Lcd_WriteData(0X0D); 
	Lcd_WriteData(0X0B); 
	Lcd_WriteData(0X33); 
	Lcd_WriteData(0X37); 
	Lcd_WriteData(0X0F); 
 	lcd_display_off();
}



/*************************************************
��������LCD_Set_XY
���ܣ�����lcd��ʾ��ʼ��
��ڲ�����xy����
����ֵ����
*************************************************/
void Lcd_SetXY(uint16_t Xpos, uint16_t Ypos)
{	
	Lcd_WriteIndex(0x2A);
	Lcd_WriteData_16Bit(Xpos+2);
	Lcd_WriteIndex(0x2B);
	Lcd_WriteData_16Bit(Ypos+1);
	Lcd_WriteIndex(0x2c);	
} 
/*************************************************
��������LCD_Set_Region
���ܣ�����lcd��ʾ�����ڴ�����д�������Զ�����
��ڲ�����xy�����յ�
����ֵ����
*************************************************/
//������ʾ����
void Lcd_SetRegion(uint16_t xStar, uint16_t yStar,uint16_t xEnd,uint16_t yEnd)
{
	Lcd_WriteIndex(0x2A);
	Lcd_WriteData_16Bit(xStar);
	Lcd_WriteData_16Bit(xEnd);
	Lcd_WriteIndex(0x2B);
	Lcd_WriteData_16Bit(yStar);
	Lcd_WriteData_16Bit(yEnd);
	Lcd_WriteIndex(0x2c);
}

	
/*************************************************
3
��������LCD_DrawPoint
���ܣ���һ����
��ڲ�����xy�������ɫ����
����ֵ����
*************************************************/
void Gui_DrawPoint(uint16_t x,uint16_t y,uint16_t Data)
{
	Lcd_SetXY(x,y);
	Lcd_WriteData_16Bit(Data);

}    

/*************************************************
��������Lcd_Clear
���ܣ�ȫ����������
��ڲ����������ɫCOLOR
����ֵ����
*************************************************/
void Lcd_Clear(uint16_t Color)               
{	
   unsigned int i;
   Lcd_SetRegion(0,0,128-1,128-1);
	 LCD_CS_CLR;
   LCD_RS_SET;	
   for(i=0;i<128*128;i++)
   {	
	  	//Lcd_WriteData_16Bit(Color);
		SPIv_WriteData(Color>>8);
		SPIv_WriteData(Color);
   }   
		LCD_CS_SET;
}
void lcd_display_on(void)
     {
	Lcd_WriteIndex(0x11);  
  Lcd_WriteIndex(0x29); 
     }
void lcd_display_off(void)
      {
	Lcd_WriteIndex(0x10);//�رճ���
	Lcd_WriteIndex(0x28);//LCD�ر�
      }