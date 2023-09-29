#ifndef LTR24API_H_
#define LTR24API_H_


#include "ltrapi.h"


#ifdef __cplusplus
extern "C" {
#endif


/*===============================================================================================*/
#ifdef _WIN32
    #ifdef LTR24API_EXPORTS
        #define LTR24_EXPORT(type) __declspec(dllexport) type APIENTRY
    #else
        #define LTR24_EXPORT(type) __declspec(dllimport) type APIENTRY
    #endif
#elif defined __GNUC__
    #define LTR24_EXPORT(type) __attribute__ ((visibility("default"))) type
#else
    #define LTR24_EXPORT(type) type
#endif

/** @brief  ������� ������ ����������. */
#define LTR24_VERSION_CODE      0x02000000UL

/** @brief  ���������� �������. */
#define LTR24_CHANNEL_NUM       4

/** @brief  ���������� ���������� � ������ ���. �����. */
#define LTR24_RANGE_NUM         2

/** @brief  ���������� ���������� � ������ ICP-�����. */
#define LTR24_ICP_RANGE_NUM     2

/** @brief  ���������� ������ �������������. */
#define LTR24_FREQ_NUM          16

/** @brief  ���������� �������� ��������� ���� */
#define LTR24_I_SRC_VALUE_NUM    2

/** @brief  ������ ���� � ��������� ������. */
#define LTR24_NAME_SIZE          8

/** @brief  ������ ���� � �������� ������� ������. */
#define LTR24_SERIAL_SIZE       16

/** @defgroup errors ���� ������.
 *  @{
 */
#define LTR24_ERR_INVAL_FREQ        (-10100)
#define LTR24_ERR_INVAL_FORMAT      (-10101)
#define LTR24_ERR_CFG_UNSUP_CH_CNT  (-10102)
#define LTR24_ERR_INVAL_RANGE       (-10103)
#define LTR24_ERR_WRONG_CRC         (-10104)
#define LTR24_ERR_VERIFY_FAILED     (-10105)
#define LTR24_ERR_DATA_FORMAT       (-10106)
#define LTR24_ERR_UNALIGNED_DATA    (-10107)
#define LTR24_ERR_DISCONT_DATA      (-10108)
#define LTR24_ERR_CHANNELS_DISBL    (-10109)
#define LTR24_ERR_UNSUP_VERS        (-10110)
#define LTR24_ERR_FRAME_NOT_FOUND   (-10111)
#define LTR24_ERR_UNSUP_FLASH_FMT   (-10116)
#define LTR24_ERR_INVAL_I_SRC_VALUE (-10117)
#define LTR24_ERR_UNSUP_ICP_MODE    (-10118)

/** @} */

/** @defgroup freqs ���� ������ �������������.
 *  @{
 */
/** @brief  117.1875 ���.       */
#define LTR24_FREQ_117K     0
/** @brief  78.125 ���.         */
#define LTR24_FREQ_78K      1
/** @brief  58.59375 ���.       */
#define LTR24_FREQ_58K      2
/** @brief  39.0625 ���.        */
#define LTR24_FREQ_39K      3
/** @brief  29.296875 ���.      */
#define LTR24_FREQ_29K      4
/** @brief  19.53125 ���.       */
#define LTR24_FREQ_19K      5
/** @brief  14.6484375 ���.     */
#define LTR24_FREQ_14K      6
/** @brief  9.765625 ���.       */
#define LTR24_FREQ_9K7      7
/** @brief  7.32421875 ���.     */
#define LTR24_FREQ_7K3      8
/** @brief  4.8828125 ���.      */
#define LTR24_FREQ_4K8      9
/** @brief  3.662109375 ���.    */
#define LTR24_FREQ_3K6      10
/** @brief  2.44140625 ���.     */
#define LTR24_FREQ_2K4      11
/** @brief  1.8310546875 ���.   */
#define LTR24_FREQ_1K8      12
/** @brief  1.220703125 ���.    */
#define LTR24_FREQ_1K2      13
/** @brief  915.52734375 ��.    */
#define LTR24_FREQ_915      14
/** @brief  610.3515625 ��.     */
#define LTR24_FREQ_610      15
/** @} */

/** @defgroup ranges ���� ���������� � ������ ���. ����.
 *  @{
 */
/** @brief  &#B1;2 �.   */
#define LTR24_RANGE_2   0
/** @brief  &#B1;10 �.  */
#define LTR24_RANGE_10  1
/** @} */

/** @defgroup icp_ranges ���� ���������� � ������ ICP-����.
 *  @{
 */
/** @brief  ~1 �.   */
#define LTR24_ICP_RANGE_1   0
/** @brief  ~5 �.   */
#define LTR24_ICP_RANGE_5   1
/** @} */


/** @defgroup i_src_vals �������� ��������� ����.
 *  @{
 */
/** @brief  2.86 ��.   */
#define LTR24_I_SRC_VALUE_2_86   0
/** @brief  10 ��.  */
#define LTR24_I_SRC_VALUE_10     1
/** @} */

/** @defgroup formats ���� �������� ��������.
 *  @{
 */
/** @brief  20-������ ������.   */
#define LTR24_FORMAT_20     0
/** @brief  24-������ ������.   */
#define LTR24_FORMAT_24     1
/** @} */

/** @defgroup proc_flags �����, ����������� ���������� ������.
 *  @{
 */
/** @brief  �������, ��� ����� ��������� ������������� ������������ */
#define LTR24_PROC_FLAG_CALIBR       0x00000001
/** @brief  �������, ��� ����� ��������� ���� ��� � ������ */
#define LTR24_PROC_FLAG_VOLT         0x00000002
/** @brief �������, ��� ���������� ��������� ��������� ��� */
#define LTR24_PROC_FLAG_AFC_COR      0x00000004
/** @brief �������, ��� ���� ��������� �� ����������� ������ */
#define LTR24_PROC_FLAG_NONCONT_DATA 0x00000100
/** @} */


/*================================================================================================*/
#pragma pack(4)

/** @brief ������������ ���-������� ��������� ��� */
typedef struct {
    double a0;
    double a1;
    double b0;
} TLTR24_AFC_IIR_COEF;

/** @brief ����� ������������� ��� ��������� ��� ������ */
typedef struct {
    /** @brief ������� �������, ��� ������� ����� ��������� �������� �� FirCoef */
    double AfcFreq;
    /** @brief ����� ��������� ���������� ��������� ��������������� �������
         � �������� ��������� ��� ����. ������� ������������� � ������� �������
         �� AfcFreq ��� ������� ������ � ������� ��������� */
    double FirCoef[LTR24_CHANNEL_NUM][LTR24_RANGE_NUM];
    /** @brief ������������ ���-������� ��� ��������� ��� ��� �� ��������
     *  #LTR24_FREQ_39K � ���� */
    TLTR24_AFC_IIR_COEF AfcIirCoef;
} TLTR24_AFC_COEFS;

/** @brief  ���������� � ������.
 *
 *  �������� ���������� � ������. ��� ����������, ����� �������� �����
 *  SupportICP � VerPLD, ������� �� ��� ����-�� � ������������� ������
 *  ����� ������  LTR24_GetConfig().
 */
typedef struct {
    /** @brief  �������� ������ ("LTR24").  */
    CHAR        Name[LTR24_NAME_SIZE];
    /** @brief  �������� ����� ������.      */
    CHAR        Serial[LTR24_SERIAL_SIZE];
    /** @brief  ������ �������� ����.       */
    BYTE        VerPLD;
    /** @brief  ������� ��������� ��������� � ICP �������� */
    BOOL        SupportICP;
    /** @brief  ����������������� ����. ������ ����� 0 */
    DWORD       Reserved[8];
    /** @brief  ������ ��������� ������������� �������������. */
    struct {
        /** @brief  ��������.               */
        float   Offset;
        /** @brief  ����������� ��������.   */
        float   Scale;
    } CalibCoef[LTR24_CHANNEL_NUM][LTR24_RANGE_NUM][LTR24_FREQ_NUM];
    /** @brief  ������������ ��� ������������� ���. */
    TLTR24_AFC_COEFS AfcCoef;
    /** @brief  ���������� �������� ���������� ����� ��� ������� ������
               (������ ��� LTR24-2). */
    double ISrcVals[LTR24_CHANNEL_NUM][LTR24_I_SRC_VALUE_NUM];
} TINFO_LTR24;

/** @brief  ����������� ��������� ������.
 *
 *  ������ ������� ��������� ������, ���������� �
 *  ��� ���������, ��������� ������ �����. ���������� � ����������� �������
 *  ����������. ��������� ���� ��������� �������� ��� ��������� �������������
 *  ��� ��������� ���������� ������. ����� �������������� ������� �������������
 *  � ������� ������� LTR24_Init.
 */
typedef struct {
    /** @brief  ������ ��������� TLTR24.
     *
     *  ����������� ������������� ��� ������ ������� LTR24_Init.
     */
    INT         Size;
    /** @brief  ����� ����� � LTR ��������. */
    TLTR        Channel;
    /** @brief  ������� ��������� ����� ������ (TRUE -- ���� ������ �������). */
    BOOL        Run;
    /** @brief  ��� ������� �������������.
     *
     *  ��������������� ������ ����� �� �������� @ref freqs "LTR24_FREQ_*".
     *  ��������������� �������������.
     */
    BYTE        ADCFreqCode;
    /** @brief  �������� ������� ������������� � ��.
     *
     *  ����������� ��������� ������� �������������, ��������������� ����
     *  � ���� ADCFreqCode, ����� ���������� ������� LTR24_SetADC.
     */
    double      ADCFreq;
    /** @brief  ��� ������� ������.
     *
     *  ��������������� ������ ����� �� �������� @ref formats "LTR24_FORMAT_*".
     *  ��������������� �������������.
     */
    BYTE        DataFmt;
    /** @brief  �������� ��������� ���� ��� ���� ������� ����������� ICP-��������.
     *
     *  ��������������� ������ ����� �� �������� @ref i_src_vals "LTR24_I_SRC_VALUE_*".
     *  ��������������� �������������. */
    BYTE        ISrcValue;
    /** @brief  ��������� �������� �������.
     *
     *   �������� �������� ������ ("��������� ����" ��� "ICP-����" � ����������� ��
     *   �������� �������� ���� ICPMode ��� ������� ������)
     *   ��� ���� ������� (TRUE � �������).
     *
     *   ��������������� �������������.
     */
    BOOL        TestMode;
    /** @brief ������. ���� �� ������ ���������� ������������� */
    DWORD       Reserved[16];
    /** @brief  ��������� �������.
     *
     *  ��� ���� ��������������� �������������.
     */
    struct {
        /** @brief  ��������� ������.
         *
         *  ��������������� �������������.
         */
        BOOL    Enable;
        /** @brief  ��� ��������� ������.
         *
         *  ��������������� ������ ����� �� ��������
         *  @ref ranges "LTR24_RANGE_*". ��������������� �������������.
         */
        BYTE    Range;
        /** @brief  ����� ������� ���������� ������������ (TRUE -- �������).
         *
         *  ����� �������� ������ ������ � ������, ���� ���� ICPMode ����� FALSE.
         *  ��������������� �������������.
         */
        BOOL    AC;
        /** @brief  ��������� ������ ��������� ICP-��������
         *
         *  ���� FALSE - ������������ ����� "���. ����" ��� "��������� ����"
         *               (� ����������� �� ���� TestMode)
         *  ���� TRUE  - ����� "ICP" ��� "ICP ����" */
        BOOL    ICPMode;
        /** @brief ������. ���� �� ������ ���������� ������������� */
        DWORD   Reserved[4];
    } ChannelMode[LTR24_CHANNEL_NUM];
    /** @brief  ���������� � ������.*/
    TINFO_LTR24 ModuleInfo;
    /** @brief  ������ ������������ ������������� �������������.
     *
     *  ����������� ��� ��������� ������ � ������� LTR24_ProcessData()
     *  ������������� ������������ �� ������� ������, ��������� � �������.
     *  ��� ������ LTR24_GetConfig() � ������ ���� ���������� ���������
     *  ������������� ������������ (�� ��, ��� � � ModuleInfo).
     *  ��, ��� �������������, ������������ ����� �������� � ������ ����
     *  ���� ������������.
     */
    struct {
        /** @brief  ��������.               */
        float   Offset;
        /** @brief  ����������� ��������.   */
        float   Scale;
    } CalibCoef[LTR24_CHANNEL_NUM][LTR24_RANGE_NUM][LTR24_FREQ_NUM];
    /** @brief  ������������ ��� ������������� ���, ����������� � �������
     *  LTR24_ProcessData().
     *
     *  ��� ������ LTR24_GetConfig() ���� ���������� �������� �� ��� ������
     * (�� ��, ��� � � ModuleInfo) */
    TLTR24_AFC_COEFS AfcCoef;
    /** @brief  ��������� �� ��������� � �����������, ������������� ������
     *  ����������� � ������������ ������������.     */
    PVOID       Internal;
} TLTR24;

#pragma pack()


/*================================================================================================*/
/* ���������� ������� ������ ����������. */
LTR24_EXPORT(DWORD) LTR24_GetVersion(void);

/* �������������� ����������� ���������. */
LTR24_EXPORT(INT) LTR24_Init(TLTR24 *hnd);

/* ��������� ������ � ��������� ������ � �����.
 * ���������� ��� ������.
 */
LTR24_EXPORT(INT) LTR24_Open(TLTR24 *hnd, DWORD addr, WORD port, const CHAR *csn, INT slot);

LTR24_EXPORT(INT) LTR24_OpenEx(TLTR24 *hnd, DWORD net_addr, WORD net_port, const CHAR *crate_sn,
    INT slot, DWORD in_flags, DWORD *out_flags);

/* ��������� ������. ���� ��� ���� ������, �� �� ��������� ���������������.
 * ���������� ��� ������.
 */
LTR24_EXPORT(INT) LTR24_Close(TLTR24 *hnd);

/* ���������� LTR_OK, ���� ������ ������ ��� ��� ������, ���� ������.
 */
LTR24_EXPORT(INT) LTR24_IsOpened(TLTR24 *hnd);

/* ��������� ���������� �� ���� ������ ������ � ��������� ���� ModuleInfo �
 * ����������� ��������� ������.
 */
LTR24_EXPORT(INT) LTR24_GetConfig(TLTR24 *hnd);

/* �������� ��������� ��������� � ������.
 * ���������� ��� ������.
 */
LTR24_EXPORT(INT) LTR24_SetADC(TLTR24 *hnd);

/* ��������� ���� ������.
 * ���������� ��� ������.
 */
LTR24_EXPORT(INT) LTR24_Start(TLTR24 *hnd);

/* ������������� ���� ������.
 * ���������� ��� ������.
 */
LTR24_EXPORT(INT) LTR24_Stop(TLTR24 *hnd);

/* ������������ ������ ��� ���������� ����� ������.
 * �������� ����� ��������� ������������ ����.
 * ���������� ��� ������.
 */
LTR24_EXPORT(INT) LTR24_SetZeroMode(TLTR24 *hnd, BOOL enable);

/* ������������ ������ ��� ���������� ����� ������.
 * �������� ����� ��������� ���������� ������������ ��� ������� ������.
 * ���������� ��� ������.
 */
LTR24_EXPORT(INT) LTR24_SetACMode(TLTR24 *hnd, BYTE chan, BOOL ac_mode);

/* ��������� ����� ������ �� ������.
 * ������ ����������� ��-�������. ���� �������� ������� �������� �� �������
 * ���������� ������ ���. � ����������� ������� ������ �� ��������.
 * ��� 20-������� ������� ������ ������ ��� ������� �� ������
 * �������� ����� (DWORD), ��� 24-������� ������� - �� ���� ������� ����,
 * � ������� ���������� �������� ������� � ������� ����� ������� �� �������
 * ������.
 * �.�. ���� ���������� ���������� ������� ����� 2, ������������ 20-������
 * ������ ������, �� ���� ���� ����� ������ 2 ������� ����� ��� 8 ����. ���
 * 24-������� ������� ������ ����� 4 ������� ����� ��� 16 ����.
 * ������ ������������ � ������ data, ����� ������� - � ������ tmark.
 * size - ���������� ��������� �������� data � tmark.
 * timeout - ������������ ����� ���������� � ������� ��� ����� ������.
 * ������������ ���������� �������� ������� ���� ��� ��� ������.
 */
LTR24_EXPORT(INT) LTR24_Recv(TLTR24 *hnd, DWORD *data, DWORD *tmark, DWORD size, DWORD timeout);

/* ���������� LTR24_Recv ��������� ����� ������ �� ������. � ������ time
 * ������������ ���������� ����� ������� ��� ������� ������� � ������� unixtime.
 */
LTR24_EXPORT(INT) LTR24_RecvEx(TLTR24 *ltr24, DWORD *data, DWORD *tmark, DWORD size, DWORD timeout,
    LONGLONG *time_vals);

/* ������������ ����� ������, �������� �� ������, ��������� �����������
 * ������������, ��������� � ������ ��� ���� ���. ����� �����������
 * ������������� �������� ������ (� ������ ������� ���� ������� ����).
 * size - ���������� ��������� � �������. ����� ���������� � size
 * ������������ ���������� ���������� ��������� ����� ��������
 * ������������ ������ (��������, ��� �������� ������������� �� ������� �����
 * ������).
 * � ������ �������� ������������� �� ������� ����� ������ ������� ��������
 * �������� �����, ��������� ���������� ��� ����������� �������, � ����������
 * ������. ���� ������� ������ ����� ������, �� ������� ��� ����� ����������
 * � ���������� ������.
 * � ������ ovload ������������ �������� ���������� ������� ������� �������
 * (������ ������� ������������� ������ � 24-������ ������� ������), ����������
 * ��������� ������� ovload ������ ���� ����� ��, ��� � � ������� dest
 * (�.�. �� ������ ������ ������������ ��� �������).
 * ��������� ��� ������������� 24-������� ������� ������������ 2 ������� �����
 * �� ���� ������, �� ���������� ��������� ������� dest ������ ���� � 2 ����
 * ������, ��� � �������� ������� src.
 */
LTR24_EXPORT(INT) LTR24_ProcessData(TLTR24 *hnd, const DWORD *src, double *dest, INT *size,
    DWORD flags, BOOL *ovload);

/* ���������� ������ � ��������� ������.
 */
LTR24_EXPORT(LPCSTR) LTR24_GetErrorString(INT err);



/* ���������� ������ � ����� ��� �������� ����������� ���������
 * ��� ������������.
 */
LTR24_EXPORT(INT) LTR24_FindFrameStart(TLTR24 *hnd, const DWORD *data, INT size, INT *index);

LTR24_EXPORT(INT) LTR24_StoreConfig(TLTR24 *hnd, TLTR_CARD_START_MODE start_mode);


#ifdef __cplusplus
}
#endif

#endif
