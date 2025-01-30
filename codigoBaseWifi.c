#include <WiFi.h>
#include <PubSubClient.h>

// Configura aquí tu SSID y tu contraseña de la red
const char *ssid = "2DAW_IoT";
const char *password = "Somos2DAW";

// Configura aquí tu servidor de mqtt, puerto contraseña y topic de comunicación que usaremos más adelante
const char *mqtt_server = "ha.ieshm.org";
const int mqtt_port = 1883;
const char *mqtt_user = "mqtt";
const char *mqtt_password = "mqtt";
const char *mqtt_topic = "g6/rele";

WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi()
{
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

    // Es importante configurar el serial adecuado para que la salida aparezca en el IDE
    Serial.begin(115200);
    setup_wifi();
    client.setServer(mqtt_server, mqtt_port);
}

void loop()
{
    if (!client.connected())
    {
        reconnect();
    }
    client.loop();
}