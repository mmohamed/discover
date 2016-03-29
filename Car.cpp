// 
// 
// 

#include "Car.h"

Car::Car() :
Task() {
	this->backLeft = new AF_DCMotor(1, MOTOR12_64KHZ);
	this->backRight = new AF_DCMotor(2, MOTOR12_64KHZ);
	this->frontRight = new AF_DCMotor(3);
	this->frontLeft = new AF_DCMotor(4);

	this->setSpeed(NORM);

	this->leftStatus = RELEASE;
	this->rightStatus = RELEASE;
	this->lastLeftStatus = RELEASE;
	this->lastRightStatus = RELEASE;

	this->timer = NO_TIMER;
	this->lastStartAt = 0;
	this->isRotated = false;
}

void Car::execute(String command){
	unsigned long now = millis();

	if (this->timer != NO_TIMER && (now - this->lastStartAt) > this->timer){
		// stop all
		this->stop();
	}

	if (this->lastLeftStatus != this->leftStatus || this->lastRightStatus != this->rightStatus){
		this->frontRight->run(this->rightStatus);
		this->frontLeft->run(this->leftStatus);
		this->backRight->run(this->rightStatus);
		this->backLeft->run(this->leftStatus);	
	}
}

bool Car::onRotation(){
	return this->isRotated;
}

void Car::rotate(int direction, int angle, int speed){
	this->setSpeed(speed);
	// if in slow mode 1 degree => 2 millis
	int rotationTimer = angle * 2;
	if (speed == NORM)
		rotationTimer = (int)rotationTimer * 0.75;
	if (speed == FAST)
		rotationTimer = rotationTimer / 2;

	this->timer = rotationTimer;
	this->lastStartAt = millis();

	// save old
	this->lastLeftStatus = this->leftStatus;
	this->lastRightStatus = this->rightStatus;

	if (direction == ROTATE_RIGHT){
		// inversed
		this->leftStatus = BACKWARD;
		this->rightStatus = RELEASE;
	}
	else{
		this->leftStatus = FORWARD;
		this->rightStatus = RELEASE;
	}

	this->isRotated = true;
}

void Car::setSpeed(int speed){
	if (speed > 255)
		speed = 255;

	this->frontRight->setSpeed(speed);
	this->frontLeft->setSpeed(speed);
	this->backRight->setSpeed(speed);
	this->backLeft->setSpeed(speed);
}

void Car::forward(int speed, int timer){
	this->setSpeed(speed);
	//set timer limit
	this->timer = timer;
	this->lastStartAt = millis();
	// inversed all
	this->set(BACKWARD);
}

void Car::backward(int speed, int timer){
	this->setSpeed(speed);
	//set timer limit
	this->timer = timer;
	this->lastStartAt = millis();
	// inversed all
	this->set(FORWARD);
}

void Car::stop(){
	this->timer = NO_TIMER;
	this->isRotated = false;
	this->set(RELEASE);
}

void Car::set(int direction){
	this->lastLeftStatus = this->leftStatus;
	this->lastRightStatus = this->rightStatus;
	this->leftStatus = direction;
	this->rightStatus = direction;
}

String Car::direction(){
	if (this->leftStatus != this->rightStatus)
		return String("ROTATE");
	if (this->leftStatus == RELEASE)
		return String("RELEASE");
	if (this->leftStatus == FORWARD)
		return String("BACKWARD");
	return String("FORWARD");
}