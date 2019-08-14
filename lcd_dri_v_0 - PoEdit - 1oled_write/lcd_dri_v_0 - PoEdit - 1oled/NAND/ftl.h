#ifndef __FTL_H
#define __FTL_H
#include "main.h"
///////////////////////////////////////////////////////////////////////////////////
//����һЩ���õ��������Ͷ̹ؼ��� 
typedef int32_t  s32;
typedef int16_t s16;
typedef int8_t  s8;

typedef const int32_t sc32;  
typedef const int16_t sc16;  
typedef const int8_t sc8;  

typedef __IO int32_t  vs32;
typedef __IO int16_t  vs16;
typedef __IO int8_t   vs8;

typedef __I int32_t vsc32;  
typedef __I int16_t vsc16; 
typedef __I int8_t vsc8;   

typedef uint32_t  u32;
typedef uint16_t u16;
typedef uint8_t  u8;

typedef const uint32_t uc32;  
typedef const uint16_t uc16;  
typedef const uint8_t uc8; 

typedef __IO uint32_t  vu32;
typedef __IO uint16_t vu16;
typedef __IO uint8_t  vu8;

typedef __I uint32_t vuc32;  
typedef __I uint16_t vuc16; 
typedef __I uint8_t vuc8;  
//////////////////////////////////////////////////////////////////////////////////	
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32������
//NAND FLASH FTL���㷨����	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2016/1/15
//�汾��V1.3
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved
//********************************************************************************
//����˵��
//V1.1 20160124
//�޸�FTL_CopyAndWriteToBlock��FTL_WriteSectors����,��߷�0XFFʱ��д���ٶ�.  
//V1.2 20160520
//1,�޸�FTL_ReadSectors,����ECC�����ж�,��⻵�鴦��,�����Ӷ������,����ٶ�
//2,����FTL_BlockCompare��FTL_SearchBadBlock����,������Ѱ����
//3,�޸�FTL_Format�����ⷽʽ,����FTL_USE_BAD_BLOCK_SEARCH��
//V1.3 20160530
//�޸ĵ�1bit ECC�������ʱ����ȡ2�Σ���ȷ��1bit �����Է�������޸�����
////////////////////////////////////////////////////////////////////////////////// 	

//������������
//�������Ϊ1,����FTL_Format��ʱ��,��Ѱ����,��ʱ��(512M,3��������),�һᵼ��RGB������
#define FTL_USE_BAD_BLOCK_SEARCH		0		//�����Ƿ�ʹ�û�������



u8 FTL_Init(void); 
void FTL_BadBlockMark(u32 blocknum);
u8 FTL_CheckBadBlock(u32 blocknum); 
u8 FTL_UsedBlockMark(u32 blocknum);
u32 FTL_FindUnusedBlock(u32 sblock,u8 flag);
u32 FTL_FindSamePlaneUnusedBlock(u32 sblock);
u8 FTL_CopyAndWriteToBlock(u32 Source_PageNum,u16 ColNum,u8 *pBuffer,u32 NumByteToWrite);
u16 FTL_LBNToPBN(u32 LBNNum); 
u8 FTL_WriteSectors(u8 *pBuffer,u32 SectorNo,u16 SectorSize,u32 SectorCount);
u8 FTL_ReadSectors(u8 *pBuffer,u32 SectorNo,u16 SectorSize,u32 SectorCount);
u8 FTL_CreateLUT(u8 mode);
u8 FTL_BlockCompare(u32 blockx,u32 cmpval);
u32 FTL_SearchBadBlock(void);
u8 FTL_Format(void); 
#endif

