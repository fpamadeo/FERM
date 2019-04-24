# F.E.R.M.

## UIC ECE Senior Design 2018-2019

_______________________________________________________________________________________________________________________________
## Table of Contents:
**FERMix** | **Fryer**
----- | -----
**1** | [Members](README.md#1-Members)
**2** | [About the Project](README.md#2-About-the-Project)
2.1 | [Abstract](README.md#21-Abstract)
2.2 | [Project Overview](README.md#22-Project-Overview)
2.3 | [Design Alternatives](README.md#23-Design-Alternatives)
2.4 | ["Final Design"](README.md#24-Final-design)
2.5 | [Conclusion](README.md#25-Conclusion)
**3** | [Construction Guide](README.md##3-Construction-Guide)
3.1 | [LCD Screen](README.md#31-LCD-Screen)
3.2 | [Ultrasonic Sensor](README.md#32-Ultrasonic-Sensor)
3.3 | [Motor Driver](README.md#33-Motor-Driver)
3.4 | [Keypad](README.md#34-keypad)
**4** | [Acknowledgements](README.md##4-Acknowledgements)
 
____________________________________________________________________
## 1. Members:
* Francis Paul Amadeo
* Erick Estrada
* Meshal Alsaeed
* Rami Muhammad
______________________________________________________
## 2. About the Project:
### 2.1 Abstract:
>The project aims to create an affordable system for all commercial-grade fryers. In regards to cook-time management, we wish to ease the cooks’ workload by automating the deep frying process. However, we do not want our project to interfere with their normal operation while frying. Our project would just be a failsafe so that the food does not get overcooked. To solve these objectives, we opted to go for a modular design, which will include the main system and extensions. The main system will be chain-driven. The extensions can be customized depending on the user’s needs and space. Also, this design will feature pre-set and configurable user settings. Thus, giving the cooks a less stressful environment, making them free to do more things in the kitchen. The system is designed primarily as a way to simplify and reduce the complexity of frying food for restaurants by taking into account the FDA’s regulations.

### 2.2 Project Overview:
>The goal is to build an add-on for restaurant deep fryers. This add-on would automate the lowering and raising of the frying basket, with the user inputting how long the deep frying will last. Due to the stressful environment of restaurant kitchens, there are lots of food that get  burned from being left alone for too long. With our add-on, food waste would be reduced in addition to simplifying the frying process for workers.

### 2.3 Design Alternatives:
**Mechanisms:**
>The Actuator would help decrease the bulkiness of our system. However, this would also limit the modularity of the system, compared to the chain driven design we opted for.
> 
>The Lead Screw would give us a high positioning accuracy, but would in turn, be inefficient. Furthermore, lead screws are significantly more expensive compare to the other designs we had in mind

**Sensors:**
>A magnetic switch would be a great sensor to detect when the fryer basket is on our hanger, since most likely the basket is made of metal. However, since the hanger is made of metal itself, we opted to not use a magnetic switch.
>
>Similar to a magnetic switch, an inductive sensor will detect when metal object is near it. But rather than having a 0 or 1 input, it can sense how far the nearest metal is. Unfortunately, we opted to use the sensor we already have on-hand so we could use the resources for elsewhere. Going forward, we would have went with this sensor.

### 2.4 "Final Design":
>For the final design, we are going  to use a chain-driven mechanism, with one of the links of the chains attached to a steel pipe with threaded ends. This end could then be attached to a various choice of connectors which in turn, be connected to other pipes and finally to the fryer basket hanger. This gives the user the ability to customize the connections in accordance with their need. Furthermore, other than the basic timer option, the system gives the user the options to save up to three preset times and to calibrate the depth of the fryer vat.

### 2.5 Conclusion:
>In hindsight, with the large mechanical aspect of our system, we would have benefited with consulting with more mechanical engineers with our design. We would have also hoped to be able to test our other design alternatives, and be able to pick which one is the best.
> 
>Going forward, we have some design changes in order to improve the overall functionality and appearance of the system. These changes would include: a mechanism to prevent the chain from slacking as weight is added to the system; inductive sensing instead of ultrasonic; metal housing; a more permanent wiring and circuit layout and; other relatively minor issues we have yet to tackle due to time and financial constraints. 

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

______________________________________________________
## 4. Acknowledgements:
>Team F.E.R.M. would like to thank: the staff of UIC’s Makerspace; the members of Chicago Engineering Design Team; Mona Hurt and; our advisor, Dr. Wenjing Rao.


