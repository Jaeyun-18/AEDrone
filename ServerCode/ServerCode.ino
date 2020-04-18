#include <SPI.h>
#include "WizFi250.h"

char ssid[] = "GSSH_Drone";
char pass[] = "0123456789";
int status = WL_IDLE_STATUS;
WiFiServer server(80);
int check = 0; //심전지 센서의 아두이노에서 신호과 왔을 시 드론 조종 코드로 변환된다.
int check1 = 0;
int i,j;
char a[100];
char a_[100];
int pos_H[3];
int pos_D[3];

void printWifiStauts();

void setup()
{
  for (i=0; i<100; i++)
  {
    a[i] = a_[i] = 'x';
  }
  
  Serial.begin(115200);
  WiFi.init();

  if (WiFi.status() == WL_NO_SHIELD)
  {
    Serial.println("WiFi shield not present");
    while (true);
  }

  Serial.print("Attempting to start AP ");
  Serial.println(ssid);
  
  status = WiFi.beginAP(ssid, 10, pass, ENC_TYPE_WPA2_PSK);

  Serial.println("Access point started");
  printWifiStatus();

  server.begin();
  Serial.println("Server started");
}

void loop()
{
  WiFiClient client = server.available();
  if (check == 1)
  {
    
    Serial.println(1);
    if (check1 == 0)
    {
      for (j=0; j<100; j++)
        Serial.println(a[j]);
  
      check1=1;
    }
  }

  else if (client)
  {
    Serial.println("!! New client");
    
    while (client.connected()) 
    {
      if(client.available()) 
      {
        char c = client.read();
        Serial.println(c);
        a[i] = c;
        i++;
        
        if(c == 'a') break;
      }
    }
    client.stop();
    check=1;
    Serial.print(check);
    Serial.println("Client disconnected");
  }
}

void printWifiStatus()
{
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  Serial.println();
  Serial.print("To see this page in action, connect to ");
  Serial.print(ssid);
  Serial.print(" and open a browser to http://");
  Serial.println(ip);
  Serial.println();
}
