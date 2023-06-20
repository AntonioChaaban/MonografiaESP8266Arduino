#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <WiFiClient.h>

const char* ssid = "LocationConnection";
const char* password = "12345678";
const char* nameAp = "AP5";

const char* serverName = "/tcp-data";

void setup() {

  Serial.begin(115200);

  Serial.println("Conectando-se à rede WiFi...");

  // Substitua "NomeDaRede" e "SenhaDaRede" pelas informações da sua rede WiFi
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Ainda não conectado...");
  }
  Serial.println("Conectado à rede WiFi!");
  Serial.println(WiFi.localIP());
}

void loop() {
  // put your main code here, to run repeatedly:
  WiFiClient client;
  HTTPClient http;

  StaticJsonDocument<500> doc;
  JsonArray clientArray = doc.createNestedArray("clients");
  JsonObject clientObject = clientArray.createNestedObject();
  clientObject["AP"] = nameAp;
  clientObject["RSSI"] = WiFi.RSSI();
  clientObject["FREQUENCIA"] = WiFi.channel() * 5 + 2400;
  int aux = WiFi.channel() * 5 + 2400;

  String jsonString;
  serializeJson(doc, jsonString);
  Serial.println(WiFi.RSSI());
  Serial.println(aux);


  // Your Domain name with URL path or IP address with path
  http.begin(client, serverName);
  http.addHeader("Content-Type", "application/json");
  int httpResponseCode = http.POST(jsonString);
  Serial.print("HTTP Response code: ");
  Serial.println(httpResponseCode);
  http.end();

}
