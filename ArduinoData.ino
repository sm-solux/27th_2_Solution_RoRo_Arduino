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

    /**
     * 정면 거리가 특정값 보다 작아지는 경우 (장애물에 가까워지면) || 바닥 거리가 특정값보다 커지는 경우 (낭떠러지 만나면)
     * → 속도 줄이면서, 거리가 더 긴 쪽으로 우회전 혹은 좌회전 지시
    */
    if (frontDistance < frontThresholds || bottomDistance > bottomThresholds) {
        rightDistance = rightUltrasonic.readDistance();
        leftDistance = leftUltrasonic.readDistance();
        if (rightDistance > leftDistance) {
            mySerial.print(getOperationCode(DirectionCode::RIGHT, SpeedCode::SLOW)); //모터 제어 아두이노에게 동작 코드 전송
            lcd.printstr("Move to Right");
            lcd.printDistance(rightDistance);
        }
        else {
            mySerial.print(getOperationCode(DirectionCode::LEFT, SpeedCode::SLOW));
            lcd.printstr("Move to Left");
            lcd.printDistance(leftDistance);
        }
    }
    //평소에는 속도 높이면서 전진 지시
    else {
        mySerial.print(getOperationCode(DirectionCode::FRONT, SpeedCode::FAST));
        lcd.printstr("Move to Front");
        lcd.printDistance(frontDistance);
    }

    delay(1500); //딜레이 주지 않으면 데이터 전송 시 값이 이상하게 변함
}