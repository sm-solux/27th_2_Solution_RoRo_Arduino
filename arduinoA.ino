#include <SoftwareSerial.h>
#include "ultrasonic.h"
#include "lcd.h"
#include "pinNumber.h"
#include "operationCode.h"

SoftwareSerial mySerial(PIN_RX, PIN_TX);
Ultrasonic ultrasonicBottom(TRIG_B, ECHO_B), ultrasonicRight(TRIG_R, ECHO_R), ultrasonicLeft(TRIG_L, ECHO_L), ultrasonicFront(TRIG_F, ECHO_F);
Lcd lcd(0x27, 16, 2); 

int distanceBottom, distanceRight, distanceLeft, distanceFront, thresholdsFront = 15, thresholdsBottom = 20;

void setup() {
    mySerial.begin(9600);
    ultrasonicRight.setup();
    ultrasonicLeft.setup();
    ultrasonicFront.setup();
    ultrasonicBottom.setup();
    lcd.setup(); 
}

void loop() {
    distanceFront = ultrasonicFront.readDistance();
    distanceBottom = ultrasonicBottom.readDistance();

    if (distanceFront < thresholdsFront || distanceBottom > thresholdsBottom) {
        distanceRight = ultrasonicRight.readDistance();
        distanceLeft = ultrasonicLeft.readDistance();
        if (distanceRight > distanceLeft) {
            mySerial.print(getOperationCode(DirectionCode::RIGHT, SpeedCode::SLOW));
            lcd.printstr("Move to Right");
            lcd.printDistance(distanceRight);
        }
        else {
            mySerial.print(getOperationCode(DirectionCode::LEFT, SpeedCode::SLOW));
            lcd.printstr("Move to Left");
            lcd.printDistance(distanceLeft);
        }
    }
    else {
        mySerial.print(getOperationCode(DirectionCode::FRONT, SpeedCode::FAST));
        lcd.printstr("Move Forward");
        lcd.printDistance(distanceFront);
    }

    delay(1500);
}