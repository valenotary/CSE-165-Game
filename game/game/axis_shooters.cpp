#include "axis_shooters.h"

float rBound = 1.0;
float lBound = -1.0;

float bullet::bullet_speed = 0.01;

bullet::bullet(float x, float y, float z, float w, float h) :Rect(x, y, w, h) {
	this->z = z;
}

void bullet::draw(float z) {
	glColor3f(1.0, 0.0, 0.0);

	glBegin(GL_POLYGON);

	glVertex3f(x, y, z);
	glVertex3f(x + w, y, z);
	glVertex3f(x + w, y - h, z);
	glVertex3f(x, y - h, z);

	glEnd();
}

void bullet::shoot() {
	y -= bullet_speed;
}


AxisShooter::AxisShooter(const char* filename, float x, float y, float w, float h, int mode): TexRect(filename, x, y, w, h) {
	midX = (this->x + this->w)/ 2;
	this->mode = mode;
	xSpeed = ySpeed = 0.005;
	shooterBound = 1.0;

	if (mode == 0) {
		playerDetector = new Rect(midX - shooterBound, y, 2*shooterBound, 2.0);
	}
	else if (mode == 1) {
		//playerDetector = new Rect(x, y, 2.0, 2.0);
	}
	isRight = true;
	//std::cout << x << std::endl;
	setRate(2000);
	start();
}

void AxisShooter::draw(float z) {
	glBindTexture(GL_TEXTURE_2D, texture_id);
	glEnable(GL_TEXTURE_2D);

	glBegin(GL_QUADS);
	glColor4f(1, 1, 1, 1);
	glTexCoord2f(0, 0);
	glVertex3f(x, y - h, z);

	glTexCoord2f(0, 1);
	glVertex3f(x, y, z);

	glTexCoord2f(1, 1);
	glVertex3f(x + w, y, z);

	glTexCoord2f(1, 0);
	glVertex3f(x + w, y - h, z);

	glEnd();

	glDisable(GL_TEXTURE_2D);

	for (std::vector<bullet*>::iterator tamy = bullets.begin(); tamy != bullets.end(); tamy++) {
		(*tamy)->draw(z + 0.01);
	}
}

void AxisShooter::AxisBehavior(float x, float y) {
	move();
	decideShoot(x, y);
	std::vector<bullet*>::iterator tamy = bullets.begin();
	//std::cout << "Girl Coordinates : " << x << " " << y << std::endl;
	//while (tamy != bullets.end()) {
	//	(*tamy)->shoot();
	//	(*tamy)->cy = (this->y + h) / 2;
	//	if ((*tamy)->getY() < (-0.5)) {
	//		std::cout << "deleted " << (*tamy)->getY() << " " <<(*tamy)->getX() << std::endl;
	//		std::cout << (*tamy)->cx << " " << (*tamy)->cy << std::endl;
	//		tamy = bullets.erase(tamy);
	//	} else {
	//		++tamy;
	//	}
	//}
}

void AxisShooter::move() {
	switch (mode) {
	case 0:						//oscillate horizontally
		x += xSpeed;
		//midX = (x + w) / 2;
		//playerDetector->setX(midX - shooterBound);
		//write stuff here
		//test-case: just moving horizontally back and forth
		if ((x + w) > (rBound + w)) {
			isRight = false;
			xSpeed = -xSpeed;
		}
		else if (x < (lBound - w)) {
			isRight = true;
			xSpeed = -xSpeed;
		}
		//std::cout << "MOVING LEFT/RIGHT" << std::endl;
		break;
	case 1:						//oscillate vertically
		//write stuff here
		break;
	}
	midX = (x + w) / 2;
	playerDetector->setX(midX - shooterBound);
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
		//std::cout << xSpeed << std::endl;
	}
	if (shooterBound > 0.1) {
		shooterBound -= 0.01;
		playerDetector->setX(midX - (shooterBound));
		playerDetector->setW(shooterBound * 2);
	//	std::cout << playerDetector->getX() << " " << playerDetector->getW() << std::endl;
	}
	if (getRate() > 100) {
		setRate(getRate() - 50);
	}
	if (shoot()) {
		std::cout << ((getX() + getW()) / 2) << std::endl;
		//std::cout << "PEW" << std::endl;
		bullets.push_back(new bullet((x+w) / 2, y - 0.1));
		//std::cout << 
	}
}

AxisShooter::~AxisShooter() {
	delete playerDetector;
	for (int i = 0; i < bullets.size(); i++) {
		delete bullets[i];
	}
}
