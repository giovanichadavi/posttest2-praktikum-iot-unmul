#define BLYNK_TEMPLATE_ID "TMPL6exv4Tjb-"
#define BLYNK_TEMPLATE_NAME "SensorGasIOT"
#define BLYNK_AUTH_TOKEN "wqwsJgQM0W_WoKtpnxgyYFqHnWC105j7"


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
 
#define BLYNK_PRINT Serial    


#define buzzer 4 //D2

char ssid[] = "Universitas Mulawarman"; //Enter WIFI Name
char pass[] = ""; //Enter WIFI Password
 
BlynkTimer timer;
WidgetLED led(V2);
 
int mq2 = A0;
int data = 0; 

void setup() 
{
  Serial.begin(115200);
  pinMode(buzzer, OUTPUT);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  timer.setInterval(1000L, getSendData);
}
 
void loop() 
{
  timer.run();
  Blynk.run();
}
 
void getSendData()
{
  data = analogRead(mq2); 
  Blynk.virtualWrite(V6, data);      
  Serial.print("Analog Sensor:");
  Serial.print(data);
  Serial.print("\t");
  if (data > 350 )// sesuaikan kondisi batas terdeteksi Gas
  {
    Serial.println("Gas Bocor!");
    tone(buzzer, 1000, 200);
    led.on();
  }
  else
  {
    Serial.println("AMAN");
    noTone(buzzer);
    led.off();
  }
 
}
