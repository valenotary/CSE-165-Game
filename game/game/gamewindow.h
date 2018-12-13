#pragma once
#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include "glutwindow.h"
#include "AnimatedRect.h"
#include "character.h"
#include "axis_shooters.h"
#include "game.h"

class gamewindow: public glutwindow {
	//prepare all objects that I'll want to call in here
	//AnimatedRect *p1;
	//AnimatedRect *girl_idle;
	//AnimatedRect *girl_running;
	//TexRect* bg;
	//Character* girl;
	//AxisShooter* test;
	Game* game;

public:
	gamewindow(int argc, char** argv);

	void draw();

	void keyDown(unsigned char, float, float);
	void keyUp(unsigned char, float, float);
	
	void leftMouseDown(float, float);
	void rightMouseDown(float, float);
	void leftMouseUp(float, float);
	void rightMouseUp(float, float);

	void timer();

	~gamewindow();
};

#endif /*GAMEWINDOW_H*/