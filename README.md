# Edificios inteligentes

## Tutorial: Conexión de Sensores a ESP32 con Arduino y MQTT

## 1. Introducción

En este tutorial aprenderemos a conectar diversos dispositivos para crear un entorno domótico en el que se maximizan diversas áreas y optimizan procesos tales como la seguridad, eficiencia , comodidad y sostenible.

## 2. Materiales Necesarios

Lista de todo lo que necesitaréis:

- ESP32.
- Sensores (en este caso emplearemos un relé digital , un sensor KY-038 (sonido) , una cerradura electrónica).
- Protoboard y cables.
- Software: Arduino IDE, broker MQTT (p.ej., Mosquitto), etc.
- Ordenador con conexión a Internet.

---

## 3. Preparación del Entorno

### 3.1 Instalación del Arduino IDE

- Descargar el ID de Arduino.
- Dentro de la interfaz debemos seleccionar la Sp32 Dev module.

### 3.2 Instalación de Librerías Necesarias

Lista de librerías que deben instalarse desde el gestor de librerías:

- `PubSubClient` (para MQTT).
- Librerías específicas.

### Código de prueba en arduino

- Este código enciende y apaga un led del propio SP32 periódicamente.

```cpp #define LED_BUILTIN 2

void setup() {
  // El código introducido aquí se ejecuta al inicio

  pinMode(LED_BUILTIN, OUTPUT);

}

void loop() {
  // El código introducido aquí se repite contínuamente

  digitalWrite(LED_BUILTIN, HIGH);
  delay(2000);
  digitalWrite(LED_BUILTIN, LOW);
  delay(2000);

}
```

---

## 4. Conexión de los Sensores

### 4.1 Esquema de Conexión

- Explica cómo conectar los sensores a la ESP32.
- Incluye un diagrama visual (puedes usar Fritzing o dibujarlo).

### 4.2 Tabla de Pines

| Sensor       | Pin de Datos | Pin de Alimentación | Otros Pines |
| ------------ | ------------ | ------------------- | ----------- |
| **Sensor 1** | GPIO XX      | 3.3V                | GND         |
| **Sensor 2** | GPIO XX      | 5V                  | GND         |

---

## 5. Configuración del MQTT

### 5.1 Configuración del Broker MQTT

- Explicación breve sobre el broker MQTT.
- Instalación y configuración de Mosquitto (u otra opción).

### 5.2 Configuración del Broker MQTT

- Explicación breve sobre el broker MQTT.
- Instalación y configuración de Mosquitto (u otra opción).

### 5.3 Configuración de la ESP32

- Cómo definir la conexión al WiFi.
- Configuración del cliente MQTT en el código.

---

## 6. Código Arduino

En esta sección, abordaremos el código necesario para la integración de los sensores y actuadores en la **ESP32**, utilizando **MQTT** para la comunicación con el sistema.

### Sensores y Actuadores Utilizados

A continuación, se detallan los sensores y actuadores empleados, junto con los pines de conexión en la **ESP32**:

| Componente            | Descripción                                                      |
| --------------------- | ---------------------------------------------------------------- |
| **Relé digital**      | Activa o desactiva el paso de corriente según una señal digital. |
| **Sensor KY-038**     | Detecta niveles de ruido de forma analógica o digital.           |
| **Cerradura digital** | Permite gestionar accesos abriendo o cerrando una cerradura.     |
| **RFID RC522**        | Autenticación con tarjetas o llaveros RFID.                      |

---

### 6.1 Código Base para la ESP32

Este código configura la conexión **WiFi** y el cliente **MQTT**

```cpp
#include <WiFi.h>
#include <PubSubClient.h>

//Configura aquí tu SSID y tu contraseña de la red
const char* ssid = "2DAW_IoT";
const char* password = "Somos2DAW";

//Configura aquí tu servidor de mqtt, puerto contraseña y topic de comunicación que usaremos más adelante
const char* mqtt_server = "ha.ieshm.org";
const int mqtt_port = 1883;
const char* mqtt_user = "mqtt";
const char* mqtt_password = "mqtt";
const char* mqtt_topic = "g6/rele";

WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi() {
  Serial.println("Conectando a Wi-Fi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nWi-Fi conectado.");
  Serial.print("Dirección IP: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Intentando conectar al broker MQTT...");
    if (client.connect("ESP32", mqtt_user, mqtt_password)) {
      Serial.println("Conectado.");
      client.subscribe(mqtt_topic);
    } else {
      Serial.print("Fallo en la conexión, código de error: ");
      Serial.print(client.state());
      Serial.println(" Reintentando en 5 segundos...");
      delay(5000);
    }
  }
}

void setup() {

  //Es importante configurar el serial adecuado para que la salida aparezca en el IDE
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}

```

### 6.2 Explicación de cada uno de los sensores

- Cómo se formatean los datos de los sensores.
- Tópicos MQTT utilizados.

---

## 7. Pruebas y Verificación

### 7.1 Verificación de la Conexión WiFi

- Cómo verificar que la ESP32 está conectada al WiFi.

### 7.2 Monitorización de Datos en el Broker MQTT

- Cómo suscribirse a los tópicos usando herramientas como MQTT Explorer o `mosquitto_sub`.

### 7.3 Solución de Problemas Comunes

- Problemas de conexión WiFi.
- Problemas al publicar datos.

---

## 8. Ampliaciones y Mejoras

- Ideas para expandir el proyecto, como agregar más sensores o actuar sobre los datos recibidos.

---

## 9. Recursos y Enlaces de Interés

- Enlaces a documentación oficial.
- Recursos para aprender más sobre MQTT, ESP32 y Arduino.

---

## 10. Licencia

- Información sobre cómo otros pueden usar o modificar tu tutorial.
