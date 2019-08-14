#ifndef _H_SPI_H
#define _H_SPI_H
#include "stm32f4xx_hal.h"
//���Ŷ���
#define lcd1_res_Pin GPIO_PIN_0
#define lcd1_res_GPIO_Port GPIOA
#define lcd1_cs_Pin GPIO_PIN_3
#define lcd1_cs_GPIO_Port GPIOA
#define lcd1_dc_Pin GPIO_PIN_4
#define lcd1_dc_GPIO_Port GPIOA
#define Contact_PinA7_Pin GPIO_PIN_4
#define Contact_PinA7_GPIO_Port GPIOC
//step1
//��Ӧ��spi��GPIO��
void MX_GPIO_Init(void);//������ʼ��
//step2
/* SPI1 init function */
void MX_SPI1_Init(void);//������ʼ��
//step3
/****************************************************************************
* ��    �ƣ�void Lcd1_Reset(void)
* ��    �ܣ�Һ��Ӳ��λ����
* ��ڲ�������
* ���ڲ�������
* ˵    ����Һ����ʼ��ǰ��ִ��һ�θ�λ����
****************************************************************************/
void Lcd1_Reset(void);//LCD��ʼ��
/****************************************************************************
* ��    �ƣ�void Lcd1_Init(void)
* ��    �ܣ�Һ����ʼ������
* ��ڲ�������
* ���ڲ�������
* ˵    ����Һ����ʼ��_ILI9225_176X220
****************************************************************************/
void Lcd1_Init(void);//LCD��ʼ��
/*************************************************
��������Lcd1_Set_XY
���ܣ�����Lcd1��ʾ��ʼ��
��ڲ�����xy����
����ֵ����
*************************************************/
void Lcd1_SetXY(uint16_t Xpos, uint16_t Ypos);
/****************************************************************************
* ��    �ƣ�void Lcd1_WriteData_16Bit(uint16_t Data)
* ��    �ܣ���Һ����дһ��16λ����
* ��ڲ�����Data
* ���ڲ�������
* ˵    �����������ָ����ַд��һ��16λ����
****************************************************************************/
void Lcd1_WriteData_16Bit(uint16_t Data);
#endif
