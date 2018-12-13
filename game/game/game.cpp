#include "game.h"

#define IDLE_RIGHT 0
#define IDLE_LEFT 1
#define MOVING_RIGHT 2
#define MOVING_LEFT 3

Game::Game() {
	init();
}

void Game::init() {
	menu = new Menu();
	menu->init();
	bg = new TexRect("resources/textures/bg.png", -1, 1, 2, 2);
	girl = new Character("resources/textassets/girl.txt", 0, -0.5, 0.2, 0.1, 0.2);
	shooter = new AxisShooter("resources/textures/TAMY'S_SPACESHIP.png", -0.1, 0.5, 0.4, 0.2, 0);

	isMenu = true;
	gameRunning = false;
}

void Game::draw() {
	if (isMenu) {
		menu->draw();
	}
	if (gameRunning) {
		bg->draw(0.15);
		girl->draw();
		shooter->draw(0.2);
	}
}

void Game::handleDownInputs(unsigned char key) {
	if (key == 'a') {
		girl->updateState(MOVING_LEFT);
	}
	if (key == 'd') {
		girl->updateState(MOVING_RIGHT);
	}
}

void Game::handleUpInputs(unsigned char key) {
	if (key != NULL) {
		if (girl->leftORright()) {
			girl->updateState(IDLE_RIGHT);
		}
		else {
			girl->updateState(IDLE_LEFT);
		}
	}
}

void Game::leftMouseInputs(float x, float y) {
	if (menu->menu_boxes[0]->contains(x, y)) {
		menu = false;
		gameRunning = true;
	} else if (menu->menu_boxes[1]->contains(x, y)) {
		exit(0);
	}
}

void Game::checkBehaviors() {
	girl->cBehavior();
	shooter->AxisBehavior(girl->getX(), girl->getY());
}


Game::~Game() {
	delete menu;
	delete girl;
	delete bg;
	delete shooter;
}
