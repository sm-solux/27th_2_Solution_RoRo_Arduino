// #include <AFMotor.h> 
// #include <SoftwareSerial.h>
// #define PIN_RX 9 //SERVO-2
// #define PIN_TX 10 //SER1

// AF_DCMotor motorRight(4), motorLeft(1), motor(3); 
// SoftwareSerial mySerial(PIN_RX, PIN_TX);
// int speed = 150;

// void setup() {
//     motorLeft.setSpeed(speed);
//     motorLeft.run(RELEASE); 
//     motorRight.setSpeed(speed);
//     motorRight.run(RELEASE); 
//     motor.setSpeed(speed);
//     motor.run(RELEASE); 

//     Serial.begin(9600);
//     mySerial.begin(9600);
// }

// void loop() {
//     long distance = 0;

//     if (mySerial.available()) {
//         distance = mySerial.parseInt(); 
//         Serial.println(distance);  
//     }

//     motorRight.run(FORWARD);
//     motorLeft.run(FORWARD);
//     motor.run(FORWARD);

//     if (distance > 50) {
//         speed = 180;
//         motorRight.setSpeed(speed);
//         motorLeft.setSpeed(speed);
//         motorRight.run(FORWARD);
//         motorLeft.run(FORWARD);
//     }
//     //우회전 구현 
//     else {
//         speed -= 10;
//         motorRight.setSpeed(speed);
//         motorLeft.setSpeed(speed);
//         motorRight.run(BACKWARD);
//         motorLeft.run(FORWARD);
//         delay(500);
//     }
// }