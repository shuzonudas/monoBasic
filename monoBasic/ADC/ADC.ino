#include <monoBasic.h>

monoBasic lcd;

void setup() {
lcd.begin(); //Initialize the IO.
lcd.clear(); //Clears the LCD
lcd.line(0);
lcd.column(0);
lcd.print("MonoView!");

lcd.line(1);
lcd.column(24);
lcd.print("ADC Demo");

}


void loop() {
int adc=0;
char numberBuffer[30];

adc = analogRead(2);
lcd.line(2);
sprintf(numberBuffer,"ADC A2:%.4d",adc);
lcd.print(numberBuffer);
delay(10);

adc = analogRead(3);
lcd.line(3);
sprintf(numberBuffer,"ADC A3:%.4d",adc);
lcd.print(numberBuffer);
delay(10);

adc = analogRead(4);
lcd.line(4);
sprintf(numberBuffer,"SCA A4:%.4d",adc);
lcd.print(numberBuffer);
delay(10);

adc = analogRead(5);
lcd.line(5);
sprintf(numberBuffer,"SCL A5:%.4d",adc);
lcd.print(numberBuffer);
delay(10);

adc = analogRead(6);
lcd.line(6);
sprintf(numberBuffer,"ADC A6:%.4d",adc);
lcd.print(numberBuffer);
delay(10);

adc = analogRead(7);
lcd.line(7);
sprintf(numberBuffer,"ADC A7:%.4d",adc);
lcd.print(numberBuffer);
delay(10);

}

