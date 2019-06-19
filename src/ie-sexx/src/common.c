
/*******************************************************************************
*���������ǻ���Ƽ����޹�˾��Ȩ����
********************************************************************************
* �ļ�����:  common.c
* ��������:  ͨ���ļ�����ӡ��Ϣ
* ʹ��˵��: ������ʹ���ļ�����ʱ����Լ������
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
//#include "app_protocol.h"
#include "common.h"
//#include "buspro_error.h"

CHAR   *g_FileName = "NULL";
INT32   g_FileLine = 0;
INT32   g_PrintLevel=0;      /* 0: �رմ�ӡ,
                                1: ������д�ӡ,
                                2: ���INFO��WARN��ERROR����Ĵ�ӡ,
                                3: ���ERROR��WARN�����ӡ,
                                4: ֻ���ERROR�����ӡ */

/***********************************************************

* ��������:��ӡ����
***********************************************************/
void AgvPrintFunc(INT32 LogType, const CHAR* format, ...)
{
    va_list vp;

    if (VALUE_0 == g_PrintLevel)
    {
        return;
    }

    if (PRINT_DEBUG == LogType && g_PrintLevel <= 1)
    {
        printf("[DEBUG][%s][%d]:", g_FileName, g_FileLine);
    }
    else if (PRINT_INFO == LogType && g_PrintLevel <= 2)
    {
        printf("[INFO][%s][%d]:", g_FileName, g_FileLine);
    }
    else if (PRINT_WARN == LogType && g_PrintLevel <= 3)
    {
        printf("[WARN][%s][%d]:", g_FileName, g_FileLine);
    }
    else if (PRINT_ERROR == LogType)
    {
        printf("[ERROR][%s][%d]:", g_FileName, g_FileLine);
    }
    else
    {
        return;
    }

    va_start(vp, format);
    vprintf(format, vp);
    va_end(vp);
}

/*
void InvertUint8(unsigned char *dBuf,unsigned char *srcBuf)
{
    int i;
    unsigned char tmp[4];
    tmp[0] = 0;
    for(i=0;i< 8;i++)
    {
      if(srcBuf[0]& (1 << i))
        tmp[0]|=1<<(7-i);
    }
    dBuf[0] = tmp[0];
}
 
void InvertUint16(unsigned short *dBuf,unsigned short *srcBuf)
{
    int i;
    unsigned short tmp[4];
    tmp[0] = 0;
    for(i=0;i< 16;i++)
    {
  if(srcBuf[0]& (1 << i))
        tmp[0]|=1<<(15 - i);
    }
    dBuf[0] = tmp[0];
}

unsigned short CRC16(unsigned char *puchMsg, unsigned int usDataLen)
{
  unsigned short wCRCin = 0xFFFF;
  unsigned short wCPoly = 0x8005;
  unsigned char wChar = 0;
	unsigned int  i;
  
  while (usDataLen--) 	
  {
        wChar = *(puchMsg++);
        InvertUint8(&wChar,&wChar);
        wCRCin = wCRCin^(wChar << 8);
        for(i = 0;i < 8;i++)
        {
          if(wCRCin & 0x8000)
            wCRCin = (wCRCin << 1) ^ wCPoly;
          else
            wCRCin = wCRCin << 1;
        }
  }
  InvertUint16(&wCRCin,&wCRCin);
  wCRCin = HTONS(wCRCin);
  
  return (wCRCin);
}
*/

/******************************* Դ�ļ����� ***********************************/


