#include <AFMotor.h>
#include <SoftwareSerial.h>
#include "pinNumber.h"
#include "operationCode.h"

AF_DCMotor motorRight(1), motorLeft(2);
SoftwareSerial mySerial(PIN_RX, PIN_TX);

const int maxSpeed = 250, minSpeed = 150, standardSpeed = 200;
int currentSpeed = standardSpeed, speedGap = 10;
DirectionCode directionCode = DirectionCode::FRONT;
SpeedCode speedCode = SpeedCode::FAST;

void handleDirection(DirectionCode directionCode);
void handleSpeed(SpeedCode speedCode);

void setup() {
    motorRight.setSpeed(currentSpeed);
    motorLeft.setSpeed(currentSpeed);
    motorRight.run(RELEASE);
    motorLeft.run(RELEASE);

    Serial.begin(9600);
    mySerial.begin(9600);
}

void loop() {
    if (mySerial.available()) {
        String operationCode = mySerial.readString();
        Serial.println(operationCode);
        directionCode = parseDirectionCode(operationCode);
        speedCode = parseSpeedCode(operationCode);
    }

    handleDirection(directionCode);
    handleSpeed(speedCode);
    delay(500);
}

void handleDirection(DirectionCode directionCode) {
    if (directionCode == DirectionCode::RIGHT) {
        motorRight.run(BACKWARD);
        motorLeft.run(FORWARD);
    }
    else if (directionCode == DirectionCode::LEFT) {
        motorRight.run(FORWARD);
        motorLeft.run(BACKWARD);
    }
    else {
        motorRight.run(FORWARD);
        motorLeft.run(FORWARD);
    }
}

void handleSpeed(SpeedCode speedCode) {
    if (speedCode == SpeedCode::FAST) {
        if (currentSpeed < maxSpeed) currentSpeed += speedGap;
    }
    else if (speedCode == SpeedCode::SLOW) {
        if (currentSpeed > minSpeed) currentSpeed -= speedGap;
    }
    else if (speedCode == SpeedCode::STOP) {
        motorRight.setSpeed(0);
        motorLeft.setSpeed(0);
        motorRight.run(RELEASE);
        motorLeft.run(RELEASE);
    }
    else {
        motorRight.setSpeed(standardSpeed);
        motorLeft.setSpeed(standardSpeed);
        motorRight.run(FORWARD);
        motorLeft.run(FORWARD);
    }
}