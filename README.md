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

| Sensor          | Pin de Datos | Pin de Alimentación | Otros Pines |
|------------------|--------------|---------------------|-------------|
| **Sensor 1**    | GPIO XX      | 3.3V                | GND         |
| **Sensor 2**    | GPIO XX      | 5V                  | GND         |

---

## 5. Configuración del MQTT

### 5.1 Configuración del Broker MQTT

- Explicación breve sobre el broker MQTT.
- Instalación y configuración de Mosquitto (u otra opción).

### 5.2 Configuración de la ESP32

- Cómo definir la conexión al WiFi.
- Configuración del cliente MQTT en el código.

---

## 6. Código Arduino

### 6.1 Código Base para la ESP32

- Explica las partes principales del código:
  - Conexión WiFi.
  - Configuración del cliente MQTT.
  - Lógica para leer los sensores y publicar los datos.

Incluye el código comentado línea por línea.

### 6.2 Explicación de la Publicación de Datos

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
