#include "gamewindow.h"

gamewindow::gamewindow(int argc, char ** argv): glutwindow(argc, argv) {
	game = new Game();

	timerSetInterval(1000 / 60);
	timerStart();
}

void gamewindow::draw() {
	game->draw();
}

void gamewindow::keyDown(unsigned char key, float x, float y) {
	if (key == 27) {
		exit(0);
	}
	game->handleDownInputs(key);
}

void gamewindow::keyUp(unsigned char key, float x, float y) {
	game->handleUpInputs(key);
}

void gamewindow::leftMouseDown(float x, float y) {
	game->leftMouseInputs(x, y);
}

void gamewindow::rightMouseDown(float x, float y) {

}

void gamewindow::leftMouseUp(float x, float y) {

}

void gamewindow::rightMouseUp(float x, float y) {

}

void gamewindow::timer() {
	game->checkBehaviors();
	redraw();
}

gamewindow::~gamewindow() {
	delete game;
}


