#include <monoBasic.h>


monoBasic lcd;


void setup() {
lcd.begin(); //Initialize the IO.
lcd.clear(); //Clears the LCD
lcd.line(3);
lcd.column(25);
lcd.print("MonoView!");


}

void loop() {

}

