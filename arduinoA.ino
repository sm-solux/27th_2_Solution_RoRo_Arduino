#include <SoftwareSerial.h>
#include "ultrasonic.h"
#include "lcd.h"
#define PIN_RX 9
#define PIN_TX 10 
#define TRIG_R 7
#define ECHO_R 6
#define TRIG_L 5
#define ECHO_L 4
#define TRIG_F 3
#define ECHO_F 2

SoftwareSerial mySerial(PIN_RX, PIN_TX);
Ultrasonic ultrasonicRight(TRIG_R, ECHO_R), ultrasonicLeft(TRIG_L, ECHO_L), ultrasonicFront(TRIG_F, ECHO_F);
Lcd lcd(0x27, 16, 2); 

void setup() {
    mySerial.begin(9600); 
    ultrasonicRight.setup(); 
    ultrasonicLeft.setup(); 
    ultrasonicFront.setup(); 
    lcd.setup(); 
}

void loop() {
    int distance = ultrasonicFront.readDistance(); 

    if (distance < 15) {
        int distanceRight = ultrasonicRight.readDistance();
        int distanceLeft = ultrasonicLeft.readDistance();
        if (distanceRight > distanceLeft) {
            mySerial.print(distanceRight);
            lcd.printstr("Move to Right");
            lcd.printDistance(distanceRight);
        }
        else {
            mySerial.print(distanceLeft);
            lcd.printstr("Move to Left");
            lcd.printDistance(distanceLeft);
        }
    }
    else {
        mySerial.print(distance);
        lcd.printstr("Move Forward");
        lcd.printDistance(distance);
    }
    delay(1500);
}