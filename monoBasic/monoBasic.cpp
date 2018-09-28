/*
  Written by Mohammed Rezwanul Islam
*/

#include "Arduino.h"
#include "monoBasic.h"

monoBasic::monoBasic(void)

{

	 _SCKPin = 15;
	 _CSPin = 7;
	 _SDAPin = 14;

   //set pin directions
  pinMode(_CSPin, OUTPUT);
  pinMode(_SDAPin, OUTPUT);
  pinMode(_SCKPin, OUTPUT);

  pinMode(6, OUTPUT);
  digitalWrite(6, HIGH);
 
  //disable monoBasic to start with 
  digitalWrite(_CSPin, HIGH);
  digitalWrite(_SDAPin, LOW);
  digitalWrite(_SCKPin, LOW);

  

 }
 

void monoBasic::backlight(byte bklt)
{
analogWrite(6, bklt);
}
 
void monoBasic::contrast(byte con)
{
  if(con<0) {con=0;}
  if(con>32) {con=32;}

con = con | 0x80;
monoBasic::command(con);  
}


void monoBasic::displayAllPointsOn()
{
  monoBasic::command(0xA5);
}


void monoBasic::displayAllPointsOff()
{
  monoBasic::command(0xA4);
}


void monoBasic::softwareReset()
{
  monoBasic::command(0xE2);  //reset
}


 
void monoBasic::line(byte line)
{
  if (line<0){line = 0;}
  if (line>8){line = 8;}
  
  line = 176+line;
  
  monoBasic::command(line);  //set line
/*
  monoBasic::command(0x10);  //set col=0 upper 3 bits
  monoBasic::command(0x00);  //set col=0 lower 4 bits
*/
  monoBasic::column(0x00);
}

 void monoBasic::column(byte payload)
{
if(payload<0){payload=0;}
if(payload>95){payload=95;}

byte lower = 0x0F;
byte upper = 0x70;

lower = payload & 0x0F;
upper =payload &0x70;

upper = upper>>4;
 
upper = 0x10 | upper;
 
monoBasic::command(upper);
monoBasic::command(lower);
}

void monoBasic::scroll(byte payload)
{
/*  payload = payload+64;
  if (payload >127){payload = 127;}
 */
  payload =64+ payload;
  
  if (payload <0){payload = 64;}
  if (payload >127){payload = 127;}
  monoBasic::command(payload);
}

void monoBasic::displayOff()
{
  monoBasic::command(0xAE);
}

void monoBasic::displayOn()
{
  monoBasic::command(0xAF);
}

void monoBasic::displayNormal()
{
  monoBasic::command(0xA6);
}

void monoBasic::displayInverse()
{
  monoBasic::command(0xA7);
}

 void monoBasic::println(char *characters)
{
  monoBasic::command(0x10);  //set column=0 upper 3 bits
  monoBasic::command(0x00);  //set column=0 lower 4 bits

  while (*characters)
  {
    monoBasic::character(*characters++);
  }
}


 
 void monoBasic::print(char *characters)
{
  while (*characters)
  {
    monoBasic::character(*characters++);
  }
}

 void monoBasic::print(int num)
{
char c[8];
itoa(num,c,10);
monoBasic::print(c);
}

void monoBasic::println(int num)
{
char c[8];
itoa(num,c,10);
monoBasic::println(c);
}


void monoBasic::character(char character)
{
  for (int index = 0; index < 5; index++)
  {
	byte myByte = 0;
	myByte = pgm_read_byte(&(ASCII[(byte)character - 0x20][index]));

     monoBasic::data(myByte);  
  
  }
  monoBasic::data(0x00);  
}


void monoBasic::clear()
{
  
  //display off
  monoBasic::command(0xAE);
  
  for (int i = 0; i < 864; i++)
  {
    monoBasic::data(0x00);  
  }

  monoBasic::command(0xB0);  //set page address
  monoBasic::command(0x10);  //set col=0 upper 3 bits
  monoBasic::command(0x00);  //set col=0 lower 4 bits

  monoBasic::command(0x40);  //set row 0

  //display on
  monoBasic::command(0xAF);

}

void monoBasic::command(byte payload)
{
  
  //select monoPro
  //  digitalWrite(_CSPin, LOW);
  cbi(PORTD,0x07);

  //write data/command bit
  //0=command & 1= data 
  cbi(PORTC,0x00);

  //digitalWrite(_SCKPin, HIGH);
  sbi(PORTC,0x01);
  //digitalWrite(_SCKPin, LOW);
  cbi(PORTC,0x01);

  //write payload 8 bits
  for(int i=7;i>=0;i--)
  {
      if((payload>>i)&1 ==1)
      {sbi(PORTC,0x00);}
      else
      {cbi(PORTC,0x00);}
      //toggle clock
    sbi(PORTC,0x01);
    cbi(PORTC,0x01);
  }

//  digitalWrite(_CSPin, HIGH);
  sbi(PORTD,0x07);
}


void monoBasic::begin()
{
  monoBasic::command(0xE2);  //reset
  delay(10);
  monoBasic::command(0xA4);  //power save off
  monoBasic::command(0x2F);  //power control set
  monoBasic::command(0xB0);  //set page address
  monoBasic::command(0xA0);  //normal operation
  monoBasic::command(0x10);  //set col=0 upper 3 bits
  monoBasic::command(0x00);  //set col=0 lower 4 bits


  monoBasic::contrast(0x0E);  //set contrast
  
  monoBasic::command(0xAF);  //monoBasic display on
  delay(500);
}


void monoBasic::data(byte payload)
{
  //select monoPro
  //  digitalWrite(_CSPin, LOW);
  cbi(PORTD,0x07);

  //write data/command bit
  //0=command & 1= data 
  sbi(PORTC,0x00);

  //digitalWrite(_SCKPin, HIGH);
  sbi(PORTC,0x01);
  //digitalWrite(_SCKPin, LOW);
  cbi(PORTC,0x01);

  //write payload 8 bits
  for(int i=7;i>=0;i--)
  {
      if((payload>>i)&1 ==1)
      {sbi(PORTC,0x00);}
      else
      {cbi(PORTC,0x00);}
      //toggle clock
    sbi(PORTC,0x01);
    cbi(PORTC,0x01);
  }
}
