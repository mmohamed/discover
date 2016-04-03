// Bluetooth.h

#ifndef _BLUETOOTH_h
#define _BLUETOOTH_h

#include "Task.h"

class Bluetooth : public Task {

public:
	Bluetooth(int lap = 500);
	bool set(String data);
	String get();
private:
	String receivedCommand;
	String sendedData;
	virtual void execute(String command);
};

#endif

