#include <SPI.h>
#include <LoRa.h>
#include <elapsedMillis.h>

#define BAND  915E6
#define SS    10
#define RST   9
#define DIO0  2

elapsedMillis requestMillis;
elapsedMillis serialPrintMillis;

unsigned long requestInterval       = 2000;
unsigned long serialPrintInterval   = 10000;

byte turn;

String area1  = "L1";
String area2  = "L2";
String area3  = "L3";
String area4  = "L4";

String
areaData1, sensor1a, sensor1b, sensor1c, sensor1d, sensor1e,
areaData2, sensor2a, sensor2b, sensor2c, sensor2d, sensor2e,
areaData3, sensor3a, sensor3b, sensor3c, sensor3d, sensor3e,
areaData4, sensor4a, sensor4b, sensor4c, sensor4d, sensor4e;

void setup()
{
  Serial.begin(9600);

  initLoRa();

  turn = 1;
}

void loop()
{
  waitResponse();
  
  if (requestMillis >= requestInterval)
  {
    if (turn == 1)
    {
      sendRequest (area1);
      turn = 2;
    }
    else if (turn == 2)
    {
      sendRequest (area2);
      turn = 3;
    }
    else if (turn == 3)
    {
      sendRequest (area3);
      turn = 4;
    }
    else if (turn == 4)
    {
      sendRequest (area4);
      turn = 1;
    }
    requestMillis = 0;
  }

  if (serialPrintMillis >= serialPrintInterval)
  {
    Serial.print ("Area 1 : ");
    Serial.print (areaData1);
    Serial.print ("\tArea 2 : ");
    Serial.print (areaData2);
    Serial.print ("\tArea 3 : ");
    Serial.print (areaData3);
    Serial.print ("\tArea 4 : ");
    Serial.println (areaData4);

    Serial.print ("S1A    : ");
    Serial.print (sensor1a);
    Serial.print ("\tS2A    : ");
    Serial.print (sensor2a);
    Serial.print ("\tS3A    : ");
    Serial.print (sensor3a);
    Serial.print ("\tS4A    : ");
    Serial.println (sensor4a);

    Serial.print ("S1B    : ");
    Serial.print (sensor1b);
    Serial.print ("\tS2B    : ");
    Serial.print (sensor2b);
    Serial.print ("\tS3B    : ");
    Serial.print (sensor3b);
    Serial.print ("\tS4B    : ");
    Serial.println (sensor4b);

    Serial.print ("S1C    : ");
    Serial.print (sensor1c);
    Serial.print ("\tS2C    : ");
    Serial.print (sensor2c);
    Serial.print ("\tS3C    : ");
    Serial.print (sensor3c);
    Serial.print ("\tS4C    : ");
    Serial.println (sensor4c);

    Serial.print ("S1D    : ");
    Serial.print (sensor1d);
    Serial.print ("\tS2D    : ");
    Serial.print (sensor2d);
    Serial.print ("\tS3D    : ");
    Serial.print (sensor3d);
    Serial.print ("\tS4D    : ");
    Serial.println (sensor4d);

    Serial.print ("S1E    : ");
    Serial.print (sensor1e);
    Serial.print ("\tS2E    : ");
    Serial.print (sensor2e);
    Serial.print ("\tS3E    : ");
    Serial.print (sensor3e);
    Serial.print ("\tS4E    : ");
    Serial.println (sensor4e);
    
    serialPrintMillis = 0;
  }
}

void initLoRa()
{
  LoRa.setPins(SS, RST, DIO0);
  if (!LoRa.begin(BAND))
  {
    while (1);
  }
}

void sendRequest (String target)
{
  LoRa.beginPacket ();
  LoRa.print (target);
  LoRa.print ("#");
  LoRa.endPacket ();
}

void waitResponse()
{
  String area, sensorA, sensorB, sensorC, sensorD, sensorE;
  int packetSize = LoRa.parsePacket();
  if (packetSize)
  {
    while (LoRa.available())
    {
      area = LoRa.readStringUntil ('#');
      sensorA = LoRa.readStringUntil ('#');
      sensorB = LoRa.readStringUntil ('#');
      sensorC = LoRa.readStringUntil ('#');
      sensorD = LoRa.readStringUntil ('#');
      sensorE = LoRa.readStringUntil ('#');
      dataHandler (area, sensorA, sensorB, sensorC, sensorD, sensorE);
    }
  }
}

void dataHandler (String field, String sensor1, String sensor2, String sensor3, String sensor4, String sensor5)
{
  if (field == area1)
  {
    areaData1 = field;
    sensor1a  = sensor1;
    sensor1b  = sensor2;
    sensor1c  = sensor3;
    sensor1d  = sensor4;
    sensor1e  = sensor5;
  }
  else if (field == area2)
  {
    areaData2 = field;
    sensor2a  = sensor1;
    sensor2b  = sensor2;
    sensor2c  = sensor3;
    sensor2d  = sensor4;
    sensor2e  = sensor5;
  }
  else if (field == area3)
  {
    areaData3 = field;
    sensor3a  = sensor1;
    sensor3b  = sensor2;
    sensor3c  = sensor3;
    sensor3d  = sensor4;
    sensor3e  = sensor5;
  }
  else if (field == area4)
  {
    areaData4 = field;
    sensor4a  = sensor1;
    sensor4b  = sensor2;
    sensor4c  = sensor3;
    sensor4d  = sensor4;
    sensor4e  = sensor5;
  }
}
