# F.E.R.M.

## UIC ECE Senior Design 2018-2019

_______________________________________________________________________________________________________________________________
## Table of Contents:
**FERMix** | **Fryer**
----- | -----
**1** | [Members](README.md#1-Members)
**2** | [About the Project](README.md#2-About-the-Project)
**3** | [Construction Guide](README.md##3-Construction-Guide)
3.1 | [LCD Screen](README.md#31-LCD-Screen)
3.2 | [Ultrasonic Sensor](README.md#32-Ultrasonic-Sensor)
3.3 | [Motor Driver](README.md#33-Motor-Driver)
3.4 | [Keypad](README.md#34-keypad)
 
____________________________________________________________________
## 1. Members:
* Francis Paul Amadeo
* Erick Estrada
* Meshal Alsaeed
* Rami Muhammad
______________________________________________________
## 2. About the Project:
* Abstract:
>The project aims to create an affordable system for all commercial-grade fryers. In regards to cook-time management, we wish to ease the cooks’ workload by automating the deep frying process. However, we do not want our project to interfere with their normal operation while frying. Our project would just be a failsafe so that the food does not get overcooked. To solve these objectives, we opted to go for a modular design, which will include the main system and extensions. The main system will be chain-driven. The extensions can be customized depending on the user’s needs and space. Also, this design will feature pre-set and configurable user settings. Thus, giving the cooks a less stressful environment, making them free to do more things in the kitchen. The system is designed primarily as a way to simplify and reduce the complexity of frying food for restaurants by taking into account the FDA’s regulations.

______________________________________________________
## 3. Construction Guide:
* We are using an Arduino Mega (Elegoo MEGA2560 R3)
* We are using the MD10C R3 Motor Driver
### 3.1 LCD Screen:
Arduino | 2x16 LCD 
--- | ---
GND | VSS
5V | VDD
GND -> 1kOhm Resistor | VO
D12 | RS
GND | RW
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

### 3.2 Ultrasonic Sensor:
Arduino | HC-SR04 
--- | ---
GND | GND
D48 | ECHO
D49 | TRIGGER
5V | VCC

### 3.3 Motor Driver:
Arduino | MD10C R3
--- | ---
GND | GND
D13 | PWM
D53 | DIR


### 3.4 Keypad:
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

***\*Keypad pins are numbered left to right, from the POV of looking at the back upright\****


