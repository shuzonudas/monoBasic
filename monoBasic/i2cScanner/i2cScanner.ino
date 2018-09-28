/*
Original code from
https://playground.arduino.cc/Main/I2cScanner

modified by Rezwan for monoView
*/
#include <Arduino.h>
#include <monoBasic.h>
#include <Wire.h>


monoBasic lcd;

  byte error, address;
  int nDevices;
char buffer[50];

void setup()
{
	Wire.begin();
	lcd.begin();
	lcd.clear();
	lcd.line(0);
	sprintf(buffer,"I2C Scanner");
		lcd.println(buffer);
    
	
	}

void loop()
{

lcd.line(1);
	sprintf(buffer,"Scanning...");
		lcd.println(buffer);
  nDevices = 0;
  for(address = 1; address < 127; address++ ) 
  {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

	lcd.line(2);
    if (error == 0)
    {
		sprintf(buffer,"I2C at adr: 0x%0x",address);
		lcd.println(buffer);
		nDevices++;
	}
    else if (error==4) 
    {
		sprintf(buffer,"error at adr: 0x%0x",address);
		lcd.println(buffer);
    }    
  }
  if (nDevices == 0)
		sprintf(buffer,"No device        ");
		lcd.println(buffer);
  

  delay(1000);           // wait 1 second
}

