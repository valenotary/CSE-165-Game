#pragma once
#ifndef MENU_H
#define MENU_H

#include <gl/freeglut.h>
#include <vector>

#include "Rect.h"

class Menu {

public:
	std::vector<Rect*> menu_boxes;
	Menu();

	void init();
	void draw();

	~Menu();
};

#endif /*MENU_H*/