#include "gps/zedf9p.h"

void InitializeZedf9pObject(T_ZF9P_s_ModuleConfig *_module)
  {
  _module->sdaPin = 0xFF;
  _module->clockPin = 0xFF;
  _module->misoPin = 0xFF;
  _module->mosiPin = 0xFF;
  _module->chipSelectPin = 0xFF;
  _module->baudRate = 0xFFFFFFFF;
  _module->commsMethod = uninitialized;
  }

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
  SetUbxZedf9pSetting(UBX_RTCM_1124, 1);
  SetUbxZedf9pSetting(UBX_RTCM_1230, 10);
  }

void SetUbxZedf9pSetting(T_ZF9P_e_Setting _setting, uint32_t _value)
  {
  T_ZF9P_s_UbxMessage ubxMessage;
  ubxMessage.preambleCharacter1 = 0xB5;
  ubxMessage.preambleCharacter2 = 0x62;
  //ubxMessage.messageClass = ;
  }

void SendUbxMessage(T_ZF9P_s_ModuleConfig *_module, uint16_t _ubxMessage, uint8_t *_payload, uint16_t _length)
  {
  uint8_t* ubxFrame = malloc(sizeof(uint8_t) * (_length + 8));
  uint8_t byte = 0;
  uint8_t checksumA = 0;
  uint8_t checksumB = 0;
  ubxFrame[byte] = 0xB5;
  ubxFrame[++byte] = 0x62;
  ubxFrame[++byte] = (_ubxMessage & 0xFF00) >> 8;
  checksumA += ubxFrame[byte];
  checksumB += checksumA;
  ubxFrame[++byte] = (_ubxMessage & 0x00FF);
  checksumA += ubxFrame[byte];
  checksumB += checksumA;
  ubxFrame[++byte] = (_length & 0x00FF);
  checksumA += ubxFrame[byte];
  checksumB += checksumA;
  ubxFrame[++byte] = (_length & 0xFF00) >> 8;
  checksumA += ubxFrame[byte];
  checksumB += checksumA;
  for (int i = 0; i < _length; i++)
    {
    ubxFrame[++byte] = _payload[i];
    checksumA += ubxFrame[byte];
    checksumB += checksumA;
    }
  ubxFrame[++byte] = checksumA;
  ubxFrame[++byte] = checksumB;

  /* Here we send the message */

  free(ubxFrame);
  }
