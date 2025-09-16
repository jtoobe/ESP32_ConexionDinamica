Para compilar el script se debera usar la opcion en la ide de Arduino: Tools / Partition Scheme => Huge APP (3MB No OTA/ 1MB SPIFFS)

Los pines del Puente L298N se deberan conectar de esta forma:

Motor 1: ena 33, en1 32, en2 25

Motor 2: enab 26, en3 27, en4 14

( ver pinout L298N en https://github.com/jtoobe/ESP32_L298N/blob/main/l298n.JPG )

El ESP32 al iniciarse aguarda durante 5 segundos en el puerto USB instrucciones de como recibira en lo sucesivo las ordenes para el motor, esta configuracion es persistente.


Via USB por un JSON:

{"tipo": "reset"}

Via WIFI por un JSON:

{"tipo": "conexion","modo": "wifi","ssid": "xxxxxxxxxx","password": "xxxxxxxxx"}

Via Bluetooth por un JSON:

{"tipo":"conexion","modo":"bluetooth","nombre":"ESP32_BT"}


Para hacer funcionar el motor 1 por USB enviar:

{"tipo": "orden","subtipo": "motor","motor": 1,"accion": "adelante","velocidad": 120}
{"tipo": "orden","subtipo": "motor","motor": 1,"accion": "parar","velocidad": 120}
{"tipo": "orden","subtipo": "motor","motor": 1,"accion": "atras","velocidad": 120}

Para hacer funcionar el motor por WIFI enviar por curl:

curl -X POST http://[IP del ESP32]:8080/orden -H "Content-Type: application/json" -d "{\"tipo\":\"orden\",\"subtipo\":\"motor\",\"motor\":1,\"accion\":\"parar\",\"velocidad\":120}"

y se recibira: {"status":"ok"}

Otra forma con curl:

Definir en un archivo motor.json lo siguiente:

{
  "tipo": "orden",
  "subtipo": "motor",
  "motor": 1,
  "accion": "parar",
  "velocidad": 120
}

e invocarlo con:

curl -X POST http://[IP del ESP32]:8080/orden -H "Content-Type: application/json" --data "@motor.json"

Para hacer funcionar el motor 1 por Bluetooth enviar al COM asignado:

{"tipo": "orden","subtipo": "motor","motor": 1,"accion": "adelante","velocidad": 120}

{"tipo": "orden","subtipo": "motor","motor": 1,"accion": "parar","velocidad": 120}

{"tipo": "orden","subtipo": "motor","motor": 1,"accion": "atras","velocidad": 120}
