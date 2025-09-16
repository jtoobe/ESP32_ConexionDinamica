#pragma once
#include <Arduino.h>

namespace ConfigManager {
  void begin();  // Inicializa Preferences

  void saveModo(const String& modo);
  String getModo();

  void saveWiFi(const String& ssid, const String& password);
  String getSSID();
  String getPassword();

  void saveBluetoothName(const String& nombre);
  String getBluetoothName();

  void clear();  // Borra toda la configuración
}
