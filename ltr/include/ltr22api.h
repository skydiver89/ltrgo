#include "ltrapi.h"

#ifndef LTR22API_H_
#define LTR22API_H_

#ifdef _WIN32
    #ifdef LTR22API_EXPORTS
        #define LTR22API_DllExport(type)    __declspec(dllexport) type APIENTRY
        #define LTR22API_Export             __declspec(dllexport)
    #else
        #define LTR22API_DllExport(type)    __declspec(dllimport) type APIENTRY
        #define LTR22API_Export             __declspec(dllimport)
    #endif
#elif defined __GNUC__
    #define LTR22API_DllExport(type) __attribute__ ((visibility("default"))) type
    #define LTR22API_Export __attribute__ ((visibility("default")))
#else
    #define LTR22API_DllExport(type)    type
    #define LTR22API_Export
#endif

//#define LTR22_MODULE_CODE    0x1616 //
#define LTR22_ADC_NUMBERS    4
#define LTR22_ADC_CHANNELS   LTR22_ADC_NUMBERS
#define LTR22_RANGE_NUMBER   6
#define LTR22_RANGE_OVERFLOW 7

#define LTR22_MAX_DISC_FREQ_NUMBER 25    // ���������� ������������ ������

// ���� ���������� ���
#define LTR22_ADC_RANGE_1       0
#define LTR22_ADC_RANGE_0_3     1
#define LTR22_ADC_RANGE_0_1     2
#define LTR22_ADC_RANGE_0_03    3
#define LTR22_ADC_RANGE_10      4
#define LTR22_ADC_RANGE_3       5


// ��������� �������� ������
#define LTR22_ERROR_SEND_DATA                              (-6000)
#define LTR22_ERROR_RECV_DATA                              (-6001)
#define LTR22_ERROR_NOT_LTR22                              (-6002)
#define LTR22_ERROR_OVERFLOW                               (-6003)
#define LTR22_ERROR_ADC_RUNNING                            (-6004)
#define LTR22_ERROR_MODULE_INTERFACE                       (-6005)
#define LTR22_ERROR_INVALID_FREQ_DIV                       (-6006)
#define LTR22_ERROR_INVALID_TEST_HARD_INTERFACE            (-6007)
#define LTR22_ERROR_INVALID_DATA_RANGE_FOR_THIS_CHANNEL    (-6008)
#define LTR22_ERROR_INVALID_DATA_COUNTER                   (-6009)
#define LTR22_ERROR_PRERARE_TO_WRITE                       (-6010)
#define LTR22_ERROR_WRITE_AVR_MEMORY                       (-6011)
#define LTR22_ERROR_READ_AVR_MEMORY                        (-6012)
#define LTR22_ERROR_PARAMETERS                             (-6013)
#define LTR22_ERROR_CLEAR_BUFFER_TOUT                      (-6014)
#define LTR22_ERROR_SYNC_FHAZE_NOT_STARTED                 (-6015)
#define LTR22_ERROR_INVALID_CH_NUMBER                      (-6016)






#pragma pack(4)

typedef struct {
    TLTR_DESCRIPTION_MODULE Description;    // �������� ������
    TLTR_DESCRIPTION_CPU CPU;                // �������� AVR
} TINFO_LTR22, *PTINFO_LTR22;


typedef struct  {
    float FactoryCalibOffset[LTR22_RANGE_NUMBER];
    float FactoryCalibScale[LTR22_RANGE_NUMBER];

    float UserCalibOffset[LTR22_RANGE_NUMBER];
    float UserCalibScale[LTR22_RANGE_NUMBER];
} ADC_CHANNEL_CALIBRATION;


/** ������������ ������ */
typedef struct {
  //**** ��������� ����������       //
  INT size;                            // ������ ��������� TLTR22 1036 ����
  TLTR Channel;                        // ��������� ��������� ��� ������ � ������� ����� ������

  // ��������� ������
  BYTE Fdiv_rg;                        // �������� ������� ������ 1..15
  BOOLEAN Adc384;                      // �������������� �������� ������� ������� true =3 false =2
  BOOLEAN AC_DC_State;                 // ��������� true =AC+DC false=AC
  BOOLEAN MeasureADCZero;              // ��������� ������������ ���� (true - �������� false - ���������)
  BOOLEAN DataReadingProcessed;        // ��������� ���������� ��� true-��� ����������� false - ���
  BYTE    ADCChannelRange[LTR22_ADC_NUMBERS];// ������ ��������� ��� �� ������� 0 - 1� 1 - 0.3� 2 - 0.1� 3 - 0.03� 4 - 10� 5 - 3�

  BOOLEAN ChannelEnabled[LTR22_ADC_NUMBERS];        // ��������� �������, ������� - true �������� - false

  INT FreqDiscretizationIndex;            // ������� �������������, ������������ ������ 0..24 - � ����������� �� �������
                                        // �� ������� LTR22_DISK_FREQ_ARRAY
   
  BYTE SyncType;        // ��� ������������� 0 - ���������� ����� �� ������� Go
                        //1 - ��������� ������
                        //2 - ������� �����
                        //3 - �������������
  BOOLEAN SyncMaster;   // true - ������ ������� ������, false - ������ ��������� ������������

  TINFO_LTR22 ModuleInfo;
  ADC_CHANNEL_CALIBRATION ADCCalibration[LTR22_ADC_NUMBERS][LTR22_MAX_DISC_FREQ_NUMBER];

} TLTR22,*PTLTR22;  

