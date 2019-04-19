#include <LiquidCrystal.h>
#include <Wire.h>
#include <Keypad.h>
//**********************************************************************************************************//
//Preset:
String preset[3] = {"0015","0030","0100"}; //"MMSS" //Preset times

//LCD pins:
const int rs = 12, en = 11, d0 = 23, d1 = 27, d2 = 31, d3 = 35, d4 = 34, d5 = 30, d6 = 26, d7 = 22;
LiquidCrystal lcd(rs, en, d0, d1, d2, d3, d4, d5, d6, d7);

//MOTOR:
#define pwmPin 13 //Pin to send how fast it is
#define dirPin 53 //Pin to send if going clockwise or counter-clockwise
#define UP true //boolean value to send to move up
#define DOWN false //boolean value to send to move down
#define MOTOR_DELAY 100 //how long is each "step"; in microseconds
#define MOTOR_SPEED 255 //PWM value to send to motor driver; Range: 0-255
#define DEFAULT_STEPS 10 //From lowest point to highest point in steps

//ULTRASONIC(US)  SENSOR:
#define echoPin 48 //ECHO
#define trigPin 49 //TRIGGER
#define sensorDelay 100 //centiseconds 
#define sensorThres 10 //threshold 
//Keypad:
const byte ROWS = 4; //How many rows are there in the keypad
const byte COLS = 4; //How many columns are there in the keypad

