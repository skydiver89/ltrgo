
#ifndef __LTR34API__
#define __LTR34API__

#ifdef _WIN32
    #ifdef LTR34API_EXPORTS
        #define LTR34API_DllExport(type)   __declspec(dllexport) type APIENTRY
    #else
        #define LTR34API_DllExport(type)   __declspec(dllimport) type APIENTRY
    #endif
#elif defined __GNUC__
    #define LTR34API_DllExport(type) __attribute__ ((visibility("default"))) type
#else
    #define LTR34API_DllExport(type) type
#endif


#include "ltrapi.h"

    // ���������
#define LTR34_ERROR_SEND_DATA              (-3001)
#define LTR34_ERROR_RECV_DATA              (-3002)
#define LTR34_ERROR_RESET_MODULE           (-3003)
#define LTR34_ERROR_NOT_LTR34              (-3004)
#define LTR34_ERROR_CRATE_BUF_OWF          (-3005)
#define LTR34_ERROR_PARITY                 (-3006)
#define LTR34_ERROR_OVERFLOW               (-3007)
#define LTR34_ERROR_INDEX                  (-3008)
    //
#define LTR34_ERROR                        (-3009)
#define LTR34_ERROR_EXCHANGE               (-3010)
#define LTR34_ERROR_FORMAT                 (-3011)
#define LTR34_ERROR_PARAMETERS             (-3012)
#define LTR34_ERROR_ANSWER                 (-3013)
#define LTR34_ERROR_WRONG_FLASH_CRC        (-3014)
#define LTR34_ERROR_CANT_WRITE_FLASH       (-3015)
#define LTR34_ERROR_CANT_READ_FLASH        (-3016)
#define LTR34_ERROR_CANT_WRITE_SERIAL_NUM  (-3017)
#define LTR34_ERROR_CANT_READ_SERIAL_NUM   (-3018)
#define LTR34_ERROR_CANT_WRITE_FPGA_VER    (-3019)
#define LTR34_ERROR_CANT_READ_FPGA_VER     (-3020)
#define LTR34_ERROR_CANT_WRITE_CALIBR_VER  (-3021)
#define LTR34_ERROR_CANT_READ_CALIBR_VER   (-3022)
#define LTR34_ERROR_CANT_STOP              (-3023)
#define LTR34_ERROR_SEND_CMD               (-3024)
#define LTR34_ERROR_CANT_WRITE_MODULE_NAME (-3025)
#define LTR34_ERROR_CANT_WRITE_MAX_CH_QNT  (-3026)
#define LTR34_ERROR_CHANNEL_NOT_OPENED     (-3027)
#define LTR34_ERROR_WRONG_LCH_CONF         (-3028)



#define LTR34_MAX_BUFFER_SIZE         2097151
#define LTR34_EEPROM_SIZE                2048
#define LTR34_USER_EEPROM_SIZE           1024
#define LTR34_DAC_NUMBER_MAX                8


/* ������� ����� ���������� � ������ */
#define LTR34_SERIAL_SIZE                                    24
#define LTR34_MODULE_NAME_SIZE                               16
#define LTR34_FPGA_VER_SIZE                                  8
#define LTR34_CALIBR_VER_SIZE                                8
/** ������������ �������� ��� �������� ������� */
#define LTR34_FREQ_DIV_MAX                                   60

/* ������ ������������� */
#define LTR34_ACKTYPE_ECHO           (1)  /** ������������� �� ������ ����� */
#define LTR34_ACKTYPE_STATUS         (0)  /** ������ ������� �� 1024 ����� */



