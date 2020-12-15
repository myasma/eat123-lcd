
//~ pcf2116.cpp V0.1
 //~ Arduino - Library for pcf2116 - i2c LCD-Display
 //~ creatured by Martin Demuth, May 29th 2016
 //~ released into Public Domain, without any warranty!
 

#include "Arduino.h"
#include "Wire.h"
#include "pcf2116c.h"

Pcf::Pcf(char myI2cAdr)
{
_myI2cAdr = myI2cAdr;
	}	
char cDigit[24];
int m=0;

	//--------------------------------Init------------------------------->
//void Pcf::init(char _myI2cAdr) {
void Pcf::init(){
Wire.begin(_myI2cAdr);
Wire.beginTransmission(_myI2cAdr); // transmit to device
Wire.write(0x00); //ControlByte set RS und RW for following DataBytes
Wire.write(0x04);  //set mode incecrement
Wire.write(0x0E); //turn on Display, Cursor Off
Wire.write(0x2E);  //Select 3LineDisplay 0x2E !!! Voltage Generator enabled!!
//Wire.write(0x2C);  //Select 3LineDisplay 0x2E !!! Voltage Generator disabled!!
Wire.write(0x01); // reset am Schluss, benötigt mindestens 165µs!!
delay(2);
	if (Wire.endTransmission() != 0){
Serial.print("Wire NOK");
 }else {
	 Serial.print("Init done");
 }
 }
//--------------funktion CursorPositionierung------>
void Pcf::setPos(int row,int col) {
int Pos;
Pos =  (96 + (row * 32) + col);
byte myddadr(Pos);
Wire.beginTransmission(_myI2cAdr);
Wire.write(0x00);
Wire.write(myddadr); //setze Cursor an Pos 
Wire.endTransmission();
delay(10);
}
//---------------------convert ints 2 digits-------->
int int2charray(int myInt) {
m = 0;
char Dig[24];
//char cDigit[24];
int charIndex = 0;
int myIntQ = myInt;
if (myInt < 0) {
myInt = abs(myInt);
m = 0; 
}
do {   
Dig[charIndex] = (((myInt%10) + 0x30));
myInt = myInt/10;
++charIndex;
} while (myInt != 0);
if (myIntQ < 0) {
  Dig[charIndex] = '-'; 
} else {
  --charIndex;
}
int k = charIndex;
for ( k; k >= 0; k--) {
cDigit[m]= Dig[k];
char Zeichen = char(Dig[k]);
m=m+1;
}
return m;
}
//----------------------------------------------->
void Pcf::printVal(int row, int col, int data) {
int m = int2charray(data); //zerlege int Zahl in Digits (Array"cDigit") und gib die Anzahl der Digits in "m" zurück
//char cDigit[24];
setPos(row,col);
int i = 0;
Wire.beginTransmission(_myI2cAdr);
Wire.write(0x40);
for (i; i< m; i++) {
bitSet(cDigit[i],7); //setze msb für umgekehrten Font des pcf2116C -lcd_chip.
Wire.write(cDigit[i]);
}
Wire.endTransmission();
i = 0;
for (i=0; i< m; ++i) {
}
i = 0;
for (i=0; i< m; ++i) {
  cDigit[i] = {};
}
}
//--------------------------------------------------->
//---------------clearLine--------------------------->
void Pcf::clearLine(int row,int colStart, int colEnd ) {
setPos(row,colStart);
int i = 0;
Wire.beginTransmission(_myI2cAdr);
Wire.write(0x40);
for (i=0; i<= (colEnd - colStart); i++) {
Wire.write(0x20);
}
Wire.endTransmission();
}
//----------------------------------------------------->
//-------------------printText------------------------->
void Pcf::printTxt(int row, int col, String strgtxt) {
int l = strgtxt.length();
char txt[l+1];
strgtxt.toCharArray(txt,l+1);
int i = 0;
for (i = 0; i < (sizeof(txt)-1); i++) {
bitSet(txt[i],7);
}
setPos(row,col);
Wire.beginTransmission(_myI2cAdr);
Wire.write(0x40);
Wire.write(txt); 
Wire.endTransmission();
}

