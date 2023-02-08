//각 센서의 핀 번호
/**
 * 아두이노 간 시리얼 통신을 위한 디지털 핀 번호
 * 디지털 핀 서로 크로스해서 연결해야 함
 * ex. 아두이노 A Pin 9 - 아두이노 B Pin 10 연결 + 아두이노 A Pin 10 - 아두이노 B Pin 9 연결
*/
#define PIN_RX 9 //수신부 (모터 쉴드의 SERVO-2)
#define PIN_TX 10 //발신부 (모터 쉴드의 SER1)

//적외선 센서 핀 번호
//bottom
#define TRIG_B 12
#define ECHO_B 11 
//right
#define TRIG_R 7
#define ECHO_R 6
//left
#define TRIG_L 5
#define ECHO_L 4
//front
#define TRIG_F 3
#define ECHO_F 2

//모터 핀 번호
//right
#define MOTOR_R 1
//left
#define MOTOR_L 2