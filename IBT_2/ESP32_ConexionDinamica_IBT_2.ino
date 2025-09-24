#include <Arduino.h>
#include "ConexionHandler.h"
#include "OrdenHandler.h"
#include "Logger.h"
#include "ConfigManager.h"
//#include <LittleFS.h>


ModoConexion modoActual = USB;


void setup() {
  Serial.begin(115200);
  // if (!LittleFS.begin(true)) {
  //   Serial.println("❌ Error al montar LittleFS");
  //   return;
  // }
  // Serial.println("✅ LittleFS montado correctamente");
  // listarArchivos();
  Logger::init();
  ConfigManager::begin();
  ConexionHandler::init();

  Logger::log("⏳ Esperando configuración por USB (5s)");

  unsigned long startTime = millis();
  bool configurado = false;

  while (millis() - startTime < 5000) {
    ConexionHandler::checkUSB(modoActual);
    if (modoActual != USB) {
      configurado = true;
      break;
    }
  }

  if (!configurado) {
    Logger::log("🔁 No se recibió configuración. Recuperando modo guardado...");
    String modoGuardado = ConfigManager::getModo();

    if (modoGuardado == "wifi") {
      modoActual = WIFI;
      ConexionHandler::reconectarWiFi();
    } else if (modoGuardado == "bluetooth") {
      modoActual = BLUETOOTH;
      ConexionHandler::reconectarBluetooth();
    } else {
      Logger::log("⚠️ No hay configuración previa. Quedando en modo USB.");
      modoActual = USB;
    }
  }
}

void loop() {
  if (modoActual == USB) {
    ConexionHandler::checkUSB(modoActual);
  } else if (modoActual == WIFI) {
    ConexionHandler::handleWiFi();
  } else if (modoActual == BLUETOOTH) {
    ConexionHandler::handleBluetooth();
  }
}
