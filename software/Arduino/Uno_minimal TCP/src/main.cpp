#include <Arduino.h>
#include <SPI.h>
#include <Ethernet.h>       // Ethernet library v2 is required
#include<EthernetUdp.h>
#include <ModbusEthernet.h>

//Ethernet configuration
byte mac[] = {
  0xa8, 0x61, 0x0a, 0xae, 0xe4, 0x39
};
IPAddress ip(192, 168, 2, 101);

//declare pins
const int i1 = 5;
const int i2 = 6;
const int i3 = A2;
const int i4 = A3;

const int a1 = A0;
const int a2 = A1;

const int q1 = 6;
const int q2 = 7;
const int led = 5;

const int ethernet_ss = 10;


// ModBus Registers offsets
const int i_1 = 100;
const int i_2 = 101;
const int i_3 = 102;
const int i_4 = 103;

const int a_1 = 200;
const int a_2 = 201;

const int q_1 = 300;
const int q_2 = 301;
const int q_led = 302;

//ModBus Object
ModbusEthernet mb;



void setup() {
  Serial.begin(9600);
  Serial.println("Setting Pins");
  //set pins
  pinMode(i1, INPUT);
  pinMode(i2, INPUT);
  pinMode(i3, INPUT);
  pinMode(i4, INPUT);
  pinMode(q1, OUTPUT);
  pinMode(q2, OUTPUT);
  pinMode(led, OUTPUT);
  //init Ethernet
  Serial.println("Intitializing Ethernet");
  Ethernet.init(ethernet_ss);        
  Ethernet.begin(mac, ip);  
  delay(1000);         
  Serial.print(Ethernet.localIP());
  //init modbus
  Serial.println("Initializing Modbus");
  mb.server();
  //add registers
  Serial.println("Adding registers");
  mb.addIsts(i_1);
  mb.addIsts(i_2);
  mb.addIsts(i_3);
  mb.addIsts(i_4);

  mb.addIreg(a_1);
  mb.addIreg(a_2);

  mb.addCoil(q_1);
  mb.addCoil(q_2);
  mb.addCoil(q_led);
  Serial.println("Done!");
}

void loop() {
  mb.task();
  digitalWrite(q1, mb.Coil(q_1));
  digitalWrite(q2, mb.Coil(q_2));
  digitalWrite(led, mb.Coil(q_led));

  mb.Ists(i_1, digitalRead(i1));
  mb.Ists(i_2, digitalRead(i2));
  mb.Ists(i_3, digitalRead(i3));
  mb.Ists(i_4, digitalRead(i4));

  mb.Ireg(a_1, analogRead(a1));
  mb.Ireg(a_2, analogRead(a2));
}

