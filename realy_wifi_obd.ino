#include <ESP8266WiFi.h>
#define LED D1
#define LED2 D0
const char* ssid = "Robo";
const char* password = "lopklopk";
unsigned char status_led=0;
unsigned char status_led2=0;
//IPAddress ip(192, 168, 43, 238); //set static ip
//IPAddress gateway(192, 168, 0, 1); //set getteway
IPAddress subnet(255, 255, 255, 0);//set subnet
WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  pinMode(LED, OUTPUT);
    pinMode(LED2, OUTPUT);
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
 // WiFi.config(ip, gateway, subnet);
  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  server.begin();
  Serial.println("Server started");
  Serial.println(WiFi.localIP());
}

void loop() {
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  
  Serial.println("new client");
  while(!client.available())
  {
    
    delay(1);
    
  }
  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();
  if (req.indexOf("/ledoff") != -1)
  {
    status_led=0;   
    digitalWrite(LED,LOW);
    Serial.println("LED OFF");
  }
  else if(req.indexOf("/ledon") != -1)
  {
    status_led2=1;
    digitalWrite(LED,HIGH);
    Serial.println("LED ON");
  }
  
  if (req.indexOf("/led2off") != -1)
  {
    status_led2=0;   
    digitalWrite(LED2,LOW);
    Serial.println("LED2 OFF");
  }
  else if(req.indexOf("/led2on") != -1)
  {
    status_led=1;
    digitalWrite(LED2,HIGH);
    Serial.println("LED2 ON");
  }
  String web = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
  web += "<html>\r\n";
  web += "<body>\r\n";
  web += "<h1>LED Status</h1>\r\n";
  web += "<p>\r\n";
  if(status_led==1)
      web += "LED On\r\n";
  else
      web += "LED Off\r\n";
       if(status_led2==1)
      web += "LED2 On\r\n";
  else
      web += "LED2 Off\r\n";
  web += "</p>\r\n";
  web += "</p>\r\n";
  web += "<a href=\"/ledon\">\r\n";
  web += "<button>LED On</button >\r\n";

    web += "<a href=\"/led2on\">\r\n";
  web += "<button>LED2 On</button >\r\n";
  web += "</a>\r\n";
  web += "</p>\r\n";
  
  web += "<a href=\"/ledoff\">\r\n";
  web += "<button>LED Off</button >\r\n";
  
  web += "<a href=\"/led2off\">\r\n";
  web += "<button>LED2 Off</button >\r\n";
  web += "</a>\r\n";
  
  web += "</body>\r\n";
  web += "</html>\r\n";
  
  client.print(web);
}
