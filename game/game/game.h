#pragma once
#ifndef GAME_H
#define GAME_H

#include <gl/freeglut.h>
#include <string>
#include <sstream>

#include "character.h"
#include "axis_shooters.h"
#include "menu.h"

void drawString(void *, const char *, float, float, float);

struct counter: protected Timer {
	bool timerStillRunning;
	int seconds;
	std::stringstream str;
	std::string seconds_string;
	counter();
	void action();;
};

class Game {
	bool gameRunning, gameOver;
	std::string final_string;
	int score;
	counter meh;
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