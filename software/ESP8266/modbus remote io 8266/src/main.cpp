#include <Arduino.h>
#include <ModbusIP_ESP8266.h>
#include <ESP8266WiFi.h>


//declare pins
const int led = 0;
const int but = 1;


// ModBus Registers offsets
const int TEST_HREG = 100;
const int TEST_COIL = 200;
const int TEST_BUTT = 300;
const int TEST_SENS = 400;


//ModBus Object
ModbusIP mb;

//var
long ts;
long intervall; //intervall for scanning analog inputs

void setup() {
  Serial.begin(115200);

  WiFi.begin("SSID", "PSW");

  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }

  Serial.println(""),
  Serial.println("WiFi Connected");
  Serial.println("IP Address: ");
  Serial.println(WiFi.localIP());

  pinMode(but, INPUT);

  ts = millis();

  //initalize MOdbus Server(slave)
  mb.server();
  mb.addHreg(TEST_HREG, 0xABCD);
  mb.addCoil(TEST_COIL);
  mb.addIsts(TEST_BUTT);
  mb.addIreg(TEST_SENS);
}

void loop() {
  //Modbus Task(does the black magic)
  mb.task();
  delay(10); //remove or lower if other things in loop, speeds up respones via ModBus
  digitalWrite(led, mb.Coil(TEST_COIL));
  mb.Ists(TEST_BUTT, digitalRead(but));

  if (millis() > ts + intervall){
    mb.Ireg(TEST_SENS, random(255));
  }
}