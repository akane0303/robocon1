#include <PS3BT.h>
#include <PS3USB.h>
#include <usbhub.h>
#ifdef dobogusinclude

#include <spi4teensy3.h>
#endif
#include <SPI.h>
#include"analoog.h"

USB Usb;
BTD Btd(&Usb);
PS3BT PS3(&Btd);
//PS3BT PS3(&);

int pinmA[2] = {2, 3};

int pinmB[2] = {4, 5};

int pinmC[2] = {6, 7};

int pinmD[2] = {44, 46};



int pin_hand1 = 38;
int pin_hand2 = 39;

int pin_arm1 = 40;
int pin_arm2 = 41;


int direction(int x, int y) {
  double deg , rad;
  int pattern = 0;
  x -= 128;
  y = abs(y - 256) - 128;
  rad = atan2((double)y, (double)x);
  deg = rad * 180.0 / (atan(1.0) * 4.0);
  if (abs(x) > 16 || abs(y) > 16) {
    deg += 180.0;
    for (int i = 0; i < 8; i++) {
      if (deg >= 0.0 + (i * 45.0) && deg < 45.0 + (i * 45.0)) {//分割数を指定
        pattern = i + 1;
      }
    }
  }
  //Serial.print(x);
  //Serial.print(" ");
  //Serial.print(y);
  //Serial.print(" ");
  //Serial.println();
  //(pattern);
  return pattern;
}



void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

#if !defined(__MIPSEL__)
  while (!Serial);
