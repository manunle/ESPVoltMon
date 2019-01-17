 #include <Arduino.h>
#include "ESPBASE.h"
#include "Gsender.h"

const byte mqttDebug = 1;
long lastVolts = 0;
long durationVolts = 10000;
byte ShouldSleep = 1;
Gsender *gsender;

ESPBASE Esp;

void setup() 
{
  Serial.begin(115200);
  pinMode(5,OUTPUT);
  Esp.initialize();
  gsender = Gsender::Instance();
}

void VoltLoop()
{
  long t=millis();
  if(t > durationVolts + lastVolts)
  {
    Serial.println("Reading volts");
    int a = analogRead(A0);
    Serial.println(a);
    lastVolts = t;
    float v=(1/1024.0*(float)a);
    float tmp = (10000.0+config.voltcalib)/(150000.0+(10000.0+config.voltcalib));
    float v2=v/tmp;
    Esp.mqttSend("volts/"+config.DeviceName+"/value","volts:"+String(v2),"");
    if(v2 < config.VoltEmailThreshold)
    {
      String subject = config.DeviceName + " volts";
      if(gsender->Subject(subject)->Send(config.EmailAddress, config.DeviceName + " volts is " + String(v2))) 
      {
        Serial.println("Message send.");
      } 
      else 
      {
        Serial.print("Error sending message: ");
        Serial.println(gsender->getError());
      } 
    }
    Esp.loop();
    if(config.SleepAfterVolts && sleepable)
    {
      Serial.println("sleeping");
       ESP.deepSleep(config.SleepAfterVoltsDuration*1000*1000);
    }
  }
}

void loop() {
  //  WebServer requests handling
//  VoltLoop();
  Esp.loop();
  VoltLoop();
  digitalWrite(5,HIGH);
}

void mqttCallback(char* topic, byte* payload, unsigned int length) {
  char c_payload[length];
  memcpy(c_payload, payload, length);
  c_payload[length] = '\0';
  
  String s_topic = String(topic);
  String s_payload = String(c_payload);
  
  if (mqttDebug) {
    Serial.print("MQTT in: ");
    Serial.print(s_topic);
    Serial.print(" = ");
    Serial.print(s_payload);
  }

  if (s_topic == config.SleepTopic) {
    Serial.println("Got set: ");
    Serial.println(s_payload);
    char dname[20];
    String DeviceName;
    char *p = c_payload;
    char *str;
    str = strtok_r(p,";",&p);
    strncpy(dname,str,20);
    Serial.print("device name: ");
    DeviceName = String(dname);
    Serial.println(DeviceName);
    if(DeviceName == String(config.DeviceName))
    {
      Serial.println("This is for me");
      String mess = String(p);
      Serial.println(mess);
//      if(mess=="Sleep")
//      {
        Serial.print("Going to sleep for ");
        Serial.print(String(config.SleepDuration));
        Serial.println(" seconds");
        digitalWrite(5,LOW);
        ESP.deepSleep(config.SleepDuration*1000*1000);
//      }
    }
  }
  else {
    if (mqttDebug) { Serial.println(" [unknown message]"); }
  }
}

void mqttSubscribe()
{
    if (Esp.mqttClient->connected()) 
    {
      if (Esp.mqttClient->subscribe(config.SleepTopic.c_str())) 
      {
        Esp.mqttSend(String("TestChip"),config.DeviceName,config.SleepTopic + String(": subscribed"));
        Esp.mqttSend(StatusTopic,verstr,","+Esp.MyIP()+" start");
      }
    }
}

