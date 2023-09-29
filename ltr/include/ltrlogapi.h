#ifndef __LTRLOGAPI_H_
#define __LTRLOGAPI_H_

#include "ltrapi.h"
#include <stddef.h>


#ifdef _WIN32
    #ifdef LTRLOGAPI_EXPORTS
        #define LTRLOGAPI_DllExport(type)    __declspec(dllexport) type APIENTRY
    #else
        #define LTRLOGAPI_DllExport(type)    __declspec(dllimport) type APIENTRY
    #endif
#elif defined __GNUC__
    #define LTRLOGAPI_DllExport(type) __attribute__ ((visibility("default"))) type
#else
    #define LTRLOGAPI_DllExport(type) type
#endif


#define LTRLOG_MSG_SIGN   0xA54C



#pragma pack (4)
typedef struct {
    INT    Size;
    TLTR   Channel;
    PVOID  Internal;
} TLTRLOG;


/** ���������, ����������� ���������� ��������� ������� */
typedef struct {
    WORD Sign; /**< ������� ���������. ������ ����� #LTRLOG_MSG_SIGN */
    WORD Size; /**< ������ ����� ��������� � ���������� */
    INT  Err;  /**< ��� ������ (����� �������� ������ ��� ������ ������) */
    LARGE_INTEGER Time; /**< ����� ������������� ��������� � ������� */
    BYTE Lvl; /**< ������� ��������� */
    BYTE Reserved[15]; /**< ������ */
    char Msg[1]; /**< ����� ��������� (���������� �����) */
} TLTRLOG_MSG;

/** ������ ��������� ��������� (������������� �����) */
#define LTRLOG_MSG_HDR_SIZE (offsetof(TLTRLOG_MSG, Msg))

#pragma pack ()

#ifdef __cplusplus
extern "C" {
#endif
  
  
LTRLOGAPI_DllExport(INT) LTRLOG_Init(TLTRLOG *hnd);
LTRLOGAPI_DllExport(INT) LTRLOG_Open(TLTRLOG *hnd, DWORD net_addr, WORD net_port);
LTRLOGAPI_DllExport(INT) LTRLOG_Close(TLTRLOG *hnd);
LTRLOGAPI_DllExport(INT) LTRLOG_Shutdown(TLTRLOG *hnd);

/***************************************************************************//**
 * ����� ��������� �� �������. ���������� ���������� ��� ������ ����� �������
 * ���� ������ ��������� �� ������� ��� ������� �������.
 *
 * � ������ ������ �������� ��������� ���������� � msg ��������� �� ���������
 * ��������� ���������, ������� ����� ������� ���������� � ������� LTRLOG_FreeMsg().
 * ���� �� �������� ������� �� ������� �� ������ ������� ���������, �� � msg
 * ������������ ������� ���������.
 *
 * @param [in]  hnd      ��������� ����������
 * @param [out] msg      � ������ ���������� ������������ ��������� �� ���������
 *                       ��������� � �������� ���������� ��� NULL, ���� ���������
 *                       �� ���� �������.
 * @param [in]  tout     ������� �� ����� ������ ��������� � ��
 * @return               ��� ������
 ******************************************************************************/
LTRLOGAPI_DllExport(INT) LTRLOG_GetNextMsg(TLTRLOG *hnd, TLTRLOG_MSG **msg, DWORD tout);

/***************************************************************************//**
 * ������������ ������ ��������� ���������, ������������ LTRLOG_GetNextMsg().
 * ������ ���������� ������ ��� ��������� ������ ��������� ����� ��� ���������.
 *
 * @param[in]  msg      ��������� �� ��������� ��������� ���������
 * @return              ��� ������
 ******************************************************************************/
LTRLOGAPI_DllExport(INT) LTRLOG_FreeMsg(TLTRLOG_MSG *msg);

#ifdef __cplusplus
}
#endif


#endif
