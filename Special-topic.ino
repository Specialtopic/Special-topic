#include <Ping.h>
#include <Servo.h>
Servo servoPin1;
Servo servoPin2;

Ping ping1 = Ping(7);   //宣告前方超音波
Ping ping2 = Ping(11);   //宣告左方超音波
Ping ping3 = Ping(4);    //宣告右方超音波

int i;

void setup() {
  servoPin1.attach(12);/*右邊*/
  servoPin2.attach(13);/*左邊*/
  
  pinMode(A4,INPUT);//紅外線右方
  pinMode(2,OUTPUT);//紅外線右方
  
  pinMode(A5,INPUT);//紅外線左方
  pinMode(9,OUTPUT);//紅外線左方
  Serial.begin(9600);
}

void loop(){
  int centimeter;
  float a=0,b=0,c=0;

  int left1 = irDetect(2,3,38000);
  int right1 = irDetect(9,10,38000);

  int left = analogRead(left1);
  int right = analogRead(right1);

  /*Serial.print("left: ");
  Serial.print(left);
  Serial.println();
  Serial.print("right: ");
  Serial.print(right);
  Serial.println();*/

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
  c=ping3.centimeters();    //右方超音波

  forward();

  /*******前方遇到障礙物***********/
  if(a<=10.5)
  {
    turn_left();
    forward();
    delay(850);
    turn_right();
    forward();
  }
  /*******左方遇到障礙物***********/
  if(b<=4) {
    turnright();
  }
  /*******右方遇到障礙物***********/
  if(c<=4) {
    turnleft();
  }
  /*******左前方遇到障礙物***********/
  if((left<=568) && (b<=4)) {
    turnright();
  }
  /*******右前方遇到障礙物***********/
  if((right<=576) && (c<=4)) {
    turnleft();
  }
}

/*副程式專區*/
  void forward(){                /*前進的副程式*/
    for(i=0;i<3;i++){
    servoPin1.write(0);
    servoPin2.write(180);
    delay(100);
      }
   }
  void backward(){
    for(i=0;i<2;i++){
    servoPin1.write(180);
    servoPin2.write(0);
    delay(10);
      }
    }
  void turn_left(){            /*左轉的副程式*/
    for(i=0;i<=4.8;i++){
    servoPin1.write(0);
    servoPin2.write(0);
    delay(100);
      }
   }
  void turn_right(){           /*右轉的副程式*/
    for(i=0;i<=6;i++){
    servoPin1.write(180);
    servoPin2.write(180);
    delay(100);
      }
   }
   /*---------微調--------------*/
   void turnleft(){                /*微調的副程式*/
    for(i=0;i<5;i++){
    servoPin1.write(85);
    servoPin2.write(95);
    delay(100);
      }
   }
   void turnright(){                /*微調的副程式*/
    for(i=0;i<2;i++){
    servoPin1.write(100);
    servoPin2.write(100);
    delay(150);
      }
   }
   void stopnow() {
    for(i=0;i<2;i++){
    servoPin1.write(100);
    servoPin2.write(100);
      }
   }
int irDetect(int irLedPin,int irReceiverPin,long frequency) {
  tone(irLedPin,frequency);
  delay(0.000000000000000000000000001);
  int ir = digitalRead(irReceiverPin);
  delay(0.000000000000000000000000001);
  return ir;
}

