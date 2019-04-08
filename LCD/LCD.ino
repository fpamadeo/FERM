#include <LiquidCrystal.h>
#include <Wire.h>
#include <Keypad.h>

//LCD pins:
const int rs = 12, en = 11, d0 = 23, d1 = 27, d2 = 31, d3 = 35, d4 = 34, d5 = 30, d6 = 26, d7 = 22;
LiquidCrystal lcd(rs, en, d0, d1, d2, d3, d4, d5, d6, d7);

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

//GLOBAL Variables
//Timer:
String timeIN = "0000";
int timeLeft = 0; //should always be in seconds
bool error = false;

void setup() 
{

  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.setCursor(0,11);    
  lcd.print("TIME:)
  lcd.setCursor(1,11);    
  lcd.print(timeIN[0]);
  lcd.print(timeIN[1]);
  lcd.print(":");
  lcd.print(timeIN[2]);
  lcd.print(timeIN[3]);
}

void updateTime(){
  int minutes, seconds;
  minutes = timeLeft / 60;
  seconds = timeLeft % 60;
  if(minutes > 99){
    minutes = 99;
  }
  lcd.setCursor(1,11);    
  lcd.print(minutes/10);
  lcd.print(minutes%10);
  lcd.print(":");
  lcd.print(seconds/10);
  lcd.print(seconds/10);
}

void checkKey(char input){
  switch(input){
    case "1":
    case "2":
    case "3":
    case "4":
    case "5":
    case "6":
    case "7":
    case "8":
    case "9":
    case "0":
      //Remove the first char of the string and add the input at the end:
      if(timeIN[0] == "0"){
        timeIN.remove(0,1);
        timeIN += input;
      }
      else{
        error = true;
      }
      break;
   case "*": //Enter?
      //use function to start timer here
   case "#": //Cancel?
      //Use Function to cancel timer here
   case "A": //Shift fn?
   
   case "B": //Preset 1?
   case "C": //Preset 2?
   case "D": //Preset 3?
   default:
      error = true;
      break;
  }
}
void loop() 
{
  //Getting input; customKey == NULL if there is none
  char customKey = userKeypad.getKey();

  //Check if there's an interrupt or there is time left:
  if (customKey){
    checkKey(customKey);
  }

 if (timeLeft > 0){
    updateTime();
    timeLeft--;
 }
}
