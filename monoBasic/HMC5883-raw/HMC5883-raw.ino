#include <monoBasic.h>
#include <Wire.h> //I2C Library

#define addr 0x1E //I2C Address of HMC5883

monoBasic lcd;
char numberBuffer[30];


void setup()
{
    lcd.begin(); //Initialize the IO.
    lcd.clear(); //Clears the LCD

    lcd.line(0);
    lcd.column(0);
    lcd.println("monoView");
    lcd.line(2);
    lcd.println("  HMC5883 demo");
  
    Wire.begin();
    Wire.beginTransmission(addr); //start talking
    Wire.write(0x02); // Set the Register
    Wire.write(0x00); // Measure continuously 
    Wire.endTransmission();
}


void loop(){
  
int x,y,z; //triple axis data

//Tell the HMC what regist to begin writing data into
    Wire.beginTransmission(addr);
    Wire.write(0x03); //start with register 3.
    Wire.endTransmission();
    
    
    //Read the data.. 2 bytes for each axis.. 6 total bytes
    Wire.requestFrom(addr, 6);
  if(6<=Wire.available()){
        x = Wire.read()<<8; //MSB  x 
        x |= Wire.read(); //LSB  x
        z = Wire.read()<<8; //MSB  z
        z |= Wire.read(); //LSB z
        y = Wire.read()<<8; //MSB y
        y |= Wire.read(); //LSB y
    }
  

  
    lcd.line(4);
    sprintf(numberBuffer,"X: %.4d  ",x);
    lcd.print(numberBuffer);
    lcd.line(5);
    sprintf(numberBuffer,"Y: %.4d  ",y);
    lcd.print(numberBuffer);
    lcd.line(6);
    sprintf(numberBuffer,"Z: %.4d  ",z);
    lcd.print(numberBuffer);

    delay(500);

}

