#include<Arduino.h>
/*
EE107 Autonomous Car Project
Code by Elliott Gear
Car by Robert Hanaman
*/


// defines pins numbers
// motor pins
const int lefFor = 2;
const int rigFor = 3;
const int lefBack = 4;
const int rigBack = 5;

// sensor pins
const int trigPinL = 8;
const int echoPinL = 9;
const int trigPinR = 10;
const int echoPinR = 11;

// defines variables
long duration;
int distance;

int distanceL;
int distanceR;

bool obstructionLeft = false;
bool obstructionRight = false;

// define constants
int obsticalDetected = 15;
int turnDelayTime = 500;

// SETUP
void setup() {
    // motor setup
    pinMode(lefFor, OUTPUT);
    pinMode(rigFor, OUTPUT);
    pinMode(lefBack, OUTPUT);
    pinMode(rigBack, OUTPUT);

    // sensor setup
    pinMode(trigPinL, OUTPUT);
    pinMode(echoPinL, INPUT);
    pinMode(trigPinR, OUTPUT);
    pinMode(echoPinR, INPUT);

    Serial.begin(9600);
}

// MAIN LÖÖP
void loop() {
    if((getRightDistance() > obsticalDetected) && (getLeftDistance() > obsticalDetected)){
        driveForward();
    }
    else if((getRightDistance() > obsticalDetected) && (getLeftDistance() < obsticalDetected)){
        turnLeft();
        delay(turnDelayTime);
    }
    else if ((getRightDistance() < obsticalDetected) && (getLeftDistance() > obsticalDetected))
    {
        turnRight();
        delay(turnDelayTime);
    }
    
    
    
    else{ // emergency stop i guess????
        stop();
    }

    
}

// Obstriction setter/checker
void setObstructions(){
    return;
}


// DRIVING FUNCTIONS
void driveForward(){
    digitalWrite(lefFor , HIGH);
    digitalWrite(lefBack , LOW);
    digitalWrite(rigFor , HIGH);
    digitalWrite(rigBack , LOW);
}

void turnLeft(){
    digitalWrite(lefFor , HIGH);
    digitalWrite(lefBack , LOW);
    digitalWrite(rigFor , LOW);
    digitalWrite(rigBack , LOW);
}

void turnRight(){
    digitalWrite(lefFor , LOW);
    digitalWrite(lefBack , LOW);
    digitalWrite(rigFor , HIGH);
    digitalWrite(rigBack , LOW);
}

void stop(){
    digitalWrite(lefFor , LOW);
    digitalWrite(lefBack , LOW);
    digitalWrite(rigFor , LOW);
    digitalWrite(rigBack , LOW);
}


void obsticalChecker(){
    distanceL = getLeftDistance();
    distanceR = getRightDistance();


}

// DISTANCE GETTERS
long getLeftDistance(){
    digitalWrite(trigPinL, LOW);
    delayMicroseconds(2);

    digitalWrite(trigPinL, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPinL, LOW);

    duration = pulseIn(echoPinL, HIGH);

    distance= duration*0.034/2;

    Serial.print("Left Distance: ");
    Serial.println(distance);

    return distance;
}

long getRightDistance(){
    digitalWrite(trigPinR, LOW);
    delayMicroseconds(2);

    digitalWrite(trigPinR, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPinR, LOW);

    duration = pulseIn(echoPinR, HIGH);

    distance= duration*0.034/2;

    Serial.print("Right Distance: ");
    Serial.println(distance);

     return distance;
}
