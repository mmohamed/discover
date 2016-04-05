// Car.h

#ifndef _CARTASK_h
#define _CARTASK_h

#include <AFMotor.h>
#include "Arduino.h"
#include "Task.h"

const int SLOW = 124;
const int NORM = 172;
const int FAST = 255;

const int ROTATE_LEFT = 1;
const int ROTATE_RIGHT = 2;

const int NO_TIMER = -1;

class CarTask : public Task{

public:
	CarTask();

	void forward(int speed = NORM, int timer = NO_TIMER);
	void stop();
	void backward(int speed = NORM, int timer = NO_TIMER);
	void rotate(int direction = ROTATE_RIGHT, int angle = 90);
	bool onRotation();
	String direction();
private:
	AF_DCMotor *backRight;
	AF_DCMotor *backLeft;
	AF_DCMotor *frontRight;
	AF_DCMotor *frontLeft;
	int leftStatus;
	int rightStatus;
	int lastLeftStatus;
	int lastRightStatus;
	int timer;
	bool isRotated;
	unsigned long lastStartAt;
	void setSpeed(int speed);
	virtual void execute(String command);
	virtual void set(int direction);
};

#endif