char keys[ROWS][COLS] =  //Mapping out the corresponding characters for each key
{
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {9, 8, 7, 6}; 
byte colPins[COLS] = {5, 4, 3, 2};

Keypad userKeypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

//GLOBAL Variables:

//Strings:
String timeIN = "0000"; //Time input in by the user for "normal" executions
String tempTime = "0000"; //Time input in by the user for "shift" executions; ##TODO: Might be redundant##

//Ints
int timeLeft = 0; //The actual time the user enters; should always be in seconds
int selected = 0; //The preset the user selected to be changed
int blinkDelay = 0; //Used to make the timer blink every 1 second
long duration;     //How long til the signal comes back
int distance;      //How far til the signal bounces off of something
int stepsToDo = DEFAULT_STEPS; //Steps needed for now #TODO#
int tempSteps = 0; //Steps the user is doing before everything is saved or cancelled 

//Bool:
bool error = false; //USED TO CHECK FOR ERRORS, should never be true
bool cancel = false; //TRUE when user cancels current action/s
bool shift = false; //TRUE when user uses the shift key 
bool calibrate = false; //TRUE when the user is calibrating
bool changePreset = false; //TRUE when the user is changing a preset
bool blinkTime = false; //USED FOR MAKING THE TIME BLINK every 1 second 

//**********************************************************************************************************//
//SETUP
void setup() 
{
  //US SENSOR:
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input

  //MOTOR:
  pinMode(dirPin, OUTPUT);
  digitalWrite(dirPin, HIGH);//initialization
  analogWrite(pwmPin, 0); //initialization
  
  //TESTING:
  Serial.begin(9600);

  //LCD:
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Standby");
  lcd.setCursor(11,0);    
  lcd.print("TIME:");
  lcd.setCursor(11,1);    
  lcd.print(timeIN[0]);
  lcd.print(timeIN[1]);
  lcd.print(":");
  lcd.print(timeIN[2]);
  lcd.print(timeIN[3]);
}

//**********************************************************************************************************//
//Previous Code:
/*
//MOTOR GO UP
void moveUp(){
  digitalWrite(dirPin, HIGH);
  analogWrite(pwmPin, 255);
  delay(100);
}

//MOTOR GO DOWN
void moveDown(){
  digitalWrite(dirPin, LOW);
  analogWrite(pwmPin, 255);
  delay(100);
}
*/

//MOVE MOTOR:
void moveMotor(bool dir, int steps){
  if (steps < 1){
    error = true;
    updateScreen(); //Show on screen, there's error
    delay(3000);
    updateScreen(); //Return to standby, after three second
    return;
  }
  if (dir == UP){
    digitalWrite(dirPin, HIGH);
  }
  else{
    digitalWrite(dirPin, LOW);
  }
  analogWrite(pwmPin, MOTOR_SPEED);
  delay(MOTOR_DELAY * (steps - 1));
  analogWrite(pwmPin, MOTOR_SPEED / 2);
  delay(MOTOR_DELAY);
  analogWrite(pwmPin, 0);
  return;
}

//**********************************************************************************************************//
//UPDATES JUST TIME
void updateTime(){
  //lcd.setCursor(0,1);
  //lcd.print(timeLeft);
  int minutes, seconds;
  if(cancel){
    return;
  }
  minutes = timeLeft / 60;
  seconds = timeLeft % 60;
  if(minutes > 99){
    minutes = 99;
  }
  lcd.setCursor(11,1);    
  lcd.print(minutes/10);
  lcd.print(minutes%10);
  lcd.print(":");
  lcd.print(seconds/10);
  lcd.print(seconds%10);
  delay(1000);
}

//UPDATES DISPLAY
void updateScreen(){
  if (error){
    error = false;
    lcd.setCursor(11,1);
    lcd.print("ERROR");
    delay(1000);
  }
  if (cancel){
    cancel = false;
    lcd.setCursor(11,1);
    lcd.print("CNCEL");
    lcd.setCursor(0,0);
    lcd.print("Standby    ");
    lcd.setCursor(0,1);
    lcd.print("           ");
    delay(500);
  }
  lcd.setCursor(0,1);
  if (changePreset){
    lcd.print("Preset");
    lcd.print(" ");
  }
  if (selected != 0){
    lcd.print(selected);
    lcd.print(" ");
  }
  if (shift){
    lcd.print("S");
  }
  if (timeLeft <= 0 or cancel){
    lcd.setCursor(11,1);    
    lcd.print(timeIN[0]);
    lcd.print(timeIN[1]);
    lcd.print(":");
    lcd.print(timeIN[2]);
    lcd.print(timeIN[3]);
  }
  else{
    lcd.setCursor(0,0);
    lcd.print("ON         ");
  }
}

//**********************************************************************************************************//
//GIVES PROPER INT FOR CASES:
String getInt(char input){
  if (input == '*'){
    return "10";
  }
  if (input == '#'){
    return "11";
    }
  if (input == 'A'){
    return "12";
  }
  if (input == 'B'){
    return "13";
    }
  if (input == 'C'){
    return "14";
  }
  if (input == 'D'){
    return "15";
  }
  String returnThis = "";
  returnThis += input;
  return returnThis;
}

//**********************************************************************************************************//

//CHECKS SENSOR IF THERE IS SOMETHING THERE //#TODO: FIND DECENT NUMBER FOR THE BASKET#//
bool checkSensor(bool motorPosition){

  for(int i = 0; i < sensorDelay; i++){
       // Clears the trigPin
      digitalWrite(trigPin, LOW);
      delayMicroseconds(2);
      // Sets the trigPin on HIGH state for 10 micro seconds
      digitalWrite(trigPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigPin, LOW);
      // Reads the echoPin, returns the sound wave travel time in microseconds
      duration = pulseIn(echoPin, HIGH);
      // Calculating the distance
      distance= duration*0.034/2;
      // Prints the distance on the Serial Monitor
      Serial.print("Distance: ");
      Serial.println(distance);
      if (motorPosition == UP){
        if (distance < sensorThres){
          return false;
        }
      }
      else{
        if (distance < sensorThres){
          return true;
        }
      }
      
  }
  if (motorPosition == UP){
        return true;
      }
      else{
        return false;
      }
}

//**********************************************************************************************************//
//CHECKS KEY AND CORRESPONDS THE RIGHT ACTION
void checkKey(int input){
  switch(input){
   case 11: //Cancel?
      //Use Function to cancel timer here
      cancel = true;
      timeIN = "0000";
      timeLeft = 0;
      
      updateScreen();
      break;
   case 12: //Shift fn?
      shift = true;
      updateScreen();
      //lcd.setCursor(0,0);
      //lcd.print("SHIFT");
      break;case 13: //Preset 1?
      lcd.setCursor(0,0);
      timeIN = preset[0];
      updateScreen();
      break;
   case 14: //Preset 2?
      lcd.setCursor(0,0);
      timeIN = preset[1];
      updateScreen();
      break;
   case 15: //Preset 3?
      lcd.setCursor(0,0);
      timeIN = preset[2];
      updateScreen();
      break;
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 0:
      //Remove the first char of the string and add the input at the end:
      timeIN.remove(0,1);
      timeIN += input;
  
      updateScreen();
      break;
   case 10: //Enter?
      //use function to start timer here
      String toNum = "";
      toNum += timeIN[0];
      toNum += timeIN[1];
      timeLeft =  toNum.toInt() * 60;
      toNum = "";
      toNum += timeIN[2];
      toNum += timeIN[3];
      timeLeft = timeLeft + toNum.toInt();
      timeIN = "0000";
      updateScreen();
      break;
   default: 
      error = true;
      break;
  }
}

//CHECKS KEY AND CORRESPONDS THE RIGHT SHIFT ACTION
void checkShift(int input){
  //lcd.print(input);
  switch(input){
    case 1://Calibration
      if(not changePreset){
        calibrate = true;
        lcd.setCursor(0,0);
        lcd.print("Calibrate  ");
        updateScreen();
      }
      break;
    case 2:
      if (calibrate){
        moveMotor(UP, 1);
        tempSteps--;
      }
      break;
    case 5:
      if (calibrate){
        moveMotor(DOWN,1);
        tempSteps++;
      }
      break;
    case 4://Change Preset
      if(not calibrate){
        changePreset = true;
        lcd.setCursor(0,0);
        lcd.print("Changing ");
        updateScreen();
      }
      break;
    case 10: //Enter?
      tempSteps = 0;
      calibrate = false;
      changePreset = false;
      shift = false;
      lcd.setCursor(0,0);
      lcd.print("Saved      ");
      delay(500);
      lcd.setCursor(0,0);
      lcd.print("Standby    ");
      lcd.setCursor(0,1);
      lcd.print("           ");
      break;
   case 11: //Cancel?
      if(tempSteps > 0){
        moveMotor(UP,tempSteps);
      }
      else{
        moveMotor(DOWN, tempSteps * -1); 
      }
      tempSteps = 0;
      calibrate = false;
      changePreset = false;
      shift = false;
      lcd.setCursor(0,0);
      lcd.print("Cancelled  ");
      delay(500);
      lcd.setCursor(0,0);
      lcd.print("Standby    ");
      lcd.setCursor(0,1);
      lcd.print("           ");
      
      break;
   case 13: //Preset 1?
      if(changePreset){
        selected = 1;
        tempTime = "0000";
      }
      updateScreen();
      break;
   case 14: //Preset 2?
      if(changePreset){
        selected = 2;
        tempTime = "0000";
      }
      updateScreen();
      break;
   case 15: //Preset 3?
      if(changePreset){
        selected = 3;
        tempTime = "0000";
      }
      updateScreen();
      break;
   default:
      break;
  }
}

//Uses the whole keypad again, for changing presets
void changeSelected(int input){
  if (changePreset){
      switch(input){
       case 13: //Preset 1?
          if(changePreset){
            selected = 1;
            tempTime = "0000";
          }
          updateScreen();
          break;
       case 14: //Preset 2?
          if(changePreset){
            selected = 2;
            tempTime = "0000";
          }
          updateScreen();
          break;
       case 15: //Preset 3?
          if(changePreset){
            selected = 3;
            tempTime = "0000";
          }
          updateScreen();
          break;
        case 11: //Cancel?
          //Use Function to cancel timer here
          selected = 0;
          shift = false;
          lcd.setCursor(0,0);
          lcd.print("Cancellled  ");
          lcd.setCursor(0,1);
          lcd.print("           ");
          tempTime = "0000";
          updateScreen();
          break;
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        case 0:
          //Remove the first char of the string and add the input at the end:
          //if(tempTime[selected-1] == "0"){
            tempTime.remove(0,1);
            tempTime += input;
          //}
          //else{
          //  error = true;
          //}
          updateScreen();
          break;
       case 10: //Enter?
          //use function to start timer here
          preset[selected-1] = tempTime;
          lcd.setCursor(0,0);
          lcd.print("DONE       ");
          lcd.setCursor(0,1);
          lcd.print("           ");
          shift = true;
          selected = 0;
          tempTime = "0000";
          break;

       default:
          error = true;
          break;
    }
  }
}

//**********************************************************************************************************//
//MAIN:
void loop() 
{
  //Getting input; customKey == NULL if there is none
  char customKey = userKeypad.getKey();
  //Check if there's an interrupt or there is time left:
  if (customKey){
    String caseKey = "";
    caseKey += getInt(customKey);
    int caseKeyInt = caseKey.toInt();
    Serial.println(customKey);
    
    //lcd.setCursor(0,0);
    //lcd.print(customKey);
    //lcd.print(":");
    //lcd.print(caseKeyInt);
    
    if (not shift){
       //checkKey(caseKeyInt);
    }
    else{
      if(selected == 0){
        //checkShift(caseKeyInt);
      }
      else{
        //changeSelected(caseKeyInt);
      }
    }
  }

 if (timeLeft > 0){
    updateTime();
    timeLeft--;
    if (timeLeft == 0){
      lcd.setCursor(15,1);
      lcd.print("0");
      if(checkSensor(DOWN)){
        moveMotor(UP, stepsToDo);
      }
      lcd.setCursor(0,0);
      lcd.print("Hanger Up  ");
      lcd.setCursor(0,1);
      lcd.print("           ");
      if(checkSensor(UP)){
        moveMotor(DOWN, stepsToDo);
      }
    }
 }
 if (changePreset){
    if (blinkTime){    
      lcd.setCursor(11,1);    
      lcd.print(tempTime[0]);
      lcd.print(tempTime[1]);
      lcd.print(":");
      lcd.print(tempTime[2]);
      lcd.print(tempTime[3]);
      if(blinkDelay >= 500){
        blinkTime = false;
        blinkDelay = 0;
      }
      else{
        blinkDelay++;
      }
    }
    else{
      lcd.setCursor(11,1);    
      lcd.print("     ");
      if(blinkDelay >= 500){
        blinkTime = true;
        blinkDelay = 0;
      }
      else{
        blinkDelay++;
      }
    }
 }

}
