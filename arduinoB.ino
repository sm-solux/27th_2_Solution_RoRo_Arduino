#include <AFMotor.h> 
#include <SoftwareSerial.h>
#include "lcd.h"
#define PIN_RX 9 //SERVO-2
#define PIN_TX 10 //SER1

AF_DCMotor motorLeft(1), motorRight(2); 
SoftwareSerial mySerial(PIN_RX, PIN_TX);
Lcd lcd(0x27, 16, 2); 

void setup() {
    motorLeft.setSpeed(200);
    motorLeft.run(RELEASE); 
    motorRight.setSpeed(200);
    motorRight.run(RELEASE); 

    Serial.begin(9600);
    mySerial.begin(9600);

    lcd.setup(); 
}

void loop() {
    long distance = 0;

    if (mySerial.available()) {
        distance = mySerial.parseInt(); 
        Serial.println(distance); 
        lcd.printDistance(distance); 
    }

    if (distance < 50) motorLeft.run(RELEASE);
    else {
        motorLeft.run(FORWARD);
        delay(500);
    }
}