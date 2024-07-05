#include <Joystick.h>
#include "Adafruit_LEDBackpack.h"
#define DCSBIOS_DEFAULT_SERIAL
#include "DcsBios.h"

#include "PinsAndInitConfig.h"



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
    matrix.displaybuffer[i] = 0b0000000000000000;
    delay(100);
  }
  matrix.writeDisplay();
  analogWrite(PCAbacklightPin, 255);

  delay(1000);
}






/********* DCS BIOS **********/
// GUN BUTTON
void onGunModeKl1Change(unsigned int newValue) {
    bitWrite(matrix.displaybuffer[2], 0, newValue);
    matrix.writeDisplay();
}
DcsBios::IntegerBuffer gunModeKl1Buffer(0x72c0, 0x0004, 2, onGunModeKl1Change);
void onGunModeKl2Change(unsigned int newValue) {
    bitWrite(matrix.displaybuffer[1], 0, newValue);
    matrix.writeDisplay();
}
DcsBios::IntegerBuffer gunModeKl2Buffer(0x72c0, 0x0008, 3, onGunModeKl2Change);



// READY LIGHTS
void onWeapon1RChange(unsigned int newValue) {
    bitWrite(matrix.displaybuffer[1], 1, newValue);
    matrix.writeDisplay();
}
DcsBios::IntegerBuffer weapon1RBuffer(0x72c0, 0x0020, 5, onWeapon1RChange);
void onWeapon2RChange(unsigned int newValue) {
    bitWrite(matrix.displaybuffer[1], 2, newValue);
    matrix.writeDisplay();
}
DcsBios::IntegerBuffer weapon2RBuffer(0x72c0, 0x0080, 7, onWeapon2RChange);
void onWeapon3RChange(unsigned int newValue) {
    bitWrite(matrix.displaybuffer[1], 3, newValue);
    matrix.writeDisplay();
}
DcsBios::IntegerBuffer weapon3RBuffer(0x72c0, 0x0200, 9, onWeapon3RChange);
void onWeapon4RChange(unsigned int newValue) {
    bitWrite(matrix.displaybuffer[1], 4, newValue);
    matrix.writeDisplay();
}
DcsBios::IntegerBuffer weapon4RBuffer(0x72c0, 0x0800, 11, onWeapon4RChange);
void onWeapon5RChange(unsigned int newValue) {
    bitWrite(matrix.displaybuffer[1], 5, newValue);
    matrix.writeDisplay();
}
DcsBios::IntegerBuffer weapon5RBuffer(0x72c0, 0x2000, 13, onWeapon5RChange);


// SELECTED BUTTONS LIGHT
void onWeapon1SChange(unsigned int newValue) {
    bitWrite(matrix.displaybuffer[2], 1, newValue);
    matrix.writeDisplay();
}
DcsBios::IntegerBuffer weapon1SBuffer(0x72c0, 0x0010, 4, onWeapon1SChange);
void onWeapon2SChange(unsigned int newValue) {
    bitWrite(matrix.displaybuffer[2], 2, newValue);
    matrix.writeDisplay();
}
DcsBios::IntegerBuffer weapon2SBuffer(0x72c0, 0x0040, 6, onWeapon2SChange);
void onWeapon3SChange(unsigned int newValue) {
    bitWrite(matrix.displaybuffer[2], 3, newValue);
    matrix.writeDisplay();
}
DcsBios::IntegerBuffer weapon3SBuffer(0x72c0, 0x0100, 8, onWeapon3SChange);
void onWeapon4SChange(unsigned int newValue) {
    bitWrite(matrix.displaybuffer[2], 4, newValue);
    matrix.writeDisplay();
}
DcsBios::IntegerBuffer weapon4SBuffer(0x72c0, 0x0400, 10, onWeapon4SChange);
void onWeapon5SChange(unsigned int newValue) {
    bitWrite(matrix.displaybuffer[2], 5, newValue);
    matrix.writeDisplay();
}
DcsBios::IntegerBuffer weapon5SBuffer(0x72c0, 0x1000, 12, onWeapon5SChange);


// SELECTED WEAPON LIGHT
void onPcaButton1SChange(unsigned int newValue) {
    bitWrite(matrix.displaybuffer[0], 0, newValue);
    matrix.writeDisplay();
}
DcsBios::IntegerBuffer pcaButton1SBuffer(0x72be, 0x2000, 13, onPcaButton1SChange);
void onPcaButton2SChange(unsigned int newValue) {
    bitWrite(matrix.displaybuffer[0], 1, newValue);
    matrix.writeDisplay();
}
DcsBios::IntegerBuffer pcaButton2SBuffer(0x72be, 0x4000, 14, onPcaButton2SChange);
void onPcaButton3SChange(unsigned int newValue) {
    bitWrite(matrix.displaybuffer[0], 2, newValue);
    matrix.writeDisplay();
}
DcsBios::IntegerBuffer pcaButton3SBuffer(0x72be, 0x8000, 15, onPcaButton3SChange);
void onPcaButton4SChange(unsigned int newValue) {
    bitWrite(matrix.displaybuffer[0], 3, newValue);
    matrix.writeDisplay();
}
DcsBios::IntegerBuffer pcaButton4SBuffer(0x72c0, 0x0001, 0, onPcaButton4SChange);
void onPcaButton5SChange(unsigned int newValue) {
    bitWrite(matrix.displaybuffer[0], 4, newValue);
    matrix.writeDisplay();
}
DcsBios::IntegerBuffer pcaButton5SBuffer(0x72c0, 0x0002, 1, onPcaButton5SChange);

// CONSOLE BACKLIGHT
void onDashPanelLgtKnobChange(unsigned int newValue) {
    analogWrite(PCAbacklightPin, newValue/256);
}
DcsBios::IntegerBuffer dashPanelLgtKnobBuffer(0x729c, 0xffff, 0, onDashPanelLgtKnobChange);
void onCautAdvLgtChange(unsigned int newValue) {
    matrix.setBrightness(newValue/4096);
}
DcsBios::IntegerBuffer cautAdvLgtBuffer(0x72a2, 0xffff, 0, onCautAdvLgtChange);




/********* LOOP **********/
void loop() {
  DcsBios::loop();

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

        // if dcs bios is not connected, change leds state
        if (!Serial.available() && value) {
          if (k == 0 && i <= 4) { // buttons
            matrix.displaybuffer[0] = 0b0000000000000000;
            bitWrite(matrix.displaybuffer[0], i, !bitRead(matrix.displaybuffer[0], i));
            matrix.writeDisplay();
          } else if (k != 1 || (i != 3 && i !=4)) { // if it is not a toggle
            matrix.displaybuffer[1] = 0b0000000000000000;
            matrix.displaybuffer[2] = 0b0000000000000000;
            int blablou = i-5;
            if (k == 1) blablou = i+3;
            bitWrite(matrix.displaybuffer[1], blablou, !bitRead(matrix.displaybuffer[1], blablou));
            bitWrite(matrix.displaybuffer[2], blablou, !bitRead(matrix.displaybuffer[2], blablou));
            matrix.writeDisplay();
          }
        }
      }

      digitalWrite(PCAclockPin, 1);
      delayMicroseconds(2);
    }
  }
}


