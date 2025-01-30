#include <WiFi.h>
#include <PubSubClient.h>
#include <SPI.h>
#include <MFRC522.h>

const char *ssid = "2DAW_IoT";
const char *password = "Somos2DAW";

const char *mqtt_server = "ha.ieshm.org";
const int mqtt_port = 1883;
const char *mqtt_user = "mqtt";
const char *mqtt_password = "mqtt";
const char *mqtt_topic = "g6/rele";

#define LED_BUILTIN 2
#define RELAY_PIN 26

// Pin RST del RC522
// Pin SDA del RC522

#define RST_PIN 22
#define SS_PIN 21

WiFiClient espClient;
PubSubClient client(espClient);
String receivedMessage = "";

MFRC522 rfid(SS_PIN, RST_PIN);

// Lista de tarjetas RFID autorizadas

const char *authorizedUIDs[] = {"A1B2C3D4", "E5F6G7H8"};
const int authorizedCount = sizeof(authorizedUIDs) / sizeof(authorizedUIDs[0]);

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

bool isAuthorizedUID(String uid)
{
    for (int i = 0; i < authorizedCount; i++)
    {
        if (uid.equals(authorizedUIDs[i]))
        {
            return true;
        }
    }
    return false;
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

    SPI.begin();
    rfid.PCD_Init();
    Serial.println("Inicializando lector RFID...");
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
        Serial.println("Encendiendo relé por MQTT...");
        digitalWrite(RELAY_PIN, HIGH);
        Serial.println("Encendiendo LED por MQTT...");
        digitalWrite(LED_BUILTIN, HIGH);
    }
    else if (receivedMessage == "OFF")
    {
        Serial.println("Apagando relé por MQTT...");
        digitalWrite(RELAY_PIN, LOW);
        Serial.println("Apagando LED por MQTT...");
        digitalWrite(LED_BUILTIN, LOW);
    }

    if (rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial())
    {
        String uid = "";
        for (byte i = 0; i < rfid.uid.size; i++)
        {
            uid += String(rfid.uid.uidByte[i], HEX);
        }
        uid.toUpperCase();
        Serial.print("UID detectado: ");
        Serial.println(uid);

        if (isAuthorizedUID(uid))
        {
            Serial.println("Tarjeta autorizada. Cambiando estado del relé...");
            int currentState = digitalRead(RELAY_PIN);
            digitalWrite(RELAY_PIN, !currentState);

            if (currentState == LOW)
            {
                Serial.println("Encendiendo LED...");
                digitalWrite(LED_BUILTIN, HIGH);
            }
            else
            {
                Serial.println("Apagando LED...");
                digitalWrite(LED_BUILTIN, LOW);
            }
        }
        else
        {
            Serial.println("Tarjeta no autorizada.");
        }

        rfid.PICC_HaltA();
    }
}
