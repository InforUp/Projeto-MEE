// Template ID, Device Name and Auth Token are provided by the Blynk.Cloud
// See the Device Info tab, or Template settings
#define BLYNK_TEMPLATE_ID           "TMPLT6ax_Ps9"
#define BLYNK_DEVICE_NAME           "Quickstart Device"
#define BLYNK_AUTH_TOKEN            "0CSxOcaL5_ENJ59X2Ifk1Q-NHDq1RC7t"

#define BLYNK_PRINT Serial
 
#include "EmonLib.h"   //https://github.com/openenergymonitor/EmonLib
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
 
EnergyMonitor emon;
#define vCalibration 20
#define currCalibration 0.15
BlynkTimer timer;
 
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "REINO DO NORTE";
char pass[] = "17ak12sc06";
 
float kWh = 0;
unsigned long lastmillis = millis();
 
void myTimerEvent() {
    emon.calcVI(20, 2000);
    yield();
    Serial.print("Vrms: ");
    Serial.print(emon.Vrms, 2);
    Serial.print("V");
    
    Blynk.virtualWrite(V0, emon.Vrms);
    Serial.print("\tIrms: ");
    Serial.print(emon.Irms, 6);
    Serial.print("A");
    
    Blynk.virtualWrite(V1, emon.Irms);
    Serial.print("\tPower: ");
    Serial.print(emon.apparentPower, 4);
    Serial.print("W");
    
    Blynk.virtualWrite(V2, emon.apparentPower);
    Serial.print("\tkWh: ");
    kWh = kWh + emon.apparentPower*(millis()-lastmillis)/3600000000.0;
    Serial.print(kWh, 4);
    
    Serial.println("kWh");
    lastmillis = millis();
    Blynk.virtualWrite(V3, kWh);

}
 
void setup() {
  Serial.begin(9600);
  emon.voltage(35, vCalibration, 1.7); 
  emon.current(34, currCalibration); 
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(100L, myTimerEvent);
}
 
void loop() {
  Blynk.run();
  timer.run();
}
