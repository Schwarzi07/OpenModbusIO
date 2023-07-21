#include <Arduino.h>
#include <SPI.h>
#include <Ethernet.h>       // Ethernet library v2 is required
#include<EthernetUdp.h>
#include <ModbusEthernet.h>


//Ethernet configuration
byte mac[] = {
  0xa8, 0x61, 0x0a, 0xae, 0xe4, 0x39
};
IPAddress ip(192, 168, 2, 101); // The IP address will be dependent on your local network:

//declare pins
const int led = 9;
const int but = 8;
const int temp = A0;


// ModBus Registers offsets
// Holding registers
const int TEST_HREG = 100;
//coils
const int TEST_COIL = 200;
// discrete inputs
const int TEST_BUTT = 300;
//analog input registers
const int TEST_SENS = 400;
const int TEMP_INT  = 401;


//ModBus Object
ModbusEthernet mb;

//var
long ts;
long intervall; //intervall for scanning analog inputs




void setup() {
  // put your setup code here, to run once:
  pinMode(but, INPUT);
  pinMode(led, OUTPUT);
  //digitalWrite(led,HIGH);
/*digitalWrite(led, HIGH);
  delay(500);
  digitalWrite(led,LOW);
  delay(500);
  digitalWrite(led, HIGH);
  delay(500);
  digitalWrite(led,LOW);
  delay(500);
  digitalWrite(led, HIGH);
  delay(500);
  digitalWrite(led,LOW);*/
  ts = millis();
  intervall = 2000;

  Serial.begin(9600);     // Open serial communications and wait for port to open
  #if defined(AVR_LEONARDO)
  while (!Serial) {}        // wait for serial port to connect. Needed for Leonardo only
  #endif
  Ethernet.init(10);        // SS pin
  Ethernet.begin(mac, ip);  // start the Ethernet connection
  delay(1000);         
  Serial.print(Ethernet.localIP());     // give the Ethernet shield a second to initialize
  
  mb.server();              // Act as Modbus TCP server (slave)
  mb.addHreg(TEST_HREG, 0xABCD);  
  mb.addCoil(TEST_COIL);
  mb.addIsts(TEST_BUTT);
  mb.addIreg(TEST_SENS);
  mb.addIreg(TEMP_INT);
  
  
}

void loop() {
  // put your main code here, to run repeatedly:
  //Modbus Task(does the black magic)
  mb.task();
  delay(50); //remove or lower if other things in loop, speeds up respones via ModBus
  digitalWrite(led, mb.Coil(TEST_COIL));
  mb.Ists(TEST_BUTT, digitalRead(but));

  if (millis() > ts + intervall){
    mb.Ireg(TEST_SENS, random(50));
    mb.Ireg(TEMP_INT, map(analogRead(temp), 0, 307, 0, 150)); //internal temp sens
  }
}
