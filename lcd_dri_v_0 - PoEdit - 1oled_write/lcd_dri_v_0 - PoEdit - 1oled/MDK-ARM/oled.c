#include "oled.h" //����oled�ӿ�
struct z_unit{
uint8_t unit1[16];
uint8_t unit2[16];
};
struct z_part{
struct z_unit part[2];//���ָ���
};
struct z_part *p_z;
//����ȡģ �ֽڵ���
const unsigned char Hzk[2*32]={
/*--  ����:  ��  --*/
/*--  ����12;  �������¶�Ӧ�ĵ���Ϊ����x��=16x16   --*/
0x00,0x00,0xF8,0x88,0x88,0x88,0x88,0xFF,0x88,0x88,0x88,0x88,0xF8,0x00,0x00,0x00,
0x00,0x00,0x1F,0x08,0x08,0x08,0x08,0x7F,0x88,0x88,0x88,0x88,0x9F,0x80,0xF0,0x00,

/*--  ����:  ��  --*/
/*--  ����12;  �������¶�Ӧ�ĵ���Ϊ����x��=16x16   --*/
0x10,0x60,0x00,0xFC,0x04,0x24,0x24,0x24,0x25,0x26,0x24,0xA4,0x64,0x24,0x04,0x00,
0x84,0x42,0x31,0x0F,0x00,0x00,0x00,0x40,0x80,0x7E,0x01,0x00,0x00,0x00,0x00,0x00,

};
const unsigned char electr[2*32]={
/*--  ����:  ��  --*/
/*--  ����12;  �������¶�Ӧ�ĵ���Ϊ����x��=16x16   --*/
0x40,0x40,0x44,0x44,0x54,0x64,0x45,0x46,0x44,0x64,0x54,0x44,0x44,0x40,0x40,0x00,
0x00,0x00,0x00,0xFF,0x49,0x49,0x49,0x49,0x49,0x49,0x49,0xFF,0x00,0x00,0x00,0x00,

/*--  ����:  ��  --*/
/*--  ����12;  �������¶�Ӧ�ĵ���Ϊ����x��=16x16   --*/
0x00,0x00,0xE0,0x9C,0x84,0x84,0x84,0xF4,0x82,0x82,0x83,0x82,0x80,0x80,0x00,0x00,
0x00,0x20,0x10,0x08,0x06,0x40,0x80,0x7F,0x00,0x00,0x02,0x04,0x08,0x30,0x00,0x00,
};
//����
const unsigned char num_8x16[]={
/*--  ����:  0  --*/
/*--  ����12;  �������¶�Ӧ�ĵ���Ϊ����x��=8x16   --*/
0x00,0xE0,0x10,0x08,0x08,0x10,0xE0,0x00,0x00,0x0F,0x10,0x20,0x20,0x10,0x0F,0x00,
	
/*--  ����:  1  --*/
/*--  ����12;  ������8x16�¶�Ӧ�ĵ���Ϊ����x��=8x16   --*/
0x00,0x00,0x10,0x10,0xF8,0x00,0x00,0x00,0x00,0x00,0x20,0x20,0x3F,0x20,0x20,0x00,

/*--  ����:  2  --*/
/*--  ����12;  �������¶�Ӧ�ĵ���Ϊ����x��=8x16   --*/
0x00,0x70,0x08,0x08,0x08,0x08,0xF0,0x00,0x00,0x30,0x28,0x24,0x22,0x21,0x30,0x00,

/*--  ����:  3  --*/
/*--  ����12;  �������¶�Ӧ�ĵ���Ϊ����x��=8x16   --*/
0x00,0x00,0x80,0x40,0x30,0xF8,0x00,0x00,0x00,0x06,0x05,0x24,0x24,0x3F,0x24,0x24,

/*--  ����:  5  --*/
0x00,0x30,0x08,0x08,0x08,0x88,0x70,0x00,0x00,0x18,0x20,0x21,0x21,0x22,0x1C,0x00,

/*--  ����:  4  --*/
/*--  ����12;  �������¶�Ӧ�ĵ���Ϊ����x��=8x16   --*/
/*--  ����12;  �������¶�Ӧ�ĵ���Ϊ����x��=8x16   --*/
0x00,0xF8,0x88,0x88,0x88,0x08,0x08,0x00,0x00,0x19,0x20,0x20,0x20,0x11,0x0E,0x00,

/*--  ����:  6  --*/
/*--  ����12;  �������¶�Ӧ�ĵ���Ϊ����x��=8x16   --*/
0x00,0xE0,0x10,0x88,0x88,0x90,0x00,0x00,0x00,0x0F,0x11,0x20,0x20,0x20,0x1F,0x00,

/*--  ����:  7  --*/
/*--  ����12;  �������¶�Ӧ�ĵ���Ϊ����x��=8x16   --*/
0x00,0x18,0x08,0x08,0x88,0x68,0x18,0x00,0x00,0x00,0x00,0x3E,0x01,0x00,0x00,0x00,

/*--  ����:  8  --*/
/*--  ����12;  �������¶�Ӧ�ĵ���Ϊ����x��=8x16   --*/
0x00,0x70,0x88,0x08,0x08,0x88,0x70,0x00,0x00,0x1C,0x22,0x21,0x21,0x22,0x1C,0x00,

/*--  ����:  9  --*/
/*--  ����12;  �������¶�Ӧ�ĵ���Ϊ����x��=8x16   --*/
0x00,0xF0,0x08,0x08,0x08,0x10,0xE0,0x00,0x00,0x01,0x12,0x22,0x22,0x11,0x0F,0x00,

};
struct num_part{

uint8_t part[8];
};
struct num_sec{
struct num_part sec[2];
};
struct number{
struct num_sec n_10[10];
};
#define cs_Pin GPIO_PIN_4
#define cs_GPIO_Port GPIOE
#define dc_Pin GPIO_PIN_5
#define dc_GPIO_Port GPIOE
#define res_Pin GPIO_PIN_6
#define res_GPIO_Port GPIOE
#define sda_Pin GPIO_PIN_13
#define sda_GPIO_Port GPIOC
#define scl_Pin GPIO_PIN_14
#define scl_GPIO_Port GPIOC
//
//////////////////////////////////////////////////////////////////////////////////	 
//
//  �� �� ��   : main.c
//  �� �� ��   : v2.0
//  ��    ��   : HuangKai
//  ��������   : 2014-0101
//  ����޸�   : 
//  ��������   : OLED 4�ӿ���ʾ����(51ϵ��)
//              ˵��: 
//              ----------------------------------------------------------------
//              GND    ��Դ��
//              VCC  ��5V��3.3v��Դ
//              D0   ��PB13��SCL��
//              D1   ��PB15��SDA��
//              RES  ��PB11
//              DC   ��PB10
//              CS   ��P12               
//              ----------------------------------------------------------------
//OLEDģʽ����
//0:4�ߴ���ģʽ
//1:����8080ģʽ
#define OLED_MODE 0
#define SIZE 16
#define XLevelL		0x00
#define XLevelH		0x10
#define Max_Column	128
#define Max_Row		64
#define	Brightness	0xFF 
#define X_WIDTH 	128
#define Y_WIDTH 	64	    

