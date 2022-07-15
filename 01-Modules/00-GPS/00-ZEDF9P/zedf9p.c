#include "gps/zedf9p.h"

bool SimpleSetupZedf9p(T_ZF9P_s_ModuleConfig *_moduleConfig)
  {
  bool retVal;
  uint32_t actualBaudRate = 0;
  uint32_t desiredBaudRate = 0;

  switch (_moduleConfig->commsMethod)
    {
    case i2c:
      actualBaudRate = SetupI2cBus(_moduleConfig->sdaPin, _moduleConfig->clockPin, _moduleConfig->baudRate);
      desiredBaudRate = _moduleConfig->baudRate;
      break;
    case spi:
      retVal = false;
      break;
    default:
      return false;
    }
  if (abs(actualBaudRate - desiredBaudRate) > (desiredBaudRate / 10))
    {
    retVal = false;
    }
  else
    {
    retVal = true;
    }
  return retVal;
  }

bool SimpleSetupSurveyInBase(T_ZF9P_s_ModuleConfig *_moduleConfig, uint32_t _time, uint32_t _accuracy)
  {
  /* First we do the setup of the module on the respective comms bus */
  if(!SimpleSetupZedf9p(_moduleConfig))
    {
    return false;
    }
  SetUbxBaseSettings();
  }

void SetUbxBaseSettings()
  {
  SetUbxZedf9pSetting(UBX_RTCM_1005, 1);
  SetUbxZedf9pSetting(UBX_RTCM_1074, 1);
  SetUbxZedf9pSetting(UBX_RTCM_1084, 1);
  SetUbxZedf9pSetting(UBX_RTCM_1094, 1);
  SetUbxZedf9pSetting(UBX_RTCM_11124, 1);
  SetUbxZedf9pSetting(UBX_RTCM_1230, 10);
  }

void SetUbxZedf9pSetting(T_ZF9P_e_Setting _setting, uint32_t _value)
  {
  }
