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

/** @brief  Текущая версия библиотеки. */
#define LTR24_VERSION_CODE      0x02000000UL

/** @brief  Количество каналов. */
#define LTR24_CHANNEL_NUM       4

/** @brief  Количество диапазонов в режиме диф. входа. */
#define LTR24_RANGE_NUM         2

/** @brief  Количество диапазонов в режиме ICP-входа. */
#define LTR24_ICP_RANGE_NUM     2

/** @brief  Количество частот дискретизации. */
#define LTR24_FREQ_NUM          16

/** @brief  Количество значений источника тока */
#define LTR24_I_SRC_VALUE_NUM    2

/** @brief  Размер поля с названием модуля. */
#define LTR24_NAME_SIZE          8

/** @brief  Размер поля с серийным номером модуля. */
#define LTR24_SERIAL_SIZE       16

/** @defgroup errors Коды ошибок.
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

/** @defgroup freqs Коды частот дискретизации.
 *  @{
 */
/** @brief  117.1875 кГц.       */
#define LTR24_FREQ_117K     0
/** @brief  78.125 кГц.         */
#define LTR24_FREQ_78K      1
/** @brief  58.59375 кГц.       */
#define LTR24_FREQ_58K      2
/** @brief  39.0625 кГц.        */
#define LTR24_FREQ_39K      3
/** @brief  29.296875 кГц.      */
#define LTR24_FREQ_29K      4
/** @brief  19.53125 кГц.       */
#define LTR24_FREQ_19K      5
/** @brief  14.6484375 кГц.     */
#define LTR24_FREQ_14K      6
/** @brief  9.765625 кГц.       */
#define LTR24_FREQ_9K7      7
/** @brief  7.32421875 кГц.     */
#define LTR24_FREQ_7K3      8
/** @brief  4.8828125 кГц.      */
#define LTR24_FREQ_4K8      9
/** @brief  3.662109375 кГц.    */
#define LTR24_FREQ_3K6      10
/** @brief  2.44140625 кГц.     */
#define LTR24_FREQ_2K4      11
/** @brief  1.8310546875 кГц.   */
#define LTR24_FREQ_1K8      12
/** @brief  1.220703125 кГц.    */
#define LTR24_FREQ_1K2      13
/** @brief  915.52734375 Гц.    */
#define LTR24_FREQ_915      14
/** @brief  610.3515625 Гц.     */
#define LTR24_FREQ_610      15
/** @} */

/** @defgroup ranges Коды диапазонов в режиме диф. вход.
 *  @{
 */
/** @brief  &#B1;2 В.   */
#define LTR24_RANGE_2   0
/** @brief  &#B1;10 В.  */
#define LTR24_RANGE_10  1
/** @} */

/** @defgroup icp_ranges Коды диапазонов в режиме ICP-вход.
 *  @{
 */
/** @brief  ~1 В.   */
#define LTR24_ICP_RANGE_1   0
/** @brief  ~5 В.   */
#define LTR24_ICP_RANGE_5   1
/** @} */


/** @defgroup i_src_vals Значения источника тока.
 *  @{
 */
/** @brief  2.86 мА.   */
#define LTR24_I_SRC_VALUE_2_86   0
/** @brief  10 мА.  */
#define LTR24_I_SRC_VALUE_10     1
/** @} */

/** @defgroup formats Коды форматов отсчетов.
 *  @{
 */
/** @brief  20-битный формат.   */
#define LTR24_FORMAT_20     0
/** @brief  24-битный формат.   */
#define LTR24_FORMAT_24     1
/** @} */

/** @defgroup proc_flags Флаги, управляющие обработкой данных.
 *  @{
 */
/** @brief  Признак, что нужно применить калибровочные коэффициенты */
#define LTR24_PROC_FLAG_CALIBR       0x00000001
/** @brief  Признак, что нужно перевести коды АЦП в Вольты */
#define LTR24_PROC_FLAG_VOLT         0x00000002
/** @brief Признак, что необходимо выполнить коррекцию АЧХ */
#define LTR24_PROC_FLAG_AFC_COR      0x00000004
/** @brief Признак, что идет обработка не непрерывных данных */
#define LTR24_PROC_FLAG_NONCONT_DATA 0x00000100
/** @} */


/*================================================================================================*/
#pragma pack(4)

