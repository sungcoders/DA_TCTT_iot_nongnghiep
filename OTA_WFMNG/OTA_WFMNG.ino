/*
  DISIGN BY SCDT K$@ 
  TRY YOUR BEST.
 */
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <ESP8266HTTPUpdateServer.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
#include <PubSubClient.h>

const char* host = "IOT_Agriculture";
const char* updatePath = "/update";
const char* updateUsername = "admin";
const char* updatePassword = "admin";
const char* mqtt_server = "mohinhrauthuycanh.ddns.net";
char const* ssidname ="ESP_WFCNF01";
char const* ssidpass ="12345678";
IPAddress staticIP(192,168,1,145);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);
IPAddress dns1(8,8,8,8);
IPAddress dns2(8,8,4,4);

WiFiClient espClient;
PubSubClient client(espClient);
ESP8266WebServer webServer(8484);
ESP8266HTTPUpdateServer httpUpdater;

unsigned long t1;
const char MainPage[] PROGMEM = R"=====(
  <!DOCTYPE html>
  <html>
   <head>
       <title>IOT Agriculture</title> 
       <style> 
          body{
            text-align: center;
          }
       </style>
       <meta name="viewport" content="width=device-width,user-scalable=0" charset="UTF-8">
   </head>
   <body> 
      <div>
        <img src='https://bkaii.com.vn/images/mqtt-iot.jpg' height='400px' width='660px'>
      </div>
      <div>
        <button onclick="window.location.href='/update'">LOGIN UPLOAD FIRMWARE</button><br><br>
        <a href='https://arduino.esp8266.vn/'>Đến Trang Chủ - HOME</a>
      </div>
      <script>
      </script>
   </body> 
  </html>
)=====";

void setup(void)
{
  Serial.begin(115200);
  pinMode(D4,OUTPUT);
  WiFi.config(staticIP,gateway,subnet,dns1,dns2);
  while(WiFi.waitForConnectResult() != WL_CONNECTED)
  {
    digitalWrite(D4,LOW);
    WiFiManager wifiManager;
    wifiManager.autoConnect(ssidname,ssidpass);
  }
  digitalWrite(D4,HIGH);
  Serial.print(F("WIFI CONNECTED\nIP address: "));
  Serial.println(WiFi.localIP());
  MDNS.begin(host);
  MDNS.addService("http", "tcp", 8484);

  httpUpdater.setup(&webServer, updatePath, updateUsername, updatePassword);
  webServer.on("/",[]{
    String s = MainPage;
    webServer.send(200,"text/html",s);
  });
  webServer.begin();
  Serial.println("Web Server is started!");

  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop(void)
{
  while(WiFi.waitForConnectResult() != WL_CONNECTED)
  {
    digitalWrite(D4,LOW);
    WiFiManager wifiManager;
    wifiManager.autoConnect(ssidname,ssidpass);
    digitalWrite(D4,HIGH);
  }
  if (!client.connected())  { reconnect(); }
  MDNS.update();
  webServer.handleClient();
  client.loop();
  if(millis()-t1>=2000)
  {
    client.publish("outTopic","34679");
    t1=millis();
    Serial.println("da gui");
  }
}