//-----------------OLED�˿ڶ���----------------  					   

#define OLED_SCLK_Clr() PCout(14)=0//CLK   D0
#define OLED_SCLK_Set() PCout(14)=1

#define OLED_SDIN_Clr() PCout(13)=0//DIN   D1
#define OLED_SDIN_Set() PCout(13)=1

#define OLED_RST_Clr()  PEout(6)=0
#define OLED_RST_Set()  PEout(6)=1

#define OLED_DC_Clr()   PEout(5)=0//DC
#define OLED_DC_Set()   PEout(5)=1
 		     
#define OLED_CS_Clr()   PEout(4)=0//CS
#define OLED_CS_Set()   PEout(4)=1

//#define OLED_PWEN				PCout(15)			//OLED��Դʹ��(δ��ʼ��)


//IO��ʼ��
void oled_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, cs_Pin|dc_Pin|res_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, sda_Pin|scl_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : PEPin PEPin */
  GPIO_InitStruct.Pin = cs_Pin|dc_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = res_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(res_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : PCPin PCPin */
  GPIO_InitStruct.Pin = sda_Pin|scl_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
OLED_SCLK_Clr() ;
OLED_SCLK_Set() ;

OLED_SDIN_Clr() ;
 OLED_SDIN_Set() ;

OLED_RST_Clr() ;
 OLED_RST_Set();  

 OLED_DC_Clr();   
OLED_DC_Set() ;  
 		     
 OLED_CS_Clr() ;  
 OLED_CS_Set() ;  
}
//���Ŵ�ͨ��ʼ����
//��SSD1106д��һ���ֽڡ�
//dat:Ҫд�������/����
//cmd:����/�����־ 0,��ʾ����;1,��ʾ����;
void OLED_WR_Byte(uint8_t dat,uint8_t cmd)
{	
	uint8_t i;			  
	if(cmd)
	  OLED_DC_Set();
	else 
	  OLED_DC_Clr();		  
	OLED_CS_Clr();
	delay_us(10);
	for(i=0;i<8;i++)
	{			  
		OLED_SCLK_Clr();
		if(dat&0x80)
		   OLED_SDIN_Set();
		else 
		   OLED_SDIN_Clr();
		delay_us(10);
		OLED_SCLK_Set();
		delay_us(10);
		dat<<=1;   
	}				 		  
	OLED_CS_Set();
	OLED_DC_Set();   	  
} 
void oled_init(void)
{
oled_GPIO_Init();//���Ŵ�ͨ
	OLED_RST_Set();
	delay_ms(100);
	OLED_RST_Clr();
	delay_ms(200);
	OLED_RST_Set(); 
					  
	OLED_WR_Byte(0xAE,OLED_CMD);//--turn off oled panel
	OLED_WR_Byte(0x00,OLED_CMD);//---set low column address
	OLED_WR_Byte(0x10,OLED_CMD);//---set high column address
	OLED_WR_Byte(0x40,OLED_CMD);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
	OLED_WR_Byte(0x81,OLED_CMD);//--set contrast control register
	OLED_WR_Byte(0xCF,OLED_CMD); // Set SEG Output Current Brightness
	OLED_WR_Byte(0xA1,OLED_CMD);//--Set SEG/Column Mapping     0xa0���ҷ��� 0xa1����
	OLED_WR_Byte(0xC8,OLED_CMD);//Set COM/Row Scan Direction   0xc0���·��� 0xc8����
	OLED_WR_Byte(0xA6,OLED_CMD);//--set normal display
	OLED_WR_Byte(0xA8,OLED_CMD);//--set multiplex ratio(1 to 64)
	OLED_WR_Byte(0x3f,OLED_CMD);//--1/64 duty
	OLED_WR_Byte(0xD3,OLED_CMD);//-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
	OLED_WR_Byte(0x00,OLED_CMD);//-not offset
	OLED_WR_Byte(0xd5,OLED_CMD);//--set display clock divide ratio/oscillator frequency
	OLED_WR_Byte(0x80,OLED_CMD);//--set divide ratio, Set Clock as 100 Frames/Sec
	OLED_WR_Byte(0xD9,OLED_CMD);//--set pre-charge period
	OLED_WR_Byte(0xF1,OLED_CMD);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
	OLED_WR_Byte(0xDA,OLED_CMD);//--set com pins hardware configuration
	OLED_WR_Byte(0x12,OLED_CMD);
	OLED_WR_Byte(0xDB,OLED_CMD);//--set vcomh
	OLED_WR_Byte(0x40,OLED_CMD);//Set VCOM Deselect Level
	OLED_WR_Byte(0x20,OLED_CMD);//-Set Page Addressing Mode (0x00/0x01/0x02)
	OLED_WR_Byte(0x02,OLED_CMD);//
	OLED_WR_Byte(0x8D,OLED_CMD);//--set Charge Pump enable/disable
	OLED_WR_Byte(0x14,OLED_CMD);//--set(0x10) disable
	OLED_WR_Byte(0xA4,OLED_CMD);// Disable Entire Display On (0xa4/0xa5)
	OLED_WR_Byte(0xA6,OLED_CMD);// Disable Inverse Display On (0xa6/a7) 
	OLED_WR_Byte(0xAF,OLED_CMD);//--turn on oled panel
	
	OLED_OFF();
	
	 }
