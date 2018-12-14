#pragma once
#ifndef AXISSHOOTER_H
#define AXISSHOOTER_H

#include <vector>
#include <string>
#include <math.h>
#include <cstdlib>

#include "AnimatedRect.h"

//std::vector<std::unique_ptr<Thing>> things;
//things.emplace_back(std::make_unique<Thing>());
//things.pop_back();

struct bullet: public Rect {
	float z, cx, cy;
	static float bullet_speed;
	bullet();
public:
	bullet(float, float, float = 0.2, float = 0.05, float = 0.1);
	void draw(float);
	void shoot();
};


class AxisShooter : public TexRect, protected Timer {
	bool isRight;
	float xSpeed, ySpeed, midX, shooterBound;
	int mode;
	//std::vector<std::unique_ptr<bullet>> bullets;
	Rect* playerDetector;
	AxisShooter();
public:
	std::vector<bullet*> bullets;
	AxisShooter(const char* filename, float, float, float, float, int);

	void AxisBehavior(float, float);

	void draw(float);
	void move();
	void decideShoot(float, float);
	bool shoot();
	void action();

	~AxisShooter();
};
#endif /*AXISSHOOTER_H*/