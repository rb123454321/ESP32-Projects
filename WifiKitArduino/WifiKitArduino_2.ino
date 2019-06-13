#include <WiFi.h>

const char* ssid     = "Bura";
const char* password = "darmar123";

WiFiServer server(80);

String header;

void setup() {
  Serial.begin(115200);

  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop(){
  WiFiClient client = server.available(); 

  if (client) {  
    Serial.println("New Client.");  
    String currentLine = "";        
    while (client.connected()) {   
      if (client.available()) {   
        char c = client.read();    
        Serial.write(c);    
        header += c;
        if (c == '\n') {    
		
          if (currentLine.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
            if (header.indexOf("GET /up") >= 0) {
            client.println("<!DOCTYPE html><html>");
            
            client.println();
			
            break;
          } else { 
            currentLine = "";
          }
        } else if (c != '\r') {  
          currentLine += c;
        }
      }
    }
	
    header = "";
	
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}