void OLED_Set_Pos(unsigned char x, unsigned char y) 
{ 
	OLED_WR_Byte(0xb0+y,OLED_CMD);
	OLED_WR_Byte(((x&0xf0)>>4)|0x10,OLED_CMD);
	OLED_WR_Byte((x&0x0f)|0x01,OLED_CMD); 
}    
//��ʾ����
void OLED_ShowCHinese(uint8_t x,uint8_t y,uint8_t no)
{      			    
	uint8_t t,adder=0,i,j;
	struct z_part *p_z;
  if(no==0)
	    {
		p_z=(struct z_part*)Hzk;
	    }
	  else
	    {
		p_z=(struct z_part*)electr;
	    }
	OLED_Set_Pos(x,y);	
for(i=0;i<2;i++)
    for(j=0;j<16;j++)
		{
				OLED_WR_Byte(p_z->part[i].unit1[j],OLED_DATA);
     }	
		OLED_Set_Pos(x,y+1);	
for(i=0;i<2;i++)
    for(j=0;j<16;j++)
		{
				OLED_WR_Byte(p_z->part[i].unit2[j],OLED_DATA);
     }			
}
//��������
//��������,������,������Ļ�Ǻ�ɫ��!��û����һ��!!!	  
static void OLED_Clear(void)  
{  
	uint8_t i,n;		    
	for(i=0;i<8;i++)  
	{  
		OLED_WR_Byte (0xb0+i,OLED_CMD);    //����ҳ��ַ��0~7��
		OLED_WR_Byte (0x00,OLED_CMD);      //������ʾλ�á��е͵�ַ
		OLED_WR_Byte (0x10,OLED_CMD);      //������ʾλ�á��иߵ�ַ   
		for(n=0;n<128;n++)OLED_WR_Byte(0x00,OLED_DATA); 
	} //������ʾ
}
void show_num(uint8_t x,uint8_t y,uint8_t n)
			{
					struct number *p_num;	
           uint8_t i,j;				
					p_num=(struct number*)num_8x16;
					OLED_Set_Pos(x,y);	
    for(j=0;j<8;j++)
		      {
		OLED_WR_Byte(p_num->n_10[n].sec[0].part[j],OLED_DATA);
          }
				  OLED_Set_Pos(x,y+1);	
    for(i=0;i<8;i++)
		     {
		OLED_WR_Byte(p_num->n_10[n].sec[1].part[i],OLED_DATA);
         }	
			}
