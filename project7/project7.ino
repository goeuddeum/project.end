//const int buttonPin = 2; 
//const int buttonPin2 =10; 
const int trigPin = 12;  //초음파센서 trig핀
const int echoPin = 13; //초음파센서  echo핀
float duration = 0, distance = 0; //거리측정 변수
int seg[7] = {9,3,4,5,6,7,8}; //세그먼트
int green=A1; //녹색led
int red=A2;   //빨간색led
int buz=11;   //피에조

int num[11][7] = {
{0,0,0,1,1,0,0},  //9
{0,0,0,0,0,0,0},  //8
{0,0,0,1,1,0,1},  //7
{0,1,0,0,0,0,0},  //6
{0,1,0,0,1,0,0},  //5
{1,0,0,1,1,0,0},  //4
{0,0,0,0,1,1,0},  //3
{0,0,1,0,0,1,0},  //2
{1,0,0,1,1,1,1},  //1
{0,0,0,0,0,0,1},  //0
{1,1,1,1,1,1,1},  //끝 전부다꺼짐
};
void stopall() {  //정지함수
  digitalWrite(green, LOW);
  digitalWrite(red, HIGH);
  noTone(buz);
}
void trapiclight(){ //보행자 초록불 신호
  noTone(buz);
  delay(100);
  for(int i = 0; i < 11; i++){  //7-세그먼트
    for(int j = 0; j < 7; j++){
      digitalWrite(seg[j], num[i][j]); //9부터 1까지 줄어든다
    }
    digitalWrite(red,LOW);
    digitalWrite(green,HIGH);
    if(i>5){   //초록불 신호가 4아래일때
      tone(buz,262); //신호음
      for(int on_off = 0;on_off <=1;on_off++){  
          digitalWrite(green,on_off); //불이 깜빡인다
          delay(250);
      }
    } 
    delay(1000); //신호는 1초간격
  }
  delay(500);
}
void usual(){ //보행자 빨간불 신호
  noTone(buz);
  delay(100);
  for(int i = 0; i < 11; i++){
    for(int j = 0; j < 7; j++){
      digitalWrite(seg[j], num[i][j]);
    }
    digitalWrite(green,LOW);
    digitalWrite(red,HIGH);
    if(i>5){
      tone(buz,523);
      for(int on_off = 0;on_off <=1;on_off++){
        digitalWrite(red,on_off);
        delay(250);
      }
    }
    delay(500);
  }
  delay(500);
}
void setup() {
  for(int i = 0; i < 7; i++){
    pinMode(seg[i],OUTPUT);
  }   
  Serial.begin(9600);
  pinMode(green,OUTPUT);
  pinMode(red,OUTPUT);  
  pinMode(buz,OUTPUT);
 // pinMode(buttonPin,OUTPUT);
 // pinMode(buttonPin2,OUTPUT);
  pinMode(trigPin, OUTPUT);  
  pinMode(echoPin, INPUT);  
}
void loop() {
  digitalWrite(trigPin, HIGH); 
  delay(100);
  digitalWrite(trigPin, LOW);  //초음파 센서 작동 
  duration = pulseIn(echoPin,HIGH);  //반사신호         
  distance = ((float)(340 * duration)) / 10000 / 2; //거리측정
  if(distance < 15){  //거리가 15 이하일때 초록불이 꺼지지 않는다.
    digitalWrite(green, HIGH);
    digitalWrite(red, LOW);
    tone(buz,262);
    delay(1000);
  } 
  else {
    noTone(buz);
    delay(100);
    delay(100);
    stopall();  //정지신호 (빨간불)
    delay(3000);
    usual();  //정지신호 9초전 (빨간불)
    delay(100);
    trapiclight(); //건너는 신호 (초록불)
  }
}
