/** @file ltrt10api.h
    ���� �������� ����������� �������, ����� � �������� ��� ������ �
    ���������� ������� LTRT-10.

    ������ �������� DDS ��� ��������� ��������������� ������� �������� �������
    � ��������� � ���������� �� 4 ������. ��������� ����� ����� ������
    ���� �� ������������ ��������.

    ��� ������������� ������ ����������� ��������� (TLTRT10_CONFIG) � ���������
    ������� ��� � ������� ������� LTRT10_FillDDSFreq(),
    LTRT10_FillDDSOutAmpVolt()/LTRT10_FillDDSOutAmpCode(). ����� �����
    ���������� LTRT10_SetConfig() � ��������� ����� LTRT10_SetDDSReset().

    ����� �������� ��������� �������� ��� ���������� DDS
    ����� ��������� ����� ������������ � ����� LTRT10_SetConfig().
    */

#ifndef LTRT10API_H_
#define LTRT10API_H_


#include "ltr01api.h"

#ifdef __cplusplus
extern "C" {                                 // only need to export C interface if
                                             // used by C++ source code
#endif

#ifdef _WIN32
    #ifdef LTRT10API_EXPORTS
      #define LTRT10API_DllExport(type) __declspec(dllexport) type APIENTRY
    #else
      #define LTRT10API_DllExport(type) __declspec(dllimport) type APIENTRY
    #endif
#elif defined __GNUC__
    #define LTRT10API_DllExport(type) __attribute__ ((visibility("default"))) type
#else
    #define LTRT10API_DllExport(type)  type
#endif


/** ������ ������ � ������ ������ � ��������� #TINFO_LTRT10 */
#define LTRT10_NAME_SIZE        8
/** ������ ������ � �������� ������� ������ � ��������� #TINFO_LTRT10 */
#define LTRT10_SERIAL_SIZE      16

/** ���������� ����������� ������������ ��� ������ ������� ������� */
#define LTRT10_SWITCH_CNT       4

/** ���������� �������� �������� ������� DDS */
#define LTRT10_DDS_GAIN_CNT     2

/** ���������� ��������� ������������ �������� ������� DDS */
#define LTRT10_DDS_AMP_CNT      12

/** ������� ����� DDS */
#define LTRT10_DDS_CLK_FREQ     60000000.

/** �������� ������� ����� � DDS */
#define LTRT10_DDS_FREQ_DIV     (268435456)

/** ������������ �������� ���� FreqVal */
#define LTRT10_DDS_FREQ_VAL_MAX  (268435456-2)


/** ���� ������, ����������� ��� LTRT10. */
typedef enum
{
    LTRT10_ERR_INVALID_SWITCH_POS           = -10400, /**< ����� �������� ��� ��������� �����������*/
    LTRT10_ERR_INVALID_DDS_DIV              = -10401, /**< ����� �������� ��� ������������ �������� ��������� �������� ������� DDS */
    LTRT10_ERR_INVALID_DDS_GAIN             = -10402, /**< ����� �������� ��� �������� ��� DDS */
    LTRT10_ERR_INVALID_FREQ_VAL             = -10403, /**< ������� ����� ��� ������� ������� DDS */
    LTRT10_ERR_INVALID_DDS_AMP              = -10404, /**< ����� �������� ��� ��������� ������� DDS */
    LTRT10_ERR_GAIN2_EXCEED_GAIN1           = -10405  /**< ����. �������� ������ ������� ��������� ����. ������ ������� */
} e_LTRT10_ERROR_CODES;


/** �������� ��������� ����������� ��� ������ ������� ������� ��� �������������
    ������ */
typedef enum
{
    LTRT10_SWITCH_POS_ZERO         = 0, /**< ������ ���� */
    LTRT10_SWITCH_POS_DDS          = 1, /**< ���������� DDS ������ */
    LTRT10_SWITCH_POS_DAC          = 2, /**< ������ ������� � �������� ��� */
    LTRT10_SWITCH_POS_ZSTATE       = 3  /**< ����������������� ��������� */
} e_LTRT10_SWITCH_POS;

/** ��������� ��� ������� ������������ �������� ��������� �������� ������� DDS */
typedef enum
{
    LTRT10_DDS_DIV_1       = 0,
    LTRT10_DDS_DIV_0_75    = 1,
    LTRT10_DDS_DIV_0_5     = 2,
    LTRT10_DDS_DIV_0_25    = 3
} e_LTRT10_DDS_DIV;

/** ��������� ��� ������� ������������ �������� ��� ����� �� �������� ��������
    ������� DDS */
typedef enum
{
    LTRT10_DDS_GAIN_4   = 0,
    LTRT10_DDS_GAIN_2   = 1,
    LTRT10_DDS_GAIN_1   = 2
} e_LTRT10_DDS_GAIN;

/** ��������� ��� ������� ��������� �������� ��������� ������� �����
    LTRT10_FillDDSOutAmpCode() */
typedef enum
{
    LTRT10_DDS_OUT_AMP_9_6  = 0,
    LTRT10_DDS_OUT_AMP_7_2  = 1,
    LTRT10_DDS_OUT_AMP_4_8  = 2,
    LTRT10_DDS_OUT_AMP_3_6  = 3,
    LTRT10_DDS_OUT_AMP_2_4  = 4,
    LTRT10_DDS_OUT_AMP_1_8  = 5,
    LTRT10_DDS_OUT_AMP_1_2  = 6,
    LTRT10_DDS_OUT_AMP_0_9  = 7,
    LTRT10_DDS_OUT_AMP_0_6  = 8,
    LTRT10_DDS_OUT_AMP_0_45 = 9,
    LTRT10_DDS_OUT_AMP_0_3  = 10,
    LTRT10_DDS_OUT_AMP_0_15 = 11
} e_LTRT10_DDS_OUT_AMP;


/** ���������� � ������ */
typedef struct
{
    CHAR        Name[LTRT10_NAME_SIZE];      /**< �������� ������ (�������������� ����� ASCII-������) */
    CHAR        Serial[LTRT10_SERIAL_SIZE];  /**< �������� ����� ������ (�������������� ����� ASCII-������) */
    BYTE        VerPLD;                      /**< ������ �������� PLD  */
} TINFO_LTRT10;


/** ��������� DDS */
typedef struct
{    
    /** ����������� ������� ��������� ������� DDS. �������� �� #e_LTRT10_DDS_DIV.
        ����� ����������� ����� LTRT10_FillDDSOutAmpVolt()/LTRT10_FillDDSOutAmpCode() */
    WORD AmpDiv;
    /** ������������ �������� ��� ������ ������� ��������.
        ������ ����������� - �������� �� #e_LTRT10_DDS_GAIN.
        ����� ����������� ����� LTRT10_FillDDSOutAmpVolt()/LTRT10_FillDDSOutAmpCode() */
    BYTE Gain[LTRT10_DDS_GAIN_CNT];
    /** �������� ��� ������� ������� �� ������ DDS.
        ������� fout = FreqVal*LTRT10_DDS_CLK_FREQ/LTRT10_DDS_FREQ_DIV.
        ����� ����������� ����� LTRT10_FillDDSFreq()*/
    DWORD FreqVal;
} TLTRT10_DDS_CONFIG;


/** ��������� ������. ����������� ����� ������� LTRT10_SetConfig(). */
typedef struct
{
    BYTE SwitchPos[LTRT10_SWITCH_CNT]; /**< ��������� ������������ ��� ������� ������ */
    TLTRT10_DDS_CONFIG DDS; /**< ��������� DDS */
} TLTRT10_CONFIG;


/** ��������� ������ */
typedef struct
{
    INT size;     /**< ������ ���������. ����������� � LTRT10_Init(). */
    /** ���������, ���������� ��������� ���������� � ��������.
        �� ������������ �������� �������������. */
    TLTR Channel;
    /** ��������� �� ������������ ��������� � ����������� �����������,
        ������������� ������������� ����������� � ������������ ��� ������������. */
    PVOID Internal;
    /** ��������� ������, ������� ������������ �� LTRT10_SetConfig() */
    TLTRT10_CONFIG Cfg;

    BYTE CurDSSFreqReg; /**< �������, ����� ������ ������������ ������� DDS */
    BOOL DDSInReset; /**< �������, ��������� �� DDS � ���������� ��������� */
    double DDSFreq; /**< ������������� ������ ������� DSS. ����������� ����� LTRT10_SetConfig() */
    double DDSAmp; /**< ������������� ��������� ��������� ������� DDS. ����������� ����� LTRT10_SetConfig() */

    TINFO_LTRT10 ModuleInfo;
} TLTRT10;


/*============================================================================*/

LTRT10API_DllExport(INT) LTRT10_Init(TLTRT10 *hnd);
LTRT10API_DllExport(INT) LTRT10_Open(TLTRT10 *hnd, DWORD net_addr, WORD net_port,
                                     const CHAR *csn, WORD slot);
LTRT10API_DllExport(INT) LTRT10_Close(TLTRT10 *hnd);
LTRT10API_DllExport(INT) LTRT10_IsOpened(TLTRT10 *hnd);

/** �������� �������� DDS � ������������ � ������. ����� ���������
    ����������� ��� ����� ��������� �� ����.
   @param[in] hnd       ���������
   @return              ��� ������ */
LTRT10API_DllExport(INT) LTRT10_SetConfig(TLTRT10 *hnd);

/** ��������� ��� ������ ������� ������ ���������� DDS. ����� LTRT10_Open()
    DDS ��������� � ���������� ���������. ��� ������� LTRT10_SetDDSReset()
    ���������� ����� ������ ��������� ������������ � ������� LTRT10_SetConfig()
    ��� ������ ������. ���� DDSInReset ��������� ����������, ��������� ��
    ���������� DDS ������ � ��������� ������
   @param[in] hnd       ���������
   @param[in] reset     ��������������� ��������� ������� ������ DDS
                        (TRUE - ����� �������, FALSE - ������� �����)
   @return              ��� ������ */
LTRT10API_DllExport(INT) LTRT10_SetDDSReset(TLTRT10 *hnd, BOOL reset);


/** ������� ��������� ���� DDS.FreqVal ������������, ����� �������������� �������
    ������� DDS ���� �������� ������ � ���������.
    @param[in]  cfg       ��������� �� ��������� � �������������
    @param[in]  freq      ��������������� ������� � ��
    @param[out] set_freq  ���� �� NULL, �� ������������ �������� �������,
                          ��������������� ���������� �������� DDS.FreqVal
    @return              ��� ������ */
LTRT10API_DllExport(INT) LTRT10_FillDDSFreq(TLTRT10_CONFIG *cfg, double freq, double* set_freq);

/** ������� ��������� ���� DDS.AmpDiv � DDS.Gain ������������, ����� ��������������
    ��������� ��������� ������� DDS ���� �������� ������ � ���������.
    @param[in]  cfg       ��������� �� ��������� � �������������
    @param[in]  value     ��������������� ��������� ������� � �������
    @param[out] set_value ���� �� NULL, �� ������������ �������� ���������,
                          ��������������� ��������� ������������� ��������.
    @return               ��� ������ */
LTRT10API_DllExport(INT) LTRT10_FillDDSOutAmpVolt(TLTRT10_CONFIG *cfg, double value, double* set_value);

/** ������� ��������� ���� DDS.AmpDiv � DDS.Gain ������������ �� ����������
    ���� ��������� �� #e_LTRT10_DDS_OUT_AMP.
    @param[in]  cfg       ��������� �� ��������� � �������������
    @param[in]  code      ��� ��������� �� #e_LTRT10_DDS_OUT_AMP
    @return               ��� ������ */
LTRT10API_DllExport(INT) LTRT10_FillDDSOutAmpCode(TLTRT10_CONFIG *cfg, DWORD code);

/***************************************************************************//**
   @brief ��������� ��������� �� ������.

   ������� ���������� ������, ��������������� ����������� ���� ������, � ���������
   CP1251 ��� Windows ��� UTF-8 ��� Linux. ������� ����� ���������� ��� ������
   �� ltrt10api, ��� � ����� ���� ������ �� ltrapi.

   @param[in] err       ��� ������
   @return              ��������� �� ������, ���������� ��������� �� ������.
 ******************************************************************************/
LTRT10API_DllExport(LPCSTR) LTRT10_GetErrorString(INT err);



#ifdef __cplusplus
}                                          // only need to export C interface if
                                           // used by C++ source code
#endif

#endif                      /* #ifndef LTR11API_H_ */
