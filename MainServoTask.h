// MainServoTask.h

#ifndef _MAINSERVOTASK_h
#define _MAINSERVOTASK_h

#include <Servo.h>
#include "Task.h"

class MainServoTask: public Task {
public:
	MainServoTask(int lap = 0);
private:
	Servo *servo;
	int position;
	virtual void execute(String command);
};

#endif

