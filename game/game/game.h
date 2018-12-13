#pragma once
#ifndef GAME_H
#define GAME_H

#include <gl/freeglut.h>

#include "character.h"
#include "axis_shooters.h"
#include "menu.h"

class Game {
	bool isMenu, gameRunning;

	Menu* menu;
	Character* girl;
	TexRect* bg;
	AxisShooter* shooter;

public:
	Game();

	void init();

	void draw();

	void handleDownInputs(unsigned char);
	void handleUpInputs(unsigned char);
	void leftMouseInputs(float, float);
	void checkBehaviors();

	void start();
	void restart();

	~Game();
};


#endif /*GAME_H*/