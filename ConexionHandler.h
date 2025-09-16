#pragma once
#include <Arduino.h>

enum ModoConexion { USB, WIFI, BLUETOOTH };

namespace ConexionHandler {
  void init();
  void checkUSB(ModoConexion &modo);
  void handleWiFi();
  void handleBluetooth();
  void reconectarWiFi();
  void reconectarBluetooth();
}
