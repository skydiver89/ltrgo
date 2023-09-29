/** @file ltr210api.h
    ���� �������� ����������� ������� ��� ��������� ������������� ��������������
    ��������� ������, ������� ����� ��� LTR01. ��� �������� ������ ����������
    ����� MID ������ MID_LTR01. ������, ����� �������� ������ ������� ����������,
    ����� � ������� ������������� ��������������.

    � ���������� ������ ��� ����� ������� ��� ��������� ���������� � �������������
    ��������� ������������� ID (� ������ ������� ��� ������������� � API
    ����� �������� �������), ��� � ���������� �������, ����������� ���
    �� ���� ����� (��� �������� ������ �� ������� �������� ��� �����������
    ������� �������).

    ���������� �� ���������� ��������������� ���� ��� ����������� ���������
    ������ LTR01, � ���������� �������� ��������� ���������� TLTR. ��� �������
    ��� ����� �������� ����������� � API ��������������� �������� �������. */

#ifndef LTR01API_H_
#define LTR01API_H_


#include "ltrapi.h"

#ifdef __cplusplus
extern "C" {                                 // only need to export C interface if
                                             // used by C++ source code
#endif

#ifdef _WIN32
    #ifdef LTR01API_EXPORTS
      #define LTR01API_DllExport(type) __declspec(dllexport) type APIENTRY
    #else
      #define LTR01API_DllExport(type) __declspec(dllimport) type APIENTRY
    #endif
#elif defined __GNUC__
    #define LTR01API_DllExport(type) __attribute__ ((visibility("default"))) type
#else
    #define LTR01API_DllExport(type)  type
#endif

/** ���� �������������� ���������������, ����������� ����������, ��� �� ��������
    ������, ������� ��� LTR01, ������� ���������� */
typedef enum
{
    LTR01_SUBID_INVALID = 0,
    LTR01_SUBID_LTRS511 = 1, /**< ������������� ������ LTRS-511 */
    LTR01_SUBID_LTRS411 = 2, /**< ������������� ������ LTRS-411 */
    LTR01_SUBID_LTRS412 = 3, /**< ������������� ������ LTRS-412 */
    LTR01_SUBID_LTRT10  = 4  /**< ������������� ������ LTRT-10 */
} e_LTR01_SUBID;



/*============================================================================*/

/**  @brief �������� ���������� � �������.

    ������� ������������� ���������� � ����� �� �������� �������, ������� ��� LTR01
    � ������������ � ����������� �����������, ��������� ������� ������ � ���
    ������������� ��������� �������������� �������������.

    ����� ���������� ������ ���������� ������� ���������� � ������� LTR01_Close().
 *
 *��������� ����������
    ��������� ����������, ����� ������ � ��������, ��� ��� ������ LTR01.
    @param[in] hnd         ��������� ��� ��������� ���������� � ��������,
                           �������������� ��������������������� � ������� LTR_Init()
    @param[in] net_addr    IP-����� LTR-�������
    @param[in] net_port    TCP-���� ��� ������������ ����� � ��������
    @param[in] crate_sn    �������� ����� ������
    @param[in] slot_num    ���� ������ (�� CC_MODULE1 �� CC_MODULE16)
    @param[in] subid       ���� �� ����� #LTR01_SUBID_INVALID, �� ������� ���������
                           �������� �� ������������ ��������������� ��������������
                           ���������� � ������ ���������
    @param[out] cpld_ver   ���� �� NULL, �� � ������ ���������� �����������
                           ������ CPLD, ���������� � ������ �� ����� ������.
    @return                ��� ������ */
LTR01API_DllExport(INT) LTR01_Open(TLTR *hnd, DWORD net_addr, WORD net_port,
                                   const CHAR *crate_sn, INT slot_num, WORD subid, BYTE* cpld_ver);

/** �������� ����� ��������� � ������� LTR01_Open() ����������.
    @param[in] hnd         ��������� ���������� � ��������
    @return                ��� ������ */
LTR01API_DllExport(INT) LTR01_Close(TLTR *hnd);

/** ��������� ��������������� ID ��� ������ LTR01, � ������� ���� �����������
    �� ����� ����� � ������� LTR01_Open().
    �������������� ID ��������� ������, ����� ������� ������ �������� ������
    ����������.
    @param[in] hnd         ��������� ���������� � ��������.
    @param[out] subid      ��� ������ ������������ �������������� ID-������
                           �� #e_LTR01_SUBID.
    @return                ��� ������ */
LTR01API_DllExport(INT) LTR01_GetModuleSubID(TLTR *hnd, WORD *subid);

/** ��������������� ������� ��� ��������� ��������������� ID ������ �� ���� �����.
    ������� ������������� ���������� � �������, �������� ID ������ � ���������
    ������������� ����������.

    ���������� ������������������ ������� LTR_Init(), LTR01_Open(),
    LTR01_GetModuleSubID() � LTR01_Close().

    @param[in] net_addr    IP-����� LTR-�������
    @param[in] net_port    TCP-���� ��� ������������ ����� � ��������
    @param[in] csn         �������� ����� ������
    @param[in] slot        ���� ������ (�� CC_MODULE1 �� CC_MODULE16)
    @param[out] subid      ��� ������ ������������ �������������� ID-������
                           �� #e_LTR01_SUBID.
    @return                ��� ������ */
LTR01API_DllExport(INT) LTR01_GetSubID(DWORD net_addr, WORD net_port, const CHAR *csn,
                                       INT slot, WORD *subid);

/** ��������� ����� ������ �� ��� ��������������� ��������������
    @param[out] subid      �������������� ������������� �� #e_LTR01_SUBID.
    @return                ������ � ������ ������ */
LTR01API_DllExport(LPCSTR) LTR01_GetModuleName(WORD subid);

/*============================================================================*/

#ifdef __cplusplus
}                                          // only need to export C interface if
                                           // used by C++ source code
#endif

#endif                      /* #ifndef LTR11API_H_ */
