// 
// 
// 
#include "Arduino.h"
#include "IR.h"

IR::IR(int pin) : Task(){
	this->pin = pin;
	pinMode(this->pin, INPUT);
}

void IR::execute(String command){

}

bool IR::isDetect(){
	return digitalRead(this->pin) == LOW;
}


