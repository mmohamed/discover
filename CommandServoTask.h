// CommandServoTask.h

#ifndef _COMMANDSERVOTASK_h
#define _COMMANDSERVOTASK_h

#include <Servo.h>
#include "Task.h"

class CommandServoTask: public Task {
public:
	CommandServoTask();
	bool hasCommand();
	String getCommand();
private:
	Servo *servo;
	String lastCommand;
	virtual void execute(String command);
};

#endif

