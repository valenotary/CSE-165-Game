#include "axis_shooters.h"

float rBound = 1.0;
float lBound = -1.0;

AxisShooter::AxisShooter(const char* filename, float x, float y, float w, float h, int mode): TexRect(filename, x, y, w, h) {
	midX = (this->x + this->w)/ 2;
	this->mode = mode;
	xSpeed = ySpeed = 0.005;
	shooterBound = 1.0;

	if (mode == 0) {
		playerDetector = new Rect(midX - shooterBound, y, shooterBound, 2.0);
	}
	else if (mode == 1) {
		//playerDetector = new Rect(x, y, 2.0, 2.0);
	}
	isRight = true;

	std::cout << this->x << std::endl;
	std::cout << this->y<< std::endl;
	std::cout << this->w << std::endl;
	std::cout << this->h << std::endl;
	std::cout << this->mode << std::endl;
	//std::cout << x << std::endl;


	setRate(2000);
	start();
}

void AxisShooter::AxisBehavior(float x, float y) {
	move();
	decideShoot(x, y);
}

void AxisShooter::move() {
	switch (mode) {
	case 0:						//oscillate horizontally
		x += xSpeed;
		midX = (x + w) / 2;
		playerDetector->setX(midX - shooterBound);
		//write stuff here
		//test-case: just moving horizontally back and forth
		if ((x + w) > rBound) {
			isRight = false;
			xSpeed = -xSpeed;
		}
		else if (x < lBound) {
			isRight = true;
			xSpeed = -xSpeed;
		}
		//std::cout << "MOVING LEFT/RIGHT" << std::endl;
		break;
	case 1:						//oscillate vertically
		//write stuff here
		break;
	}
}

void AxisShooter::decideShoot(float x, float y) {
	if (playerDetector->contains(x, y)) {
		if (rand() % 10 == 1) {
			shoot();
		}
	}
}

bool AxisShooter::shoot() {
	return true;
}

void AxisShooter::action() {
	if (abs(xSpeed) < 0.2) {
		if (isRight) {
			xSpeed += 0.001;
		}
		else {
			xSpeed -= 0.001;
		}
		std::cout << xSpeed << std::endl;
	}
	if (shooterBound > 0.1) {
		shooterBound -= 0.01;
		playerDetector->setX(playerDetector->getX() + 0.01);
		playerDetector->setW(shooterBound);
		std::cout << playerDetector->getX() << " " << playerDetector->getW() << std::endl;
	}
	if (getRate() > 100) {
		setRate(getRate() - 5);
	}
	if (shoot()) {
		std::cout << "PEW" << std::endl;
	}
}

AxisShooter::~AxisShooter() {
	delete playerDetector;
}
