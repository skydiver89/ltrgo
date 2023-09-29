#ifndef LTR25API_H_
#define LTR25API_H_

#include "ltrapi.h"

#ifdef __cplusplus
extern "C" {
#endif


#ifdef _WIN32
    #ifdef LTR25API_EXPORTS
        #define LTR25API_DllExport(type) __declspec(dllexport) type APIENTRY
    #else
        #define LTR25API_DllExport(type) __declspec(dllimport) type APIENTRY
    #endif
#elif defined __GNUC__
    #define LTR25API_DllExport(type) __attribute__ ((visibility("default"))) type
#else
    #define LTR25API_DllExport(type) type
#endif


/***************************************************************************//**
  @addtogroup const_list ��������� � ������������.
  @{
  *****************************************************************************/

/** ���������� ������� ��� � ����� ������ LTR25 */
#define LTR25_CHANNEL_CNT        8

/** ���������� ������ �������������. */
#define LTR25_FREQ_CNT           8

/** ���������� ������, ��� ������� ����������� ������������� ������������ */
#define LTR25_CBR_FREQ_CNT       2

/** ���������� �������� ��������� ���� */
#define LTR25_I_SRC_VALUE_CNT    2

/** ������ ���� � ��������� ������. */
#define LTR25_NAME_SIZE          8

/** ������ ���� � �������� ������� ������. */
#define LTR25_SERIAL_SIZE       16

/** ������������ ������� �������� � ������� ��� ��������� ��������� ������ */
#define LTR25_ADC_RANGE_PEAK    10

/** ��� ���, ��������������� ������������� �������� �������� */
#define LTR25_ADC_SCALE_CODE_MAX 2000000000



/** �����, � �������� ���������� ���������������� ������� flash-������ */
#define LTR25_FLASH_USERDATA_ADDR   0x0
/** ������ ���������������� ������� flash-������ */
#define LTR25_FLASH_USERDATA_SIZE   0x100000
/** ����������� ������ ����� ��� �������� flash-������. ��� �������� ��������
    ������ ���� ������ ������� ������� */
#define LTR25_FLASH_ERASE_BLOCK_SIZE 4096

/** ������ ����� ������ TEDS �������. ������ ����� ���� ������ ������� ����� ������� */
#define LTR25_TEDS_MEMORY_BLOCK_SIZE 8


/** @brief ���� ������, ����������� ��� ������ LTR25.

   ���� ������, ������� ���������� � ������������ ������ � ltr25api.
   ��������� ���� ������, ������� ������������ ������� ��������, ���������� � ltrapi.h */
typedef enum {
    LTR25_ERR_FPGA_FIRM_TEMP_RANGE      = -10600, /**< ��������� �������� ���� ��� ��������� �������������� ��������� */
    LTR25_ERR_I2C_ACK_STATUS            = -10601, /**< ������ ������ ��� ��������� � ��������� ��� �� ���������� I2C */
    LTR25_ERR_I2C_INVALID_RESP          = -10602, /**< �������� ����� �� ������� ��� ��������� � ��������� ��� �� ���������� I2C */
    LTR25_ERR_INVALID_FREQ_CODE         = -10603, /**< ������� ����� ��� ������� ��� */
    LTR25_ERR_INVALID_DATA_FORMAT       = -10604, /**< ������� ����� ������ ������ ��� */
    LTR25_ERR_INVALID_I_SRC_VALUE       = -10605, /**< ������� ������ �������� ��������� ���� */
    LTR25_ERR_CFG_UNSUP_CH_CNT          = -10606, /**< ��� �������� ������� � ������� �� �������������� �������� ���������� ������� ��� */
    LTR25_ERR_NO_ENABLED_CH             = -10607, /**< �� ��� �������� �� ���� ����� ��� */
    LTR25_ERR_ADC_PLL_NOT_LOCKED        = -10608, /**< ������ ������� PLL ��� */
    LTR25_ERR_ADC_REG_CHECK             = -10609, /**< ������ �������� �������� ���������� ��������� ��� */
    LTR25_ERR_LOW_POW_MODE_NOT_CHANGED  = -10610, /**< �� ������� ��������� ��� ��/� ����������������� ��������� */
    LTR25_ERR_LOW_POW_MODE              = -10611, /**< ������ ��������� � ����������������� ������ */
    LTR25_ERR_INVALID_SENSOR_POWER_MODE = -10612, /**< �������� �������� ������ ������� �������� */
    LTR25_ERR_CHANGE_SENSOR_POWER_MODE  = -10613, /**< �� ������� �������� ����� ������� �������� */
    LTR25_ERR_TEDS_MODE_REQUIRED        = -10614, /**< ��� ���� �������� ���������� ��������� ������ � TEDS ����� ������� �������� */
    LTR25_ERR_TEDS_1W_NO_PRESENSE_PULSE = -10615, /**< �� ���������� ������� ����������� TEDS-������� �� ������������� ���� */
    LTR25_ERR_TEDS_1W_NOT_IDLE          = -10616, /**< ������������� ����� �� ���� � ��������� ��������� �� ������ ������ ������ */
    LTR25_ERR_TEDS_1W_UNKNOWN_ERR       = -10617, /**< ����������� ������ ��� ������ �� ������������� ����� � TEDS-�������� */
    LTR25_ERR_TEDS_1W_MEM_STATUS        = -10618, /**< �������� ��������� ������ TEDS-������� */
    LTR25_ERR_TEDS_1W_ROM_CRC           = -10619, /**< �������� �������� ����������� ����� ������������ ����������� ROM-������ TEDS-������� */
} e_LTR25_ERROR_CODES;


/** ���� ������ ����� ��� */
typedef enum {
    LTR25_FREQ_78K     = 0,     /**< 78.125 ��� */
    LTR25_FREQ_39K     = 1,     /**< 39.0625 ��� */
    LTR25_FREQ_19K     = 2,     /**< 19.53125 ��� */
    LTR25_FREQ_9K7     = 3,     /**< 9.765625 ��� */
    LTR25_FREQ_4K8     = 4,     /**< 4.8828125 ��� */
    LTR25_FREQ_2K4     = 5,    /**< 2.44140625 ��� */
    LTR25_FREQ_1K2     = 6,    /**< 1.220703125 ��� */
    LTR25_FREQ_610     = 7,    /**< 610.3515625 �� */
} e_LTR25_FREQS;


/** ������� ������ �� ������ */
typedef enum {
    LTR25_FORMAT_20 = 0, /**< 20-������ ������������� (1 ����� �� ������) */
    LTR25_FORMAT_32 = 1, /**< 32-������ ������������� (2 ����� �� ������) */
} e_LTR25_FORMATS;

/** �������� ��������� ����. */
typedef enum {
    LTR25_I_SRC_VALUE_2_86   = 0, /**< 2.86 ��. */
    LTR25_I_SRC_VALUE_10     = 1  /**< 10 ��. */
} e_LTR25_I_SOURCES;

/** @brief ����� ��������� ������.

    �����, ����������� ������� ������� LTR25_ProcessData() */
typedef enum {
    /** �������, ��� ����� ��������� ���� ��� � ������. ���� ������ ���� �� ������,
        �� ����� ���������� ���� ���. ��� ���� ��� #LTR25_ADC_SCALE_CODE_MAX
        ������������� ������������� ���������� ��� �������������� ���������. */
    LTR25_PROC_FLAG_VOLT          = 0x0001,
    /** �� ��������� LTR25_ProcessData() ������������, ��� �� �� ���������
        ���������� ��� �������� ������ � ��������� ������������� �������� �� ������
        ������ ����������� ����� ������, �� � ����� ��������.
        ���� �������������� �� ��� ������ ��� ���� � �� �� ������ ��������������
        ��������, �� ����� ������� ������ ����, ����� ������� ���������� ������
        ������ ��������������� ����� */
    LTR25_PROC_FLAG_NONCONT_DATA = 0x0100,
    /** ��� ������������� ����� ������� ����� ���������� �������� ������� �������.
     *  ������ LTR25 ����������� ������� ������. ��� ������������� ������ ��-���������
     *  ��������� ��� ����, ��� ���������. ����� ������ ��� ���������� ����������,
     *  ��� ��� ��� �����, ����� �������� ���� ���� */
    LTR25_PROC_FLAG_CORRECT_INVERSION = 0x1000
} e_LTR25_PROC_FLAGS;



/** @brief ��������� �������� ������.

    ������������ LTR25_ProcessData() ��� ������� ������������ ������ � ����������,
    ��� �� ��������� ����� ��� �� ��� ������� ������ � �������������� � �������
    LTR25_ProcessData() ����� */
typedef enum {
    LTR25_CH_STATUS_OK          = 0, /**< ����� � ������� ��������� */
    LTR25_CH_STATUS_SHORT       = 1, /**< ���� ���������� �������� ��������� */
    LTR25_CH_STATUS_OPEN        = 2, /**< ��� ��������� ������ ���� */
} e_LTR25_CH_STATUS;

/** @brief ����� ������� ��������

    ����� ������� ���� �������� ��� ���� ������ �������. ��������������� ��������
    LTR25_SetSensorsPowerMode(). */
typedef enum {
    LTR25_SENSORS_POWER_MODE_ICP = 0, /**< ������� �������� ��������. ������� ����� ��� ICP-��������. */
    LTR25_SENSORS_POWER_MODE_OFF = 1, /**< � ������ ������ ������� �������� ��������� */

    LTR25_SENSORS_POWER_MODE_TEDS = 2, /**< ������ ������� �������� ����������. ��� �����������
                                         ����� ��� ������ ������ TEDS-�������� */
} e_LTR25_SENSORS_POWER_MODE;

/** @} */

/***************************************************************************//**
  @addtogroup type_list ���� ������.
  @{
  *****************************************************************************/

#pragma pack(4)

/** @brief ������������� ������������.

    ���������, �������� ������������� ������������ ��� ������ ������
    � ���������. */
typedef struct {
    float   Offset; /**< ��� �������� */
    float   Scale;  /**< ����������� ����� */
} TLTR25_CBR_COEF;



/** @brief ����� ������������� ��� ��������� ��� ������ */
typedef struct {
    /** ������� �������, ��� ������� ����� ��������� �������� �� FirCoef */
    double AfcFreq;
    /** ����� ��������� ���������� ��������� ��������������� �������
         � �������� ��������� ��� ����. ������� ������������� � ������� �������
         �� AfcFreq ��� ������� ������ */
    double FirCoef[LTR25_CHANNEL_CNT];
} TLTR25_AFC_COEFS;

/** @brief  ���������� � ������.

    ���������, ���������� ���������� � ������� �������� ��������� ������ �
    ����������, ��������� �� Flash-������ ������ (�������� �����, �������������
    ������������).

    ��� ���� ����������� ��� ������ LTR25_Open()
 */
typedef struct {
    /** �������� ������ ("LTR25").  */
    CHAR        Name[LTR25_NAME_SIZE];
    /** �������� ����� ������.      */
    CHAR        Serial[LTR25_SERIAL_SIZE];
    /** ������ �������� ���� */
    WORD        VerFPGA;
    /** ������ �������� PLD */
    BYTE        VerPLD;
    /** ������� ����� */
    BYTE        BoardRev;
    /** �������, ��� �������������� ������� ������ ��� ��� */
    BOOL        Industrial;
    /** ����������������� ����. ������ ����� 0 */
    DWORD       Reserved[8];
    /** ������������� ������������ ������. ����������� �� Flash-������
        ������ ��� ������ LTR25_Open() ��� LTR25_GetConfig() � �����������
        � ���� ��� ���������� �� ����� ������ LTR25_SetADC() */
    TLTR25_CBR_COEF CbrCoef [LTR25_CHANNEL_CNT] [LTR25_CBR_FREQ_CNT];
    /** ������������ ��� ��������� ��� ������ */
    TLTR25_AFC_COEFS AfcCoef;
    /** ��������� ���� */
    double     Reserved2[32*LTR25_CHANNEL_CNT-sizeof(TLTR25_AFC_COEFS)/sizeof(double)];
} TINFO_LTR25;

/** @brief ��������� ������ ���.

    ���������, ���������� ��������� ������ ������ ���. */
typedef struct {
    BOOL  Enabled; /**< �������, �������� �� ���� �� ������� ������ */
    DWORD Reserved[11];  /**< ��������� ���� (�� ������ ���������� �������������) */
} TLTR25_CHANNEL_CONFIG;

/** @brief ��������� ������.

    ��������� �������� ��� ��������� ������, ������� ������ ���������
    ������������ ����� ������� LTR25_SetADC(). */
typedef struct {
    TLTR25_CHANNEL_CONFIG Ch[LTR25_CHANNEL_CNT]; /**< ��������� ������� ��� */
    BYTE        FreqCode; /**< ���, �������� ��������� ������� ����� ���.
                               ���� �� �������� #e_LTR25_FREQS */
    BYTE        DataFmt;  /**< ������, � ������� ����� ������������ �������
                               ��� �� ������. ���� �� �������� #e_LTR25_FORMATS.
                               ������ ���������� ����� ���������� ������������
                               ���� �� ���� ������ � ������ �� ������������
                               ���������� ����������� ������� */
    BYTE        ISrcValue; /**< ������������ �������� ��������� ����. ���� ��
                                �������� #e_LTR25_I_SOURCES */
    DWORD       Reserved[50]; /**< ��������� ���� (�� ������ ���������� �������������) */
} TLTR25_CONFIG;


/** @brief ��������� �������� ��������� ������.

    ���������, ���������� ��������� ������, ������� ������������ ������ ������������
    ������ ��� ������, ��� ��� ��� ���������� ������ ������ ������� ltr25api. */
typedef struct {
    BYTE   FpgaState; /**<  ������� ��������� ����. ���� �� �������� �� e_LTR_FPGA_STATE */
    BYTE   EnabledChCnt; /**< ���������� ����������� �������. ���������������
                                ����� ������ LTR25_SetADC() */
    BOOL   Run;         /**< �������, ������� �� ���� ������ */
    double AdcFreq;     /**< ������������� ������� ���. ����������� �����
                            ������ LTR25_SetADC() */
    BOOL   LowPowMode; /**< �������, ��������� �� ������ � ��������� �������
                            �����������. � ���� ��������� ������ ��������� ���������
                            ��� ��� ������ ����� ������. ���������� ������
                            ������� ����������� � ������� LTR25_SetLowPowMode() */
    DWORD   SensorsPowerMode; /**< ������� ����� ������� �������� ��� ���� ������
                                   �������. �������� �� #e_LTR25_SENSORS_POWER_MODE.
                                   ���������� ������ ������� ����������� � �������
                                   ������� LTR25_SetSensorsPowerMode(). */
    DWORD   Reserved[30]; /**< ��������� ���� */
} TLTR25_STATE;

/** @brief  ����������� ��������� ������.
 *
 *  ������ ������� ��������� ������, ���������� �
 *  ��� ���������, ��������� ������ �����. ���������� � ����������� �������
 *  ����������. ��������� ���� ��������� �������� ��� ��������� �������������
 *  ��� ��������� ���������� ������. ����� �������������� ������� �������������
 *  � ������� ������� LTR25_Init().
 */
typedef struct {
    INT         Size; /**< ������ ���������. ����������� � LTR25_Init(). */
    /** ���������, ���������� ��������� ����������� ���������� �� ������� ltrd.
        �� ������������ �������� �������������. */
    TLTR        Channel;
    /** ��������� �� ������������ ��������� � ����������� �����������,
      ������������� ������������� ����������� � ������������ ��� ������������. */
    PVOID       Internal;
    /** ��������� ������. ����������� ������������� ����� ������� LTR25_SetADC(). */
    TLTR25_CONFIG Cfg;
    /** ��������� ������ � ������������ ���������. ���� ���������� ���������
        ����������. ���������������� ���������� ����� ��������������
        ������ ��� ������. */
    TLTR25_STATE  State;
    /** ���������� � ������ */
    TINFO_LTR25 ModuleInfo;
} TLTR25;

#pragma pack()

/** @} */

/***************************************************************************//**
    @addtogroup func_init ������� ������������� � ������ � ����������� � �������.
    @{
*******************************************************************************/

/***************************************************************************//**
  @brief ������������� ��������� ������.

  ������� �������������� ���� ��������� ��������� ������ ���������� ��-���������.
  ��� ������� ������ ���������� ��� ������ ��������� #TLTR25 ����� �������
  ��������� �������.
   @param[in] hnd       ��������� ������
   @return              ��� ������
 ******************************************************************************/
LTR25API_DllExport(INT) LTR25_Init(TLTR25 *hnd);

/***************************************************************************//**
   @brief �������� ���������� � �������.

   ������� ������������� ���������� � ������� � ������������ � �����������
   �����������, ��������� ������� ������ � ��������� ���������� � ���.
   ������ ���� ������� ����� ������� � �������. ����� ���������� ������
   ���������� ������� ���������� � ������� LTR25_Close().

   @param[in] hnd       ��������� ������
   @param[in] ltrd_addr  IP-����� ������, �� ������� �������� ������ ltrd, � 32-������
                        ������� (������ � ������� "������ ������� IP-�������"
                        @docref_ltrapi{����������� ��� ���������� ltrapi}).
                        ���� ������ ltrd �������� �� ��� �� ������, ��� � ���������,
                        ���������� ������ �������, �� � �������� ������
                        ����� �������� LTRD_ADDR_DEFAULT.
   @param[in] ltrd_port TCP-���� ��� ����������� � ������ ltrd. �� ���������
                        ������������ LTRD_PORT_DEFAULT.
   @param[in] csn       �������� ����� ������, � ������� ��������� ������������
                        ������. ������������ ����� �������������� ����� ASCII-������.
                        ��� ���������� � ������ ��������� ������� ����� ��������
                        ������ ������ ��� ������� ���������.
   @param[in] slot      ����� ����� ������, � ������� ���������� ������������ ������.
                        �������� �� LTR_CC_CHNUM_MODULE1 �� LTR_CC_CHNUM_MODULE16.
   @return              ��� ������
*******************************************************************************/
LTR25API_DllExport(INT) LTR25_Open(TLTR25 *hnd, DWORD ltrd_addr, WORD ltrd_port, const CHAR *csn, INT slot);

/** @cond kd_extension */
LTR25API_DllExport(INT) LTR25_OpenEx(TLTR25 *hnd, DWORD ltrd_addr, WORD ltrd_port,
    const CHAR *crate_sn, INT slot, DWORD in_flags, DWORD *out_flags);
/** @endcond */

/***************************************************************************//**
   @brief �������� ���������� � �������.

   ������� ��������� ����� �������� � ������� LTR25_Open() ����������. ������
   ���������� ����� ���������� ������ � �������. ��� ����� ������������ ��������
   ����� ������ ���� ������� ��������������� ��������� ��� ������ ������������
   ��� ������ � ������� ��� �������� ������ ����������.

   @param[in] hnd       ��������� ������
   @return              ��� ������
 ******************************************************************************/
LTR25API_DllExport(INT) LTR25_Close(TLTR25 *hnd);

/***************************************************************************//**
   @brief ��������, ������� �� ���������� � �������.

   ������� ���������, ������� �� � ������ ������ ���������� � �������. ����
   ���������� �������, ������� ���������� LTR_OK, ���� ������� --- ��� ������
   LTR_ERROR_CHANNEL_CLOSED.
   @param[in] hnd       ��������� ������
   @return              ��� ������ (LTR_OK, ���� ���������� �����������)
 ******************************************************************************/
LTR25API_DllExport(INT) LTR25_IsOpened(TLTR25 *hnd);



/** @} */

/***************************************************************************//**
    @addtogroup func_config ������� ��� ��������� �������� ������
    @{
*******************************************************************************/

/***************************************************************************//**
   @brief ������ �������� � ������.

   ������� �������� ���������, ��������������� ��������� ����� ���� Cfg ���������
   ������, � ������. ������ ���������� ����� �������� ����� ������ � �������
   LTR25_Start().

   @param[in] hnd       ��������� ������
   @return              ��� ������
 ******************************************************************************/
LTR25API_DllExport(INT) LTR25_SetADC(TLTR25 *hnd);

/** @} */



/***************************************************************************//**
    @addtogroup func_stream ������� ��� ���������� ������ ������
    @{
*******************************************************************************/

/***************************************************************************//**
    @brief ������ ����� ������.

    ��� ������ ������ ������� ����������� ���� ������ ��� �������. ����� ���������
    ���������� ���� ������� ����������� ��� � ������ �������� ���������� � ��
    ���������� �������, ������� ���������� ���������� � ������� LTR25_Recv().
    ��� ���������� ��������� ��� ��������� ����� ������ ���������� �������
    LTR25_Stop().

    ���� �� ���� �� ������� ��� ������ ���� �� ����� �������� � ������ ������ ����
    ��������������� � ������� LTR25_SetADC().

   @param[in] hnd       ��������� ������
   @return              ��� ������
 ******************************************************************************/
LTR25API_DllExport(INT) LTR25_Start(TLTR25 *hnd);

/***************************************************************************//**
    @brief ������� ����� ������.

    ��� ������ ������ ������� ������ ������������� ���� � ������ ������ ���.

    ��� ���� ������������ � ������������� ��� ����������, �� �������������
    ������ �� ������.

   @param[in] hnd       ��������� ������
   @return              ��� ������
 ******************************************************************************/
LTR25API_DllExport(INT) LTR25_Stop(TLTR25 *hnd);

/***************************************************************************//**
   @brief ����� ������ �� ������.

   ������� ��������� ������������� ����� ���� �� ������. ������������ �����
   ��������� � ����������� �������, ������� �������� � ���� ��������� ����������.
   ������ � ���������� ���� �� ���� ������ ������������ ���������� Cfg.DataFmt

   ��� ��������� �������� ���� � ��������� �������� ��� ������������ �������
   LTR25_ProcessData().

   ������� ���������� ���������� ���� ����� ������ ����������� ���������� ����,
   ���� �� ��������� ��������. ��� ���� ������� �������� ���������� ���� �����
   ������ �� ������������� ��������.

   @param[in]  hnd      ��������� ������.
   @param[out] data     ������, � ������� ����� ��������� �������� �����. ������
                        ���� �������� �� size 32-������ ����.
   @param[out] tmark    ��������� �� ������ �������� �� size 32-������ ����,
                        � ������� ����� ��������� �������� ��������� �����������,
                        ��������������� �������� ������. ��������� �����
                        ������������� ��� ������ ��� ������������ ������ ��������.
                        ����������� ��������� ������� � ������� "�����������"
                        @docref_ltrapi{����������� ��� ���������� ltrapi}.
                        ���� ����������� �� ������������, �� ����� ��������
                        � �������� ��������� ������� ���������.
   @param[in]  size     ������������� ���������� 32-������ ���� �� �����.
   @param[in]  timeout  ������� �� ���������� �������� � �������������. ���� � �������
                        ��������� ������� �� ����� ������� ������������� ����������
                        ����, �� ������� ��� ����� ������ ����������, ���������
                        � �������� ���������� ������� �������� ���������� ����
   @return              �������� ������ ���� ������������� ���� ������. ��������
                        ������ ��� ������ ���� ������������� ���������� �������
                        �������� � ����������� � ������ data ����.
*******************************************************************************/
LTR25API_DllExport(INT) LTR25_Recv(TLTR25 *hnd, DWORD *data, DWORD *tmark, DWORD size,
                                   DWORD timeout);


/****************************************************************************//**
   @brief ��������� �������� �� ������ ����.

   ������� ������������ ��� ��������� ����, �������� �� ������ � ������� LTR25_Recv().
   ������� ��������� ��������� ���� �������� ����, ��������� �������� ����������
   � ��������� �, ��� �������� ����� #LTR25_PROC_FLAG_VOLT, ��������� ������� �
   ������.

   ������� ������������, ��� ������������ ����� ��������� �� ������ ����� (������
   ����� ������� ������������ ������). ���� ��� �� ���, �� �������� ���� � ������
   ����� �������� � ������� ������ ������ LTR_ERROR_PROCDATA_UNALIGNED.

   ����� ������� ����������� �������� ������ ��� �� � ����������� �������. ���
   ������� ��������� �������� ��� ���� �� ������ ������� ����������������
   ������ ��������������� ��������������� ������ � �������� ������� ch_status.

   � ������� �� ������ LTR24 � ������ LTR25 ���������� �������� � �������������
   ��� ����������� ������ ������ ���������, ������� � LTR25_ProcessData() ���
   �������� ������.

   ������� ��������� ����������� ������ � ������� �������� �� ���������
   ����������. ��-��������� ������� ������������, ��� ��� �������� ������ ��������������
   � ������ ���� ���, �������� ������������� �������� � ����� �������� �������.
   ���� ��� ������� �� �����������, �� ����� �������� ���� #LTR25_PROC_FLAG_NONCONT_DATA.

   @param[in] hnd      ��������� ������.
   @param[in] src      ��������� �� ������, ���������� �����, �������� �� ������
                       � ������� LTR25_Recv(), ������� ����� ����������.
   @param[out] dest    ��������� �� ������, � ������� ����� ��������� ������������
                       ������. ������� ���������� ������������� ������� �� �������
                       ������� (�.�. ������ ������ ������ ������� ������������ ������,
                        ����� ������ ������ ������� ������ � �.�.).
   @param[in,out] size  �� ����� ��������� ������ ������� src ��� ���������. ��
                        ������, ��� �������� ����������, ���������� ����������
                        ����������� �������� � ������� dest.
   @param[in]  flags   ����� �� #e_LTR25_PROC_FLAGS, ����������� ������� �������.
                        ����� ���� ���������� ��������� ������ ����� ����������
                        ���.
   @param[out] ch_status  ������ �������� �� ���������� ���������, ���������������
                        ���������� ����������� �������. � ������ ������� �����������
                        ������ ������ (���� �� �������� #e_LTR25_CH_STATUS),
                        ������������, ���� �� �������� �� ��� ������
                        � ��������������� ������. ����� ���� ������� �������
                        ���������, ���� ��� ���������� �� �����.
   @return              ��� ������.
  *****************************************************************************/
LTR25API_DllExport(INT) LTR25_ProcessData(TLTR25 *hnd, const DWORD *src, double *dest,
                                    INT *size, DWORD flags, DWORD *ch_status);


/****************************************************************************//**
   @brief ����� ������ ������� �����.

   ������� ������� � �������� ������� ����� ������ �� ������ ������ �������
   ����� ������� ������ �����. ����� �������������� ��� ������������ ��
   ������ ����� ������ � ������ ������������� ���� ��� �������� �����.

   ���� � ���������� ������� ������ ����� �� �������, �� ������� ������ ������
   LTR_ERROR_FIRSTFRAME_NOTFOUND.

   @param[in] hnd      ��������� ������.
   @param[in] data     ��������� �� ������, ���������� �����, �������� �� ������
                       � ������� LTR25_Recv(), � ������� ������ ������ �����.
   @param[in] size     ���������� ���� � ������� data
   @param[out] index   � ���� ���������� ������������ ������ ��������,
                       ���������������� ������ ������� �����, ���� �������
                       ����������� �������.
   @return             ��� ������.
  *****************************************************************************/
LTR25API_DllExport(INT) LTR25_SearchFirstFrame(TLTR25 *hnd, const DWORD *data, DWORD size,
                                                DWORD *index);

/** @} */

/***************************************************************************//**
    @addtogroup func_misc ������� ���������������� ���������
    @{
*******************************************************************************/

/***************************************************************************//**
   @brief ��������� ��������� �� ������.

   ������� ���������� ������, ��������������� ����������� ���� ������, � ���������
   CP1251 ��� �� Windows ��� UTF-8 ��� �� Linux. ������� ����� ���������� ��� ������
   �� ltr25api, ��� � ����� ���� ������ �� ltrapi.

   @param[in] err       ��� ������
   @return              ��������� �� ������, ���������� ��������� �� ������.
 ******************************************************************************/
LTR25API_DllExport(LPCSTR) LTR25_GetErrorString(INT err);


/***************************************************************************//**
    @brief ������ ���������� � ������������� �������������.

    ������� ��������� ���������� �� flash-������ ������ � ��������� ���� ModuleInfo
    � ����������� ��������� ������. ��� ��� ������ �������� ��� ����������� ���
    ������ LTR25_Open(), �� ��� ������� ����� ������ ������� �� ���������.
    ������ ������ ������� ����� ���� ������������ ��� �������������� ����������
    ������������� � ModuleInfo �� ���������.


   @param[in] hnd      ��������� ������.
   @return             ��� ������.
 ******************************************************************************/
LTR25API_DllExport(INT) LTR25_GetConfig(TLTR25 *hnd);

/** @cond kd_extension */
LTR25API_DllExport(INT) LTR25_StoreConfig(TLTR25 *hnd, TLTR_CARD_START_MODE start_mode);
/** @endcond */


/***************************************************************************//**
    @brief ������� ������ � ����� ������� �����������.

    ������� ��������� ������ � ����� ������� ����������� ��� ��������� ���
    �� ����� ������ ����� � �������. � ������ ������� �����������
    ����� ������� � ��� � ��������� ���� ����������� 2.86 ��. ������
    � ��������� ��� ����������. ���� ����� ����� ���� ����������� ��� �������
    ������ ���, ��� ���� � ���� ������ ������ ������ ��������� �� ����� 5 �.

   @param[in] hnd           ��������� ������.
   @param[in] lowPowMode    ���� FALSE --- ������� ������ � ������� �����, ����� ---
                            � ����� ������� �����������.
   @return                  ��� ������.
 ******************************************************************************/
LTR25API_DllExport(INT) LTR25_SetLowPowMode(TLTR25 *hnd, BOOL lowPowMode);





/***************************************************************************//**
   @brief ��������, ��������� �� ������ ���� ������.

   ������� ���������, ��������� �� ������ ���� ������. ��� ��������� � �����
   ������ ���� ������ ���� ������ ��������.

   @param[in] hnd      ��������� ������.
   @param[out] enabled � ������ ��������� ���������� ������� � ���� ����������
                       ������������ FALSE, ���� ���� ��������, ��� TRUE �
                       ��������� ������.
   @return             ��� ������.
 ******************************************************************************/
LTR25API_DllExport(INT) LTR25_FPGAIsEnabled(TLTR25 *hnd, BOOL *enabled);

/***************************************************************************//**
   @brief ���������� ������ ���� ������.

   ������� ��������� ��� ��������� ������ ���� ������. ��� ��������� � �����
   ������ ���� ������ ���� ������ ��������. � LTR25_Open() ����������� ����������
   ������ ����, ���� ���� ������� �������� ���� � ������ ������ � ��� ����
   ������� ���������, ������� � ������� ������ ������ ������� �� ������������.

   @param[in] hnd      ��������� ������.
   @param[in] enable   ���� FALSE --- ������ ������ ����, ����� --- ����������
   @return             ��� ������.
 ******************************************************************************/
LTR25API_DllExport(INT) LTR25_FPGAEnable(TLTR25 *hnd, BOOL enable);

/** @} */


/***************************************************************************//**
    @addtogroup func_flash ������� ��� ������ � flash-������� ������
    @{
*******************************************************************************/

/***************************************************************************//**
   @brief ������ ������ �� flash-������ ������

   ������� ���������� ������, ���������� �� flash-������ ������ �� ���������
   ������. ������������ ���������� ������� ������ � ������
   #LTR25_FLASH_USERDATA_ADDR �������� #LTR25_FLASH_USERDATA_SIZE ����.

   @param[in] hnd      ��������� ������.
   @param[in] addr     ����� ������, ������� � �������� ���������� ��������� ������
   @param[out] data    ������ �� size ����, � ������� ����� �������� �����������
                       �� Flash-������ ������
   @param[in] size     ���������� ������ � ������, ������� ���������� ���������
   @return             ��� ������.
 ******************************************************************************/
LTR25API_DllExport(INT) LTR25_FlashRead(TLTR25 *hnd, DWORD addr, BYTE *data, DWORD size);

/***************************************************************************//**
   @brief ������ ������ �� flash-������ ������

   ������� ���������� ������ �� flash-������ ������ �� ���������
   ������. ������������ ������� ������ ���� �������������� ������ � �������
   LTR25_FlashErase(). ������������ ���������� ������� ������ � ������
   #LTR25_FLASH_USERDATA_ADDR �������� #LTR25_FLASH_USERDATA_SIZE ����.

   @param[in] hnd      ��������� ������.
   @param[in] addr     ����� ������, ������� � �������� ���������� ��������� ������
   @param[in] data     ������ �� size ���� � �������, ������� ����� ��������
   @param[in] size     ���������� ������ � ������, ������� ���������� ��������
   @return             ��� ������.
 ******************************************************************************/
LTR25API_DllExport(INT) LTR25_FlashWrite(TLTR25 *hnd, DWORD addr, const BYTE *data, DWORD size);

/***************************************************************************//**
   @brief �������� ������� flash-������ ������

   ������� ������� ������� �� flash-������ ������ �� ���������
   ������. �������� ���������� ��������� ����� ������� ������.
   �������� �������� ������ �������, �������� #LTR25_FLASH_ERASE_BLOCK_SIZE ����.
   ������������ ���������� ������� ������ � ������
   #LTR25_FLASH_USERDATA_ADDR �������� #LTR25_FLASH_USERDATA_SIZE ����.

   @param[in] hnd      ��������� ������.
   @param[in] addr     ����� ������, ������� � �������� ���������� ��������� ��������
   @param[in] size     ������ ��������� ������� � ������. ������ ���� ������
                       #LTR25_FLASH_ERASE_BLOCK_SIZE.
   @return             ��� ������.
 ******************************************************************************/
LTR25API_DllExport(INT) LTR25_FlashErase(TLTR25 *hnd, DWORD addr, DWORD size);

/** @} */



/***************************************************************************//**
    @addtogroup func_teds ������� ��� ������ ������� TEDS-��������
    @{
*******************************************************************************/

/***************************************************************************//**
   @brief ��������� ������ ������� ��������

   ������� ������������� ����� ������� �������� ��� ���� ������� ������.
   ������ ������� �������� ������ ��� ������� ����� 2 ��� ���� � ��� ��������
   ���� ������ 5 ��� ����.
   �������� ������� ������� �������� #LTR25_SENSORS_POWER_MODE_ICP (������������
    ��������� ��� ������� ����� 0 ��� 1).

   ��� ������� � ����������������� ������ TEDS-�������� ���������� ������
   ���������� ����� #LTR25_SENSORS_POWER_MODE_TEDS, � ������� �� ������� ��������
   ������� ��������������� ����������.

   @param[in] hnd      ��������� ������.
   @param[in] mode     ��������������� �����. �������� �� #e_LTR25_SENSORS_POWER_MODE.
   @return             ��� ������.
 ******************************************************************************/
LTR25API_DllExport(INT) LTR25_SetSensorsPowerMode(TLTR25 *hnd, DWORD mode);

/***************************************************************************//**
   @brief �������� ������� ����������������� ������ TEDS-�������

   ������� ��������� ������ �������������� ���� ����������������� ������
   TEDS-�������, ������������� � ���������� ������.

   �������������� ������ ���� ���������� ����� ������� �������� #LTR25_SENSORS_POWER_MODE_TEDS.

   @param[in] hnd      ��������� ������.
   @param[in] ch       ����� ������, � �������� ��������� ������ (�� 0 �� #LTR25_CHANNEL_CNT-1).
   @param[in] id       ��� �������� ���������� � ������� ����� �����������
                       ������������� ���� ���������� ������.
   @return             ��� ������.
 ******************************************************************************/
LTR25API_DllExport(INT) LTR25_TEDSMemoryDetect(TLTR25 *hnd, INT ch, DWORD *id);

/***************************************************************************//**
   @brief ������ �����  ����������������� ������ TEDS-�������

   ������� ��������� ������ ��������� ���������� ���� �� ��������� ������ ������
   TEDS-�������, ������������� � ���������� ������.
   �������������� ������ ���� ���������� ����� ������� �������� #LTR25_SENSORS_POWER_MODE_TEDS.

   @param[in] hnd      ��������� ������.
   @param[in] ch       ����� ������, � �������� ��������� ������ (�� 0 �� #LTR25_CHANNEL_CNT-1).
   @param[in] addr     ����� ������ TEDS-�������, ������� � �������� ����� ��������� ������
   @param[out] data    �����, � ������� ��� �������� ���������� ������� ����� ���������
                       ����������� ������. � ��� ������ ���� ���������� ����� ���
                       ���������� size ����.
   @param[in] size     ���������� ����, ������� ���������� ���������.
   @return             ��� ������.
 ******************************************************************************/
LTR25API_DllExport(INT) LTR25_TEDSMemoryRead(TLTR25 *hnd, INT ch, WORD addr, BYTE *data, DWORD size);

/***************************************************************************//**
   @brief ������ �����  ����������������� ������ TEDS-�������

   ������� ��������� ������ ��������� ���������� ���� �� ��������� ������ ������
   TEDS-�������, ������������� � ���������� ������.
   �������������� ������ ���� ���������� ����� ������� �������� #LTR25_SENSORS_POWER_MODE_TEDS.

   ������ ������ �������������� �� ������, ������������ �� ������� #LTR25_TEDS_MEMORY_BLOCK_SIZE.
   ����� ���������� ������������ ���� ������ ���� ������ #LTR25_TEDS_MEMORY_BLOCK_SIZE.

   @param[in] hnd      ��������� ������.
   @param[in] ch       ����� ������, � �������� ��������� ������ (�� 0 �� #LTR25_CHANNEL_CNT-1).
   @param[in] addr     ����� ������ TEDS-�������, ������� � �������� ����� �������� ������
   @param[in] data     ����� � ������� �� ������ (������ ��������� size ����).
   @param[in] size     ���������� ����, ������� ���������� ��������.
   @return             ��� ������.
 ******************************************************************************/
LTR25API_DllExport(INT) LTR25_TEDSMemoryWrite(TLTR25 *hnd, INT ch, WORD addr, const BYTE *data, DWORD size);

/** @} */


#ifdef __cplusplus
}
#endif

#endif
