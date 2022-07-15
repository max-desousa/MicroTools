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

/* ========== End Structures ================== */



/* =============== Begin Functions ================ */

/* Different Simplified Setups */
bool SimpleSetupZedf9p(T_ZF9P_s_ModuleConfig *_moduleConfig);
bool SimpleSetupSurveyInBase(T_ZF9P_s_ModuleConfig *_moduleConfig, uint32_t _time, uint32_t _accuracy);

/* Functions that refactor common/series-of commands */
void SetUbxBaseSettings();

/* Lower level module functions */
void SetUbxZedf9pSetting(T_ZF9P_e_Setting _setting, uint32_t _value);

/* ============= End Functions ===================== */
#endif
