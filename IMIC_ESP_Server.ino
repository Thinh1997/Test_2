#include "ESP8266WiFi.h"
#include "HardwareSerial.h"

HardwareSerial Screen(UART0);
ESP8266WiFiSTAClass Wifi;
WiFiServer TCP_Server(4545);
bool find_string(char *string, char *target);
int LED = LED_BUILTIN; //Can than voi LED BUILTIN cua ESP
uint8_t target[3] = "ON";
uint8_t dulieu[12] = {0};

void setup() {
pinMode(LED, OUTPUT);
Screen.begin(9600);
Wifi.begin("Navier - Stokes", "caicayvuive");
  while(Wifi.isConnected() != true){
    Screen.print(".");
    delay(1000);
  }
Screen.println("Wifi connected");
Screen.println("IP: ");
Screen.print(Wifi.localIP());

TCP_Server.begin(4545, 10);
}

void loop() {
  int dataSize = 0;
  if(TCP_Server.hasClient()){
    WiFiClient CLIENT = TCP_Server.available();
    Screen.print("IP Remote: ");
    Screen.print(CLIENT.remoteIP());
    Screen.println("Port Remote: ");
    Screen.print(CLIENT.remotePort());
    while((dataSize = CLIENT.available()) == 0){}
    CLIENT.read(dulieu, dataSize);
    Screen.println("Du lieu nhan duoc: ");
    Screen.print((char*)dulieu);
    bool a = find_string((char*)dulieu, (char*)target);
    Screen.print(a);
    if(a == true){
      digitalWrite(LED, LOW); //Dao nguoc lai vi LED BUILTIN cua ESP khi ra lenh HIGH se tat.
    }else{
      digitalWrite(LED, HIGH);
    }
  } 
}

bool find_string(char *string, char *target){
  bool a = 0;
  for( int i = 0; i < strlen(string); i++ ){
    if( string[i] == target[0] ){
      int j = 0;
      for( j; j < strlen(target); j++ ){
        if( string[i+j] != target[j] ){
          break;
        }
      }
      if(j == strlen(target)){
        a = 1;
      }
    }
  }
  return a;
}
