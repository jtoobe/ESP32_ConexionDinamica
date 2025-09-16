#include "ConfigManager.h"
#include <Preferences.h>

Preferences prefs;

void ConfigManager::begin() {
  prefs.begin("conexion", false);  // false = lectura/escritura
}

void ConfigManager::saveModo(const String& modo) {
  prefs.putString("modo", modo);
}

String ConfigManager::getModo() {
  return prefs.getString("modo", "usb");
}

void ConfigManager::saveWiFi(const String& ssid, const String& password) {
  prefs.putString("ssid", ssid);
  prefs.putString("pass", password);
}

String ConfigManager::getSSID() {
  return prefs.getString("ssid", "");
}

String ConfigManager::getPassword() {
  return prefs.getString("pass", "");
}

void ConfigManager::saveBluetoothName(const String& nombre) {
  prefs.putString("btname", nombre);
}

String ConfigManager::getBluetoothName() {
  return prefs.getString("btname", "ESP32_BT");
}

void ConfigManager::clear() {
  prefs.clear();
}
