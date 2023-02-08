#include <AFMotor.h>
#include <SoftwareSerial.h>
#include "PinNumber.h"
#include "OperationCode.h"

AF_DCMotor rightMotor(1), leftMotor(2);
SoftwareSerial mySerial(PIN_RX, PIN_TX);

const int maxSpeed = 250, minSpeed = 150, standardSpeed = 200;
int currentSpeed = standardSpeed, speedGap = 10;
DirectionCode directionCode = DirectionCode::FRONT;
SpeedCode speedCode = SpeedCode::FAST;

void handleDirection(DirectionCode directionCode);
void handleSpeed(SpeedCode speedCode);

void setup() {
    rightMotor.setSpeed(currentSpeed);
    leftMotor.setSpeed(currentSpeed);
    rightMotor.run(RELEASE);
    leftMotor.run(RELEASE);

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
        rightMotor.run(BACKWARD);
        leftMotor.run(FORWARD);
    }
    else if (directionCode == DirectionCode::LEFT) {
        rightMotor.run(FORWARD);
        leftMotor.run(BACKWARD);
    }
    else {
        rightMotor.run(FORWARD);
        leftMotor.run(FORWARD);
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
        rightMotor.setSpeed(0);
        leftMotor.setSpeed(0);
        rightMotor.run(RELEASE);
        leftMotor.run(RELEASE);
    }
    else {
        rightMotor.setSpeed(standardSpeed);
        leftMotor.setSpeed(standardSpeed);
        rightMotor.run(FORWARD);
        leftMotor.run(FORWARD);
    }
}