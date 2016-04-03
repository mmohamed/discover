// 
// 
// 

#include "Arduino.h"
#include "Bluetooth.h"

Bluetooth::Bluetooth(int lap) : Task(lap){
	this->lap = lap;
	Serial3.begin(9600);
}

void Bluetooth::execute(String command){
	//receive
	this->receivedCommand = "";
	while (Serial3.available() > 0){
		this->receivedCommand += char(Serial3.read());
	}
	// send
	if (!Serial3.available() && this->sendedData != ""){
		Serial3.println(this->sendedData);
		this->sendedData = "";
	}
}

bool Bluetooth::set(String data){
	this->sendedData = data;
}

String Bluetooth::get(){
	return this->receivedCommand;
}