// LedTask.h

#ifndef _LEDTASK_h
#define _LEDTASK_h

#include "Task.h"

class LedTask: public Task {

public:
	LedTask(int lap = 0, int pin = 13);
private:
	int ledState;
	int pin;
	virtual void execute(String command);
};

#endif