#pragma pack()


/*
-----------------------------------------------------------------------------------------
 �������������� ������� 
*/
#ifdef __cplusplus
extern "C" {  // only need to export C interface if
              // used by C++ source code
#endif

LTR22API_Export extern const INT LTR22_DISK_FREQ_ARRAY[LTR22_MAX_DISC_FREQ_NUMBER];


LTR22API_DllExport(INT) LTR22_Init(TLTR22 *module);
LTR22API_DllExport(INT) LTR22_Close(TLTR22 *module);
LTR22API_DllExport(INT) LTR22_Open(TLTR22 *module, DWORD saddr, WORD sport, const CHAR *csn, WORD cc);
LTR22API_DllExport(INT) LTR22_IsOpened(TLTR22 *module);
LTR22API_DllExport(INT) LTR22_GetConfig(TLTR22 *module);
LTR22API_DllExport(INT) LTR22_SetConfig(TLTR22 *module);
LTR22API_DllExport(INT) LTR22_ClearBuffer(TLTR22 *module, BOOLEAN wait_response);
LTR22API_DllExport(INT) LTR22_StartADC(TLTR22 *module, BOOLEAN WaitSync);
LTR22API_DllExport(INT) LTR22_StopADC(TLTR22 *module);
LTR22API_DllExport(INT) LTR22_SetSyncPriority(TLTR22 *module, BOOLEAN SyncMaster);
LTR22API_DllExport(INT) LTR22_SyncPhaze(TLTR22 *module, DWORD timeout);
LTR22API_DllExport(INT) LTR22_SyncPhazeStart(TLTR22 *module);
LTR22API_DllExport(INT) LTR22_SyncPhazeWaitDone(TLTR22 *module, DWORD timeout);
LTR22API_DllExport(INT) LTR22_SetFreq(TLTR22 *module, BOOLEAN adc384, BYTE Freq_dv);
LTR22API_DllExport(INT) LTR22_SwitchMeasureADCZero(TLTR22 *module, BOOLEAN SetMeasure);
LTR22API_DllExport(INT) LTR22_SwitchACDCState(TLTR22 *module, BOOLEAN ACDCState);
LTR22API_DllExport(INT) LTR22_SetADCRange(TLTR22 *module, BYTE ADCChannel, BYTE ADCChannelRange);
LTR22API_DllExport(INT) LTR22_SetADCChannel(TLTR22 *module, BYTE ADCChannel, BOOLEAN EnableADC);
LTR22API_DllExport(INT) LTR22_GetCalibrCoeffs(TLTR22 *module);
LTR22API_DllExport(INT) LTR22_Recv(TLTR22 *module, DWORD *data, DWORD *tstamp, DWORD size, DWORD timeout);
LTR22API_DllExport(INT) LTR22_GetModuleDescription(TLTR22 *module);
LTR22API_DllExport(INT) LTR22_ProcessData(TLTR22 *module, const DWORD *src_data, double *dst_data,
                                         DWORD size, BOOLEAN calibrMainPset, BOOLEAN calibrExtraVolts, BYTE * OverflowFlags);
LTR22API_DllExport(INT) LTR22_ReadAVREEPROM(TLTR22 *module, BYTE *Data, DWORD BeginAddress, DWORD size);
LTR22API_DllExport(INT) LTR22_WriteAVREEPROM(TLTR22 *module, const BYTE *Data, DWORD BeginAddress, DWORD size);
LTR22API_DllExport(LPCSTR) LTR22_GetErrorString(INT ErrorCode);

/*
�������� �������
*/
LTR22API_DllExport(INT) LTR22_TestHardwareInterface(TLTR22 *module);
LTR22API_DllExport(INT) LTR22_GetADCData(TLTR22 *module, double * Data, DWORD Size, DWORD time, 
                                        BOOLEAN calibrMainPset, BOOLEAN calibrExtraVolts);
LTR22API_DllExport(INT) LTR22_ReopenModule(TLTR22 *module);
LTR22API_DllExport(INT) LTR22_ReadAVRFirmware(TLTR22 *module, BYTE *Data, DWORD size, DWORD BeginPage, DWORD PageNumbers);
LTR22API_DllExport(INT) LTR22_WriteAVRFirmvare(TLTR22 *module, BYTE *Data, DWORD size,
                                               BOOLEAN WriteCalibrAndDescription, BOOLEAN ProgrammAVR);


#ifndef LTRAPI_DISABLE_COMPAT_DEFS
    #define LTR22_ReadAVRBroaching  LTR22_ReadAVRFirmware
    #define LTR22_WriteBroaching    LTR22_WriteAVRFirmvare
    #define LTR22_GetCalibrovka     LTR22_GetCalibrCoeffs
#endif

#ifdef __cplusplus
}
#endif


#endif
