#include <LiquidCrystal.h>
#include <Wire.h>
#include <Keypad.h>

//Preset:
String preset[3] = {"0015","0030","0100"}; //"MMSS"

//LCD pins:
const int rs = 12, en = 11, d0 = 23, d1 = 27, d2 = 31, d3 = 35, d4 = 34, d5 = 30, d6 = 26, d7 = 22;
LiquidCrystal lcd(rs, en, d0, d1, d2, d3, d4, d5, d6, d7);

//MOTOR:
#define pwmPin 13
#define dirPin 53

//Keypad:
const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = 
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

//Timer:
String timeIN = "0000";
String tempTime = "0000";
int timeLeft = 0; //should always be in seconds
int selected = 0; //selected to be changed

//Bool:
bool error = false;
bool cancel = false;
bool shift = false;
bool calibrate = false;
bool changePreset = false;
bool blinkTime = false;

//SETUP
void setup() 
{

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

//MOTOR GO UP
void moveUp(){
  digitalWrite(dirPin, HIGH);
  analogWrite(pwmPin, 255);
  delay(100);
}

//UPDATES JUST TIME
void updateTime(){
  lcd.setCursor(0,1);
  lcd.print(timeLeft);
  int minutes, seconds;
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
    delay(500);
  }
  lcd.setCursor(0,1);
  if (selected != 0){
    lcd.print("Preset");
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
    lcd.print("ON");
  }
}

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

//CHECKS KEY AND CORRESPONDS THE RIGHT ACTION
void checkKey(int input){
  switch(input){
   case 11: //Cancel?
      //Use Function to cancel timer here
      cancel = true;
      timeIN = "0000";
      lcd.setCursor(0,1);
      lcd.print(timeIN);
      timeLeft = 0;
      updateScreen();
      break;
   case 12: //Shift fn?
      shift = true;
      updateScreen();
      lcd.setCursor(0,0);
      lcd.print("SHIFT");
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
        updateScreen();
      }
      break;
    case 2:
      if (calibrate){
        //moveUp(); #TODO#
      }
      break;
    case 3:
      if (calibrate){
        //moveDown();
      }
      break;
    case 4://Change Preset
      if(not calibrate){
        changePreset = true;
        updateScreen();
      }
      break;
    case 10: //Enter?
      calibrate = false;
      changePreset = false;
      shift = false;
      break;
   case 11: //Cancel?
      calibrate = false;
      changePreset = false;
      shift = false;
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

   default:
      break;
  }
}

void changeSelected(int input){
  if (changePreset){
      switch(input){
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
          if(tempTime[0] == "0"){
            tempTime.remove(0,1);
            tempTime += input;
          }
          else{
            error = true;
          }
          updateScreen();
          break;
       case 10: //Enter?
          //use function to start timer here
          preset[selected-1] = tempTime;
          selected = 0;
          break;
       case 11: //Cancel?
          //Use Function to cancel timer here
          selected = 0;
          updateScreen();
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
          error = true;
          break;
    }
  }
  if (blinkTime){    
    lcd.setCursor(1,11);    
    lcd.print(tempTime[0]);
    lcd.print(tempTime[1]);
    lcd.print(":");
    lcd.print(tempTime[2]);
    lcd.print(tempTime[3]);
    blinkTime = false;
  }
  else{
    lcd.setCursor(1,11);    
    lcd.print("     ");
    blinkTime = true;
  }
}
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
    lcd.setCursor(0,0);
    lcd.print(customKey);
    lcd.print(":");
    lcd.print(caseKeyInt);
    
    if (not shift){
       checkKey(caseKeyInt);
    }
    else{
      if(selected == 0){
        checkShift(caseKeyInt);
      }
      else{
        changeSelected(caseKeyInt);
      }
    }
  }

 else if (timeLeft > 0){
    updateTime();
    timeLeft--;
    if (timeLeft == 0){
      lcd.setCursor(15,1);
      lcd.print("0");
      for(int temp = 0; temp <= 20; temp++){
        moveUp(); 
      }
      analogWrite(pwmPin, 112);
      delay(200);
      analogWrite(pwmPin, 0);
    }
 }
}
