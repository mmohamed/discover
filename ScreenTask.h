// ScreenTask.h

#ifndef _SCREENTASK_h
#define _SCREENTASK_h

#include <U8glib.h>
#include "Task.h"

class ScreenTask: public Task{
	const int CHAR_WIDTH = 5;
	const int CHAR_HEIGHT = 7;
	const int SCREEN_WIDTH = 128;
	const int SCREEN_HEIGHT = 64;

public:
	ScreenTask();

	int print(String string, int position = 0);
	void println(String string);
	void out(String string);
	virtual void debug(String string);
	void clear();
private:
	char *message;
	String content[9];
	int currentRow;

	virtual void execute(String command);
	virtual void draw();
};

#endif

