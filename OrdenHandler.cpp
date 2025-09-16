#include "OrdenHandler.h"
#include "Logger.h"
#include <ArduinoJson.h>
#include "MotorDC.h"


MotorDC motor1(33, 32, 25);  // Motor 1: ena1, en1, en2
MotorDC motor2(26, 27, 14);  // Motor 2: ena2, en1, en2


void OrdenHandler::procesarOrden(const String& jsonStr) {
  StaticJsonDocument<256> doc;
  DeserializationError err = deserializeJson(doc, jsonStr);
  Logger::log("🔧 Procesando orden: " + jsonStr);

  if (err) {
    Logger::log("❌ Error al parsear orden");
    return;
  }

  String tipo = doc["tipo"];
  String subtipo = doc["subtipo"];
  String accion = doc["accion"];
  int motorID = doc["motor"] | 1;          // por defecto motor 1
  int velocidad = doc["velocidad"] | 100;  // por defecto 100
  Logger::log("⚙️ Ejecutando motor " + String(motorID) + " con acción " + accion + " y velocidad " + String(velocidad));
  if (tipo != "orden" || subtipo != "motor") {
    Logger::log("⚠️ Orden no válida para motor");
    return;
  }

  MotorDC* motorPtr = nullptr;
  if (motorID == 1) {
    motorPtr = &motor1;
  } else if (motorID == 2) {
    motorPtr = &motor2;
  } else {
    Logger::log("⚠️ Motor inválido: " + String(motorID));
    return;
  }

  if (accion == "adelante") {
    motorPtr->adelante(velocidad);
    Logger::log("🚗 Motor " + String(motorID) + " adelante (" + String(velocidad) + ")");
  } else if (accion == "atras") {
    motorPtr->atras(velocidad);
    Logger::log("🚗 Motor " + String(motorID) + " atrás (" + String(velocidad) + ")");
  } else if (accion == "parar") {
    motorPtr->parar();
    Logger::log("🛑 Motor " + String(motorID) + " detenido");
  } else {
    Logger::log("⚠️ Acción desconocida: " + accion);
  }
}
