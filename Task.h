// Task.h

#ifndef _TASK_h
#define _TASK_h

#include "Application.h"
class Application;

class Task {

public:
	Task(int lap = 0);
	virtual ~Task();
	void start();
	void run(String command);
	void stop();
	virtual void debug(String command);
	void setApplication(Application *application);
	Application* getApplication();
	int lap = 0;
private:
	virtual void execute(String command);
	bool isRunnable();
	Application *application;
	bool isStoped = true;
	unsigned long lastExecutedTime = 0;
};

#endif

