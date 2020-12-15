/*
pcf2116.h V0.1
Arduino - Library for pcf2116 - i2c LCD-Display
creatured by Martin Demuth, May 29th 2016
released into Public Domain, without any warranty!
###################
Usage:
-->next 3 lines mandatory in your Code! 
#include <pcf2116c.h> 				include the Header File
Pcf yourLcd(0x3A);  //				create an instance for your i2cDisplay with i2cAddress
yourLcd.init();						initialize Display

-->use of Display with:
yourLcd.printTxt(LineNo, ColumnNo, Textstring)
yourLcd.printVal(LineNo, ColumnNo, num. Value)
yourLcd.clearLine(LineNo, ColumnStart, ColumnEnd)
-->
find more info in Examples directory of pcf2116c
*/

#ifndef pcf2116_h
#define pcf2116_h

#include "Arduino.h"

class Pcf
{
	public:
		Pcf(char myI2cAdr);	// mod1: prev: Pcf(char _myI2cAdr);	
		void init();
		void printTxt(int row, int col, String strgtxt);
		void printVal(int row, int col, int data);
		void clearLine(int row,int colStart, int colEnd);
	private:
		void setPos(int row, int col); //mod2: "set Pos(...)"moved from public to private
		char _myI2cAdr;
};
#endif
