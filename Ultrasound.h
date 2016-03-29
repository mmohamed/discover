// Ultrasound.h

#ifndef _ULTRASOUND_h
#define _ULTRASOUND_h

#include "Arduino.h"
#include "Task.h"

class Ultrasound : public Task {

public:
	Ultrasound(int lap = 0, int trigPin = 53, int echoPin = 52);
	float getReaded();
	bool hasMesure();
private:
	int status;
	unsigned long lastTriggered;
	float lastReaded;
	int trigPin;
	int echoPin;
	virtual void execute(String command);
};

#endif

