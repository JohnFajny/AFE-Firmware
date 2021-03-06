/* AFE Firmware for smart home devices
  LICENSE: https://github.com/tschaban/AFE-Firmware/blob/master/LICENSE
  DOC: http://smart-house.adrian.czabanowski.com/afe-firmware-pl/ */

#include "AFE-Defaults.h"

AFEDefaults::AFEDefaults() {}

void AFEDefaults::set() {

  AFEDataAccess *Data;

  DEVICE deviceConfiguration;
  FIRMWARE firmwareConfiguration;
  NETWORK networkConfiguration;
  MQTT MQTTConfiguration;
  RELAY RelayConfiguration;
  SWITCH SwitchConfiguration;
  CONTACTRON ContactronConfiguration;
  LED LEDConfiguration;
  GATE GateConfiguration;
  DH DHTConfiguration;

  sprintf(firmwareConfiguration.version, FIRMWARE_VERSION);
  firmwareConfiguration.type = FIRMWARE_TYPE;
  firmwareConfiguration.autoUpgrade = 0;
  sprintf(firmwareConfiguration.upgradeURL, "");

  Data->saveConfiguration(firmwareConfiguration);

  // Serial << endl << "firmwareConfiguration";
  sprintf(deviceConfiguration.name, "AFE-Device");

  deviceConfiguration.isLED[0] = true;
  for (uint8_t i = 1; i < sizeof(deviceConfiguration.isLED); i++) {
    deviceConfiguration.isLED[i] = false;
  }

  deviceConfiguration.isSwitch[0] = true;
  for (uint8_t i = 1; i < sizeof(deviceConfiguration.isSwitch); i++) {
    deviceConfiguration.isSwitch[i] = false;
  }

  deviceConfiguration.isRelay[0] = true;

  deviceConfiguration.isContactron[0] = true;
  for (uint8_t i = 1; i < sizeof(deviceConfiguration.isContactron); i++) {
    deviceConfiguration.isContactron[i] = false;
  }

  deviceConfiguration.isDHT = false;
  deviceConfiguration.mqttAPI = false;
  deviceConfiguration.httpAPI = true;

  Data->saveConfiguration(deviceConfiguration);

  sprintf(networkConfiguration.ssid, "");
  sprintf(networkConfiguration.password, "");
  networkConfiguration.isDHCP = true;
  networkConfiguration.ip = IPAddress(0, 0, 0, 0);
  networkConfiguration.gateway = IPAddress(0, 0, 0, 0);
  networkConfiguration.subnet = IPAddress(255, 255, 255, 0);
  networkConfiguration.noConnectionAttempts = 10;
  networkConfiguration.waitTimeConnections = 1;
  networkConfiguration.waitTimeSeries = 60;

  Data->saveConfiguration(networkConfiguration);
  //  Serial << endl << "networkConfiguration";

  sprintf(MQTTConfiguration.host, "");
  MQTTConfiguration.ip = IPAddress(0, 0, 0, 0);
  sprintf(MQTTConfiguration.user, "");
  sprintf(MQTTConfiguration.password, "");
  MQTTConfiguration.port = 1883;
  sprintf(MQTTConfiguration.topic, "/device/");

  Data->saveConfiguration(MQTTConfiguration);

  RelayConfiguration.timeToOff = 200;
  RelayConfiguration.gpio = 12;
  Data->saveConfiguration(0, RelayConfiguration);

  SwitchConfiguration.type = 0;
  SwitchConfiguration.sensitiveness = 50;
  SwitchConfiguration.gpio = 0;
  SwitchConfiguration.functionality = 0;
  SwitchConfiguration.relayID = 1;
  for (uint8_t i = 0; i < sizeof(deviceConfiguration.isSwitch); i++) {
    Data->saveConfiguration(i, SwitchConfiguration);
  }

  LEDConfiguration.gpio = 13;
  LEDConfiguration.changeToOppositeValue = false;
  for (uint8_t i = 0; i < sizeof(deviceConfiguration.isLED); i++) {
    Data->saveConfiguration(i, LEDConfiguration);
  }

  ContactronConfiguration.gpio = 14;
  ContactronConfiguration.outputDefaultState = CONTACTRON_NO;
  ContactronConfiguration.ledID = 0;
  ContactronConfiguration.bouncing = 200;
  for (uint8_t i = 0; i < sizeof(deviceConfiguration.isContactron); i++) {
    sprintf(ContactronConfiguration.name, "C%d", i + 1);
    Data->saveConfiguration(i, ContactronConfiguration);
  }

  DHTConfiguration.gpio = 14;
  DHTConfiguration.type = 1;
  DHTConfiguration.sendOnlyChanges = 1;
  DHTConfiguration.temperature.correction = 0;
  DHTConfiguration.temperature.interval = 60;
  DHTConfiguration.temperature.unit = 0;
  DHTConfiguration.humidity.correction = 0;
  DHTConfiguration.humidity.interval = 60;

  Data->saveConfiguration(DHTConfiguration);

  GateConfiguration.state[0] = GATE_OPEN;
  GateConfiguration.state[1] = GATE_PARTIALLY_OPEN;
  GateConfiguration.state[2] = GATE_PARTIALLY_OPEN;
  GateConfiguration.state[3] = GATE_CLOSED;

  Data->saveConfiguration(GateConfiguration);

  Data->saveSystemLedID(1);

  Data->saveDeviceMode(2);
  Data->saveLanguage(1);
}

void AFEDefaults::eraseConfiguration() { Eeprom.erase(); }
