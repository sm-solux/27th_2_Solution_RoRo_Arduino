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
Ultrasonic ultrasonicRight(TRIG_R, ECHO_R);
Lcd lcd(0x27, 16, 2); 

void setup() {
    mySerial.begin(9600); 
    ultrasonicRight.setup(); 
    lcd.setup(); 
}

void loop() {
    int distance = ultrasonic.readDistance(); 
    mySerial.print(distance);
    lcd.printDistance(distance);
    delay(1500); 
}