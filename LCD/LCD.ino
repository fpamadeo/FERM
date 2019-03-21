#include <LiquidCrystal.h>
#include <Wire.h>
#include <Keypad.h>

const int rs = 12, en = 11, d4 = 34, d5 = 30, d6 = 26, d7 = 22;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

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

String timeIN = "0000";


void setup() 
{

  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Enter time for frying");
  lcd.setCursor(0, 1);
  lcd.print(timeIN);
}

void loop() 
{
  char customKey = userKeypad.getKey();
  if (customKey){
    lcd.clear();
    lcd.print("Enter time for frying");
    lcd.setCursor(0, 1); 
    timeIN.remove(0,1);
    timeIN += customKey;
    lcd.print(timeIN); 
  }
}
