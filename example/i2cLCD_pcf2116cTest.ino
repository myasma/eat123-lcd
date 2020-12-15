
#include <pcf2116c.h>

//create Instance for I2c-Lcd Modul with PCF2116c-controller (e.g.EAT123A-I2C)
//with BaseAddress 0x74 (shifted right by 1 to make it compatible to Wire-library!)
Pcf myLcd(0x3A);

int loopcount = 0;

void setup() {
//for simplifying evaluation, PowerSupply for the i2c-LCD is taken from PIN A0,
// therefor a DY-reset is done every time on Upload or reset to the Arduino-Board. 

pinMode(A0,OUTPUT);  
digitalWrite(A0, LOW);
delay(500);
digitalWrite(A0,HIGH);
delay(500);
Serial.begin(9600);
delay(100);
Serial.println("starte LCD-Init");
myLcd.init();
Serial.println("done");

}

void loop() {
//Test
Serial.println("Test in progress");
// ".printVal" currently only prints values from  variables of type "int" (-32767:32767);
myLcd.printVal(1,0,32767); //print max. numeric Value
myLcd.printTxt(2,0,"ABCDEFGHIJKL"); //print textual string (Don't forget "" !)
myLcd.printTxt(3,0,"M1O2Q3S4U5WX");
delay(1000);
myLcd.clearLine(1,0,11); //delete in Line1 Column 0 to 11 (complete line!)
delay(1000);
myLcd.clearLine(2,0,11); //delete in Line2 0 to 11
delay(1000);
myLcd.clearLine(3,0,11); //del Line3 0 to 11
delay(1000);  
loopcount++;
 myLcd.printTxt(1,2,"i2c lcd");
 myLcd.printTxt(2,0,"pcf2116c: ");
 myLcd.printVal(3,6,loopcount); // print Value of int-variable "loopcount"
 myLcd.printTxt(3,0,"loop: "); 
 delay(2000);
 myLcd.clearLine(1,0,5); //delete Line1 from Column 0 to Column 5
 delay(1000);
 myLcd.clearLine(2,4,5); //delete Line2, Column 4 to 5
 delay(1000);
 myLcd.clearLine(3,5,11);
 delay(1000);
}
