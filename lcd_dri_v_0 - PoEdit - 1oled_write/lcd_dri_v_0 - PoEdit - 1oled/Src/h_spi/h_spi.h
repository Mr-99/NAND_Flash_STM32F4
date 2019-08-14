#ifndef _H_SPI_H
#define _H_SPI_H
#include "stm32f4xx_hal.h"
//引脚定义
#define lcd1_res_Pin GPIO_PIN_0
#define lcd1_res_GPIO_Port GPIOA
#define lcd1_cs_Pin GPIO_PIN_3
#define lcd1_cs_GPIO_Port GPIOA
#define lcd1_dc_Pin GPIO_PIN_4
#define lcd1_dc_GPIO_Port GPIOA
#define Contact_PinA7_Pin GPIO_PIN_4
#define Contact_PinA7_GPIO_Port GPIOC
//step1
//对应的spi的GPIO口
void MX_GPIO_Init(void);//基础初始化
//step2
/* SPI1 init function */
void MX_SPI1_Init(void);//基础初始化
//step3
/****************************************************************************
* 名    称：void Lcd1_Reset(void)
* 功    能：液晶硬复位函数
* 入口参数：无
* 出口参数：无
* 说    明：液晶初始化前需执行一次复位操作
****************************************************************************/
void Lcd1_Reset(void);//LCD初始化
/****************************************************************************
* 名    称：void Lcd1_Init(void)
* 功    能：液晶初始化函数
* 入口参数：无
* 出口参数：无
* 说    明：液晶初始化_ILI9225_176X220
****************************************************************************/
void Lcd1_Init(void);//LCD初始化
/*************************************************
函数名：Lcd1_Set_XY
功能：设置Lcd1显示起始点
入口参数：xy坐标
返回值：无
*************************************************/
void Lcd1_SetXY(uint16_t Xpos, uint16_t Ypos);
/****************************************************************************
* 名    称：void Lcd1_WriteData_16Bit(uint16_t Data)
* 功    能：向液晶屏写一个16位数据
* 入口参数：Data
* 出口参数：无
* 说    明：向控制器指定地址写入一个16位数据
****************************************************************************/
void Lcd1_WriteData_16Bit(uint16_t Data);
#endif
