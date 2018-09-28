#include <monoBasic.h>


monoBasic lcd;
void setup() {

  
lcd.begin();
lcd.clear();

lcd.line(0);
lcd.print("This is line 0");
delay(1000);
lcd.line(3);
lcd.print("This is line 3");
delay(1000);
lcd.line(7);
lcd.print("This is line 7");
delay(1000);

lcd.clear();
delay(1000);
lcd.line(0);
lcd.print("characters");
lcd.line(2);
lcd.print("int ");
lcd.print(12345678);
}

void loop() {

}

