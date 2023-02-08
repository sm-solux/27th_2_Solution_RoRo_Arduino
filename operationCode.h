enum class DirectionCode {
    FRONT, //전진 (FORWARD로 할 경우, AFMotor.h의 FORWARD 변수와 중복)
    RIGHT, //우회전
    LEFT //좌회전
};

enum class SpeedCode {
    FAST, //속도 빠르게
    SLOW, //속도 느리게
    STOP, //멈춤
    MOVE //움직임
};

String getOperationCode(DirectionCode directionCode, SpeedCode speedCode) {
    return String(static_cast<int>(directionCode)) + String(static_cast<int>(speedCode));
}

DirectionCode parseDirectionCode(String operationCode) {
    return static_cast<DirectionCode>(operationCode[0]);
}

SpeedCode parseSpeedCode(String operationCode) {
    return static_cast<SpeedCode>(operationCode[1]);
}