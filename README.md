El ESP32 al iniciarse aguarda durante 5 segundos instrucciones de como recibira las ordenes para el motor, esta configuracion es persistente.


Via USB por un JSON:

{"tipo": "reset"}

Via WIFI por un JSON:

{"tipo": "conexion","modo": "wifi","ssid": "UA-Alumnos","password": "41umn05WLC"}

Via Bluetooth por un JSON:

{"tipo":"conexion","modo":"bluetooth","nombre":"ESP32_BT"}


Para hacer funcionar el motor 1 por USB enviar:

{"tipo": "orden","subtipo": "motor","motor": 1,"accion": "adelante","velocidad": 120}
{"tipo": "orden","subtipo": "motor","motor": 1,"accion": "parar","velocidad": 120}
{"tipo": "orden","subtipo": "motor","motor": 1,"accion": "atras","velocidad": 120}

Para hacer funcionar el motor por WIFI enviar por curl:

curl -X POST http://172.22.46.68:8080/orden -H "Content-Type: application/json" -d "{\"tipo\":\"orden\",\"subtipo\":\"motor\",\"motor\":1,\"accion\":\"parar\",\"velocidad\":120}"

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

curl -X POST http://172.22.46.68:8080/orden -H "Content-Type: application/json" --data "@motor.json"
