#ifndef MICRO_TOOLS_GPS_ZEDF9P_H
#define MICRO_TOOLS_GPS_ZEDF9P_H

#include "stdlib.h"
#include "stdio.h"
#include "stdbool.h"
#include "simplePico/i2c.h"



/* ========== Begin enums ================== */

typedef enum
  {
  i2c,
  spi
  } T_ZF9P_e_CommsMethod;

typedef enum
  {
  UBX_RTCM_1005,
  UBX_RTCM_1074,
  UBX_RTCM_1084,
  UBX_RTCM_1094,
  UBX_RTCM_1124,
  UBX_RTCM_1230
  } T_ZF9P_e_Setting;

typedef enum
  {
  UBX_MSG_CLS_ACK = 0x05,
  UBX_MSG_CLS_CFG = 0x06,
  UBX_MSG_CLS_INF = 0x04,
  UBX_MSG_CLS_LOG = 0x21,
  UBX_MSG_CLS_MGA = 0x13,
  UBX_MSG_CLS_MON = 0x0A,
  UBX_MSG_CLS_NAV = 0x01,
  UBX_MSG_CLS_NAV2 = 0x29,
  UBX_MSG_CLS_RXM = 0x02,
  UBX_MSG_CLS_SEC = 0x27,
  UBX_MSG_CLS_TIM = 0x0D,
  UBX_MSG_CLS_UPD = 0x09
  } T_ZF9P_e_UbxMessageClasses;

typedef enum
  {
  /* Begin ACK Class MsgId's */
  UBX_MSG_ID_ACK = 0x01,
  UBX_MSG_ID_NAK = 0x00,
  /* End ACK Class MsgId's */

  /* Begin CFG Class MsgId's */
  UBX_MSG_ID_ANT = 0x13,
  UBX_MSG_ID_CFG = 0x09,
  UBX_MSG_ID_DAT = 0x06,
  UBX_MSG_ID_DGNSS = 0x70,
  UBX_MSG_ID_GEOFENCE = 0x69,
  UBX_MSG_ID_GNSS = 0x3E,
  UBX_MSG_ID_INF = 0x02, UBX_MSG_ID_ITFM = 0x39,
  UBX_MSG_ID_LOGFILTER = 0x47,
  UBX_MSG_ID_MSG = 0x01,
  UBX_MSG_ID_NAV5 = 0x24,
  UBX_MSG_ID_NAVX5 = 0x23,
  UBX_MSG_ID_NMEA = 0x17,
  UBX_MSG_ID_ODO = 0x1E,
  UBX_MSG_ID_PRT = 0x00,
  UBX_MSG_ID_PWR = 0x57,
  UBX_MSG_ID_RATE = 0x08,
  UBX_MSG_ID_RINV = 0x34,
  UBX_MSG_ID_RST = 0x04,
  UBX_MSG_ID_SBAS = 0x16,
  UBX_MSG_ID_TMODE3 = 0x71,
  UBX_MSG_ID_TP5 = 0x31,
  UBX_MSG_ID_USB = 0x1B,
  UBX_MSG_ID_VALDEL = 0x8C,
  UBX_MSG_ID_VALGET = 0x8B,
  UBX_MSG_ID_VALSET = 0x8A,
  /* End CFG Class MsgId's */

  /* Begin INF Class MsgId's */
  UBX_MSG_ID_DEBUG = 0x04,
  UBX_MSG_ID_ERROR = 0x00,
  UBX_MSG_ID_NOTICE = 0x02,
  UBX_MSG_ID_TEST = 0x03,
  UBX_MSG_ID_WARNING = 0x01,
  /* End INF Class MsgId's */

  /* Begin LOG Class MsgId's */
  UBX_MSG_ID_CREATE = 0x07,
  UBX_MSG_ID_ERASE = 0x03,
  UBX_MSG_ID_FINDTIME = 0x0E,
  UBX_MSG_ID_INFO = 0x08,
  /* End LOG Class MsgId's */
  } T_ZF9P_e_MessageId;

/* ========== End enums ================== */

/* ========== Begin Structures ================== */

/* This is a c library but we'll go about it is a relatively object oriented 
 * fasion */
typedef struct T_ZF9P_s_ModuleConfig 
  {
  T_ZF9P_e_CommsMethod commsMethod;
  uint8_t sdaPin;
  uint8_t clockPin;
  uint8_t misoPin;
  uint8_t mosiPin;
  uint8_t chipSelectPin;
  uint32_t baudRate;
  } T_ZF9P_s_ModuleConfig;

typedef struct T_ZF9P_s_UbxMessage
  {
  uint8_t preambleCharacter1;
  uint8_t preambleCharacter2;
  uint8_t messageClass;
  uint8_t messageID;
  uint16_t messageLength;
  uint8_t *messagePayload;
  uint8_t checksumByteA;
  uint8_t checksumByteB;
  } T_ZF9P_s_UbxMessage;

/* ========== End Structures ================== */



/* =============== Begin Functions ================ */

/* Different Simplified Setups */
bool SimpleSetupZedf9p(T_ZF9P_s_ModuleConfig *_moduleConfig);
bool SimpleSetupSurveyInBase(T_ZF9P_s_ModuleConfig *_moduleConfig, uint32_t _time, uint32_t _accuracy);

/* Functions that refactor common/series-of commands */
void SetUbxBaseSettings();

/* Lower level module functions */
void SetUbxZedf9pSetting(T_ZF9P_e_Setting _setting, uint32_t _value);
void SendUbxMessage();

/* ============= End Functions ===================== */
#endif
