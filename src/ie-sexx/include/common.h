/*******************************************************************************
*���������ǻ���Ƽ����޹�˾��Ȩ����
********************************************************************************
* �ļ�����:  common.h
* ��������:  ͨ���ļ���ͷ�ļ�����ӡ��Ϣ
* ʹ��˵��:
* �ļ�����:
* ��д����:
* �޸���ʷ:
* [��ʽҪ���޸İ汾ʹ����λ�ַ���ʾ, ����ǰ2λΪ����, ��ʾ�ϴ��޸�; ��1λΪ
*  ��ĸ������, ��ʾ��С�޸ģ��޸����ڲ���"yyyy/mm/dd"�ĸ�ʽ���޸��˱���������
*  ȫ�����̶�ռ3�������ֵĴ�С�޸�����������Ҫ����80�У���������֮������룻
*  �汾�����ڡ��޸��ˡ��޸�����֮��ʹ��1���ո�ָ�
* �޸İ汾  �޸�����   �޸���  �޸�����
* ------------------------------------------------------------------------------
* 01a
*******************************************************************************/

/******************************** ͷ�ļ�������ͷ *****************************/
#ifndef COMMON_H
#define COMMON_H

#include "stdarg.h"
#include <string.h>
#include<stdio.h>

#include "swp_type.h"  //�������Ͷ���


extern CHAR    *g_FileName;
extern INT32   g_FileLine;

/****************************************************************
* ÊýÖµ¶¨Òå
****************************************************************/
#define VALUE    (-1)
#define VALUE_0  (0)
#define VALUE_1  (1)
#define VALUE_2  (2)
#define VALUE_3  (3)
#define VALUE_4  (4)
#define VALUE_5  (5)
#define VALUE_6  (6)
#define VALUE_9  (9)
#define VALUE_10 (10)
#define VALUE_15 (15)
#define VALUE_16 (16)

#define PRINT_INFO   0
#define PRINT_WARN   1
#define PRINT_ERROR  2
#define PRINT_DEBUG  3


#ifdef WIN32
#define filename(x) (strrchr(x,'\\')?strrchr(x,'\\')+1:x)
#else
#define filename(x) strrchr(x,'/')?strrchr(x,'/')+1:x
#endif

/******************************************************************
* �ֽ���ת���꺯��
******************************************************************/
/* u16 �ĸߵ��ֽ�ת���궨�� */
#define HTONS(x)    ((((x) & 0x00FF) << 8) | (((x) & 0xFF00) >> 8)) // u16����ӳ�䵽�����ֽ���
#define NTOHS(x)    ((((x) & 0x00FF) << 8) | (((x) & 0xFF00) >> 8)) // u16����ӳ�䵽�����ֽ���

/* u32 �ĸߵ��ֽ�ת���궨�� */
#define HTONL(x)    ((((x) & 0x000000FF) << 24)|(((x) & 0x0000FF00) << 8)|(((x) & 0x00FF0000) >> 8)|(((x) & 0xFF000000) >> 24)) // u32����ӳ�䵽�����ֽ���
#define NTOHL(x)    ((((x) & 0x000000FF) << 24)|(((x) & 0x0000FF00) << 8)|(((x) & 0x00FF0000) >> 8)|(((x) & 0xFF000000) >> 24)) // u32����ӳ�䵽�����ֽ���

/*  ����� */
#define PACK_1_BYTE(pucBuff, ucData)   {*pucBuff = ucData; pucBuff++;}
#define PACK_2_BYTE(pucBuff, usData)   {*(BITS16*)pucBuff = HTONS(usData); pucBuff += sizeof(BITS16);}
#define PACK_4_BYTE(pucBuff, ulData)   {*(BITS32*)pucBuff = HTONL(ulData); pucBuff += sizeof(BITS32);}
/*  ����� */
#define UNPACK_1_BYTE(pucBuff, ucData) {ucData = *pucBuff; pucBuff++;}
#define UNPACK_2_BYTE(pucBuff, usData) {usData = NTOHS(*(BITS16*)pucBuff); pucBuff += sizeof(BITS16);}
#define UNPACK_4_BYTE(pucBuff, ulData) {ulData = NTOHL(*(BITS32*)pucBuff); pucBuff += sizeof(BITS32);}

#define PRINT_INFO   0
#define PRINT_WARN   1
#define PRINT_ERROR  2
#define PRINT_DEBUG  3

#define PRINT_LOG  g_FileName =(CHAR*)filename(__FILE__); g_FileLine = __LINE__; AgvPrintFunc

/***********************************************************
* ��������:��ӡ����
***********************************************************/
void AgvPrintFunc(INT32 LogType, const CHAR* format, ...);
unsigned short CRC16(unsigned char *puchMsg, unsigned int usDataLen);


#endif /* COMMON_H */
/******************************** ͷ�ļ����� **********************************/

