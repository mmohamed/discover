
#include "Application.h"
#include "ScreenTask.h"
#include "LedTask.h"
#include "MainServoTask.h"
#include "CommandServoTask.h"
#include "Ultrasound.h"
#include "IR.h"
#include "Battery.h"
#include "CarTask.h"
#include "Bluetooth.h"

Application app;

Ultrasound *frontUltrasound;
Ultrasound *leftUltrasound;
Ultrasound *rightUltrasound;

IR *frontObstacle;
//IR *backObstacle;

ScreenTask *screen;

//LedTask *led;
//CommandServoTask *commandServo;
//MainServoTask *autoServo;

Battery *battery;
CarTask *car;

Bluetooth *bridge;

const int MODE_AUTO = 1;
const int MODE_CMD = 2;

int mode = MODE_AUTO;

void setup() {

	app.init();

	screen = new ScreenTask();
	//led = new LedTask(100);
	//autoServo = new MainServoTask(5000);
	//commandServo = new CommandServoTask();
	frontUltrasound = new Ultrasound(5, 53, 52);
	rightUltrasound = new Ultrasound(5, 47, 46);
	leftUltrasound = new Ultrasound(5, 49, 48);
	//backObstacle = new IR(50);
	frontObstacle = new IR(51);

	battery = new Battery(1000, A7);
	car = new CarTask();
	bridge = new Bluetooth(50);

	screen->start();
	//led->start();
	//autoServo->start();
	//commandServo->start();
	frontUltrasound->start();
	rightUltrasound->start();
	leftUltrasound->start();
	frontObstacle->start();
	//backObstacle->start();
	battery->start();
	car->start();
	bridge->start();

	app.registerDebugger(screen);

	//app.registerTask(led);
	//app.registerTask(autoServo);
	//app.registerTask(commandServo);
	app.registerTask(frontUltrasound);
	app.registerTask(rightUltrasound);
	app.registerTask(leftUltrasound);
	app.registerTask(frontObstacle);
	//app.registerTask(backObstacle);
	app.registerTask(battery);
	app.registerTask(car);
	app.registerTask(bridge);

	screen->println("Init all service.......OK");

	// disable auto-flush before loop
	screen->setAutoFlush(false);
}

void loop() {
	app.fire();

	print();

	modeSwitch();

	if (mode == MODE_AUTO){
		processAuto();
	}else if(mode == MODE_CMD){
		processOnCommand();
	}
}

void modeSwitch()
{
	if (bridge->get() != ""){
		
		String command = bridge->get();
		command.toUpperCase();
		command.trim();

		if (command == "AUTO" && mode != MODE_AUTO){
			mode = MODE_AUTO;
			bridge->set("Switch mode for Auto");
		}
		else if (command == "CMD" && mode != MODE_CMD){
			mode = MODE_CMD;
			bridge->set("Switch mode for Command");
		}
	}
}
/*
* Command process
*/
void processOnCommand()
{
	if (bridge->get() != ""){ // has command
		String command = bridge->get();
		command.toUpperCase();
		command.trim();

		if (command == "GO"){
			bridge->set("Go for 1000ms");
			car->forward(FAST, 1000);
		}
		else if (command == "BACK"){
			bridge->set("Back for 1000ms");
			car->backward(FAST, 1000);
		}
		else if (command == "RR"){
			bridge->set("Rotation for 90d or right");
			car->rotate(ROTATE_RIGHT);
		}
		else if (command == "RL"){
			bridge->set("Rotation for 90d or left");
			car->rotate(ROTATE_LEFT);
		}
		else if(command !="CMD" && command != "AUTO"){
			car->stop();
			bridge->set("unknown command ! => "+command);
		}
	}
}

/*
* Auto-process
*/
void processAuto(){

	// get of reader distance on front
	long frontMesure = frontUltrasound->hasMesure() ? frontUltrasound->getReaded() : 99999999;
	long rightMesure = rightUltrasound->hasMesure() ? rightUltrasound->getReaded() : 99999999;
	long leftMesure = leftUltrasound->hasMesure() ? leftUltrasound->getReaded() : 99999999;

	// take min
	long mesure = min(frontMesure, rightMesure);
	mesure = min(mesure, leftMesure);

	if ((!car->onRotation() && mesure == 99999999) || frontObstacle->isDetect()){
		car->stop();
	}
	else{
		if (mesure > 500){
			car->forward(FAST);
		}else if (mesure < 500 && mesure > 50){
			car->forward(SLOW);
		}
		else{
			car->stop();
		}
	}
}

/**
* Print global status on screen
*/
void print(){

	if (frontUltrasound->hasMesure()){
		long frontDistance = frontUltrasound->getReaded();
		String frontFormated = String((float)frontDistance / 1000.0);
		for (int i = frontFormated.length(); i < 5; i++){
			frontFormated += '0';
		}
		screen->print("[FrontUltrasound]..." + String(frontFormated), 1);
	}
	else{
		screen->print("[FrontUltrasound].....NOK" , 1);
	}

	if (rightUltrasound->hasMesure()){
		long rightDistance = rightUltrasound->getReaded();
		String rightFormated = String((float)rightDistance / 1000.0);
		for (int i = rightFormated.length(); i < 5; i++){
			rightFormated += '0';
		}
		screen->print("[RightUltrasound]..." + String(rightFormated), 2);
	}
	else{
		screen->print("[RightUltrasound].....NOK", 2);
	}

	if (leftUltrasound->hasMesure()){
		long leftDistance = leftUltrasound->getReaded();
		String leftFormated = String((float)leftDistance / 1000.0);
		for (int i = leftFormated.length(); i < 5; i++){
			leftFormated += '0';
		}
		screen->print("[LeftUltrasound]...." + String(leftFormated), 3);
	}
	else{
		screen->print("[LeftUltrasound].....NOK", 3);
	}

	if (frontObstacle->isDetect()){
		screen->print("[FrontIR].............YES", 4);
	}
	else{
		screen->print("[FrontIR]..............NO", 4);
	}

	/*if (backObstacle->isDetect()){
		screen->print("[BackIR]..............YES", 5);
	}
	else{
		screen->print("[BackIR]...............NO", 5);
	}*/
	screen->print("[BackIR]..............NOK", 5);

	if (battery->hasStatus()){
		String value = String((float)battery->getStatus());
		value += "v";
		screen->print("[Battery]..........." + String(value), 6);
	}
	else{
		screen->print("[Battery]..............NO", 6);
	}

	screen->print("[Car]............." + car->direction(), 7);

	String m = "NOK";
	if (mode == MODE_AUTO)
		m = "AUTO";
	else
		m = "COMMAND";

	screen->print("[Mode]............." + m, 8);

	/*if (commandServo->hasCommand()){
		String command = commandServo->getCommand();
		for (int i = command.length(); i < 3; i++){
		command = '0' + command;
		}
		screen->print("[CommandServo]........" + command, 8);
		}else{
		screen->print("[CommandServo].........NO", 8);
	}*/

	// flush
	screen->flush();
}