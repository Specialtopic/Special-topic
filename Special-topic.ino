#include <Ping.h>
#include <Servo.h>
Servo servoPin1;
Servo servoPin2;

Ping ping1 = Ping(11);   //宣告前方超音波
Ping ping2 = Ping(12);   //宣告左方超音波
Ping ping3 = Ping(4);    //宣告右方超音波
int Redleft = 9;   //宣告紅外線左方
int Redright = 2;  //宣告紅外線右方

int i;

void setup() {
  servoPin1.attach(12);/*右邊*/
  servoPin2.attach(13);/*左邊*/
  pinMode(Redleft,INPUT);
  pinMode(Redright,INPUT);
  Serial.begin(9600);
}

void loop(){
  int centimeter,left,right;
  float a=0,b=0,c=0;

  ping1.fire();//前方超音波
  /*Serial.print("Microseconds1: ");
  Serial.print(ping1.microseconds());
  Serial.print(" | Centimeters1: ");
  Serial.print(ping1.centimeters());
  Serial.println();*/

  ping2.fire();//左方超音波
  /*Serial.print("Microseconds2: ");
  Serial.print(ping2.microseconds());
  Serial.print(" | Centimeters2: ");
  Serial.print(ping2.centimeters());
  Serial.println();*/

  ping3.fire();//右方超音波
  /*Serial.print("Microseconds2: ");
  Serial.print(ping3.microseconds());
  Serial.print(" | Centimeters2: ");
  Serial.print(ping3.centimeters());
  Serial.println();*/

  a=ping1.centimeters();    //前方超音波
  b=ping2.centimeters();    //左方超音波
  c=ping2.centimeters();    //右方超音波

  left = analogRead(Redleft);//紅外線左方數值
  right = analogRead(Redright);//紅外線右方數值

  forward();

  if(a<=10) { //前方
    turn_left();
    turn_right();
    forward();
  }

  /***左轉**/
  if(c<=10) {  //右方
    turn_left();
    turn_right();
    forward();
  }
  if((a<=10) && (c<=10)) { //前方和右方
    turn_left();
    turn_right();
    forward();
  }

  /***右轉**/
  if(b<=10) {  //左方
    turn_right();
    turn_left();
    forward();
  }
  if((a<=10) && (b<=10)) { //前方和左方
    turn_right();
    turn_left();
    forward();
  }
}

/*副程式專區*/
  void forward(){              /*前進的副程式*/
    for(i=0;i<8;i++){
    servoPin1.write(0);
    servoPin2.write(180);
    delay(100);
    }
}
  void backward(){
    for(i=0;i<2;i++){
    servoPin1.write(180);
    servoPin2.write(0);
    delay(100);
    }
}
  void turn_left(){            /*左轉的副程式*/
    for(i=0;i<6;i++){
    servoPin1.write(0);
    servoPin2.write(0);
    delay(100);
    }
}
  void turn_right(){           /*右轉的副程式*/
    for(i=0;i<6;i++){
    servoPin1.write(180);
    servoPin2.write(180);
    delay(100);
    }
}

