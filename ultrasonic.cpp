#include "Arduino.h"
#include "Ultrasonic.h"

Ultrasonic::Ultrasonic(int trig, int echo): trig(trig), echo(echo) {}

//적외선 센서 핀 번호 설정
void Ultrasonic::setup() {
    pinMode(trig, OUTPUT);
    pinMode(echo, INPUT); 
}

//초음파 센서 값 읽어오는 함수 
int Ultrasonic::readDistance() {
    float duration, distance;

    //초음파 센서는 초음파를 발사 후 돌아오는 시간을 역산하여 거리 값으로 계산 
    digitalWrite(trig, HIGH); //초음파 발사 
    delay(10); 
    digitalWrite(trig, LOW); //초음파 발사 중단 

    duration = pulseIn(echo, HIGH); //초음파 센서 Echo 핀에 신호가 들어올 때까지의 시간(마이크로초 단위, 1초 = 1000000마이크로초) 
    distance = (340. * duration / 10000) / 2; //초음파 속도 340m/s
    return distance; //cm 단위
}