#pragma pack(4)

    typedef struct {
        float FactoryCalibrOffset[2*LTR34_DAC_NUMBER_MAX];
        float FactoryCalibrScale[2*LTR34_DAC_NUMBER_MAX];
    } LTR34_DAC_CHANNEL_CALIBRATION;

    typedef struct {
        CHAR Name[LTR34_MODULE_NAME_SIZE];
        CHAR Serial[LTR34_SERIAL_SIZE];
        CHAR FPGA_Version[LTR34_FPGA_VER_SIZE];
        CHAR CalibrVersion[LTR34_CALIBR_VER_SIZE];
        BYTE MaxChannelQnt;
    } TINFO_LTR34,*PTINFO_LTR34;

    //**** ������������ ������
    typedef struct {
        INT size;                    /** ������ ��������� */
        TLTR Channel;                /** ��������� ������ ����� � ������� */
        DWORD LChTbl[LTR34_DAC_NUMBER_MAX];   /** ������� ���������� ������� */
        //**** ��������� ������
        BYTE FrequencyDivisor;       /** �������� ������� ������������� 0..60 (31.25..500 ���) */
        BYTE ChannelQnt;             /** ���������� �������: 1, 2, 4 ��� 8 */
        BOOLEAN UseClb;
        BOOLEAN AcknowledgeType;     /**< ��� �������������:
                                        LTR34_ACKTYPE_ECHO - �������� �������������
                                                ������� �����
                                        LTR34_ACKTYPE_STATUS - �������� ���������
                                                ������ �� ������ 1024 ����� */
        BOOLEAN ExternalStart;       /** ������� ����� (TRUE - ������� �����,
                                                       FALSE - ���������� */
        BOOLEAN RingMode;            /** ����� ������  (TRUE - ����� ������,
                                                       FALSE - ��������� �����) */
        BOOLEAN BufferFull;          /** ������ - ������� ������������ ������ */
        BOOLEAN BufferEmpty;         /** ������ - ������� ������� ������ ("���������")*/
        BOOLEAN DACRunning;          /** ������ - �������� �� ��������� */
        float FrequencyDAC;          /** ������ - ������� - �� ������� ��������
                                                  ��� � ������� ������������ */
        LTR34_DAC_CHANNEL_CALIBRATION DacCalibration; /** ������������� ������������ */
        TINFO_LTR34 ModuleInfo;   /** ���������� � ������ */
    } TLTR34,*PTLTR34;


#ifndef LTRAPI_DISABLE_COMPAT_DEFS
    typedef LTR34_DAC_CHANNEL_CALIBRATION DAC_CHANNEL_CALIBRATION;
#endif

#pragma pack()