//��ʾ����
void oled_num(uint8_t x,uint8_t y,uint16_t n)
			{
   uint8_t unitPlace = n / 1 % 10;
   uint8_t tenPlace = n / 10 % 10;
   uint8_t hundredPlace = n / 100 % 10;
   uint8_t thousandPlace = n / 1000 % 10;

  show_num(x,y,thousandPlace);

  show_num(x+8,y,hundredPlace);
					
  show_num(x+16,y,tenPlace);
				
  show_num(x+24,y,unitPlace);
		
			}
////��㺯��
//void OLED_DrawPoint(unsigned char x,unsigned char y,unsigned char t)
//{
//        unsigned char pos,bx,temp=0;
//				static unsigned char OLED_GRAM[128][8];
//        if(x>127||y>63)return;//3?3?��??�쨢?.OLED_GRAM[pos][bx],
//        pos=7-y/8;
//        bx=y%8;
//        temp=1<<(7-bx);
//        if(t)OLED_GRAM[x][pos]|=temp;
//        else OLED_GRAM[x][pos]&=~temp; 
//				OLED_Set_Pos(x,pos);		
//	      OLED_WR_Byte(OLED_GRAM[x][pos],OLED_DATA);
//}			
/****************************************************************************
* ���ƣ�GUI_HLine()
* ���ܣ���ˮƽ�ߡ�
* ��ڲ����� x0     ˮƽ����������е�λ��
*           y0      ˮƽ����������е�λ��
*           x1      ˮƽ���յ������е�λ��
*           color   ��ʾ��ɫ(���ںڰ�ɫLCM��Ϊ0ʱ��Ϊ1ʱ��ʾ)
* ���ڲ�������
* ˵�������ڵ�ɫ��4���Ҷȵ�Һ������ͨ���޸Ĵ˺�����ͼ����ٶȣ��絥ɫLCM������һ�θ�
*      ��8���㣬������Ҫһ����һ�����д��LCM�С�
****************************************************************************/
static void  GUI_HLine(uint16_t x0, uint8_t y0, uint16_t x1, uint8_t color)
{
    uint8_t  temp;
    if(x0>x1)               // ��x0��x1��С�������У��Ա㻭ͼ
    {
        temp = x1;
        x1 = x0;
        x0 = temp;
    }
    do
    {
        OLED_DrawPoint(x0, y0, color);   // �����ʾ�������ֱ��
        x0++;
    }
    while(x1>=x0);
}
//˯��ģʽ�����뻽��
	//���ѳ�ʼ��
/**
  * @brief  OLED_ON����OLED�������л���
  * @param  ��
    * @retval ��
  */
void OLED_ON(void)
{
    OLED_WR_Byte(0X8D,OLED_CMD);  //���õ�ɱ�
    OLED_WR_Byte(0X14,OLED_CMD);  //������ɱ�
    OLED_WR_Byte(0XAF,OLED_CMD);  //OLED����
}

 /**
  * @brief  OLED_OFF����OLED���� -- ����ģʽ��,OLED���Ĳ���10uA
  * @param  ��
    * @retval ��
  */
void OLED_OFF(void)
{
    OLED_WR_Byte(0X8D,OLED_CMD);  //���õ�ɱ�
    OLED_WR_Byte(0X10,OLED_CMD);  //�رյ�ɱ�
    OLED_WR_Byte(0XAE,OLED_CMD);  //OLED����
}
//������
