#include "Utils.h"
#include <esp_bt_device.h>

String getBluetoothMAC() {
  const uint8_t* mac = esp_bt_dev_get_address();
  char macStr[18];
  sprintf(macStr, "%02X:%02X:%02X:%02X:%02X:%02X",
          mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
  return String(macStr);
}
