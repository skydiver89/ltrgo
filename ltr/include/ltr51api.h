#include "ltrapi.h"


#ifdef _WIN32
    #ifdef LTR51API_EXPORTS
        #define LTR51API_DllExport(type)   __declspec(dllexport) type APIENTRY
    #else
        #define LTR51API_DllExport(type)   __declspec(dllimport) type APIENTRY
    #endif
#elif defined __GNUC__
    #define LTR51API_DllExport(type) __attribute__ ((visibility("default"))) type
#else
    #define LTR51API_DllExport(type) type
#endif


#define LTR51_K_RANGE_1_2 (-1.6737)
#define LTR51_K_RANGE_10  (-0.2010)
#define LTR51_UREF_VALUE  (2.048)

/** ����������� ����� �������� �����. � ����� ������� ��������� */
#define LTR51_BASE_VAL_MIN  70
/** ������������ ������� ��� ������������� ��� ������ */
#define LTR51_FS_MAX        500000



/** ������������ ���������� ���������� � ������ */
#define LTR51_MEZZANINE_CNT             8
/** ���������� ������� � ����� ��������� */
#define LTR51_MEZZANINE_CHANNEL_CNT     2

/** ������������ ���������� ������� � ������ */
#define LTR51_CHANNEL_CNT   (LTR51_MEZZANINE_CNT*LTR51_MEZZANINE_CHANNEL_CNT)


/** �������� ������� */
typedef enum {
    LTR51_THRESHOLD_RANGE_10V  = 0,
    LTR51_THRESHOLD_RANGE_1_2V = 1
} e_LTR51_THRESHOLD_RANGE;

/** ����������� ��������, ������������ ��� ����� */
typedef enum {
    /** ������������ �� ������ ������� */
    LTR51_EDGE_MODE_RISE     = 0,
    /** ������������ �� ����� ������� */
    LTR51_EDGE_MODE_FALL     = 1
} e_LTR51_EDGE_MODE;

/** ������������ �������� ������ (������������� ������ ��� ���������� H-51FA) */
typedef enum {
    /**< �������������� ����� (���������� ������ H-51FL) */
    LTR51_FREQ_RANGE_LOW     = 0,
    /**< ��������������� ����� (���������� ������ H-51FH) */
    LTR51_FREQ_RANGE_HIGH    = 1
} e_LTR51_FREQ_RANGE;

/** ����������� ������ LTR51 */
typedef enum {
    LTR51_MOD_OLD = 0, /**< ������ ����������� LTR51 */
    LTR51_MOD_M   = 1  /**< ����������� LTR51M */
} e_LTR51_MODIFICATION;


// ���� ������
#define LTR51_NO_ERR                                  (0)
#define LTR51_ERR_WRONG_MODULE_DESCR                  (-5001)
#define LTR51_ERR_CANT_OPEN                           (-5002)
#define LTR51_ERR_CANT_LOAD_ALTERA                    (-5003)
#define LTR51_ERR_INVALID_CRATE_SN                    (-5004)
#define LTR51_ERR_INVALID_SLOT_NUM                    (-5005)
#define LTR51_ERR_CANT_SEND_COMMAND                   (-5006)
#define LTR51_ERR_CANT_RESET_MODULE                   (-5007)
#define LTR51_ERR_MODULE_NO_RESPONCE                  (-5008)
#define LTR51_ERR_CANT_OPEN_MODULE                    (-5009)
#define LTR51_ERR_PARITY_TO_MODULE                    (-5010)
#define LTR51_ERR_PARITY_FROM_MODULE                  (-5011)
#define LTR51_ERR_ALTERA_TEST_FAILED                  (-5012)
#define LTR51_ERR_CANT_START_DATA_AQC                 (-5013)
#define LTR51_ERR_CANT_STOP_DATA_AQC                  (-5014)
#define LTR51_ERR_CANT_SET_FS                         (-5015) 
#define LTR51_ERR_CANT_SET_BASE                       (-5016)
#define LTR51_ERR_CANT_SET_EDGE_MODE                  (-5017)
#define LTR51_ERR_CANT_SET_THRESHOLD                  (-5018)
#define LTR51_WRONG_DATA                              (-5019)
#define LTR51_ERR_WRONG_HIGH_THRESOLD_SETTINGS        (-5020)
#define LTR51_ERR_WRONG_LOW_THRESOLD_SETTINGS         (-5021)
#define LTR51_ERR_WRONG_FPGA_FILE                     (-5022)
#define LTR51_ERR_CANT_READ_ID_REC                    (-5023)
#define LTR51_ERR_WRONG_ID_REC                        (-5024)
#define LTR51_ERR_WRONG_FS_SETTINGS                   (-5025)
#define LTR51_ERR_WRONG_BASE_SETTINGS                 (-5026)
#define LTR51_ERR_CANT_WRITE_EEPROM                   (-5027)
#define LTR51_ERR_CANT_READ_EEPROM                    (-5028)
#define LTR51_ERR_WRONG_EEPROM_ADDR                   (-5029)
#define LTR51_ERR_WRONG_THRESHOLD_VALUES              (-5030)
#define LTR51_ERR_ERROR_OVERFLOW                      (-5031)
#define LTR51_ERR_MODULE_WRONG_ACQ_TIME_SETTINGS      (-5032)
#define LTR51_ERR_NOT_ENOUGH_POINTS                   (-5033)
#define LTR51_ERR_WRONG_SRC_SIZE                      (-5034)