#endif
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1);
  }
  Serial.print(F("\r\nPS3 Bluetooth Library Started"));
  pinMode(pinmA[0], OUTPUT);
  pinMode(pinmA[1], OUTPUT);
  pinMode(pinmB[0], OUTPUT);
  pinMode(pinmB[1], OUTPUT);
  pinMode(pinmC[0], OUTPUT);
  pinMode(pinmC[1], OUTPUT);
  pinMode(pinmD[0], OUTPUT);
  pinMode(pinmD[1], OUTPUT);
  pinMode(pin_hand1,OUTPUT);
  pinMode(pin_hand2,OUTPUT);
  pinMode(pin_arm1,OUTPUT);
  pinMode(pin_arm2,OUTPUT);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  Usb.Task();
  mo move(pinmA[0], pinmA[1]);
  mo move2(pinmB[0], pinmB[1]);
  mo move3(pinmC[0], pinmC[1]);
  mo move4(pinmD[0], pinmD[1]);

  omuni omuni1(move, move2, move3, move4);
  /*
    int x=LeftHatX;
    int y=RightHatY;
    x -= 128;
    y = abs(y - 256) - 128;
  */
  Usb.Task();
  if (PS3.PS3Connected || PS3.PS3NavigationConnected) {
    int p = 1;
    int lx = PS3.getAnalogHat(LeftHatX);
    int ly = PS3.getAnalogHat(LeftHatY);
    int ryy = PS3.getAnalogHat(RightHatY);
    int rxx = PS3.getAnalogHat(RightHatX);
    int x = (50 + (lx - 128)) * p;
    int y = (127 - (abs(ly - 256))) * 2;
    int x1 = abs(-50 + (lx - 128)) * p;
    int y1 = abs(-127 - (abs(ly - 256))) * 2;
    int rx = (127 + (rxx - 128)) * 2;
    int ry = (127 - abs(ryy - 256)) * 2;
    int rx1 = abs(-127 + (rxx - 128)) * 2;
    int ry1 = abs(-127 - (abs(ryy - 256))) * 2;

    Serial.print("lx:");
    Serial.print(lx);
    Serial.print(" ");
    Serial.print("ly:");
    Serial.print(ly);
    Serial.print(" ");
    Serial.print("rx");
    Serial.print(rx);
    Serial.print(" ");
    Serial.print("x:");
    Serial.print(x);
    Serial.print(" ");
    Serial.print("y:");
    Serial.print(y);
    Serial.print(" ");
    Serial.print("x1:");
    Serial.print(x1);
    Serial.print(" ");
    Serial.print("y1:");
    Serial.println(y1);
 if (PS3.getAnalogHat(LeftHatX) > 137||PS3.getAnalogHat(LeftHatX) <117 || PS3.getAnalogHat(LeftHatY) > 137 || PS3.getAnalogHat(LeftHatY) < 117)
   {
   switch (direction(PS3.getAnalogHat(LeftHatX), PS3.getAnalogHat(LeftHatY)))
    {
      case 0:
        omuni1.stop();
        break;
      case 8:
      case 1:
        omuni1.left(x1);
        break;
      case 2:
      case 3:
        omuni1.back(y);
        break;
      case 4:
      case 5:
        omuni1.right(x);
        break;
      case 6:
      case 7:
        omuni1.forward(y1);
        break;
      default:
        break;
    }
   }
else if (PS3.getAnalogHat(RightHatX) > 137 || PS3.getAnalogHat(RightHatX) <117 || PS3.getAnalogHat(RightHatY) > 137 || PS3.getAnalogHat(RightHatY) < 117)
  {
   
//if(direction(PS3.getAnalogHat(LeftHatX), PS3.getAnalogHat(LeftHatY))==0)
    switch (direction(PS3.getAnalogHat(RightHatX), PS3.getAnalogHat(RightHatY))) 
    {
         case 0:
           omuni1.stop();
           break;
         case 1:
         case 2:
           omuni1.obli_bl(rx1);
           break;
         case 3:
         case 4:
           omuni1.obli_br(ry);
           break;
         case 5:
         case 6:
           omuni1.obli_r(rx);
           break;
         case 7:
         case 8:
           omuni1.obli_l(ry1);
           break;
         default:
           break;
       }
     }
    
    
    else{
      

    if (PS3.getButtonPress(RIGHT)) {
      movemotor(1, 1, 1, 1);
      Serial.println("ok");
      Serial.println(" ");
    }
    else if (PS3.getButtonPress(LEFT)) {
      movemotor(-1, -1, -1, -1);
    }

    
    else if (PS3.getButtonPress(TRIANGLE)) {
      digitalWrite(pin_arm1,HIGH);
      digitalWrite(pin_arm2,LOW);
      Serial.println("up");
      Serial.println(" ");
    }
    else if (PS3.getButtonPress(CROSS)) {
      digitalWrite(pin_arm2,HIGH);
      digitalWrite(pin_arm1,LOW);
      Serial.println("down");
      Serial.println(" ");
    }
    else if (PS3.getButtonPress(CIRCLE)) {
      carry(1);
    }
    else if (PS3.getButtonPress(SQUARE)) {
      carry(0);
    }
    else {
     movemotor(0,0,0,0);
      digitalWrite(pin_hand1, LOW);
      digitalWrite(pin_hand2, LOW);
      digitalWrite(pin_arm1, LOW);
      digitalWrite(pin_arm2, LOW);
    
    }
   }
  }
}


void motor(int pin1, int pin2, int input) {
  if (input == 0) {
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, LOW);
  }
  if (input == 1) {
    digitalWrite(pin1, HIGH);
    digitalWrite(pin2, LOW);
  }
  if (input == -1) {
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, HIGH);
  }
}
void movemotor(int m1, int m2, int m3, int m4) {
  motor(pinmA[0], pinmA[1], m1);
  motor(pinmB[0], pinmB[1], m2);
  motor(pinmC[0], pinmC[1], m3);
  motor(pinmD[0], pinmD[1], m4);

}
void carry(int input ) {
  if (input == 1) {
    digitalWrite(pin_hand1, HIGH);
    digitalWrite(pin_hand2, LOW);
  }
  if (input == 0) {
    digitalWrite(pin_hand1, LOW);
    digitalWrite(pin_hand2, HIGH);
  }
}
/*void updown(int speed) {
  if (speed > 0) {
    analogWrite(pin_arm1, speed);
    analogWrite(pin_arm2, 0);
  }
  if (speed < 0) {
    analogWrite(pin_arm1, 0);
    analogWrite(pin_arm2, -speed);
  }
}*/
