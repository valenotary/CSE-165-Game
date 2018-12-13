#include "menu.h"

#define Y_UPPER_BOUND 1.0
#define Y_LOWER_BOUND -1.0
#define X_UPPER_BOUND 1.0
#define X_LOWER_BOUND -1.0

void drawString(void * font, char * s, float x, float y) {
	glRasterPos2f(x, y);
	for (unsigned int i = 0; i < strlen(s); i++) {
		glutBitmapCharacter(font, s[i]);
	}
}

Menu::Menu() {
	init();
}

void Menu::init(){
	//start
	menu_boxes.push_back(new Rect(-0.2, 0.2, 0.4, 0.2, 0.0, 1.0, 0.0));
	//exit
	menu_boxes.push_back(new Rect(-0.2, -0.2, 0.4, 0.2, 1.0, 0.0, 0.0));
}

void Menu::draw() {
	for (std::vector<Rect*>::iterator tamy = menu_boxes.begin(); tamy != menu_boxes.end(); tamy++) {
		(*tamy)->draw();
		std::cout << "Drawing menu box..." << std::endl;
	}
}

Menu::~Menu() {
	for (std::vector<Rect*>::iterator tamy = menu_boxes.begin(); tamy != menu_boxes.end(); tamy++) {
		delete (*tamy);
	}
}
