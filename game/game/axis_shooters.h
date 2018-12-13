#pragma once
#ifndef AXISSHOOTER_H
#define AXISSHOOTER_H

#include <vector>
#include <string>
#include <math.h>
#include <cstdlib>
#include "AnimatedRect.h"


class AxisShooter : public TexRect, protected Timer {
	bool isRight;
	float xSpeed, ySpeed, midX, shooterBound;
	int mode;
	std::vector<Rect*> bullets;
	Rect* playerDetector;

	AxisShooter();
public:

	AxisShooter(const char* filename, float, float, float, float, int);

	void AxisBehavior(float, float);

	void move();
	void decideShoot(float, float);
	bool shoot();
	void action();

	~AxisShooter();
};
#endif /*AXISSHOOTER_H*/