#include <AFMotor.h>
#include <SoftwareSerial.h>
#include "PinNumber.h"
#include "OperationCode.h"

AF_DCMotor rightMotor(MOTOR_R), leftMotor(MOTOR_L);
SoftwareSerial mySerial(PIN_RX, PIN_TX);

const int maxSpeed = 250, minSpeed = 150, standardSpeed = 170;
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
    //적외선 센서로 데이터 받는 아두이노로부터 전송된 동작 코드 있으면
    if (mySerial.available()) {
        String operationCode = mySerial.readString();
        Serial.println(operationCode);
        directionCode = parseDirectionCode(operationCode);
        speedCode = parseSpeedCode(operationCode);
    }

    //방향 코드, 속도 코드로 모터 제어
    handleDirection(directionCode);
    handleSpeed(speedCode);
    delay(500);
}

void handleDirection(DirectionCode directionCode) {
    //우회전
    if (directionCode == DirectionCode::RIGHT) { 
        rightMotor.run(BACKWARD);
        leftMotor.run(FORWARD);
    }
    //좌회전
    else if (directionCode == DirectionCode::LEFT) { 
        rightMotor.run(FORWARD);
        leftMotor.run(BACKWARD);
    }
    //전진
    else { 
        rightMotor.run(FORWARD);
        leftMotor.run(FORWARD);
    }
}

void handleSpeed(SpeedCode speedCode) {
    //속도 빠르게 (특정 속도까지만)
    if (speedCode == SpeedCode::FAST) {
        if (currentSpeed < maxSpeed) currentSpeed += speedGap;
    }
    //속도 느르게 (특정 속도까지만)
    else if (speedCode == SpeedCode::SLOW) {
        if (currentSpeed > minSpeed) currentSpeed -= speedGap;
    }
    //멈춤
    else if (speedCode == SpeedCode::STOP) {
        rightMotor.setSpeed(0);
        leftMotor.setSpeed(0);
        rightMotor.run(RELEASE);
        leftMotor.run(RELEASE);
    }
    //표준 속도로 움직임
    else {
        rightMotor.setSpeed(standardSpeed);
        leftMotor.setSpeed(standardSpeed);
        rightMotor.run(FORWARD);
        leftMotor.run(FORWARD);
    }
}