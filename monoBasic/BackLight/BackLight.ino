#include <monoBasic.h>


monoBasic lcd;


void setup() {
lcd.begin(); //Initialize the IO.
lcd.clear(); //Clears the LCD
lcd.line(0);
lcd.column(0);
lcd.print("MonoView!");

lcd.line(2);
lcd.column(5);
lcd.print("BackLight Demo");
}

void loop() {

  int m=0;
  char numberBuffer[5];
  for(m=255;m>1;m=m-5)
  {
    lcd.line(4);
    lcd.column(39);
    sprintf(numberBuffer,"%.3d",m);
    lcd.print(numberBuffer);
    delay(100);
    lcd.backlight(m);
    
  }
    delay(1000);
  for(m=0;m<256;m=m+5)
  {
    lcd.line(4);
    lcd.column(39);
    sprintf(numberBuffer,"%.3d",m);
    lcd.print(numberBuffer);
    delay(100);
    lcd.backlight(m);
  }
    delay(1000);
}

