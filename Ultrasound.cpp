// 
// 
// 
#include "Arduino.h"
#include "Ultrasound.h"

const int SLEEP = 0;
const int SEND = 1;

Ultrasound::Ultrasound(int lap, int trigPin, int echoPin) : Task(lap){
	this->lap = lap;

	this->trigPin = trigPin;
	this->echoPin = echoPin;

	pinMode(this->trigPin, OUTPUT);
	pinMode(this->echoPin, INPUT);
	digitalWrite(this->trigPin, LOW);

	this->status = SLEEP;
	this->lastTriggered = 0;
	this->lastReaded = -1;

}

void Ultrasound::execute(String command){
	if (this->status == SLEEP){
		digitalWrite(this->trigPin, HIGH);
		this->lastTriggered = micros();
		this->status = SEND;
	}
	else if (this->status == SEND){
		if ((micros() - this->lastTriggered) > 9){ // stop send and read 
			digitalWrite(this->trigPin, LOW);
			long readed = pulseIn(this->echoPin, HIGH);
			this->lastReaded = readed / 5.8;
			this->status = SLEEP;
		}
	}
}

float Ultrasound::getReaded(){
	return this->lastReaded;
}

bool Ultrasound::hasMesure(){
	return this->lastReaded != -1;
}


