//아두이노 동작에 대한 코드 정의
//방향 코드
enum class DirectionCode {
    FRONT, //전진 (FORWARD로 할 경우, AFMotor.h의 FORWARD 변수와 중복)
    RIGHT, //우회전
    LEFT //좌회전
};

//속도 코드
enum class SpeedCode {
    FAST, //속도 빠르게
    SLOW, //속도 느리게
    STOP, //멈춤
    MOVE //움직임
};

/**
 * 방향 코드 + 속도 코드 = 동작 코드 정의 
 * ex. 00 코드는 전진, 속도 빠르게
 * ex. 21 코드는 좌회전, 속도 느리게
 * → 적외선 센서로 데이터 받는 아두이노가 동작 코드 생성 후 모터 제어하는 아두이노에게 전송
*/
String getOperationCode(DirectionCode directionCode, SpeedCode speedCode) {
    return String(static_cast<int>(directionCode)) + String(static_cast<int>(speedCode));
}

//모터 제어하는 아두이노에게 전송된 동작 코드 → 방향 코드로 파싱
DirectionCode parseDirectionCode(String operationCode) {
    return static_cast<DirectionCode>(operationCode.substring(0, 1).toInt());
}

//모터 제어하는 아두이노에게 전송된 동작 코드 → 속도 코드로 파싱
SpeedCode parseSpeedCode(String operationCode) {
    return static_cast<SpeedCode>(operationCode.substring(1, 2).toInt());
}