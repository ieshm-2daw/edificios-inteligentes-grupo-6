#include <WiFi.h>
#include <PubSubClient.h>

const char *ssid = "2DAW_IoT";
const char *password = "Somos2DAW";

const char *mqtt_server = "ha.ieshm.org";
const int mqtt_port = 1883;
const char *mqtt_user = "mqtt";
const char *mqtt_password = "mqtt";
const char *mqtt_topic = "g6/rele";

#define LED_BUILTIN 2
#define RELAY_PIN 26

WiFiClient espClient;
PubSubClient client(espClient);
String receivedMessage = "";

void setup_wifi()
{
    delay(10);
    Serial.println("Conectando a Wi-Fi...");
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        Serial.print(".");
    }
    Serial.println("\nWi-Fi conectado.");
    Serial.print("Dirección IP: ");
    Serial.println(WiFi.localIP());
}

void callback(char *topic, byte *payload, unsigned int length)
{
    String message = "";
    for (unsigned int i = 0; i < length; i++)
    {
        message += (char)payload[i];
    }
    receivedMessage = message;
    Serial.print("Mensaje recibido: ");
    Serial.println(receivedMessage);
}

void reconnect()
{
    while (!client.connected())
    {
        Serial.print("Intentando conectar al broker MQTT...");
        if (client.connect("ESP32", mqtt_user, mqtt_password))
        {
            Serial.println("Conectado.");
            client.subscribe(mqtt_topic);
        }
        else
        {
            Serial.print("Fallo en la conexión, código de error: ");
            Serial.print(client.state());
            Serial.println(" Reintentando en 5 segundos...");
            delay(5000);
        }
    }
}

void setup()
{
    Serial.begin(115200);

    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(RELAY_PIN, OUTPUT);

    setup_wifi();
    client.setServer(mqtt_server, mqtt_port);
    client.setCallback(callback);

    digitalWrite(RELAY_PIN, LOW);
    Serial.println("Relé configurado y apagado.");
    digitalWrite(LED_BUILTIN, LOW);
    Serial.println("LED configurado y apagado.");
}

void loop()
{
    if (!client.connected())
    {
        reconnect();
    }
    client.loop();

    if (receivedMessage == "ON")
    {
        Serial.println("Encendiendo relé...");
        digitalWrite(RELAY_PIN, HIGH);
        Serial.println("Encendiendo LED...");
        digitalWrite(LED_BUILTIN, HIGH);
    }
    else if (receivedMessage == "OFF")
    {
        Serial.println("Apagando relé...");
        digitalWrite(RELAY_PIN, LOW);
        Serial.println("Apagando LED...");
        digitalWrite(LED_BUILTIN, LOW);
    }
}