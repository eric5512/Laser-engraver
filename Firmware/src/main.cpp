#include <ESP8266WiFi.h>
#include "pass.h"

#define MAGIC_NUMBER 0x69
#define PORT 420

WiFiServer server = WiFiServer(PORT);

void setup() {
    Serial.begin(9600);
    Serial.print("Connecting to the router");
    WiFi.begin(SSID, PASS);
    while (WiFi.status() != WL_CONNECTED) { delay(500); Serial.print("."); }
    Serial.println("\nConnected!");
    server.begin();
}

void loop() {
    WiFiClient client = server.accept();
    if (client) {
        while (client.available() <= 0);
        if (((uint8_t)client.read()) != MAGIC_NUMBER) return;
        Serial.println("New client: " + client.remoteIP().toString());

        while (client) {
            if (client.available() > 0) {
                char op = client.read(); // Pong server
                client.write(op);
                // switch (op) {
                // case 0x00:
                //     // TODO: do stuff
                //     break;
                // default:
                //     break;
                // }
            }
        }

        Serial.println("Client disconnected!");
    }
}