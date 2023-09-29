/** \mainpage
 *
 */
 
#ifndef LTR032API_H
#define LTR032API_H

#include "ltrapitypes.h"


#ifdef _WIN32
    #ifdef LTR032API_EXPORTS
        #define LTR032API_DllExport(type)    __declspec(dllexport) type APIENTRY
    #else
        #define LTR032API_DllExport(type)    __declspec(dllimport) type APIENTRY
    #endif
#elif defined __GNUC__
    #define LTR032API_DllExport(type) __attribute__ ((visibility("default"))) type
#else
    #define LTR032API_DllExport(type) type
#endif

#ifdef __cplusplus
extern "C" {
#endif

/** \cond */
/** ������ ���������� ��� ������ � �����-������������ LTR032. */
#define LTR032_CURR_VERS_MAJOR      1
#define LTR032_CURR_VERS_MINOR      0
#define LTR032_CURR_VERS_BUILD      0
#define LTR032_CURR_VERS_CODE       0x01000000UL
/** \endcond */

/** \defgroup namur_default �������� ����� �� ��������� ��� ������� NAMUR
 * @{
 */
/** �������� ���� �� ��������� ��� ������� ������ NAMUR */
#define LTR032_NAMUR_DEFAULT_LOWER  1.3146F
/** �������� ���� �� ��������� ��� �������� ������ NAMUR */
#define LTR032_NAMUR_DEFAULT_UPPER  1.9466F
/** @} */

/** \brief ���� ������
 *  \anchor ltr032_errors
 */
enum {
    /** ����������� ��� �����-����������� */
    LTR032_ERR_INVAL_CRATE_TYPE         = -10304,
    /** ������� ��������� �����-������������ */
    LTR032_ERR_CMD_REJECTED             = -10305,
    /** ������� ����� ����� ������ ������ M1S OUT */
    LTR032_ERR_INVALID_M1S_OUT_MODE     = -10306,
    /** ������� ������ ��������� ������ NAMUR */
    LTR032_ERR_INVALID_NAMUR_LEVELS     = -10307,
    /** ������� ����� ������ ������������ */
    LTR032_ERR_INVALID_THERM_SENS_IND   = -10308
};

/** \brief ������� ������������� ��������
 *  \anchor ltr032_temp_sens
 */
enum {
    /** ������ ������������� ������ */
    LTR032_TEMP_SENS_LOWER,
    /** ������� ������������� ������ */
    LTR032_TEMP_SENS_UPPER
};

/** \brief ������ ������ ������ M1S_OUT (������ ��������� �����, ��������)
 *  \anchor ltr032_m1sout_modes
 */
enum {
    /** �������� ���������� */
    LTR032_M1SOUT_MODE_OPEN=0,
    /** �������� �������� */
    LTR032_M1SOUT_MODE_CLOSE=1,
    /** �������� ���������� �� 100 �� � ������ ����� ������� */
    LTR032_M1SOUT_MODE_CLOSE_PULSE=2,
    /** �������� ����������� �� 100 �� � ������ ����� ������� */
    LTR032_M1SOUT_MODE_OPEN_PULSE = 4
};

/** ��������� ���������� � �����-������������. */
struct ltr032;

/** ���������� ������� ������ ����������. */
LTR032API_DllExport(DWORD) ltr032_get_version(void);

/** \brief ������� ��������� ��������� ����������
 *  
 *  ���������� �������� ���������� � ����������� ������� ����������.
 *  � ��� �������� ������� ��������� ������, ���������, ����� ����� � ������.
 *  
 *  ����� ���������� ������������� ���������, ��� ���������� ����������
 *  � ������� ������� \ref ltr032_exit.
 *  \return ��������� ��������� ���������� ��� NULL, ���� ������������ ������
 */
LTR032API_DllExport(struct ltr032 *) ltr032_init(void);

/** \brief ���������� �������� ����������
 *  
 *  ����������� �������, ���������� ��� �������� ��������� ����������.
 *  ���� ����� ����� � �����-������������ �� ��� ������, �� �� ���������
 *  �����������. ���������� ������������� ������� ��������� ����������
 *  �����������.
 *  \param ltr032 ��������
 */
LTR032API_DllExport(void) ltr032_exit(struct ltr032 *ltr032);

/** \brief ��������� ����� ����� � �����-������������
 *
 *  ���������� �������������� ����� LTR ������, ���������� �� ����� �
 *  IP ������� \a ip_addr � ��������� TCP-���� \a port. ���������� �����
 *  ���������� �� ��������� ������ \a serial.
 *
 *  ���� \a serial ����� NULL ���
 *  ������ ������, ����� ����������� ������ �����-���������� � ������ LTR
 *  �������. � �������� IP ������ � ������ ����� ����� ������������ ���������
 *  SADDR_DEFAULT � SPORT_DEFAULT, ��� ������������� ��������� ������ � �����
 *  �� ���������. � IP ������ ����� ���� �� �������� � ��������
 *  (��������, 127.0.0.1 ������������� 0x7F000001UL).
 *
 *  ����� ���������� ������ � �����-������������ ���������� ������� ����� �����
 *  � ������� ������� \ref ltr032_close.
 *  \param ltr032 ��������
 *  \param ip_addr IP ����� ����� � LTR ��������
 *  \param port TCP ����, �������������� LTR ��������
 *  \param serial �������� ����� �����-�����������
 *  \return 0 ��� ��� ������ � ������ ������
 */
LTR032API_DllExport(INT) ltr032_open(struct ltr032 *ltr032, DWORD ip_addr, WORD port,
                              const char *serial);

/** \brief ���������, ������ �� ����� ����� � �����-������������
 *  \param ltr032 ��������
 *  \return 0, ���� ����� ����� ������, ��� �� 0, ���� ������
 */
LTR032API_DllExport(INT) ltr032_is_open(struct ltr032 *ltr032);

/** \brief ��������� ����� ����� � �����-������������
 *  \param ltr032 ��������
 *  \return 0 ��� ��� ������ � ������ ������
 */
LTR032API_DllExport(INT) ltr032_close(struct ltr032 *ltr032);

/** \brief ������������� ����� ������ ������ M1S_OUT
 *
 *  ��� ������ ������ ���������� � ������� �������� \ref ltr032_m1sout_modes
 *  "LTR032_M1SOUT_MODE_*".
 *  \param ltr032 ��������
 *  \param mode ��� ����� ������
 *  \return 0 ��� ��� ������ � ������ ������
 */
LTR032API_DllExport(INT) ltr032_set_m1sout_mode(struct ltr032 *ltr032, BYTE mode);

/** \brief ��������� ����� ������ ������ M1S_OUT
 *
 *  ���������� ������� ����� ������ ������ M1S_OUT. ��������� ������ ������
 *  ������������ ����������� \ref ltr032_m1sout_modes "LTR032_M1SOUT_MODE_*".
 *  \param ltr032 ��������
 *  \param mode ��������� �� ��� ������ ������
 *  \return 0 ��� ��� ������ � ������ ������
 */
LTR032API_DllExport(INT) ltr032_get_m1sout_mode(struct ltr032 *ltr032, BYTE *mode);

/** \brief �������� ��������� �������� NAMUR ��� ����� START_IN
 *
 *  �������� ��������� ������� ����������� � ������������ (��). �����
 *  ������������ ��������� �������� ������� �� ��������� \ref namur_default
 *  "LTR032_NAMUR_DEFAULT_*".
 *  \param ltr032 ��������
 *  \param lower �������� ���� ������� ������
 *  \param upper �������� ���� �������� ������
 *  \return 0 ��� ��� ������ � ������ ������
 */
LTR032API_DllExport(INT) ltr032_set_startin_namur(struct ltr032 *ltr032, float lower, float upper);

/** \brief ��������� ��������� �������� NAMUR ��� ����� START_IN
 *
 *  �������� ��������� ������� ���������� � ������������ (��).
 *  \param ltr032 ��������
 *  \param lower ��������� �� �������� ���� ������� ������
 *  \param upper ��������� �� �������� ���� �������� ������
 *  \return 0 ��� ��� ������ � ������ ������
 */
LTR032API_DllExport(INT) ltr032_get_startin_namur(struct ltr032 *ltr032, float *lower, float *upper);

/** \brief ��������� ������� ����������� � ������������
 *  
 *  ����������� ���������� � ������� ������ ������� \a sens. �������
 *  ������������� ������������ ����������� \ref ltr032_temp_sens
 *  "LTR032_TEMP_SENS_*". ����������� ���������� � �������� �� �������.
 *  \param ltr032 ��������
 *  \param sens ������ ������������
 *  \param temp ��������� �� �������� ������� �����������
 *  \return 0 ��� ��� ������ � ������ ������
 */
LTR032API_DllExport(INT) ltr032_get_temperature(struct ltr032 *ltr032, BYTE sens, float *temp);

/** \brief ��������� ������� �������� ���������� �������
 *  
 *  ���������� ������� ���������� � ������� (�).
 *  \param ltr032 ��������
 *  \param volt ��������� �� �������� ���������� �������
 *  \return 0 ��� ��� ������ � ������ ������
 */
LTR032API_DllExport(INT) ltr032_get_supply_voltage(struct ltr032 *ltr032, float *volt);

/** \brief ������������� ������� ����� � �����-�����������
 *
 *  ��� ������������� ������� ����������� 64-������
 *  <a href=http://ru.wikipedia.org/wiki/UNIX-%D0%B2%D1%80%D0%B5%D0%BC%D1%8F>
 *  POSIX ������</a>.
 *  \param ltr032 ��������
 *  \param ptime �������� �������
 *  \return 0 ��� ��� ������ � ������ ������
 */
LTR032API_DllExport(INT) ltr032_set_time(struct ltr032 *ltr032, ULONGLONG ptime);

/** \brief ��������� ������� ����� � �����-�����������
 *
 *  ��� ������������� ������� ����������� 64-������
 *  <a href=http://ru.wikipedia.org/wiki/UNIX-%D0%B2%D1%80%D0%B5%D0%BC%D1%8F>
 *  POSIX ������</a>.
 *  \param ltr032 ��������
 *  \param ptime ��������� �� �������� �������
 *  \return 0 ��� ��� ������ � ������ ������
 */
LTR032API_DllExport(INT) ltr032_get_time(struct ltr032 *ltr032, ULONGLONG *ptime);

/** \brief ���������� ��������� �������� ��������� ������
 *  \param ltr032 ��������
 *  \return ��������� �� ��������� �������� ��� NULL � ������ ������
 */
LTR032API_DllExport(const char *) ltr032_get_error_string(struct ltr032 *ltr032);

/** \brief ���������� ��������� �� ������ ���������
 *
 *  ������ ��������� -- ��������� ���������� LTRAPI, ��������� TLTR,
 *  �������������� ����� ����� ����� � �����-������������ ����� LTR ������.
 *
 *  �������� ��������� � ������������ �� � �������� LTRAPI ������������ � �����
 *  �������� � �������.
 *  \param ltr032 ��������
 *  \param ltr ��������� �� ��������� TLTR, ������� ����� �������������������
 *  \return 0 ��� ��� ������ � ������ ������
 */
LTR032API_DllExport(INT) ltr032_get_legacy_interface(struct ltr032 *ltr032, void *ltr);

/** \brief ��������� ������ ���������� ����� �����-�����������
 *
 *  ���������� ����� �������� � ������������ �����-�����������,
 *  ����������������� ���� ������, �������� ����������� ��������.
 *  ���������� � �����-������������ ���������� � �������.
 *  \param ltr032 ��������
 *  \return 0 ��� ��� ������ � ������ ������
 */
LTR032API_DllExport(INT) ltr032_reset(struct ltr032 *ltr032);

/** \brief ��������� ������� �� �������� �������� � ���������
 *
 *  ������� �������������� ����� ������ ���������� ����� �����-����������� �
 *  ������ ������� ����������. ���������� � �����-������������ ���������� �
 *  �������.
 *  \param ltr032 ��������
 *  \return 0 ��� ��� ������ � ������ ������
 */
LTR032API_DllExport(INT) ltr032_start_boot(struct ltr032 *ltr032);

#ifdef __cplusplus
}
#endif

#endif
