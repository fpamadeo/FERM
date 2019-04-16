# F.E.R.M.

## UIC ECE Senior Design 2018-2019

_______________________________________________________________________________________________________________________________
## Table of Contents:
**FERMix** | **Fryer**
----- | -----
**1** | [Members](README.md#1-Members)
**2** | [Construction Guide](README.md##2-Construction-Guide)
2.1 | [LCD Screen](README.md#21-LCD-Screen)
2.2 | [Ultrasonic Sensor](README.md#22-Ultrasonic-Sensor)
2.3 | [Motor Driver](README.md#23-Motor-Driver)
2.4 | [Keypad](README.md#24-keypad)
_____________________________________________________________________
## 1. Members:
* Francis Paul Amadeo
* Erick Estrada
* Meshal Alsaeed
* Rami Muhammad
______________________________________________________
## 2. Construction Guide:
* We are using an Arduino Mega (Elegoo MEGA2560 R3)
* We are using the MD10C R3 Motor Driver
### 2.1 LCD Screen:
Arduino | 2x16 LCD 
--- | ---
GND | VSS
5V | VDD
GND -> 1kOhm Resistor | VO
D12 | RS
D11 | E 
D23 | DB0
D27 | DB1
D31 | DB2
D35 | DB3
D34 | DB4
D30 | DB5
D26 | DB6
D22 | DB7
5V -> 224Ohm | A
GND | K

### 2.2 Ultrasonic Sensor:
Arduino | HC-SR04 
--- | ---
GND | GND
D48 | ECHO
D49 | TRIGGER
5V | VCC

### 2.3 Motor Driver:
Arduino | MD10C R3
--- | ---
GND | GND
D13 | PWM
D53 | DIR


### 2.4 Keypad:
Arduino | Keypad
--- | ---
D2 | 1
D3 | 2
D4 | 3
D5 | 4
D6 | 5
D7 | 6
D8 | 7
D9 | 8

** * \*Keypad pins are numbered left to right, from the POV of looking at the back upright\* * **