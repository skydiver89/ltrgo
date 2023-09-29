#ifndef LTRAPI_COMPAT_DEFS_H
#define LTRAPI_COMPAT_DEFS_H

/*  ���������, ����������� ������ ��� �������� ������������� */

#define SADDR_LOCAL                             LTRD_ADDR_LOCAL
#define SADDR_DEFAULT                           LTRD_ADDR_DEFAULT
#define SPORT_DEFAULT                           LTRD_PORT_DEFAULT

#define CRATE_MAX                               LTR_CRATES_MAX
#define MODULE_MAX                              LTR_MODULES_PER_CRATE_MAX


#define CSN_SERVER_CONTROL                      LTR_CSN_SERVER_CONTROL



#define CRATE_TYPE_UNKNOWN                      LTR_CRATE_TYPE_UNKNOWN
#define CRATE_TYPE_LTR010                       LTR_CRATE_TYPE_LTR010
#define CRATE_TYPE_LTR021                       LTR_CRATE_TYPE_LTR021
#define CRATE_TYPE_LTR030                       LTR_CRATE_TYPE_LTR030
#define CRATE_TYPE_LTR031                       LTR_CRATE_TYPE_LTR031
#define CRATE_TYPE_LTR032                       LTR_CRATE_TYPE_LTR032
#define CRATE_TYPE_LTR_CU_1                     LTR_CRATE_TYPE_LTR_CU_1
#define CRATE_TYPE_LTR_CEU_1                    LTR_CRATE_TYPE_LTR_CEU_1
#define CRATE_TYPE_BOOTLOADER                   LTR_CRATE_TYPE_BOOTLOADER

#define CRATE_IFACE_UNKNOWN                     LTR_CRATE_IFACE_UNKNOWN
#define CRATE_IFACE_USB                         LTR_CRATE_IFACE_USB
#define CRATE_IFACE_TCPIP                       LTR_CRATE_IFACE_TCPIP

#define CRATE_IP_STATUS_OFFLINE                 LTR_CRATE_IP_STATUS_OFFLINE
#define CRATE_IP_STATUS_CONNECTING              LTR_CRATE_IP_STATUS_CONNECTING
#define CRATE_IP_STATUS_ONLINE                  LTR_CRATE_IP_STATUS_ONLINE
#define CRATE_IP_STATUS_ERROR                   LTR_CRATE_IP_STATUS_ERROR

#define CRATE_IP_FLAG_AUTOCONNECT               LTR_CRATE_IP_FLAG_AUTOCONNECT


#define SERIAL_NUMBER_SIZE      LTR_CRATE_SERIAL_SIZE


#define MID_EMPTY               LTR_MID_EMPTY
#define MID_IDENTIFYING         LTR_MID_IDENTIFYING
#define MID_LTR01               LTR_MID_LTR01
#define MID_LTR11               LTR_MID_LTR11
#define MID_LTR22               LTR_MID_LTR22
#define MID_LTR24               LTR_MID_LTR24
#define MID_LTR25               LTR_MID_LTR25
#define MID_LTR27               LTR_MID_LTR27
#define MID_LTR34               LTR_MID_LTR34
#define MID_LTR35               LTR_MID_LTR35
#define MID_LTR41               LTR_MID_LTR41
#define MID_LTR42               LTR_MID_LTR42
#define MID_LTR43               LTR_MID_LTR43
#define MID_LTR51               LTR_MID_LTR51
#define MID_LTR114              LTR_MID_LTR114
#define MID_LTR210              LTR_MID_LTR210
#define MID_LTR212              LTR_MID_LTR212


#define CC_CONTROL              LTR_CC_CHNUM_CONTROL
#define CC_MODULE1              LTR_CC_CHNUM_MODULE1
#define CC_MODULE2              LTR_CC_CHNUM_MODULE2
#define CC_MODULE3              LTR_CC_CHNUM_MODULE3
#define CC_MODULE4              LTR_CC_CHNUM_MODULE4
#define CC_MODULE5              LTR_CC_CHNUM_MODULE5
#define CC_MODULE6              LTR_CC_CHNUM_MODULE6
#define CC_MODULE7              LTR_CC_CHNUM_MODULE7
#define CC_MODULE8              LTR_CC_CHNUM_MODULE8
#define CC_MODULE9              LTR_CC_CHNUM_MODULE9
#define CC_MODULE10             LTR_CC_CHNUM_MODULE10
#define CC_MODULE11             LTR_CC_CHNUM_MODULE11
#define CC_MODULE12             LTR_CC_CHNUM_MODULE12
#define CC_MODULE13             LTR_CC_CHNUM_MODULE13
#define CC_MODULE14             LTR_CC_CHNUM_MODULE14
#define CC_MODULE15             LTR_CC_CHNUM_MODULE15
#define CC_MODULE16             LTR_CC_CHNUM_MODULE16
#define CC_USERDATA             LTR_CC_CHNUM_USERDATA


#define CC_RAW_DATA_FLAG        LTR_CC_FLAG_RAW_DATA

#define FLAG_RBUF_OVF           LTR_FLAG_RBUF_OVF
#define FLAG_RFULL_DATA         LTR_FLAG_RFULL_DATA

#define LTR_SERVER_PARAM_ETH_CRATE_POLL_TIME   LTRD_PARAM_ETH_CRATE_POLL_TIME
#define LTR_SERVER_PARAM_ETH_CRATE_CON_TOUT    LTRD_PARAM_ETH_CRATE_CON_TOUT
#define LTR_SERVER_PARAM_ETH_CRATE_CTLCMD_TOUT LTRD_PARAM_ETH_CRATE_CTLCMD_TOUT
#define LTR_SERVER_PARAM_ETH_INTF_CHECK_TIME   LTRD_PARAM_ETH_INTF_CHECK_TIME



typedef TLTR_CRATE_IP_ENTRY         TIPCRATE_ENTRY;
typedef TLTR_CRATE_INFO             TCRATE_INFO;
typedef TLTR_DESCRIPTION_MODULE     TDESCRIPTION_MODULE;
typedef TLTR_DESCRIPTION_CPU        TDESCRIPTION_CPU;
typedef TLTR_DESCRIPTION_FPGA       TDESCRIPTION_FPGA;
typedef TLTR_DESCRIPTION_ADC        TDESCRIPTION_ADC;
typedef TLTR_DESCRIPTION_DAC        TDESCRIPTION_DAC;
typedef TLTR_DESCRIPTION_MEZZANINE  TDESCRIPTION_MEZZANINE;
typedef TLTR_DESCRIPTION_DIGITAL_IO TDESCRIPTION_DIGITAL_IO;
typedef TLTR_DESCRIPTION_INTERFACE  TDESCRIPTION_INTERFACE;

#endif // LTRAPI_COMPAT_DEFS_H
