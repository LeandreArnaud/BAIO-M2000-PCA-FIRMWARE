#include <Joystick.h>
#include "Adafruit_LEDBackpack.h"
#define DCSBIOS_DEFAULT_SERIAL
#include "DcsBios.h"

/********* PINs SETUP **********/
const int PCA_SDA = 2;
const int PCA_SCL = 3;
const int PCAlatchPin = 7;
const int PCAdataPin = 4;
const int PCAclockPin = 6;
const byte PCAbacklightPin = 5;



/********* INIT VALUES AND CST **********/
byte PCAvalues[2] = {255, 255};
const byte registreLength = 8;


Joystick_ Joystick(
  0x04, // id of the gamepad, icrease in other pads to avoid conflict
  0x05, //Gamepad
  13, // button
  0, // hat
  false, // X
  false, // Y
  false, // Z
  false, // Rx
  false, // Ry
  false, // Rz
  false, // rudder
  false, // throttle
  false, // rudder
  false, // rudder
  false // steering
);

Adafruit_LEDBackpack matrix = Adafruit_LEDBackpack();




/********* SETUP **********/
void setup() {
  DcsBios::setup();

  matrix.begin(0x70);  // pass in the address 70 or 74
  matrix.setBrightness(15);
  matrix.setDisplayState(true);

  pinMode(PCAbacklightPin, OUTPUT);

  pinMode(PCAlatchPin, OUTPUT);
  pinMode(PCAclockPin, OUTPUT);
  pinMode(PCAdataPin, INPUT);

  Joystick.begin();

  // debug
  // Serial.begin(9600);

  // init digits
  for (uint8_t i=0; i<8; i++) {
    matrix.displaybuffer[i] = 0b0000000000000111; // buttons, digitR, digitL
    delay(100);
  }
  matrix.writeDisplay();
  analogWrite(PCAbacklightPin, 255);

  delay(1000);
}






/********* DCS BIOS **********/
// backlight
void onConsolePanelLgtKnobChange(unsigned int newValue) {
    analogWrite(PCAbacklightPin, newValue/256);
}
DcsBios::IntegerBuffer consolePanelLgtKnobBuffer(0x72A0, 0xffff, 0, onConsolePanelLgtKnobChange);




/********* LOOP **********/
void loop() {
  scanPCA();
  delay(10);
}


void scanPCA() {
  digitalWrite(PCAlatchPin,1);
  delayMicroseconds(20);
  digitalWrite(PCAlatchPin,0);

  for (int k=0; k<2; k++) {
    for (int i=7; i>=0; i--) {
      digitalWrite(PCAclockPin, 0);
      delayMicroseconds(2);
      bool value = digitalRead(PCAdataPin);
      
      // if value has changed
      if (value != bitRead(PCAvalues[k], i)) {
        bitWrite(PCAvalues[k], i, value);

        Joystick.setButton(registreLength*k+i, value);
        // debug
        // Serial.println(registreLength*k+i);
        // Serial.println(value);
        // Serial.println("----");
      }

      digitalWrite(PCAclockPin, 1);
      delayMicroseconds(2);
    }
  }
}


