// 
// 
// 

#include "CommandServoTask.h"
#include "Arduino.h"
#include <Servo.h>

const int pin = 10;
const int min = 18;

CommandServoTask::CommandServoTask() :
Task() {
	this->servo = new Servo();
	this->servo->attach(pin);
	this->servo->write(18);
	this->lastCommand = "";
}

void CommandServoTask::execute(String command){
	String cmd = "SERVO";

	if (command.substring(0, cmd.length()) == cmd){
		String originalCommand = command.substring(0);
		String newposition = command.substring(cmd.length());
		newposition.trim();

		// save 
		this->lastCommand = newposition;

		int position = newposition.toInt();
		if (position < min)
			position = min;

		this->servo->write(position);
	}
}

bool CommandServoTask::hasCommand(){
	return this->lastCommand !=  "";
}

String CommandServoTask::getCommand(){
	return this->lastCommand;
}




