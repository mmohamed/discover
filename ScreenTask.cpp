// 
// 
// 

#include "ScreenTask.h"

U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NO_ACK);

ScreenTask::ScreenTask() :
Task() {

	if (u8g.getMode() == U8G_MODE_R3G3B2) {
		u8g.setColorIndex(255); // white
	}
	else if (u8g.getMode() == U8G_MODE_GRAY2BIT) {
		u8g.setColorIndex(3); // max intensity
	}
	else if (u8g.getMode() == U8G_MODE_BW) {
		u8g.setColorIndex(1); // pixel on
	}
	else if (u8g.getMode() == U8G_MODE_HICOLOR) {
		u8g.setHiColorByRGB(255, 255, 255);
	}
	// init 
	this->clear();
}

void ScreenTask::execute(String command){

	String cmd = "SCREEN";
	String clearcmd = "CLEAR";

	if (command.substring(0, cmd.length()) == cmd){
		String originalCommand = command.substring(0);
		String message = command.substring(cmd.length());
		message.trim();
		this->println(message);
	}
	else if (command.substring(0, clearcmd.length()) == clearcmd){ 
		this->clear();
	}
}

int ScreenTask::print(String string, int position){
	if (string.length() > (SCREEN_WIDTH / CHAR_WIDTH)){
		string = string.substring(0, 22) + "...";
	}
	if (position == 0)
		this->content[this->currentRow] = string;
	else
		this->content[position] = string;

	this->draw();

	if (position == 0)
		return this->currentRow;
	return position;
}

void ScreenTask::println(String string){
	if (this->currentRow == 9){ // last row
		for (int i = 0; i < 8; i++)
			this->content[i] = this->content[i + 1];
		this->currentRow = 8;
		this->print(string);
		this->currentRow = 9;
	}
	else{
		this->print(string);
		this->currentRow = this->currentRow + 1;
	}
}

void ScreenTask::out(String string){
	while (-1 != string.indexOf('\n')){
		String line = string.substring(0, string.indexOf('\n'));
		string = string.substring(string.indexOf('\n') + 1);
		line.trim();
		this->println(line);
	}
	// one line  or last line
	string.trim();
	if (string.length() > 0){
		this->println(string);
	}
}

void ScreenTask::debug(String string){
	while (string.length() > 0){
		String line = string.substring(0, 25);
		string = string.substring(25);
		line.trim();
		this->println(line);
	}
	// one line  or last line
	string.trim();
	if (string.length() > 0){
		this->println(string);
	}
}

void ScreenTask::clear(){
	u8g.firstPage();
	do {} while (u8g.nextPage());
	for (int i = 0; i < 9; i++){
		this->content[i] = String("");
	}
	this->currentRow = 0;
}

void ScreenTask::draw(){
	//u8g.setFont(u8g_font_unifont);
	u8g.setFont(u8g_font_5x7);
	// print message
	u8g.firstPage();
	do {
		for (int i = 0; i < 9; i++){
			if (NULL != this->content[i] ){
				String msg = this->content[i];
				char convertedMessage[msg.length() + 1];
				msg.toCharArray(convertedMessage, msg.length() + 1);

				u8g.drawStr(0, (i*CHAR_HEIGHT) + CHAR_HEIGHT, convertedMessage);
			}
		}
	} while (u8g.nextPage());
}

