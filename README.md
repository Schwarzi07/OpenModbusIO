# OpenModbusIO
Hardware and software for Mobus based remote IO

# Goal
The goal of this project is to create open source IO for Modbus TCP or Modbus RTU. This repository will hold the source code and the PCB design files for this project. 

# Software
Currnetly the software is written in C++ on the Arduino platform via Visual Studio Code and PlatformIO. My plans are to switch to an RTOS when the hardware expands.

# Hardware
The hardware is curently based on Arduino and is using the Arduino Ethernet shield with the Wiznet w5500 Ethernet controller.
I design the PCBs in KiCad and will limit myself to two layers to keep costs low and enable DIY PCB fabrication using CNC milling or other methods.

# Current status
Currently I have basic software and a shield for an Arduino UNO.