#ifdef __cplusplus
extern "C" {
#endif




#pragma pack(4) 

typedef struct {
    CHAR Name[16];
    CHAR Serial[24];
    BYTE Reserved[128-40];
} TLTR51_MEZZANINE_INFO;

typedef struct {
    CHAR Name[15];
    BYTE Modification; /**< ����������� ������ - �������� �� #e_LTR51_MODIFICATION */
    CHAR Serial[24];
    CHAR FirmwareVersion[8];// ������ �������� AVR
    CHAR FirmwareDate[16];  // ���� �������� ������ ������ �������� AVR  
    CHAR FPGA_Version[8]; // ������ �������� ����
} TINFO_LTR51,*PTINFO_LTR51; 

typedef struct {
   INT size;               // ������ ���������
   
   TLTR Channel;  
   WORD ChannelsEna;       // ����� ��������� ������� (����������, ����� ��������� �����.)
   
   INT  SetUserPars;       // ���������, �������� �� Fs � Base �������������
   
   INT LChQnt;             // ���������� ���������� �������    
   DWORD LChTbl[16];       // ������� ���������� �������
   
   double Fs;                // ������� ������� �������
   WORD Base;                // �������� ������� ���������
   double F_Base;             // ������� ��������� F_Base=Fs/Base
   
   
   int AcqTime;            // ����� ����� � �������������       
   int TbaseQnt;           // ���������� �������� ���������, ����������� ��� ����������� ���������� ��������� ���������
   
   TINFO_LTR51 ModuleInfo;
} TLTR51, *PTLTR51; // ��������� �������� ������

#pragma pack()


LTR51API_DllExport (INT)    LTR51_Init(PTLTR51 hnd);
LTR51API_DllExport (INT)    LTR51_Open(PTLTR51 hnd, DWORD net_addr, WORD net_port,
                                    const CHAR *crate_sn, INT slot_num, const char *ttf_name);
LTR51API_DllExport(INT)     LTR51_GetMezzaninesInfo(PTLTR51 hnd, TLTR51_MEZZANINE_INFO *descr);
LTR51API_DllExport (INT)    LTR51_IsOpened(PTLTR51 hnd);
LTR51API_DllExport (INT)    LTR51_Close(PTLTR51 hnd);
LTR51API_DllExport (LPCSTR) LTR51_GetErrorString(INT Error_Code); 
LTR51API_DllExport (INT)    LTR51_WriteEEPROM(PTLTR51 hnd, INT Address, BYTE val);
LTR51API_DllExport (INT)    LTR51_ReadEEPROM(PTLTR51 hnd, INT Address, BYTE *val);
LTR51API_DllExport (DWORD)  LTR51_CreateLChannel(INT PhysChannel, double *HighThreshold,
                                                 double *LowThreshold, INT ThresholdRange,
                                                 INT EdgeMode);

LTR51API_DllExport (DWORD)  LTR51_CreateLChannelEx(INT PhysChannel, double *HighThreshold,
                                                  double *LowThreshold, INT ThresholdRange,
                                                  INT EdgeMode, INT FreqRange);

LTR51API_DllExport (INT)    LTR51_Config(PTLTR51 hnd);
LTR51API_DllExport (INT)    LTR51_Start(PTLTR51 hnd);
LTR51API_DllExport (INT)    LTR51_Stop(PTLTR51 hnd);
LTR51API_DllExport (INT)    LTR51_Recv(PTLTR51 hnd, DWORD *data, DWORD *tmark, DWORD size, DWORD timeout);
LTR51API_DllExport (INT)    LTR51_ProcessData(PTLTR51 hnd, const DWORD *src, DWORD *dest, double *Frequency, DWORD *size);
LTR51API_DllExport (INT)    LTR51_GetThresholdVals(PTLTR51 hnd, INT LChNumber, double *HighThreshold, double *LowThreshold, INT ThresholdRange);
LTR51API_DllExport (DWORD)  LTR51_CalcTimeOut(PTLTR51 hnd, INT n);


#ifdef __cplusplus 
}
#endif  

















