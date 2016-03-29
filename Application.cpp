// 
// 
// 

#include "Arduino.h"
#include "Application.h"
#include "Task.h"
#include "ScreenTask.h"

Application::Application() {

}

void Application::init() {
	this->taskNumber = 0;
	this->serialBuffer = "";
	this->command = "";
	this->send = false;
	Serial.begin(19200);
}

void Application::registerTask(Task *task) {
	if (this->taskNumber == MAX_TASK)
		return;
	this->tasks[this->taskNumber] = task;
	this->taskNumber++;

	task->setApplication(this);
}

void Application::registerDebugger(Task *screen){
	this->debugger = screen;
	this->registerTask(screen);
}

void Application::fire() {
	if (Serial.available()) {
		char ch = Serial.read();
		if (ch != -1) {
			if (ch == '\n' || ch == '\r' || ch == '\r\n'){
				this->command = this->serialBuffer.substring(0);
				this->send = true;
				this->serialBuffer = "";
				this->command.trim();
			}
			else{
				this->serialBuffer += ch;
			}
		}
	}

	for (int i = 0; i < MAX_TASK; i++) {
		if (this->send){
			this->command.toUpperCase();
			this->tasks[i]->run(this->command);
		}
		else{
			this->tasks[i]->run(String(""));
		}
	}
	this->send = false;
}

void Application::debug(String data) {
	if (this->debugger != NULL){
		this->debugger->debug(data);
	}
}

void Application::printSerial(String string){
	Serial.println(string);
}

void Application::unregisterTask(Task *task) {

}

Application::~Application() {

}



