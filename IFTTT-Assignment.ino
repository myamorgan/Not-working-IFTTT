#include <ETH.h>
#include <WiFi.h>
#include <M5StickCPlus.h>

#define SECRET_SSID " Centurylink0586"
#define SECRET_PASS "d6bb6f784c6cbb"

const char* resource = "/trigger/ClassButtonA/with/key/xjgs1m-BcSjD-sJxU24cS" ;
const char* server = "maker.ifttt.com";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200) ; 
  M5.begin ();
  delay(1000) ; 
  M5.Lcd.fillScreen (BLACK) ;
  M5.Lcd.setTextColor (RED) ; 
  M5.Lcd.setTextSize (2) ; 
  M5.Lcd.print("IFTTT Demo"); 
  
  WiFi.begin(SECRET_SSID, SECRET_PASS) ; 
  Serial.print("Connecting to ") ;
  Serial.println(SECRET_SSID) ;
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".") ;
    delay(500); 
}

Serial.println(); 
Serial.print("Connecting to ") ;
Serial.println(SECRET_SSID) ;

}
void loop() {
  M5.update ();
  if(M5.BtnA.wasPressed()) {
      makeIFTTTRequest(); 
    M5.Lcd.println("Btn Pressed"); 
  }

}

void makeIFTTTRequest () {
  Serial.print("Connecting to ") ;
  Serial.print(server) ;
 WiFiClient client ;
 int retries = 5; 
 while(!!!client.connect(server, 80) && (retries-- > 0)) {
  Serial.print("."); 
 }
  Serial.println(); 
  if(!!!client.connected()) {
      Serial.print("Failed to connect, going back to sleep") ;
  }
Serial.print("Request Resource: "); 
Serial.println(resource); 
  client.print(String("GET") + resource + " HTTP/1.1\r\n" + "Host: " + server 
      + "\r\n" + "Connection: close\r\n\r\n"); 

// time is 5 secs worth of 100 millisecs delay
int timeout = 5 * 10;
while(!!!client.available() && (timeout-- >0)) {
  delay(100);     
}

if (!!!client.available()) {
  Serial.print("No response, going back to sleep");
}

while(client.available()) {
  Serial.write(client.read());
}

Serial.println("closing connection");
client.stop(); 

}
