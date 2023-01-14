# 1 "c:\\Users\\sm-pc\\Desktop\\solux_arduino\\arduinoA.ino"
// #include <SoftwareSerial.h>
// #include "ultrasonic.h"
// #define PIN_RX 9
// #define PIN_TX 10 
// #define TRIG 7
// #define ECHO 6

// SoftwareSerial mySerial(PIN_RX, PIN_TX);
// Ultrasonic ultrasonic(TRIG, ECHO);

// void setup() {
//     mySerial.begin(9600); 
//     ultrasonic.setup(); 
// }

// void loop() {
//     int distance = ultrasonic.readDistance(); 
//     mySerial.print(distance);
//     delay(1500); 
// }
# 1 "c:\\Users\\sm-pc\\Desktop\\solux_arduino\\arduinoB.ino"
# 2 "c:\\Users\\sm-pc\\Desktop\\solux_arduino\\arduinoB.ino" 2
# 3 "c:\\Users\\sm-pc\\Desktop\\solux_arduino\\arduinoB.ino" 2
# 4 "c:\\Users\\sm-pc\\Desktop\\solux_arduino\\arduinoB.ino" 2



AF_DCMotor motorLeft(1), motorRight(2);
SoftwareSerial mySerial(9 /*SERVO-2*/, 10 /*SER1*/);
Lcd lcd(0x27, 16, 2);

void setup() {
    motorLeft.setSpeed(200);
    motorLeft.run(4);
    motorRight.setSpeed(200);
    motorRight.run(4);

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

    if (distance < 50) motorLeft.run(4);
    else {
        motorLeft.run(1);
        delay(500);
    }
}
