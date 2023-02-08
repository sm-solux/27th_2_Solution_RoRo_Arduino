#include <SoftwareSerial.h>
#include "Ultrasonic.h"
#include "Lcd.h"
#include "PinNumber.h"
#include "OperationCode.h"

SoftwareSerial mySerial(PIN_RX, PIN_TX);
Ultrasonic bottomUltrasonic(TRIG_B, ECHO_B), rightUltrasonic(TRIG_R, ECHO_R), leftUltrasonic(TRIG_L, ECHO_L), frontUltrasonic(TRIG_F, ECHO_F);
Lcd lcd(0x27, 16, 2); 

int bottomDistance, rightDistance, leftDistance, frontDistance, frontThresholds = 15, bottomThresholds = 20;

void setup() {
    mySerial.begin(9600);
    rightUltrasonic.setup();
    leftUltrasonic.setup();
    frontUltrasonic.setup();
    bottomUltrasonic.setup();
    lcd.setup(); 
}

void loop() {
    frontDistance = frontUltrasonic.readDistance();
    bottomDistance = bottomUltrasonic.readDistance();

    if (frontDistance < frontThresholds || bottomDistance > bottomThresholds) {
        rightDistance = rightUltrasonic.readDistance();
        leftDistance = leftUltrasonic.readDistance();
        if (rightDistance > leftDistance) {
            mySerial.print(getOperationCode(DirectionCode::RIGHT, SpeedCode::SLOW));
            lcd.printstr("Move to Right");
            lcd.printDistance(rightDistance);
        }
        else {
            mySerial.print(getOperationCode(DirectionCode::LEFT, SpeedCode::SLOW));
            lcd.printstr("Move to Left");
            lcd.printDistance(leftDistance);
        }
    }
    else {
        mySerial.print(getOperationCode(DirectionCode::FRONT, SpeedCode::FAST));
        lcd.printstr("Move to Front");
        lcd.printDistance(frontDistance);
    }

    delay(1500);
}