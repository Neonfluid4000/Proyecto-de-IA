#include "DHT.h"
#include "BluetoothSerial.h"

#define DHTPIN 4
#define DHTTYPE DHT11
#define RelayPin 14

DHT dht(DHTPIN, DHTTYPE);

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run 'make menuconfig' to and enable it
#endif 
#define LED 2
String message = "";
char incoming;
BluetoothSerial SerialBT;


void setup(){
  SerialBT.begin("BlueESP32");
  Serial.begin(115200); 
  dht.begin();
  pinMode (LED , OUTPUT);
  pinMode(RelayPin, OUTPUT);
}

void loop(){
 
 
  float t = dht.readTemperature();
  float h = dht.readHumidity();

  SerialBT.print(t);
  SerialBT.println(";");
  SerialBT.print(h);
  SerialBT.print(";");


  if (SerialBT.available()){
    char incoming = SerialBT.read();
    if (incoming != '\n'){
      message += String(incoming);
    }
  
    else{
      
      if(message == "ON"){
        digitalWrite(LED, HIGH);
      }
      if(message == "OFF"){
        digitalWrite(LED, LOW);
      }
      if(message =="ron"){
        digitalWrite(RelayPin, HIGH);
   
      }
      if(message == "roff"){
        digitalWrite(RelayPin, LOW);
      }
            if(SerialBT.available()){
    Serial.println(message);
  }
    message="";  
    }
    delay(20);
    

  }

  }
  