/** @brief Коэффициенты БИХ-фильтра коррекции АЧХ */
typedef struct {
    double a0;
    double a1;
    double b0;
} TLTR24_AFC_IIR_COEF;

/** @brief Набор коэффициентов для коррекции АЧХ модуля */
typedef struct {
    /** @brief Частота сигнала, для которой снято отношение амплитуд из FirCoef */
    double AfcFreq;
    /** @brief Набор отношений измеренной амплитуды синусоидального сигнала
         к реальной амплитуде для макс. частоты дискретизации и частоты сигнала
         из AfcFreq для каждого канала и каждого диапазона */
    double FirCoef[LTR24_CHANNEL_NUM][LTR24_RANGE_NUM];
    /** @brief Коэффициенты БИХ-фильтра для коррекции АЧХ АЦП на частотах
     *  #LTR24_FREQ_39K и ниже */
    TLTR24_AFC_IIR_COEF AfcIirCoef;
} TLTR24_AFC_COEFS;

/** @brief  Информация о модуле.
 *
 *  Содержит информацию о модуле. Вся информация, кроме значений полей
 *  SupportICP и VerPLD, берется из ПЗУ моду-ля и действительна только
 *  после вызова  LTR24_GetConfig().
 */
typedef struct {
    /** @brief  Название модуля ("LTR24").  */
    CHAR        Name[LTR24_NAME_SIZE];
    /** @brief  Серийный номер модуля.      */
    CHAR        Serial[LTR24_SERIAL_SIZE];
    /** @brief  Версия прошивки ПЛИС.       */
    BYTE        VerPLD;
    /** @brief  Признак поддержки измерения с ICP датчиков */
    BOOL        SupportICP;
    /** @brief  Зарезервированные поля. Всегда равны 0 */
    DWORD       Reserved[8];
    /** @brief  Массив заводских калибровочных коэффициентов. */
    struct {
        /** @brief  Смещение.               */
        float   Offset;
        /** @brief  Коэффициент масштаба.   */
        float   Scale;
    } CalibCoef[LTR24_CHANNEL_NUM][LTR24_RANGE_NUM][LTR24_FREQ_NUM];
    /** @brief  Коэффициенты для корректировки АЧХ. */
    TLTR24_AFC_COEFS AfcCoef;
    /** @brief  Измеренные значения источников токов для каждого канала
               (только для LTR24-2). */
    double ISrcVals[LTR24_CHANNEL_NUM][LTR24_I_SRC_VALUE_NUM];
} TINFO_LTR24;

/** @brief  Управляющая структура модуля.
 *
 *  Хранит текущие настройки модуля, информацию о
 *  его состоянии, структуру канала связи. Передается в большинство функций
 *  библиотеки. Некоторые поля структуры доступны для изменения пользователем
 *  для настройки параметров модуля. Перед использованием требует инициализации
 *  с помощью функции LTR24_Init.
 */
