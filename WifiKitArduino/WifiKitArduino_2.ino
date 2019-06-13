#include <WiFi.h>

const char* ssid     = "Bura";
const char* password = "darmar123";

WiFiServer server(80);

String header;

void send_html() {
	client.println("<!DOCTYPE html>");
	client.println("<html lang=\"en\">");
	client.println("<head>");
	client.println("    <meta charset=\"UTF-8\">");
	client.println("    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">");
	client.println("    <meta http-equiv=\"X-UA-Compatible\" content=\"ie=edge\">");
	client.println("    <title>Controller</title>");
	client.println("    <style>");
	client.println("    html { ");
	client.println("        font-family: Helvetica; ");
	client.println("        display: inline-block; ");
	client.println("        margin: 0px auto; ");
	client.println("        text-align: center;");
	client.println("    }");
	client.println("    .gumb {");
	client.println("        font-size: 1.2em;");
	client.println("        color: whitesmoke;");
	client.println("        background-color: rgb(37, 165, 59);");
	client.println("        text-shadow: 2px 2px 1px black;");
	client.println("        padding: 10px;");
	client.println("        margin: 5px;");
	client.println("        text-decoration:none;");
	client.println("    }");
	client.println("    </style>");
	client.println("    <h1>Controller</h1>");
	client.println("</head>");
	client.println("<body>");
	client.println("    <a class=\"gumb\" href=\"/up\">UP</a> <br><br><br>");
	client.println("    <a class=\"gumb\" href=\"/left\">LEFT</a>");
	client.println("    <a class=\"gumb\" href=\"/right\">RIGHT</a><br><br><br>");
	client.println("    <a class=\"gumb\" href=\"/down\">DOWN</a> ");
	client.println("</body>");
}

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
            
            if (header.indexOf("GET /hello") >= 0) {
				send_html();
			}
			else if(header.indexOf("GET /up") >= 0) {
				send_html();
			}
			else if(header.indexOf("GET /down") >= 0) {
				send_html();
			}
			else if(header.indexOf("GET /left") >= 0) {
				send_html();
			}
			else if(header.indexOf("GET /right") >= 0) {
				send_html();
			}
			
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