// Battery.h

#ifndef _BATTERY_h
#define _BATTERY_h

#include "Task.h"

class Battery : public Task {

public:
	Battery(int lap = 0, int pin = A7);
	bool hasStatus();
	float getStatus();
private:
	float status;
	int pin;
	virtual void execute(String command);
};

#endif

