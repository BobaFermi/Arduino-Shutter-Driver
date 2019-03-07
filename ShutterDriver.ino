#include "Timer.h"
Timer t;

// use motor shield
#include <AFMotor.h>

//instantiate four shutter objects
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
  //set maximum current for driving shutters
  shut1.setSpeed(255);
  shut2.setSpeed(255);
  shut3.setSpeed(255);
  shut4.setSpeed(255);

  //run forward to open all shutters
  shut1.run(FORWARD);
  shut2.run(FORWARD);
  shut3.run(FORWARD);
  shut4.run(FORWARD);

  //set up all LED pins as outputs
  pinMode(LED_1, OUTPUT); 
  pinMode(LED_2, OUTPUT); 
  pinMode(LED_3, OUTPUT); 
  pinMode(LED_4, OUTPUT); 

  //set up all digital inputs as inputs
  pinMode(INP_1, INPUT);  
  pinMode(INP_2, INPUT);      
  pinMode(INP_3, INPUT);      
  pinMode(INP_4, INPUT);      

  //set initial status to 'closed' status
  status_1 = 1;
  status_2 = 1;
  status_3 = 1;
  status_4 = 1;

  //change to open mode
  changeStatus1(0);
  changeStatus2(0);
  changeStatus3(0);
  changeStatus4(0);
}

//stops driving current through shutter 1
void resetOutput1() {
  shut1.run(RELEASE);
}
//stops driving current through shutter 2
void resetOutput2() {
  shut2.run(RELEASE);
}
//stops driving current through shutter 3
void resetOutput3() {
  shut3.run(RELEASE);
}
//stops driving current through shutter 4
void resetOutput4() {
  shut4.run(RELEASE);
}

//used to control direction of current in shutter 1
void changeStatus1(int mode) {
  if ((mode == 1) && (status_1 != 1)) {   //if shutter status is closed, and we select open mode
    shut1.run(FORWARD);                   //drive forward current to open the shutter
    status_1 = 1;                         //keep track of the open sttus of the shutter
    t.after( tWait, resetOutput1 );       //after tWait time, stop driving current
    digitalWrite(LED_1, HIGH);            //switch shutter 1 LED indicator on
    return;                               //go back to start of void loop()
  }
  if ((mode == 0) && (status_1 != 0)) {   //if shutter status is open, and we select closed mode
    shut1.run(BACKWARD);                  //drive reverse current to close the shutter
    status_1 = 0;                         //keep track of the shutter closed status
    t.after( tWait, resetOutput1 );       //after tWait duration, stop driving current
    digitalWrite(LED_1, LOW);             //switch off shutter 1 LED indicator
  }
}

//used to control direction of current in shutter 2
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

//used to control direction of current in shutter 3
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

//used to control direction of current in shutter 4
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

  t.update();       //make sure we haven't gone over tWait time yet

  TTL_1 = digitalRead(INP_1);   //check the digital input to control shutter 1
  
  if ((TTL_1 == HIGH) && (status_1 == 0) ) {        //if the status is closed and the digital input is high
    changeStatus1(1);                               //drive current to open shutter
  } else if ((TTL_1 == LOW) && (status_1 == 1)) {   //if the status is open and the digital input is low
    changeStatus1(0);                               //drive current to close the shutter
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
