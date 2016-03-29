// 
// 
// 
#include "Arduino.h"
#include "MainServoTask.h"
#include <Servo.h>

const int pin = 9;
const int min = 18;

MainServoTask::MainServoTask(int lap) :
Task(lap) {
	this->servo = new Servo();
	this->servo->attach(pin);
	this->position = min;
	this->lap = lap;
	this->servo->write(min);
}

void MainServoTask::execute(String command) {
	switch (this->servo->read()) {
	case min:
		this->position = 90;
		break;
	case 90:
		this->position = 180;
		break;
	case 180:
		this->position = min;
		break;
	}
	this->servo->write(this->position);
}

