// IR.h

#ifndef _IR_h
#define _IR_h

#include "Task.h"

class IR : public Task {

public:
	IR(int pin = 50);
	bool isDetect();
private:
	int pin;
	virtual void execute(String command);
};

#endif

