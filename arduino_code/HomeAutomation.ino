/*
  LiquidCrystal Library - Serial Input

  Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
  library works with all LCD displays that are compatible with the
  Hitachi HD44780 driver. There are many of them out there, and you
  can usually tell them by the 16-pin interface.

  This sketch displays text sent over the serial port
  (e.g. from the Serial Monitor) on an attached LCD.

  The circuit:
   LCD RS pin to digital pin 12
   LCD Enable pin to digital pin 11
   LCD D4 pin to digital pin 5
   LCD D5 pin to digital pin 4
   LCD D6 pin to digital pin 3
   LCD D7 pin to digital pin 2
   LCD R/W pin to ground
   10K resistor:
   ends to +5V and ground
   wiper to LCD VO pin (pin 3)

  Library originally added 18 Apr 2008
  by David A. Mellis
  library modified 5 Jul 2009
  by Limor Fried (http://www.ladyada.net)
  example added 9 Jul 2009
  by Tom Igoe
  modified 22 Nov 2010
  by Tom Igoe
  modified 7 Nov 2016
  by Arturo Guadalupi

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/LiquidCrystalSerialDisplay

*/

// include the library code:
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
const int lightsPin = 8;
const int fanPin = 10;
const int tvPin = 9;
String data = "";
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  // set up the LCD's number of columns and rows:
  digitalWrite(lightsPin, HIGH);
  digitalWrite(fanPin, HIGH);
  digitalWrite(tvPin, HIGH);
  pinMode(lightsPin, OUTPUT);
  pinMode(fanPin, OUTPUT);
  pinMode(tvPin, OUTPUT);
 
  lcd.begin(16, 2);
  //lcd.setCursor(0, 0);
  lcd.print("Welcome, Mahesh");
  lcd.setCursor(0, 1);
  lcd.print("No device:Active");
  // initialize the serial communications:
  Serial.begin(9600);
}

//lcd.setCursor(0, 0); // top left
//lcd.setCursor(15, 0); // top right
//lcd.setCursor(0, 1); // bottom left
//lcd.setCursor(15, 1); // bottom right

void clearSecondRow() {
  for (int i = 0; i < 16; i++)
  {
    lcd.setCursor(i, 1);
    lcd.write(" ");
  }
}

void loop() {
  // when characters arrive over the serial port...
  if (Serial.available()) {
    // wait a bit for the entire message to arrive
    delay(100);
    // read all the available characters
    while (Serial.available() > 0) {
      data = Serial.readString();
      // display each character to the LCD
      if (data == "lights_on") {
        clearSecondRow();
        digitalWrite(lightsPin, LOW);
        lcd.setCursor(0, 1);
        lcd.print("Lights: ON");
        Serial.println(1);
        //lcd.blink();
      } else if (data == "lights_off") {
        clearSecondRow();
        digitalWrite(lightsPin, HIGH);
        lcd.setCursor(0, 1);
        lcd.print("Lights: OFF");
        Serial.println(0);
        //lcd.blink();
      } else if (data == "fan_on") {
        clearSecondRow();
        digitalWrite(fanPin, LOW);
        lcd.setCursor(0, 1);
        lcd.print("Fan: ON");
        Serial.print(1);
        //lcd.blink();
      } else if (data == "fan_off") {
        clearSecondRow();
        digitalWrite(fanPin, HIGH);
        lcd.setCursor(0, 1);
        lcd.print("Fan: OFF");
        Serial.print(0);
        //lcd.blink();
      } else if (data == "tv_on") {
        clearSecondRow();
        digitalWrite(tvPin, LOW);
        lcd.setCursor(0, 1);
        lcd.print("TV: ON");
        Serial.print(1);
        //lcd.blink();
      } else if (data == "tv_off") {
        clearSecondRow();
        digitalWrite(tvPin, HIGH);
        lcd.setCursor(0, 1);
        lcd.print("TV: OFF");
        Serial.print(0);
        //lcd.blink();
      } else if (data == "turn_all_on") {
        clearSecondRow();
        digitalWrite(tvPin, LOW);
        digitalWrite(fanPin, LOW);
        digitalWrite(lightsPin, LOW);
        lcd.setCursor(0, 1);
        lcd.print("All turned: ON");
        Serial.print(1);
        //lcd.blink();
      } else if (data == "turn_all_off") {
        clearSecondRow();
        digitalWrite(tvPin, HIGH);
        digitalWrite(fanPin, HIGH);
        digitalWrite(lightsPin, HIGH);
        lcd.setCursor(0, 1);
        lcd.print("All turned: OFF");
        Serial.print(0);
        //lcd.blink();
      }
    }
  }
}
