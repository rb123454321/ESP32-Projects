#include "WiFi.h"
#include "ESPAsyncWebServer.h"
 
const char *ssid = "MyESP32AP";
const char *password = "testpassword";
 
AsyncWebServer server(80);

const char* webpage = R"(<!DOCTYPE html><html lang=\"en\"><head>    <meta charset=\"UTF-8\">    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">    <meta http-equiv=\"X-UA-Compatible\" content=\"ie=edge\">    <title>Controller</title>    <style>    html {         font-family: Helvetica;         display: inline-block;         margin: 0px auto;         text-align: center;    }    .gumb {        font-size: 1.2em;        color: whitesmoke;        background-color: rgb(37, 165, 59);        text-shadow: 2px 2px 1px black;        padding: 10px;        margin: 5px;        text-decoration:none;    }    </style>    <h1>Controller</h1></head><body>    <a class=\"gumb\" href=\"/up\">UP</a> <br><br><br>    <a class=\"gumb\" href=\"/left\">LEFT</a>    <a class=\"gumb\" href=\"/right\">RIGHT</a><br><br><br>    <a class=\"gumb\" href=\"/down\">DOWN</a> </body></html>)";



void setup()
{
  Serial.begin(115200);

  WiFi.softAP(ssid, password);

  Serial.println();
  Serial.print("IP address: ");
  Serial.println(WiFi.softAPIP());

  server.on("/hello", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "text/html", webpage);
  });

  server.on("/up", HTTP_GET, [](AsyncWebServerRequest *request) {
    // Move movement upwards
    Serial.println("You wanted to go UP");
    request->redirect("hello");
  });

  server.on("/right", HTTP_GET, [](AsyncWebServerRequest *request) {
    // Move movement right
    Serial.println("You wanted to go RIGHT");
    request->redirect("hello");
  });

  server.on("/down", HTTP_GET, [](AsyncWebServerRequest *request) {
    // Move movement downwards
    Serial.println("You wanted to go DOWN");
    request->redirect("hello");
  });

  server.on("/left", HTTP_GET, [](AsyncWebServerRequest *request) {
    // Move movement left
    Serial.println("You wanted to go LEFT");
    request->redirect("hello");
  });

  server.begin();
}
 
void loop(){}
