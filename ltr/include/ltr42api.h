#ifndef LTR42API_H_
#define LTR42API_H_


#include "ltrapi.h"


/*================================================================================================*/
#ifdef _WIN32
    #ifdef LTR42API_EXPORTS
        #define LTR42API_DllExport(type)   __declspec(dllexport) type APIENTRY
    #else
        #define LTR42API_DllExport(type)   __declspec(dllimport) type APIENTRY
    #endif
#elif defined __GNUC__
    #define LTR42API_DllExport(type) __attribute__ ((visibility("default"))) type
#else
    #define LTR42API_DllExport(type)   type
#endif


#define LTR42_ERR_DATA_TRANSMISSON_ERROR              (-8013)
#define LTR42_ERR_WRONG_SECOND_MARK_CONF              (-8017)
#define LTR42_ERR_WRONG_START_MARK_CONF               (-8018)

#define LTR42_MARK_MODE_INTERNAL         (0)
#define LTR42_MARK_MODE_MASTER           (1)
#define LTR42_MARK_MODE_EXTERNAL         (2)

#define LTR42_EEPROM_SIZE                (512)


/*================================================================================================*/
#pragma pack(4) 
/* ��������� �������� ������ */
typedef struct {
    CHAR Name[16];
    CHAR Serial[24];
    CHAR FirmwareVersion[8];            /* ������ ����� */
    CHAR FirmwareDate[16];              /* ���� �������� ������ ������ ����� */
} TINFO_LTR42, *PTINFO_LTR42;

typedef struct {
    TLTR Channel;
    INT size;                           /* ������ ��������� */
    BOOLEAN AckEna;
    struct {
        INT SecondMark_Mode;            /* ����� �����. 0 - �����., 1-�����.+�����, 2-����� */
        INT StartMark_Mode;
    } Marks;                            /* ��������� ��� ������ � ���������� ������� */
    TINFO_LTR42 ModuleInfo;
} TLTR42, *PTLTR42;                     /* ��������� �������� ������ */
#pragma pack()


/*================================================================================================*/
#ifdef __cplusplus
extern "C" {
#endif

LTR42API_DllExport(INT) LTR42_Init(PTLTR42 hnd);

LTR42API_DllExport(INT) LTR42_Open(PTLTR42 hnd, INT net_addr, WORD net_port, const CHAR *crate_sn,
    INT slot_num);
LTR42API_DllExport(INT) LTR42_IsOpened(PTLTR42 hnd);
LTR42API_DllExport(INT) LTR42_Close(PTLTR42 hnd);

LTR42API_DllExport(INT) LTR42_Config(PTLTR42 hnd);
LTR42API_DllExport(INT) LTR42_ConfigAndStart(PTLTR42 hnd);

LTR42API_DllExport(INT) LTR42_WritePort(PTLTR42 hnd, WORD OutputData);
LTR42API_DllExport(INT) LTR42_WriteArray(PTLTR42 hnd, const WORD *OutputArray, INT ArraySize);

LTR42API_DllExport(INT) LTR42_WritePortSaved(PTLTR42 hnd, WORD OutputData);

LTR42API_DllExport(INT) LTR42_StartSecondMark(PTLTR42 hnd);
LTR42API_DllExport(INT) LTR42_StopSecondMark(PTLTR42 hnd);
LTR42API_DllExport(INT) LTR42_MakeStartMark(PTLTR42 hnd);

LTR42API_DllExport(INT) LTR42_WriteEEPROM(PTLTR42 hnd, INT Address, BYTE val);
LTR42API_DllExport(INT) LTR42_ReadEEPROM(PTLTR42 hnd, INT Address, BYTE *val);

LTR42API_DllExport(INT) LTR42_StoreConfig(PTLTR42 hnd, TLTR_CARD_START_MODE start_mode);

LTR42API_DllExport(LPCSTR) LTR42_GetErrorString(INT Error_Code);


/***************************************************************************//**
  @brief ��������� ������ �������� ����� �����

  ������ ������� ��������� ������ ����� ��������, ������������� ������� ��
  ������ ��� ��������� ����� �����, ���� ��������� ���������� ����� ����� ��
  ����� (����� #LTR42_MARK_MODE_MASTER).
  ��-��������� ����� �������� ���������� ������� 200��, ��� ����� ����
  ������������ ��� ������� ������ ��������� �� ������� ��������. ������ �������
  ��������� ���������� ������� ����� ��������.
  ������ ������� �������� ������ � ��������, ������� � ������ 2.0.

  @param[in] hnd        ��������� ������
  @param[in] time_mks   ����� �������� � ���. ���� 0 --- �� ������������ �������
                        ��-��������� (~200��).
  @return               ��� ������
 ******************************************************************************/
LTR42API_DllExport (INT) LTR42_SetStartMarkPulseTime(TLTR42 *hnd, DWORD time_mks);


#ifdef __cplusplus 
}
#endif

#endif
















