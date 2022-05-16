


#include <NewPing.h>

#define forward 1
#define left 2
#define right 3
#define pause 0
#define atBlack > 900 
#define atWhite < 900 

int vSpeed = 150;        // MAX 255
int turn_speed = 50;    // MAX 255
int turn_delay = 10;


bool sensor=true;
//L293 Connection
const int motorABrake      = 9;
const int MotorABDIR      = 12; //LEFT MOTOR
const int motorAspeed  = 6;

const int motorBBrake      = 8;
const int MotorBDIR      = 13; //RIGHT MOTOR
const int motorBspeed  = 11;

const int correctionLED = 4;
const int leftLED = 5;
const int rightLED = 7;
//Sensor Connection
const int left_sensor_pin = A2;
const int right_sensor_pin = A3;
const int correction_pin = A4;

//ultrasonic snesor pin
const int echoPin = 2;
const int trigPin = 10;
const float soundSpeed = .0343; // cm/microsec

bool LEDstate = true;
int left_sensor_state;
int right_sensor_state;
int correction_sensor_state;


bool endOfTrip=false;


int orderArray [] = {left, forward,left, forward, left, right, pause};
int orderArrayLength = sizeof(orderArray);
float duration, distance;
NewPing sonar(trigPin, echoPin, 200);

void setup() {
  //pinMode(motorABrake, OUTPUT);
  pinMode(MotorABDIR, OUTPUT);
  //pinMode(motorBBrake, OUTPUT);
  pinMode(MotorBDIR, OUTPUT);
  pinMode(leftLED, OUTPUT);
  pinMode(rightLED, OUTPUT);
  pinMode(correctionLED, OUTPUT);
  pinMode(left_sensor_pin, INPUT);
  pinMode(left_sensor_pin, INPUT);
  pinMode(correction_pin, INPUT);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  digitalWrite(motorBspeed, LOW);
  digitalWrite(motorAspeed, LOW);
  Serial.begin(9600);
  delay(3000);

}
int trip=0;

void loop() {

  pulsing();
  
  
  // duration = pulseIn(echoPin, HIGH);
  distance = sonar.ping_cm(); //= (duration  * soundSpeed) / 2;

  //Serial.print("Distance: ");
 // Serial.println(distance);

  left_sensor_state = analogRead(left_sensor_pin);
  right_sensor_state = analogRead(right_sensor_pin);
  correction_sensor_state = analogRead(correction_pin);
/*
  Serial.print("LEFT: ");
  Serial.print(left_sensor_state);
  //Serial.println();
  Serial.print("  RIGHT: ");
  Serial.print(right_sensor_state);
 // Serial.println();
  Serial.print("  BACK: ");
  Serial.println(correction_sensor_state);
*/

  
  while(endOfTrip)
  {
      blinkk(LOW,HIGH,HIGH);
      analogWrite (motorAspeed, 0);
      analogWrite (motorBspeed, 0);
       Serial.println("  END   ");
  }

// > 900 atWhite  !!!!
// < 900 atBlack  !!!!

   
  if (distance < 7 && distance > 0){
    stopM(LOW, LOW, HIGH);
  }
  else if(correction_sensor_state atBlack && right_sensor_state atBlack && left_sensor_state atBlack)
  {

          /*
          #define forward 1
          #define left 2
          #define right 3
          #define pause 0
           */ 
         if(trip==8){
            executeOrder(0);
            trip=0;
         }
         if(trip==7){
            executeOrder(2);
            trip=8;
         }           
         if(trip==6){
            executeOrder(3);
            trip=7;
         }
         if(trip==5){
            executeOrder(2);
            trip=6;
         }  
         else if(trip==4){
            executeOrder(2);
            trip=5;
         }
         else if(trip==3){
            executeOrder(1);
            trip = 4;
         }
         else if(trip==2){
            executeOrder(1);
            trip=3;
         }        
         else if(trip==1){
            executeOrder(2);
            trip=2;  
         }
         else if(trip==0){
            executeOrder(2);
            trip=1;
         }
    

     
   }
   
      /*
      if(right_sensor_state atWhite && left_sensor_state atWhite && correction_sensor_state atWhite){ 
          goBackwards();
          delay(50);
      }
      
      else*/
      if(right_sensor_state atWhite && left_sensor_state atWhite && correction_sensor_state atBlack){

        goForward();
      }
      else{
        if(sensor){
            if (right_sensor_state atBlack) {
              turnRight();
            } 
        
            if (left_sensor_state atBlack) {
              turnLeft();
            }
            sensor!=sensor;
        }else{
            if (left_sensor_state atBlack) {
              turnLeft();
            }
            else if (right_sensor_state atBlack) {
              turnRight();
            }
            sensor!=sensor;
        }
      }
    

}


