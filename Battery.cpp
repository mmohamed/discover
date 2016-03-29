// 
// 
// 

#include "Arduino.h"
#include "Battery.h"

Battery::Battery(int lap, int pin) : Task(lap){
	this->lap = lap;
	this->pin = pin;
	this->status = 0.0;
}

void Battery::execute(String command){
	unsigned int value = analogRead(this->pin);
	this->status = value * (5.0 / 1023);
}

float Battery::getStatus(){
	return this->status;
}

bool Battery::hasStatus(){
	return this->status != 0.0;
}
