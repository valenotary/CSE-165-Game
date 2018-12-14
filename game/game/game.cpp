#include "game.h"

#define IDLE_RIGHT 0
#define IDLE_LEFT 1
#define MOVING_RIGHT 2
#define MOVING_LEFT 3

bool trigger;

void drawString(void * font, const char * s, float x, float y, float z) {
	glRasterPos3f(x, y, z);
	for (unsigned int i = 0; i < strlen(s); i++) {
		glutBitmapCharacter(font, s[i]);
	}
}

counter::counter() {
	seconds = 0;
	setRate(1000);
	start();
	timerStillRunning = true;
}

void counter::action() {
		seconds++;
		str << seconds;
		seconds_string = str.str();
		str.str(std::string());
		glutPostRedisplay();

}

Game::Game() {
	init();
}

void Game::init() {
	bg = new TexRect("resources/textures/bg.png", -1, 1, 2, 2);
	girl = new Character("resources/textassets/girl.txt", 0, -0.3, 0.2, 0.1, 0.2);
	shooter = new AxisShooter("resources/textures/TAMY'S_SPACESHIP.png", -0.1, 0.5, 0.4, 0.2, 0);
	counter meh();
	trigger = false;

	gameRunning = true;
	gameOver = false;
	score = 0;
}

void Game::draw() {
	if (gameRunning) {
		bg->draw(0.15);
	}
	if (gameOver) {
		drawString(GLUT_BITMAP_TIMES_ROMAN_24, "Game Ended", -0.2, 0.6, 0.3);
		drawString(GLUT_BITMAP_TIMES_ROMAN_24, "Alive For: ", -0.2, 0.4, 0.3);
		drawString(GLUT_BITMAP_TIMES_ROMAN_24, final_string.c_str(), -0.2, 0.2, 0.3);

	}
	if (gameRunning) {
		drawString(GLUT_BITMAP_9_BY_15, meh.seconds_string.c_str(), 0.8, 0.8, 0.2);
		girl->draw();
		shooter->draw(0.2);
	}

}

void Game::handleDownInputs(unsigned char key) {
	if (gameRunning) {
		if (key == 'a') {
			girl->updateState(MOVING_LEFT);
		}
		if (key == 'd') {
			girl->updateState(MOVING_RIGHT);
		}
	}
	if (gameOver) {
		if (key == 'r') {
			gameRunning = true;
			gameOver = false;
			meh.seconds = 0;
			score = 0;
		}
	}
}

void Game::handleUpInputs(unsigned char key) {
	if (gameRunning) {
		if (key != NULL) {
			if (girl->leftORright()) {
				girl->updateState(IDLE_RIGHT);
			}
			else {
				girl->updateState(IDLE_LEFT);
			}
		}
	}
}

void Game::leftMouseInputs(float x, float y) {
}

void Game::checkBehaviors() {
	if (gameRunning) {
		girl->cBehavior();
		shooter->AxisBehavior(girl->getX(), girl->getY());
		for (std::vector<bullet*>::iterator tamy = shooter->bullets.begin(); tamy != shooter->bullets.end();) {
			(*tamy)->shoot();
			if (girl->contains((*tamy)->getX(), (*tamy)->getY())) {
				gameRunning = false;
				gameOver = true;
				while (score != meh.seconds) {
					score++;
				}
				final_string = std::to_string(score);
				//if (trigger) {
				//	std::cout << "DIED" << std::endl;

				//	std::cout << final_string << std::endl;
				//	trigger = false;
				//}
			} else if ((*tamy)->getY() < (-0.5)) {
			std::cout << "deleted " << (*tamy)->getY() << " " <<(*tamy)->getX() << std::endl;
			std::cout << (*tamy)->cx << " " << (*tamy)->cy << std::endl;
			tamy = shooter->bullets.erase(tamy);
		} else {
				tamy++;
			}
		}
	}
}

void Game::restart() {
	gameRunning = true;
	gameOver = false;

	delete girl;
	delete bg;
	delete shooter;

	init();
}


Game::~Game() {
	delete girl;
	delete bg;
	delete shooter;
}