void executeOrders(){
  for(int i = 0; i < orderArrayLength; i++){
      executeOrder(orderArray[i]);
    }
  }


  void executeOrder(int orderNumber){
    switch(orderNumber){
      case forward:
        goForward();
        delay(300);
         break;
      case left:
        turnLeft();
        delay(333);
         break;
      case right:
        turnRight();
        delay(366);
         break;
      case pause:
        stopM(HIGH, HIGH, HIGH);
        endOfTrip=true;
         break;
      default:
        goForward();
        break;
      } 
  }

void pulsing() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, HIGH);
}

void turnLeft() {
  
  digitalWrite(leftLED, HIGH);

  digitalWrite (motorABrake, LOW);
  digitalWrite (motorBBrake, LOW);

  digitalWrite(MotorABDIR, LOW);
  digitalWrite(MotorBDIR, HIGH);

  analogWrite (motorAspeed, turn_speed);
  analogWrite (motorBspeed, vSpeed);

   digitalWrite(leftLED, LOW);

}

void turnRight() {
  digitalWrite(rightLED, HIGH);


  digitalWrite (motorABrake, LOW);
  digitalWrite (motorBBrake, LOW);

  digitalWrite(MotorABDIR, HIGH);
  digitalWrite(MotorBDIR, LOW);

  analogWrite (motorAspeed, vSpeed);
  analogWrite (motorBspeed, turn_speed);

  digitalWrite(rightLED, LOW);
}

void goForward() {
  digitalWrite(rightLED, HIGH);
  digitalWrite(leftLED, HIGH);

  digitalWrite (MotorABDIR, HIGH);
  digitalWrite(motorABrake, LOW);

  digitalWrite (MotorBDIR, HIGH);
  digitalWrite(motorBBrake, LOW);

  analogWrite (motorAspeed, vSpeed);
  analogWrite (motorBspeed, vSpeed);

  digitalWrite(rightLED, LOW);
  digitalWrite(leftLED, LOW);
}

void goBackwards(){

    digitalWrite(rightLED, HIGH);
  digitalWrite(leftLED, HIGH);

  digitalWrite (MotorABDIR, LOW);
  digitalWrite(motorABrake, LOW);

  digitalWrite (MotorBDIR, LOW);
  digitalWrite(motorBBrake, LOW);

  analogWrite (motorAspeed, vSpeed);
  analogWrite (motorBspeed, vSpeed);

  digitalWrite(rightLED, LOW);
  digitalWrite(leftLED, LOW);
  
  
  }


void stopM(bool state2, bool state, bool state3) {

  LEDstate = !LEDstate;
  digitalWrite(leftLED, state2);
  digitalWrite(rightLED, state);
 
  digitalWrite(correctionLED, state3);
  analogWrite (motorAspeed, 0);
  analogWrite (motorBspeed, 0);
   delay(250);

  digitalWrite(leftLED, LOW);
  digitalWrite(rightLED, LOW);
  digitalWrite(correctionLED, LOW);
}



void blinkk(bool state1, bool state2, bool state3){

  for(int i=0;i<10;i++)
  {
    
      Serial.println("  blink   ");
    digitalWrite(leftLED, state1);
    digitalWrite(rightLED, state2);
    digitalWrite(correctionLED, state3);
  
    state1 =! state1;
    state2 =! state2;
    state3 =! state3;
    delay(200);
  } 
  digitalWrite(leftLED, LOW);
  digitalWrite(rightLED, LOW);
  digitalWrite(correctionLED, LOW);
}
