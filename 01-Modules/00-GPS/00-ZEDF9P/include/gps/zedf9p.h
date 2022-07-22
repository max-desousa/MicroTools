#ifndef MICRO_TOOLS_GPS_ZEDF9P_H
#define MICRO_TOOLS_GPS_ZEDF9P_H

#include "stdlib.h"
#include "stdio.h"
#include "stdbool.h"
#include "simplePico/i2c.h"



/* ========== Begin enums ================== */

typedef enum
  {
  uninitialized,
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

/* We'll include precompiler definitions for all UBX messages */
#include "msgs_ubx.h"

/* ========== End enums ================== */

/* ========== Begin Structures ================== */

/* This is a c library but we'll go about it is a relatively object oriented 
 * fasion */
typedef struct T_ZF9P_s_ModuleConfig 
  {
  uint8_t sdaPin;
  uint8_t clockPin;
  uint8_t misoPin;
  uint8_t mosiPin;
  uint8_t chipSelectPin;
  uint32_t baudRate;
  T_ZF9P_e_CommsMethod commsMethod;
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
void InitializeZedf9pObject(T_ZF9P_s_ModuleConfig *_module);
bool SimpleSetupZedf9p(T_ZF9P_s_ModuleConfig *_moduleConfig);
bool SimpleSetupSurveyInBase(T_ZF9P_s_ModuleConfig *_moduleConfig, uint32_t _time, uint32_t _accuracy);

/* Functions that refactor common/series-of commands */
void SetUbxBaseSettings();

/* Lower level module functions */
void SetUbxZedf9pSetting(T_ZF9P_e_Setting _setting, uint32_t _value);
void SendUbxMessage(T_ZF9P_s_ModuleConfig *_module, uint16_t _ubxMessage, uint8_t *_payload, uint16_t _length);

/* ============= End Functions ===================== */
#endif
