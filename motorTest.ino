void setup() 
{
  pinMode(22, OUTPUT);
  // put your setup code here, to run once:

}

void loop() 
{


for (int i=0; i <= 255; i++)
{
      analogWrite(8, i);
      delay(10);
 }


/*
delay(1000);
digitalWrite(22, HIGH);
analogWrite(8, 255);
delay(500);
analogWrite(8, 200);
delay(500);
analogWrite(8, 150);
delay(500);
analogWrite(8, 100);
delay(500);
analogWrite(8, 50);
delay(500);
analogWrite(8, 0);
delay(500);


digitalWrite(22, LOW);
analogWrite(8, 50);
delay(500);
analogWrite(8, 100);
delay(500);
analogWrite(8, 150);
delay(500);
analogWrite(8, 200);
delay(500);
analogWrite(8, 255);
delay(1000);
//analogWrite(8, 0);
//delay(1000);

 
*/
  
  // put your main code here, to run repeatedly:

}
