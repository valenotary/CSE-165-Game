#pragma once
#ifndef ANIMATEDRECT_H
#define ANIMATEDRECT_H

#include "TexRect.h"
#include "Timer.h"

class AnimatedRect : public TexRect, protected Timer {

	int rows;
	int cols;

	int curr_row;
	int curr_col;

	bool complete;
	bool animating;
	bool loop;

	void advance();
public:

	bool done();

	AnimatedRect(const char*, int, int, int, float, float, float, float);

	void draw(float z);

	void playLoop();

	void playOnce();

	void reset();

	void pause();

	void cut();

	void resume();

	void action();

	void play();

};

#endif /*ANIMATEDRECT_H*/