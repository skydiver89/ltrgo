#ifndef LTRAPITYPES_H_
#define LTRAPITYPES_H_


#include "lwintypes.h"
#include "ltrapidefine.h"


#ifdef __cplusplus
extern "C" {
#endif

/** @cond obsolete */

#ifndef COMMENT_LENGTH
#define COMMENT_LENGTH (256)
#endif

#ifndef ADC_CALIBRATION_NUMBER
#define ADC_CALIBRATION_NUMBER (256)
#endif

#ifndef DAC_CALIBRATION_NUMBER
#define DAC_CALIBRATION_NUMBER (256)
#endif


#pragma pack(4)


typedef struct {
    INT code;
    LPCSTR message;
} TLTR_ERROR_STRING_DEF;


/* �������� ������ */
typedef struct {
    BYTE CompanyName[16];
    BYTE DeviceName[16];                                   /* �������� ������� */
    BYTE SerialNumber[16];                                 /* �������� ����� ������� */
    BYTE Revision;                                         /* ������� ������� */
    BYTE Comment[COMMENT_LENGTH];
} TLTR_DESCRIPTION_MODULE;
/* �������� ���������� � ����������� ����������� */
typedef struct {
    BYTE Active;                                           /* ���� ������������� ��������� �����
                                                            * ���������
                                                            */
    BYTE Name[16];                                         /* �������� */
    double ClockRate;
    DWORD FirmwareVersion;
    BYTE Comment[COMMENT_LENGTH];
} TLTR_DESCRIPTION_CPU;
/* �������� ���� */
typedef struct {
    BYTE Active;                                           /* ���� ������������� ��������� �����
                                                            * ���������
                                                            */
    BYTE Name[16];                                         /* �������� */
    double ClockRate;
    DWORD FirmwareVersion;
    BYTE Comment[COMMENT_LENGTH];
} TLTR_DESCRIPTION_FPGA;
/* �������� ��� */
typedef struct {
    BYTE Active;                                           /* ���� ������������� ��������� �����
                                                            * ���������
                                                            */
    BYTE Name[16];                                         /* �������� */
    double Calibration[ADC_CALIBRATION_NUMBER];            /* ���������������� ������������ */
    BYTE Comment[COMMENT_LENGTH];
} TLTR_DESCRIPTION_ADC;
/* �������� ��� */
typedef struct {
    BYTE Active;                                           /* ���� ������������� ��������� �����
                                                            * ���������
                                                            */
    BYTE Name[16];                                         /* �������� */
    double Calibration[DAC_CALIBRATION_NUMBER];            /* ���������������� ������������ */
    BYTE Comment[COMMENT_LENGTH];
} TLTR_DESCRIPTION_DAC ;
/* �������� h-��������� */
typedef struct {
    BYTE Active;                                           /* ���� ������������� ��������� �����
                                                            * ���������
                                                            */
    BYTE Name[16];                                         /* �������� ������� */
    BYTE SerialNumber[16];                                 /* �������� ����� ������� */
    BYTE Revision;                                         /* ������� ������� */
    double Calibration[4];                                 /* ���������������� ������������ */
    BYTE Comment[COMMENT_LENGTH];                          /* ����������� */
} TLTR_DESCRIPTION_MEZZANINE;
/* �������� ��������� �/� */
typedef struct {
    BYTE Active;                                           /* ���� ������������� ��������� �����
                                                            * ���������
                                                            */
    BYTE Name[16];                                         /* �������� */
    WORD InChannels;                                       /* ����� ������� */
    WORD OutChannels;                                      /* ����� ������� */
    BYTE Comment[COMMENT_LENGTH];
} TLTR_DESCRIPTION_DIGITAL_IO;
/* �������� ������������ ������� */
typedef struct _DESCRIPTION_INTERFACE_ {
    BYTE Active;                                           /* ���� ������������� ��������� �����
                                                            * ���������
                                                            */
    BYTE Name[16];                                         /* �������� */
    BYTE Comment[COMMENT_LENGTH];
} TLTR_DESCRIPTION_INTERFACE;




/** @endcond */

/***************************************************************************//**
  @addtogroup type_list
  @{
  *****************************************************************************/

/** @brief ���������� � ���� � ���������� ����������� ������.

    ������ ��������� ����������� �������� LTR_GetCrateInfo() � �������� ����������
    � ���� ������ � ���������� ��� �����������.
 */
typedef struct {
    BYTE CrateType;                      /**< ��� ������ --- �������� �� #en_LTR_CrateTypes */
    BYTE CrateInterface;                 /**< ��������� ����������� ������ ---
                                              �������� �� #en_LTR_CrateIface */
} TLTR_CRATE_INFO;


/** @brief ������ � IP-������� ������

   ������ ��������� �������� ���������� � ������ �� IP-������ ������, �����������
   � ���������� ������ ltrd, � ����� ��������� ����������� ������ �� ����������
   Ethernet (TCP/IP), ���������������� ������ ������ */
typedef struct {
    DWORD ip_addr;                             /**< IP-����� ������. ������ ���������� ����
                                                    saddr � #TLTR */
    DWORD flags;                               /**< ����� ������, ��������� � ������ �������,
                                                    �� #en_LTR_CrateIpFlags */
    CHAR serial_number[LTR_CRATE_SERIAL_SIZE]; /**< ���� ����� ���������, ��
                                                    � ������ ���� ���������� �������� �����
                                                    ������������� ������. ����
                                                    ����� ����� ������������ ���
                                                    �������� ���������� � �������.
                                                    ��� ��������� �������� status ������
                                                    ���� �������� ������ ������, �.�.
                                                    �������� ����� ���������� */
    BYTE is_dynamic;      /**< ��������� ����. ������ ����� 0 */
    BYTE status;          /**< ��������� ����������� ������, ����������������
                               ������ ������. ���� �������� �� #en_LTR_CrateIpStatus */
} TLTR_CRATE_IP_ENTRY;

/** @brief ���������� ������

    ��������� �������� ���������� � ��������� ������ � ��������� ����������
    ������ � �������, ������� ����� ������ ltrd.
    ������ ���������� ����� ���� �������� ����� ����������� ���������� � �������
    ������� LTR_GetCrateStatistic().
    ���������� ������� � ������� ������������ ����� ����� ltrd � �������. */
typedef struct {
    DWORD size;                             /**< ������ ���� �������������� �����
                                                 ���������, ������� ���� ���� size */
    DWORD flags;                            /**< ����� --- ������ */
    WORD crate_type;                        /**< ��� ������ �� #en_LTR_CrateTypes */
    WORD crate_intf;                        /**< ���������, �� �������� ���������
                                                 ����� �� #en_LTR_CrateIface */
    WORD crate_state;                       /**< ������ */
    WORD crate_mode;                        /**< ����� ������ ������ �� #en_LTR_CrateMode */
    ULONGLONG con_time;                     /**< ����� ������������ ���������� ������
                                                 � ������� (������ unixtime) */
    WORD res[11];                           /**< ������ */
    WORD modules_cnt;                       /**< ���������� ������ � ������ ���� ������ */
    WORD mids[LTR_MODULES_PER_CRATE_MAX];   /**< ID-������� ��� ���� ������ ������ */
    WORD res2[3*LTR_MODULES_PER_CRATE_MAX]; /**< ������ */
    WORD ctl_clients_cnt;                   /**< ���������� ��������, ������������ ��
                                                 ������������ ������ � ������ */
    WORD total_mod_clients_cnt;             /**< ���������� ��������, ������������ ��
                                                 ���� ������� ������ */
    DWORD res3[11];                         /**< ������ */

    ULONGLONG wrd_sent;                     /**< ����� ���������� ����, ���������� �
                                                 ����� (������ � ���� ��� �������) */
    ULONGLONG wrd_recv;                     /**< ����� ���������� ����, �������� ��
                                                 ������ (�� ������ ������ � ���� ��� �������) */
    double bw_send;                         /**< ������� �������� �������� ���� � ����� (����/�) */
    double bw_recv;                         /**< ������� �������� ������ ���� �� ������ (����/c) */
    ULONGLONG crate_wrd_recv;               /**< ���������� �������� ����
                                                 ��������������� �� ������ */
    ULONGLONG internal_rbuf_miss;            /**< ���������� ���������� ������� � ������
                                                  ��-�� ����������� ������������ */
    DWORD internal_rbuf_ovfls;               /**< ���������� ������������ ����������
                                                   ������ ������ */
    DWORD rbuf_ovfls;                        /**< ���������� ������������ ������
                                                  ����� ������ �� ������� � ������
                                                  ltrd ��� ������� ������ (���������
                                                  �� ���� �������) */
    DWORD total_start_marks;                 /**< ���������� �������� ����� "�����" ��� �� ������,
                                                  ��� � �� ������� */
    DWORD total_sec_marks;                   /**< ���������� �������� ��������� ����� ��� �� ������,
                                                  ��� � �� ������� */
    DWORD crate_start_marks;                 /**< ���������� �������� ����� "�����"
                                                  ��������������� �� ������ */
    DWORD crate_sec_marks;                   /**< ���������� �������� ��������� �����
                                                  ��������������� �� ������ */
    ULONGLONG crate_unixtime;                /**< ��������� �������� �����������
                                                  ��������� ����� (������ unixtime),
                                                  ���� �������������� ������� */
    DWORD therm_mask;                        /**< ����� �������������� ��������� �����������
                                                  (���� �� �������������� --- 0) */
    float therm_vals[LTR_CRATE_THERM_MAX_CNT]; /**< �������� ��������� ����������� ������. �������������
                                                    ������ ���� ��������������� ��� � therm_mask � 1 */
    DWORD res4[19];                          /**< ������ */
} TLTR_CRATE_STATISTIC;

/** @brief ���������� ������

    ��������� �������� ���������� � ��������� ������ � ��������� ����������
    ������ � ������ �������, ������� ����� ������ ltrd.
    ������ ���������� ����� ���� �������� ����� ����������� ���������� � �������
    ������� LTR_GetModuleStatistic().
    ���������� ������� � ������� ����������� ������ � ������������ ������ ��
    ������� ������ ����� LTR_ResetModule() */
typedef struct {
    DWORD size;                             /**< ������ ���� �������������� �����
                                                 ���������, ������� ���� ���� size */
    WORD client_cnt;                        /**< ���������� ��������, ������������ ����������
                                                 � ������� */
    WORD mid;                               /**< ������������� ������ �� #en_LTR_MIDs */
    DWORD flags;                            /**< ����� ������, ����������� �����������
                                                 ������, �� #en_LTR_ModuleDescrFlags */
    CHAR  name[LTR_MODULE_NAME_SIZE];       /**< ������ � ��������� ������ (�������� � �������������,
                                                  ���� ltrd �������� �� ����������) */
    DWORD res[5];                           /**< ������ */
    ULONGLONG wrd_sent;                     /**< ���������� ����, ���������� ������ */
    ULONGLONG wrd_recv;                     /**< ���������� ����, �������� �� ������ */
    double bw_send;                         /**< ������� �������� �������� ���� � ������ (����/�) */
    double bw_recv;                         /**< ������� �������� ������ ���� �� ������ (����/�) */
    ULONGLONG wrd_sent_to_client;           /**< ���������� ����, ���������� ������� */
    ULONGLONG wrd_recv_from_client;         /**< ���������� ����, �������� �� ������� */
    ULONGLONG wrd_recv_drop;                /**< ���������� ����������� ���� ��-�� ������������
                                                 ������ �� ����� � ������ ltrd */
    DWORD rbuf_ovfls;                       /**< ���������� ������������ ������ �� �����
                                                 � ������ ltrd */
    DWORD send_srvbuf_size;                 /**< ������ ������ � ltrd ��� ������ �� �������� */
    DWORD recv_srvbuf_size;                 /**< ������ ������ � ltrd ��� ������ �� ����� */
    DWORD send_srvbuf_full;                 /**< �� ������� ���� �������� ����� �� �������� */
    DWORD recv_srvbuf_full;                 /**< �� ������� ���� �������� ����� �� ����� */
    DWORD send_srvbuf_full_max;             /**< �� ������� ���� ��� ����������� �������� ����� �� �������� */
    DWORD recv_srvbuf_full_max;             /**< �� ������� ���� ��� ����������� �������� ����� �� ����� */
    DWORD res2[17];                         /**< ������ */
    DWORD start_mark;                       /**< ���������� �������� ����� "�����" �� ������ */
    DWORD sec_mark;                         /**< ���������� �������� ��������� ����� �� ������ */
    /* ����, ����������� ��������� ���������� ���������� ������� ������.
     * �������������, ������ ���� ���� ����
     */
    DWORD hard_send_fifo_size;              /**< ������ ���������� ������� ������ ������. ������ ����, � �����
                                                 ��� ��������� ���� hard_send_... ������������� ������
                                                 ��� ������� ������ � �������� �������������� ltrd �������
                                                 � ������ (��� ���� ������� ����� ���������� ���������������
                                                 ���� � ���� flags) */
    DWORD hard_send_fifo_unack_words;       /**< ������������� ���������� ������� (���������� ������������,
                                                 �� �� �������������� ����) */
    DWORD hard_send_fifo_underrun;          /**< ���������� "���������" ������� (������� �����
                                                 ��� ������� ������ �������� �� ���) � �������
                                                 ���������� ������ ������ */
    DWORD hard_send_fifo_overrun;           /**< ���������� ������������ ������� � �������
                                                 ���������� ������ ������*/
    DWORD hard_send_fifo_internal;          /**< ��������� ��������� ���������� ������� */
    DWORD res3[25];                         /**< ������ */
} TLTR_MODULE_STATISTIC;

/** @brief ���������� � ������ � ��� ��������

    ��������� �������� ���������� � ������, ������� ��� ������, ��������� � �������.
    ����������� ����� ������������ � ���� �������������� ������� �������� ������.

    ������ ���������� ����� ���� �������� ������ ���������� ����� ���� ��������
      ����� ����������� ���������� � ������� LTR_GetCrateDescr().

    */
typedef struct {
    DWORD size;                                            /**< ������ ���� �������������� �����
                                                                ���������, ������� ���� ���� size */
    char devname[LTR_CRATE_DEVNAME_SIZE];                  /**< �������� ������ */
    char serial[LTR_CRATE_SERIAL_SIZE];                    /**< �������� ����� */
    char soft_ver[LTR_CRATE_SOFTVER_SIZE];                 /**< ������ �������� */
    char brd_revision[LTR_CRATE_REVISION_SIZE];            /**< ������� ����� */
    char brd_opts[LTR_CRATE_BOARD_OPTIONS_SIZE];           /**< ����� ����� */
    char bootloader_ver[LTR_CRATE_BOOTVER_SIZE];           /**< ������ ���������� */
    char cpu_type[LTR_CRATE_CPUTYPE_SIZE];                 /**< ��� ���������������� */
    char fpga_name[LTR_CRATE_FPGA_NAME_SIZE];              /**< �������� ���� � ������ */
    char fpga_version[LTR_CRATE_FPGA_VERSION_SIZE];        /**< ������ �������� ���� */
    char crate_type_name[LTR_CRATE_TYPE_NAME];             /**< ������ � ����� ������ */
    char spec_info[LTR_CRATE_SPECINFO_SIZE];               /**< ������ */
    BYTE protocol_ver_major;                               /**< ������ ��������� �����
                                                                ltrd � ������� (��������) */
    BYTE protocol_ver_minor;                               /**< ������ ��������� �����
                                                                ltrd � ������� (��������) */
    /** @cond kd_extension */
    BYTE slots_config_ver_major;                           /**< ������ ��������� ��� ����������
                                                                �������� ������ (��������) */
    BYTE slots_config_ver_minor;                           /**< ������ ��������� ��� ����������
                                                                �������� ������ (��������) */
    /** @endcond */
} TLTR_CRATE_DESCR;

#pragma pack()


/** @cond kd_extension */
typedef INT TLTR_CARD_START_MODE;
/** @endcond */

/** @} */

#ifdef __cplusplus
}
#endif

#endif /*#ifndef LTRAPITYPES_H_*/
