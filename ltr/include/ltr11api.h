#ifndef LTR11API_H_
#define LTR11API_H_


#include "ltrapi.h"

#ifdef __cplusplus
extern "C" {                                 // only need to export C interface if
                                             // used by C++ source code
#endif

#ifdef _WIN32
    #ifdef LTR11API_EXPORTS
      #define LTR11API_DllExport(type) __declspec(dllexport) type APIENTRY
    #else
      #define LTR11API_DllExport(type) __declspec(dllimport) type APIENTRY
    #endif
#elif defined __GNUC__
    #define LTR11API_DllExport(type) __attribute__ ((visibility("default"))) type
#else
    #define LTR11API_DllExport(type)  type
#endif

/*================================================================================================*/
#define LTR11_CLOCK                     (15000) /* �������� ������� ������ � ��� */
#define LTR11_MAX_CHANNEL               (32)    /* ������������ ����� ���������� ������� */
#define LTR11_MAX_LCHANNEL              (128)   /* ������������ ����� ���������� ������� */
#define LTR11_ADC_RANGEQNT              (4)     /* ���������� ������� ���������� ��� */


#define LTR11_MAX_ADC_DIVIDER           65535
#define LTR11_MIN_ADC_DIVIDER           2

#define LTR11_MAX_ADC_FREQ              (400000) /* ������������ ������� ��� � �� */

/* ���� ������, ������������ ��������� ���������� */
#define LTR11_ERR_INVALID_DESCR         (-1000) /* ��������� �� ��������� ������ ����� NULL */
#define LTR11_ERR_INVALID_ADCMODE       (-1001) /* ������������ ����� ������� ��� */
#define LTR11_ERR_INVALID_ADCLCHQNT     (-1002) /* ������������ ���������� ���������� ������� */
#define LTR11_ERR_INVALID_ADCRATE       (-1003) /* ������������ �������� ������� ������������� ���
                                                * ������
                                                */
#define LTR11_ERR_INVALID_ADCSTROBE     (-1004) /* ������������ �������� �������� ������� ��� ��� */
#define LTR11_ERR_GETFRAME              (-1005) /* ������ ��������� ����� ������ � ��� */
#define LTR11_ERR_GETCFG                (-1006) /* ������ ������ ������������ */
#define LTR11_ERR_CFGDATA               (-1007) /* ������ ��� ��������� ������������ ������ */
#define LTR11_ERR_CFGSIGNATURE          (-1008) /* �������� �������� ������� ����� ����������������
                                                 * ������ ������
                                                 */
#define LTR11_ERR_CFGCRC                (-1009) /* �������� ����������� ����� ����������������
                                                 * ������
                                                 */
#define LTR11_ERR_INVALID_ARRPOINTER    (-1010) /* ��������� �� ������ ����� NULL */
#define LTR11_ERR_ADCDATA_CHNUM         (-1011) /* �������� ����� ������ � ������� ������ �� ��� */
#define LTR11_ERR_INVALID_CRATESN       (-1012) /* ��������� �� ������ � �������� ������� ������
                                                * ����� NULL
                                                */
#define LTR11_ERR_INVALID_SLOTNUM       (-1013) /* ������������ ����� ����� � ������ */
#define LTR11_ERR_NOACK                 (-1014) /* ��� ������������� �� ������ */
#define LTR11_ERR_MODULEID              (-1015) /* ������� �������� ������, ��������� �� LTR11 */
#define LTR11_ERR_INVALIDACK            (-1016) /* �������� ������������� �� ������ */
#define LTR11_ERR_ADCDATA_SLOTNUM       (-1017) /* �������� ����� ����� � ������ �� ��� */
#define LTR11_ERR_ADCDATA_CNT           (-1018) /* �������� ������� ������� � ������ �� ��� */
#define LTR11_ERR_INVALID_STARTADCMODE  (-1019) /* �������� ����� ������ ����� ������ */

/* ������ ������� ��� */
#define LTR11_ADCMODE_ACQ               (0x00)  /* ���� ������ */
#define LTR11_ADCMODE_TEST_U1P          (0x04)  /* ������ ��������� ���������� +U1 */
#define LTR11_ADCMODE_TEST_U1N          (0x05)  /* ������ ��������� ���������� -U1 */
#define LTR11_ADCMODE_TEST_U2N          (0x06)  /* ������ ��������� ���������� -U2 */
#define LTR11_ADCMODE_TEST_U2P          (0x07)  /* ������ ��������� ���������� +U2 */

/* ����� ������ ����� ������ ������� */
#define LTR11_STARTADCMODE_INT       (0)     /* ���������� ����� (�� ������� �����) */
#define LTR11_STARTADCMODE_EXTRISE   (1)     /* �� ������ �������� �������; */
#define LTR11_STARTADCMODE_EXTFALL   (2)     /* �� ����� �������� �������. */

/* �������� ������������ ��� */
#define LTR11_INPMODE_EXTRISE        (0)     /* ������ �������������� �� ������ �������� ������� */
#define LTR11_INPMODE_EXTFALL        (1)     /* ������ �������������� �� ����� �������� ������� */
#define LTR11_INPMODE_INT            (2)     /* ���������� ������ ��� */

/* ������� �������� ������� */
#define LTR11_CHRANGE_10000MV         (0)     /* +-10 � (10000 ��) */
#define LTR11_CHRANGE_2500MV          (1)     /* +-2.5 � (2500 ��) */
#define LTR11_CHRANGE_625MV           (2)     /* +-0.625 � (625 ��) */
#define LTR11_CHRANGE_156MV           (3)     /* +-0.156 � (156 ��) */

/* ������ ������ ������� */
#define LTR11_CHMODE_DIFF            (0) /* ���. �����., 16 ������� */
#define LTR11_CHMODE_COMM            (1) /* ����� �����, 32 ������� */
#define LTR11_CHMODE_ZERO            (2) /* ��������� ���� */


#ifndef LTRAPI_DISABLE_COMPAT_DEFS
    /* �����������, ����������� ��� ������������� */
    #define LTR11_CHMODE_16CH            (LTR11_CHMODE_DIFF)     /* 16-��������� */
    #define LTR11_CHMODE_32CH            (LTR11_CHMODE_COMM)     /* 32-��������� */

    #define LTR11_CHGANE_10000MV         (LTR11_CHRANGE_10000MV)
    #define LTR11_CHGANE_2500MV          (LTR11_CHRANGE_2500MV)     /* +-2.5 � (2500 ��) */
    #define LTR11_CHGANE_625MV           (LTR11_CHRANGE_625MV)     /* +-0.625 � (625 ��) */
    #define LTR11_CHGANE_156MV           (LTR11_CHRANGE_156MV)     /* +-0.156 � (156 ��) */
#endif

/*================================================================================================*/


/*================================================================================================*/
#pragma pack (4)
typedef struct {
    CHAR Name[16];                      /* �������� ������ (������) */
    CHAR Serial[24];                    /* �������� ����� ������ (������) */

    WORD Ver;                           /* ������ �� ������ (������� ���� - ��������,
                                          * ������� - ��������
                                          */
    CHAR Date[14];                      /* ���� �������� �� (������) */
    struct {
        double Offset;                  /* �������� ���� */
        double Gain;                    /* ���������� ����������� */
    } CbrCoef[LTR11_ADC_RANGEQNT];      /* ������������� ������������ ��� ������� ��������� */
} TINFO_LTR11, *PTINFO_LTR11;           /* ���������� � ������ */

typedef struct {
    INT size;                               /* ������ ��������� � ������ */
    TLTR Channel;                           /* ��������� ������ ����� � ������� */

    INT StartADCMode;                       /* ����� ������ ����� ������:
                                             * LTR11_STARTADCMODE_INT     - ���������� ����� (��
                                             *                              ������� �����);
                                             * LTR11_STARTADCMODE_EXTRISE - �� ������ ��������
                                             *                              �������;
                                             * LTR11_STARTADCMODE_EXTFALL - �� ����� ��������
                                             *                              �������.
                                             */
    INT InpMode;                            /* ����� ����� ������ � ���
                                             *  LTR11_INPMODE_INT     - ���������� ������ ���
                                             *                          (������� �������� AdcRate)
                                             *  LTR11_INPMODE_EXTRISE - �� ������ �������� �������
                                             *  LTR11_INPMODE_EXTFALL - �� ����� �������� �������
                                             */
    INT LChQnt;                             /* ����� �������� ���������� ������� (������ �����) */
    BYTE LChTbl[LTR11_MAX_LCHANNEL];        /* ����������� ������� � ��������� ����������� ��������
                                             * ��������� ������ ����� �������: MsbGGMMCCCCLsb
                                             *   GG   - ������� ��������:
                                             *          0 - +-10 �;
                                             *          1 - +-2.5 �;
                                             *          2 - +-0.625 �;
                                             *          3 - +-0.156�;
                                             *   MM   - �����:
                                             *          0 - 16-���������, ������ 1-16;
                                             *          1 - ��������� ������������ ����������
                                             *              �������� ����;
                                             *          2 - 32-���������, ������ 1-16;
                                             *          3 - 32-���������, ������ 17-32;
                                             *   CCCC - ����� ����������� ������:
                                             *          0 - ����� 1 (17);
                                             *          . . .
                                             *          15 - ����� 16 (32).
                                             */
    INT ADCMode;                            /* ����� ����� ������ ��� ��� ��������� ������ */
    struct {
        INT divider;                        /* �������� �������� ������� ������, ��������:
                                             * 2..65535
                                             */
        INT prescaler;                      /* ����������� �������� ������� ������:
                                             * 1, 8, 64, 256, 1024
                                             */
    } ADCRate;                             /* ��������� ��� ������� ������� ������������� ���
                                             * ������� �������������� �� �������:
                                             * F = LTR11_CLOCK/(prescaler*(divider+1)
                                             * ��������!!! ������� 400 ��� �������� ������ �������:
                                             * ��� �� ��������� ����������� � �������� ������ �����
                                             * ��������� ��������:
                                             *   prescaler = 1
                                             *   divider   = 36
                                             */
    double ChRate;                          /* ������� ������ ������ � ��� (������ �����) ���
                                             * ���������� ������� ���
                                             */
    TINFO_LTR11 ModuleInfo;                 /* ���������� � ������ LTR11 */
} TLTR11, *PTLTR11;                          /* ��������� ��������� ������ LTR11 � ��������� ��
                                             * ����
                                             */
#pragma pack ()
/*================================================================================================*/

/*================================================================================================*/
LTR11API_DllExport(INT) LTR11_Init(PTLTR11 hnd);
LTR11API_DllExport(INT) LTR11_Open(PTLTR11 hnd, DWORD net_addr, WORD net_port, const CHAR *crate_sn,
    INT slot_num);
LTR11API_DllExport(INT) LTR11_Close(PTLTR11 hnd);
LTR11API_DllExport(INT) LTR11_IsOpened(PTLTR11 hnd);

LTR11API_DllExport(INT) LTR11_GetConfig(PTLTR11 hnd);
LTR11API_DllExport(INT) LTR11_SetADC(PTLTR11 hnd);
LTR11API_DllExport(INT) LTR11_Start(PTLTR11 hnd);
LTR11API_DllExport(INT) LTR11_Stop(PTLTR11 hnd);
LTR11API_DllExport(INT) LTR11_Recv(TLTR11 *hnd, DWORD *data, DWORD *tmark,
                                   DWORD size, DWORD timeout);
LTR11API_DllExport(INT) LTR11_ProcessData(PTLTR11 hnd, const DWORD *src, double *dest, INT *size,
                                          BOOL calibr, BOOL volt);

LTR11API_DllExport(INT) LTR11_GetFrame(PTLTR11 hnd, DWORD *buf);

/** @brief ������ �������� �������� � ����������� ���

   ������� �� ��������� �������� ������� ��� (��������� �� ��� ������) ���������
   �������� �������� � ���������, ����� �������������� ������� ���� �������� ������.
   ������� ����� �����, ��� � ������� �� ChRate ����� �������� ����� ������� ���
   � �������� � ��, � �� ���, �.�. ChRate = resultAdcFreq/(1000*LChQnt)

   @param[in] adcFreq         ��������� ������� � ��.
   @param[out] prescaler      �������� �����������, ��������������� ������ �������
   @param[out] divider        �������� ��������, ��������������� ������ �������
   @param[out] resultAdcFreq  ���������� �������� �������� ������� ��� (� ��)
   @return                    ��� ������ */
LTR11API_DllExport(INT) LTR11_FindAdcFreqParams(double adcFreq, INT *prescaler, INT *divider, double *resultAdcFreq);

/****************************************************************************//**
   @brief ����� ������ ������� �����.

   ������� ������� � �������� ������� ����� ������ �� ������ ������ �������
   ����� ������� ������ �����. ����� �������������� ��� ������������ ��
   ������ ����� ������ � ������ ������������� ���� ��� �������� �����.

   ���� � ���������� ������� ������ ����� �� �������, �� ������� ������ ������
   LTR_ERROR_FIRSTFRAME_NOTFOUND.

   @param[in] hnd      ��������� ������.
   @param[in] data     ��������� �� ������, ���������� �����, �������� �� ������
                       � ������� LTR11_Recv(), � ������� ������ ������ �����.
   @param[in] size     ���������� ���� � ������� data
   @param[out] index   � ���� ���������� ������������ ������ ��������,
                       ���������������� ������ ������� �����, ���� �������
                       ����������� �������.
   @return             ��� ������.
  *****************************************************************************/
LTR11API_DllExport(INT) LTR11_SearchFirstFrame(TLTR11 *hnd, const DWORD *data, DWORD size,
                                                DWORD *index);

LTR11API_DllExport(LPCSTR) LTR11_GetErrorString(INT err);
LTR11API_DllExport(BYTE) LTR11_CreateLChannel(BYTE phy_ch, BYTE mode, BYTE range);
/*================================================================================================*/

#ifdef __cplusplus
}                                          // only need to export C interface if
                                           // used by C++ source code
#endif

#endif                      /* #ifndef LTR11API_H_ */
