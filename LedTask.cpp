// 
// 
// 
#include "Arduino.h"
#include "LedTask.h"

LedTask::LedTask(int lap, int pin) : Task(lap){
	this->pin = pin;
	pinMode(this->pin, OUTPUT);
	this->ledState = LOW;
	this->lap = lap;
}

void LedTask::execute(String command){
	if (this->ledState == LOW)
		this->ledState = HIGH;
	else
		this->ledState = LOW;
	digitalWrite(this->pin, this->ledState);
}

