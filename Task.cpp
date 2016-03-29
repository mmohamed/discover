// 
// 
// 
#include "Arduino.h"
#include "Task.h"

Task::Task(int lap) {
	this->lap = lap;
}

void Task::setApplication(Application *application){
	this->application = application;
}

Application* Task::getApplication(){
	return this->application;
}

void Task::start() {
	if (this->isRunnable())
		return;
	this->isStoped = false;

	this->lastExecutedTime = millis();
}

void Task::run(String command) {
	if (this->isRunnable()) {
		unsigned long now = millis();

		if (now - this->lastExecutedTime > this->lap || this->lap == 0){
			// execute
			this->execute(command);
			// update
			this->lastExecutedTime = now;
		}
	}
}

void Task::stop() {
	if (!this->isRunnable())
		return;
	this->isStoped = true;
}

bool Task::isRunnable() {
	return !this->isStoped;
}

void Task::execute(String command) {

}

void Task::debug(String command) {

}

Task::~Task() {

}




