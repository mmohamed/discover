// Application.h
#include "Arduino.h"
#include "Task.h"

#ifndef _APPLICATION_h
#define _APPLICATION_h

class Task;

class Application {
	const int MAX_TASK = 12;
public:
	Application();
	void init();
	virtual ~Application();
	void registerTask(Task *task);
	void registerDebugger(Task *task);
	void fire();
	void unregisterTask(Task *task);
	void debug(String data);
	void printSerial(String string);
private:
	Task* tasks[12];
	Task* debugger;
	int taskNumber = 0;
	String serialBuffer;
	String command;
	bool send;
};

#endif

