#include "gamewindow.h"

gamewindow::gamewindow(int argc, char ** argv): glutwindow(argc, argv) {
	//initialize the objects in here (maybe even encapsulate it all into a game class and just instantiate the game object in here)
	//idleAnimation = true;
	//p1 = new AnimatedRect("resources/sprites/p1/idlep1.png", 1, 4, 100, 0, 0, 0.5, 0.5);
	//girl_idle = new AnimatedRect("resources/sprites/girl/girl_idle.png", 1, 4, 200, 0.5, 0.5, 0.1, 0.2);
	//girl_running = new AnimatedRect("resources/sprites/girl/girl_running.png", 1, 5, 200, 0.5, 0.5, 0.1, 0.2);
	//bg = new TexRect("resources/textures/bg.png", -1, 1, 2, 2);
	//girl = new Character("resources/textassets/girl.txt", 0, -0.5, 0.2, 0.1, 0.2);
	//test = new AxisShooter("resources/textures/TAMY'S_SPACESHIP.png", -0.1, 0.5, 0.4, 0.2, 0);
	//60 FPS; can check the state 60x per second

	game = new Game();

	timerSetInterval(1000 / 60);
	timerStart();
}

void gamewindow::draw() {
	//p1->draw(0.15);
	//girl_idle->draw(0.15);
	//girl_running->draw(0.15);
	//bg->draw(0.15);
	//girl->draw();
	//test->draw(0.2);
	game->draw();
}


//use key down to turn a bool off or on, then its corresponding up function to turn it back on if need be
void gamewindow::keyDown(unsigned char key, float x, float y) {
	if (key == 27) {
		exit(0);
	}

	game->handleDownInputs(key);

	//if (key == 'a') {
	//	keystates[key] = true;
	//	//girl->updateState(MOVING_LEFT);
	//	if (keystates[key] == true) {
	//		girl->updateState(MOVING_LEFT);
	//	}
	//}

	//if (key == 'd') {
	//	keystates[key] = true;
	//	//girl->updateState(MOVING_RIGHT);
	//	if (keystates[key] == true) {
	//		girl->updateState(MOVING_RIGHT);
	//	}

	//}
	//if (key == ' ') {
	//	keystates[key] = true;
	//	if (keystates[key] == true) {
	//		if (girl->leftORright()) {
	//			girl->updateState(JUMPING_RIGHT);
	//		}
	//		else {
	//			girl->updateState(JUMPING_LEFT);
	//		}
	//	}
	//}
}

void gamewindow::keyUp(unsigned char key, float x, float y) {
	//if (key != NULL) {
	//	girl->updateState(STATE_IDLE);
	//	std::cout << girl->getX() << std::endl;
	//}

	//if (key == 'a') {
	//	keystates[key] = false;
	//}
	//if (key == 'd') {
	//	keystates[key] = false;
	//}
	//if (key == ' ') {
	//	keystates[key] = false;
	//}


	//if (key != NULL) {
	//	if (girl->leftORright()) {
	//		girl->updateState(IDLE_RIGHT);
	//	} else {
	//		girl->updateState(IDLE_LEFT);
	//	}
	//	//if ((girl->leftORright()) == true) {
	//	//	girl->updateState(STATE_IDLE_RIGHT);
	//	//	std::cout << "Idling facing right now..." << std::endl;
	//	//}
	//	//else if ((girl->leftORright()) == true) {
	//	//	girl->updateState(STATE_IDLE_LEFT);
	//	//	if ((girl->leftORright()) == true) {
	//	//		std::cout << "Idling facing left now..." << std::endl;
	//	//	}
	//	//}
	//}

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
	//std::cout << "UPDATED" << std::endl;

	//TODO: UPDATE STATE METHOD
	//controls automatically what the state is, then
	//draws accordingly
	//check which animation to draw by iterating through
	//which bool state is true and PAUSING the rest
	
	//girl->cBehavior();
	//test->AxisBehavior(girl->getX(), girl->getY());

	game->checkBehaviors();

	/*if (idleAnimation) {
		girl_running->cut();
		if (girl_idle->done()) {
			girl_idle->playOnce();
		}
	}
	else {
		girl_idle->cut();
		if (girl_running->done()) {
			girl_running->playOnce();
		}
	}*/

	redraw();
}

gamewindow::~gamewindow() {
	//delete all of the objects in here (refer to above suggestion)
	//delete p1;
	//delete girl;
	//delete bg;
	//delete test;
	delete game;
}


