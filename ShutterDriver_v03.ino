/* Shutter Driver for Samsnung Q1 shutters
/*
/* - Drive 4 samsung shutters, depending on a manual input or on a TTL
/* - use motorshield to drive directional current, apply 5V to the shutter solenoids
/* - use timer for current pulses
/* - indicate shutter status with led
/* - this sketch uses an arduino mega. You need to change the pins for an uno.
/*********************************************************************************/

#include "Timer.h"
Timer t;

// use motor shield
#include <AFMotor.h>
AF_DCMotor shut1(1);
AF_DCMotor shut2(2);
AF_DCMotor shut3(3);
AF_DCMotor shut4(4);

// pins for leds and input signals
int INP_1   = 40;
int LED_1   = 23;
int INP_2   = 50;
int LED_2   = 51;
int INP_3   = 48;
int LED_3   = 49;
int INP_4   = 46;
int LED_4   = 47;

// status flags and TTL input for each shutter
int status_1;
int TTL_1;
int status_2;
int TTL_2;
int status_3;
int TTL_3;
int status_4;
int TTL_4;


// pulse length
const long tWait = 100;


void setup() {

  shut1.setSpeed(255);
  shut2.setSpeed(255);
  shut3.setSpeed(255);
  shut4.setSpeed(255);

  shut1.run(FORWARD);
  shut2.run(FORWARD);
  shut3.run(FORWARD);
  shut4.run(FORWARD);

  pinMode(LED_1, OUTPUT); 
  pinMode(LED_2, OUTPUT); 
  pinMode(LED_3, OUTPUT); 
  pinMode(LED_4, OUTPUT); 

  pinMode(INP_1, INPUT);  
  pinMode(INP_2, INPUT);      
  pinMode(INP_3, INPUT);      
  pinMode(INP_4, INPUT);      

  // set initial status 
  status_1 = 1;
  status_2 = 1;
  status_3 = 1;
  status_4 = 1;

  changeStatus1(0);
  changeStatus2(0);
  changeStatus3(0);
  changeStatus4(0);
}


void resetOutput1() {
  shut1.run(RELEASE);
}
void resetOutput2() {
  shut2.run(RELEASE);
}
void resetOutput3() {
  shut3.run(RELEASE);
}
void resetOutput4() {
  shut4.run(RELEASE);
}


void changeStatus1(int mode) {
  if ((mode == 1) && (status_1 != 1)) {
    shut1.run(FORWARD);
    status_1 = 1;
    t.after( tWait, resetOutput1 );
    digitalWrite(LED_1, HIGH);
    return;
  }
  if ((mode == 0) && (status_1 != 0)) {
    // set status 1
    shut1.run(BACKWARD);
    status_1 = 0;
    t.after( tWait, resetOutput1 );
    digitalWrite(LED_1, LOW);
  }
}

void changeStatus2(int mode) {
  if ((mode == 1) && (status_2 != 1)) {
    shut2.run(FORWARD);
    status_2 = 1;
    t.after( tWait, resetOutput2 );
    digitalWrite(LED_2, HIGH);
    return;
  }
  if ((mode == 0) && (status_2 != 0)) {
    // set status 2
    shut2.run(BACKWARD);
    status_2 = 0;
    t.after( tWait, resetOutput2 );
    digitalWrite(LED_2, LOW);
  }
}

void changeStatus3(int mode) {
  if ((mode == 1) && (status_3 != 1)) {
    shut3.run(FORWARD);
    status_3 = 1;
    t.after( tWait, resetOutput3 );
    digitalWrite(LED_3, HIGH);
    return;
  }
  if ((mode == 0) && (status_3 != 0)) {
    shut3.run(BACKWARD);
    status_3 = 0;
    t.after( tWait, resetOutput3 );
    digitalWrite(LED_3, LOW);
  }
}

void changeStatus4(int mode) {
  if ((mode == 1) && (status_4 != 1)) {
    shut4.run(FORWARD);
    status_4 = 1;
    t.after( tWait, resetOutput4 );
    digitalWrite(LED_4, HIGH);
    return;
  }
  if ((mode == 0) && (status_4 != 0)) {
    shut4.run(BACKWARD);
    status_4 = 0;
    t.after( tWait, resetOutput4 );
    digitalWrite(LED_4, LOW);
  }
}

void loop() {

  t.update();

  TTL_1 = digitalRead(INP_1);
  
  if ((TTL_1 == HIGH) && (status_1 == 0) ) {
    changeStatus1(1);
  } else if ((TTL_1 == LOW) && (status_1 == 1)) {
    changeStatus1(0);
  }

  TTL_2 = digitalRead(INP_2);
  if ((TTL_2 == HIGH) && (status_2 == 0) ) {
    changeStatus2(1);
  } else if ((TTL_2 == LOW) && (status_2 == 1)) {
    changeStatus2(0);
  }

  TTL_3 = digitalRead(INP_3);
  if ((TTL_3 == HIGH) && (status_3 == 0) ) {
    changeStatus3(1);
  } else if ((TTL_3 == LOW) && (status_3 == 1)) {
    changeStatus3(0);
  }

  TTL_4 = digitalRead(INP_4);
  if ((TTL_4 == HIGH) && (status_4 == 0) ) {
    changeStatus4(1);
  } else if ((TTL_4 == LOW) && (status_4 == 1)) {
    changeStatus4(0);
  }
}