typedef struct {
    /** @brief  Размер структуры TLTR24.
     *
     *  Заполняется автоматически при вызове функции LTR24_Init.
     */
    INT         Size;
    /** @brief  Канал связи с LTR сервером. */
    TLTR        Channel;
    /** @brief  Текущее состояние сбора данных (TRUE -- сбор данных запущен). */
    BOOL        Run;
    /** @brief  Код частоты дискретизации.
     *
     *  Устанавливается равным одной из констант @ref freqs "LTR24_FREQ_*".
     *  Устанавливается пользователем.
     */
    BYTE        ADCFreqCode;
    /** @brief  Значение частоты дискретизации в Гц.
     *
     *  Заполняется значением частоты дискретизации, соответствующим коду
     *  в поле ADCFreqCode, после выполнения функции LTR24_SetADC.
     */
    double      ADCFreq;
    /** @brief  Код формата данных.
     *
     *  Устанавливается равным одной из констант @ref formats "LTR24_FORMAT_*".
     *  Устанавливается пользователем.
     */
    BYTE        DataFmt;
    /** @brief  Значение источника тока для всех каналов подключения ICP-датчиков.
     *
     *  Устанавливается равным одной из констант @ref i_src_vals "LTR24_I_SRC_VALUE_*".
     *  Устанавливается пользователем. */
    BYTE        ISrcValue;
    /** @brief  Включение тестовых режимов.
     *
     *   Включает тестовые режимы ("Измерение нуля" или "ICP-тест" в зависимости от
     *   значения значения поля ICPMode для каждого канала)
     *   для всех каналов (TRUE – включен).
     *
     *   Устанавливается пользователем.
     */
    BOOL        TestMode;
    /** @brief Резерв. Поле не должно изменяться пользователем */
    DWORD       Reserved[16];
    /** @brief  Настройки каналов.
     *
     *  Все поля устанавливаются пользователем.
     */
    struct {
        /** @brief  Включение канала.
         *
         *  Устанавливается пользователем.
         */
        BOOL    Enable;
        /** @brief  Код диапазона канала.
         *
         *  Устанавливается равным одной из констант
         *  @ref ranges "LTR24_RANGE_*". Устанавливается пользователем.
         */
        BYTE    Range;
        /** @brief  Режим отсечки постоянной составляющей (TRUE -- включен).
         *
         *  Имеет значение только только в случае, если поле ICPMode равно FALSE.
         *  Устанавливается пользователем.
         */
        BOOL    AC;
        /** @brief  Включение режима измерения ICP-датчиков
         *
         *  Если FALSE - используется режим "Диф. вход" или "Измерение нуля"
         *               (в зависимости от поля TestMode)
         *  Если TRUE  - режим "ICP" или "ICP тест" */
        BOOL    ICPMode;
        /** @brief Резерв. Поле не должно изменяться пользователем */
        DWORD   Reserved[4];
    } ChannelMode[LTR24_CHANNEL_NUM];
    /** @brief  Информация о модуле.*/
    TINFO_LTR24 ModuleInfo;
    /** @brief  Массив используемых калибровочных коэффициентов.
     *
     *  Применяемые для коррекции данных в функции LTR24_ProcessData()
     *  калибровочные коэффициенты по каждому каналу, диапазону и частоте.
     *  При вызове LTR24_GetConfig() в данные поля копируются заводские
     *  калибровочные коэффициенты (те же, что и в ModuleInfo).
     *  Но, при необходимости, пользователь может записать в данные поля
     *  свои коэффициенты.
     */
    struct {
        /** @brief  Смещение.               */
        float   Offset;
        /** @brief  Коэффициент масштаба.   */
        float   Scale;
    } CalibCoef[LTR24_CHANNEL_NUM][LTR24_RANGE_NUM][LTR24_FREQ_NUM];
    /** @brief  Коэффициенты для корректировки АЧХ, применяемые в функции
     *  LTR24_ProcessData().
     *
     *  При вызове LTR24_GetConfig() поля копируются значения из ПЗУ модуля
     * (те же, что и в ModuleInfo) */
    TLTR24_AFC_COEFS AfcCoef;
    /** @brief  Указатель на структуру с параметрами, используемыми только
     *  библиотекой и недоступными пользователю.     */
    PVOID       Internal;
} TLTR24;

#pragma pack()


/*================================================================================================*/
/* Возвращает текущую версию библиотеки. */
LTR24_EXPORT(DWORD) LTR24_GetVersion(void);

/* Инициализирует управляющую структуру. */
LTR24_EXPORT(INT) LTR24_Init(TLTR24 *hnd);

/* Открывает модуль в указанном крейте и слоте.
 * Возвращает код ошибки.
 */
LTR24_EXPORT(INT) LTR24_Open(TLTR24 *hnd, DWORD addr, WORD port, const CHAR *csn, INT slot);

LTR24_EXPORT(INT) LTR24_OpenEx(TLTR24 *hnd, DWORD net_addr, WORD net_port, const CHAR *crate_sn,
    INT slot, DWORD in_flags, DWORD *out_flags);

/* Закрывает модуль. Если шел сбор данных, то он корректно останавливается.
 * Возвращает код ошибки.
 */
LTR24_EXPORT(INT) LTR24_Close(TLTR24 *hnd);

/* Возвращает LTR_OK, если модуль открыт или код ошибки, если закрыт.
 */
LTR24_EXPORT(INT) LTR24_IsOpened(TLTR24 *hnd);

/* Считывает информацию из флеш памяти модуля и обновляет поля ModuleInfo в
 * управляющей структуре модуля.
 */
LTR24_EXPORT(INT) LTR24_GetConfig(TLTR24 *hnd);

/* Передает выбранные настройки в модуль.
 * Возвращает код ошибки.
 */