#ifdef __cplusplus
extern "C" {
#endif

    // ������������� ����� ��������� TLTR34
    LTR34API_DllExport (INT) LTR34_Init (TLTR34 *module);

    // ������������ ����� � ������� LTR34.
    // ������ ���������� ����� STOP+RESET � ��������� ������������� ������.
    LTR34API_DllExport (INT) LTR34_Open (TLTR34 *module, DWORD net_addr, WORD net_port,
                                         const CHAR *crate_sn, WORD slot_num);
    // ������ ����� � �������.
    LTR34API_DllExport (INT) LTR34_Close (TLTR34 *module);

    // ����������� �������� ������ ����� � �������.
    LTR34API_DllExport (INT) LTR34_IsOpened (TLTR34 *module);

    /*
    ������� ��� ������ ������ �� ������.
    1) ��� ������ ��� � ������ ECHO - ��� ������, ������������
    �������, ������ ����������� � ������ ������� � ��� ����
    � ������� ������. ����� �������, � ������ ECHO ������
    ������ ������ ���������� ������ �� ������.
    2) ��� ������ ��� � ������ PERIOD - ��� ������, ������������
    �������, ������ ����������� � "������������".
    */
    LTR34API_DllExport (INT) LTR34_Recv (TLTR34 *module, DWORD *data, DWORD *tstamp,
                                         DWORD size, DWORD timeout);

    // ������������ ����������� ������
    LTR34API_DllExport (DWORD) LTR34_CreateLChannel(BYTE PhysChannel, BOOLEAN ScaleFlag);

    /*
    ������� ��� �������� ������ ������
    1) � ltr-������� ����������� ���������� ������� ������
    ����������� �� ������ LTR34 �� �������. ������� ���
    ������ � ��� � ��������� ������ (RingMode=0)
    ������ ����� �������� � ����� �����������, �� ��������
    � ������������ ������ � LTR34. ������, �������
    ������������ � ���������� ������� ��������, �.�.
    ��� ����������� ���������� ������ � ������
    ����� ������ �������� �� ������� ����� ������������� �� ���������
    ���������������� ������� ������������� ���, �.�. ��� ������ ��������
    ������������� � ���������� ������� ���������� ���������� ������
    ����� ������������� ���������� ������� �������� ��������.

    2) ���������� ������� ������ LTR34 �������� �� �������� ����������
    ������������ ������� � �������� �������������, ��� � ���������
    ������� ����� ��������� � ���������� ������ � ������ (��������,
    �� LTR34 ��� ���� ���������� ����������� ���������� ������, ��
    ��� ��� �� ��������� � ������������� �� ������ ��� �� ���������.
    � ���� ������ ������ ��������� ����� ������ �� �������).
    ��� ������ ��������� ���������� ������� ������� ������� ������
    ������� RESET (��� ���� ����� �������� ���������� �������� � ltr-�������)
    ��� ���������� ��������������� � ������ (������� LTR34_Close() � LTR34_Open())
    */
    LTR34API_DllExport (INT) LTR34_Send (TLTR34 *module, const DWORD *data,
                                         DWORD size, DWORD timeout);

    LTR34API_DllExport (INT) LTR34_ProcessData(TLTR34 *module, const double *src,
                                               DWORD *dest, DWORD size, BOOLEAN volt);

    // ������ �������� CONFIG
    LTR34API_DllExport (INT) LTR34_Config(TLTR34 *module);

    // ������ ���.
    LTR34API_DllExport (INT) LTR34_DACStart(TLTR34 *module);

    // ������� ���.
    LTR34API_DllExport (INT) LTR34_DACStop(TLTR34 *module);

    /***********************************************************************//**
       @brief ������ �� ������ ��������� ���

      ������� �������� ������� �� ������� ��������� ��� ��� �������� �������������
      � ���������� ���������. ����� ���� ������� ����� ����� �������
      LTR34_DACStopResponseWait() ��� ��������� ������.

      @param module ��������� ������ LTR34
      @return ��� ������
      ************************************************************************/
    LTR34API_DllExport (INT) LTR34_DACStopRequst(TLTR34 *module);
    /***********************************************************************//**
       @brief �������� ������ �� ������� ���

      ������� ������� ��������� ������ � ��������� �������� ���������. ������
      ���������� ������ ����� LTR34_DACStopRequst().

      ������ �������� ����� ������ ����� ����, ��� ������ �� ��� ��� ����������
      �� ����� ����� � ��������� ������, ��� ����� ������ ������������ �������
      �����, ������� � ������� ���� ������� ����������� ������ ������� �� ��������.

      ���� ������� ���������� ��� ������ LTR_ERROR_NO_CMD_RESPONSE, �� �������������
      �������� �� ���� ��������. ����� ����� ����� ���� ������ ������� ������
      ������� ��� ����������� ��������, ���� �������� ������.

      @param module ��������� ������ LTR34
      @return ��� ������
      ************************************************************************/
    LTR34API_DllExport (INT) LTR34_DACStopResponseWait(TLTR34 *module, DWORD tout);

    LTR34API_DllExport (INT) LTR34_Reset(TLTR34 *module);


    LTR34API_DllExport (INT) LTR34_GetCalibrCoeffs(TLTR34 *module);
    LTR34API_DllExport (INT) LTR34_WriteCalibrCoeffs(TLTR34 *module);

    LTR34API_DllExport (INT) LTR34_ReadFlash(TLTR34 *module, BYTE *data,
                                             WORD size, WORD Address);

    // ������� ���������������� ���������
    LTR34API_DllExport (LPCSTR) LTR34_GetErrorString(INT error);

    // �������� ����������� ����
    LTR34API_DllExport (INT) LTR34_TestEEPROM(TLTR34 *module);


    /** @brief ������ �������� �������� ������� ���

       ������� �� ��������� �������� ������� ��������� ��� (�� �����) ���������
       �������� ��������, ����� �������������� ������� ���� �������� ������
       � ��������.

       @param[in] dacFreq         ��������� ������� ��������� ��� � ��.
       @param[in] ChannelQnt      ���������� ����������� ������� � ������
       @param[out] devisor        � ������ ���������� ����������� ��������� ��������
                                  ��������, ��������������� ��������� �������.
                                  ����� ���� NULL, ���� �� ���������.
       @param[out] resultAdcFreq  � ������ ���������� ����������� ��������� ��������
                                  �������� ������� ��������� ��� � ��.
                                  ����� ���� NULL, ���� �� ���������.
       @return                    ��� ������ */
    LTR34API_DllExport(INT) LTR34_FindDacFreqDivisor(double dacFreq, BYTE ChannelQnt, BYTE *devisor, double *resultDacFreq);

#ifdef __cplusplus
}
#endif

#endif

