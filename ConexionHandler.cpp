#include "ConexionHandler.h"
#include "OrdenHandler.h"
#include "Logger.h"
#include "Utils.h"
#include "ConfigManager.h"
#include <WiFi.h>
#include <WebServer.h>
#include <BluetoothSerial.h>
#include <ArduinoJson.h>
#include <LittleFS.h>


WebServer server(8080);
BluetoothSerial SerialBT;
String bufferUSB;

void ConexionHandler::init() {}

void ConexionHandler::checkUSB(ModoConexion &modo) {
  while (Serial.available()) {
    char c = Serial.read();
    if (c == '\n') {
      bufferUSB.trim();
      if (bufferUSB.length()) {
        Logger::log("📥 JSON por USB: " + bufferUSB);
        StaticJsonDocument<256> doc;
        DeserializationError err = deserializeJson(doc, bufferUSB);
        if (!err) {
          String tipo = doc["tipo"];
          if (tipo == "conexion") {
            String nuevoModo = doc["modo"];
            ConfigManager::saveModo(nuevoModo);

            if (nuevoModo == "wifi") {
              String ssid = doc["ssid"];
              String pass = doc["password"];
              ConfigManager::saveWiFi(ssid, pass);
              WiFi.begin(ssid.c_str(), pass.c_str());
              Logger::log("🌐 Conectando a Wi-Fi...");
              while (WiFi.status() != WL_CONNECTED) {
                delay(500);
                Serial.print(".");
              }
              Logger::log("✅ Wi-Fi conectado: " + WiFi.localIP().toString());

              // Servir página HTML desde SPIFFS
              // server.on("/", HTTP_GET, []() {
              //   File file = LittleFS.open("/index.html", "r");
              //   if (!file) {
              //     server.send(404, "text/plain", "Archivo no encontrado");
              //     return;
              //   }
              //   server.streamFile(file, "text/html");
              //   file.close();
              // });

              // Recibir órdenes por HTTP
              server.on("/orden", HTTP_POST, []() {
                String body = server.arg("plain");
                Logger::log("📨 JSON por Wi-Fi: " + body);
                OrdenHandler::procesarOrden(body);
                server.sendHeader("Access-Control-Allow-Origin", "*");
                server.send(200, "application/json", "{\"status\":\"ok\"}");
              });

              server.begin();
              modo = WIFI;

            } else if (nuevoModo == "bluetooth") {
              String nombre = doc["nombre"] | "ESP32_BT";
              ConfigManager::saveBluetoothName(nombre);
              SerialBT.begin(nombre);
              Logger::log("🔷 Bluetooth iniciado como: " + nombre);
              Logger::log("📡 MAC Bluetooth: " + getBluetoothMAC());
              modo = BLUETOOTH;
            }

          } else if (tipo == "orden") {
            OrdenHandler::procesarOrden(bufferUSB);

          } else if (tipo == "reset") {
            ConfigManager::clear();
            Logger::log("🧹 Configuración borrada");
          }

        } else {
          Logger::log("❌ Error de JSON por USB");
        }
      }
      bufferUSB = "";
    } else {
      bufferUSB += c;
    }
  }
}

void ConexionHandler::handleWiFi() {
  server.handleClient();
}

void ConexionHandler::handleBluetooth() {
  static String bufferBT;
  while (SerialBT.available()) {
    char c = SerialBT.read();
    if (c == '\n') {
      bufferBT.trim();
      if (bufferBT.length()) {
        Logger::log("📨 JSON por Bluetooth: " + bufferBT);
        OrdenHandler::procesarOrden(bufferBT);
      }
      bufferBT = "";
    } else {
      bufferBT += c;
    }
  }
}

void ConexionHandler::reconectarWiFi() {
  Logger::log("🔄 Reconectando Wi-Fi...");
  String ssid = ConfigManager::getSSID();
  String pass = ConfigManager::getPassword();
  WiFi.begin(ssid.c_str(), pass.c_str());
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Logger::log("✅ Wi-Fi reconectado: " + WiFi.localIP().toString());

  // Servir página HTML desde SPIFFS
  // server.on("/", HTTP_GET, []() {
  //   File file = LittleFS.open("/index.html", "r");
  //   if (!file) {
  //     server.send(404, "text/plain", "Archivo no encontrado");
  //     return;
  //   }
  //   server.streamFile(file, "text/html");
  //   file.close();
  // });

  // Recibir órdenes por HTTP
  server.on("/orden", HTTP_POST, []() {
    String body = server.arg("plain");
    Logger::log("📨 JSON por Wi-Fi: " + body);
    OrdenHandler::procesarOrden(body);
    server.sendHeader("Access-Control-Allow-Origin", "*");
    server.send(200, "application/json", "{\"status\":\"ok\"}");
  });

  server.begin();
}

void ConexionHandler::reconectarBluetooth() {
  Logger::log("🔄 Reconectando Bluetooth...");
  String nombre = ConfigManager::getBluetoothName();
  SerialBT.begin(nombre);
  Logger::log("📡 MAC Bluetooth: " + getBluetoothMAC());
}