LTR24_EXPORT(INT) LTR24_SetADC(TLTR24 *hnd);

/* Запускает сбор данных.
 * Возвращает код ошибки.
 */
LTR24_EXPORT(INT) LTR24_Start(TLTR24 *hnd);

/* Останавливает сбор данных.
 * Возвращает код ошибки.
 */
LTR24_EXPORT(INT) LTR24_Stop(TLTR24 *hnd);

/* Используется только при запущенном сборе данных.
 * Включает режим измерения собственного нуля.
 * Возвращает код ошибки.
 */
LTR24_EXPORT(INT) LTR24_SetZeroMode(TLTR24 *hnd, BOOL enable);

/* Используется только при запущенном сборе данных.
 * Включает режим отсечения постоянной составляющей для каждого канала.
 * Возвращает код ошибки.
 */
LTR24_EXPORT(INT) LTR24_SetACMode(TLTR24 *hnd, BYTE chan, BOOL ac_mode);

/* Принимает сырые данные от модуля.
 * Данные принимаются по-кадрово. Кадр содержит текущие значения по каждому
 * включенном каналу АЦП. С выключенных каналов данные не приходят.
 * Для 20-битного формата каждый отсчет АЦП состоит из одного
 * двойного слова (DWORD), для 24-битного формата - из двух двойных слов,
 * в которых передается отдельно старшая и младшая часть отсчета по данному
 * каналу.
 * Т.е. если количество включенных каналов равно 2, используется 20-битный
 * формат данных, то один кадр будет длиной 2 двойных слова или 8 байт. Для
 * 24-битного формата размер будет 4 двойных слова или 16 байт.
 * Данные возвращаются в массив data, метки времени - в массив tmark.
 * size - количество элементов массивов data и tmark.
 * timeout - максимальное время блокировки в функции для сбора данных.
 * Возвращается количество принятых двойных слов или код ошибки.
 */
LTR24_EXPORT(INT) LTR24_Recv(TLTR24 *hnd, DWORD *data, DWORD *tmark, DWORD size, DWORD timeout);

/* Аналогично LTR24_Recv принимает сырые данные от модуля. В массив time
 * складываются абсолютные метки времени для каждого отсчета в формате unixtime.
 */
LTR24_EXPORT(INT) LTR24_RecvEx(TLTR24 *ltr24, DWORD *data, DWORD *tmark, DWORD size, DWORD timeout,
    LONGLONG *time_vals);

/* Обрабатывает сырые данные, принятые от модуля, применяет поправочные
 * коэффициенты, переводит в вольты или коды АЦП. Также проверяется
 * неразрывность принятых данных (в каждом формате есть счетчик слов).
 * size - количество элементов в массиве. После выполнения в size
 * записывается оставшееся количество элементов после удаления
 * некорректных данных (например, при передаче невыровненных по границе кадра
 * данных).
 * В случае передачи невыровненных по границе кадра данных функция вырезает
 * неполные кадры, производя вычисления над оставшимися данными, и возвращает
 * ошибку. Если входные данные имеют разрыв, то функция это также определяет
 * и возвращает ошибку.
 * В массив ovload возвращаются признаки перегрузки входных трактов каналов
 * (данный признак отслеживается только в 24-битном формате данных), количество
 * элементов массива ovload должен быть таким же, как и у массива dest
 * (т.е. на каждый отсчет возвращается его признак).
 * Поскольку при использовании 24-битного формата используется 2 двойных слова
 * на один отсчет, то количество элементов массива dest должно быть в 2 раза
 * меньше, чем у входного массива src.
 */
LTR24_EXPORT(INT) LTR24_ProcessData(TLTR24 *hnd, const DWORD *src, double *dest, INT *size,
    DWORD flags, BOOL *ovload);

/* Возвращает строку с описанием ошибки.
 */
LTR24_EXPORT(LPCSTR) LTR24_GetErrorString(INT err);



/* Определяет данные в слоте для хранения управляющей структуры
 * как некорректные.
 */
LTR24_EXPORT(INT) LTR24_FindFrameStart(TLTR24 *hnd, const DWORD *data, INT size, INT *index);

LTR24_EXPORT(INT) LTR24_StoreConfig(TLTR24 *hnd, TLTR_CARD_START_MODE start_mode);


#ifdef __cplusplus
}
#endif

#endif
