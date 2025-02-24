#include "character.h"
#include "dataloader.h"

typedef animation::iterator aIterator;
//constructor loads a vector of loadData called data loader
//then we populate the AnimatedRect* vector of state_animations
//with the dataloader vector
static float rBound = 0.9;
static float lBound = -1.0;
int NUM_OF_STATES;


//STATES:
//IDLE - 0
//MOVING - 1


//ANIMATIONS:
//--IDLE STATES
//0 - Idle Right
//1 - Idle Left
//--MOVING STATES
//2 - Moving Right
//3 - Moving Left


//RIGHT NOW THE STATES ARE ONLY 2 AND THEREFORE THERE ARE ONLY 4 ANIMATIONS
Character::Character(std::string name, float x = 0, float y = 0, float z = 0, float w = 0.1, float h = 0.2): name(name), x(x), y(y), z(z), w(w), h(h), isRight(true), initVel(0.1), vel(0) {
	//dataloader reads from a text file, and loads in the appropriate specifications of the sprites needed returned in a vector
	std::vector<cData> dataloader = loadData(name);
	//the number of states is the size of that vector / 2
	//because it's simply double the number of states,
    NUM_OF_STATES = dataloader.size() / 2;
	std::cout << NUM_OF_STATES << std::endl;
	states.resize(NUM_OF_STATES);
	for (int i = 0; i < NUM_OF_STATES * 2; i++) {
		std::cout << dataloader[i].imgName << std::endl;
		const char *c = dataloader[i].imgName.c_str();
		animations.push_back(new AnimatedRect(c, dataloader[i].row, dataloader[i].col, 200, this->x, this->y, this->w, this->h));
		//std::cout << state_animations[i]->done() << std::endl;
	}

	std::cout << animations.size() << std::endl;
	states[0] = true;
	if (states[0] == true) {
		std::cout << "Spawning in... IDLE" << std::endl;
	}

}

void Character::setName(std::string name) {
	this->name = name;
}

void Character::setX(float x) {
	this->x = x;
}

void Character::setY(float y) {
	this->y = y;
}

void Character::setZ(float z) {
	this->z = z;
}

void Character::setW(float w) {
	this->w = w;
}

void Character::setH(float h) {
	this->h = h;
}

void Character::updateState(int state) {
	int prev_state = curr_state;
	//this action int will be passed into cBehavior to check which animation to play (R/L)
	action = state;
	//the action variable is integer divided by 2 to get the correct state
	curr_state = state / NUM_OF_STATES;
	//if the action is even, then it is a right-oriented action. else if it's odd, it's a left-oriented action
	if (state % 2 == 0) {
		isRight = true;
	} else if (state % 2 == 1) {
		isRight = false;
	}
	if (curr_state != prev_state) {
		states[curr_state] = true;
		states[prev_state] = false;
	}
}

void Character::cBehavior() {
	//controls which animation should be played
	for (aIterator tamy = animations.begin(); tamy != animations.end(); tamy++) {
		if ((*tamy) != animations[action]) {
			(*tamy)->cut();
		}
	}
	if (animations[action]->done()) {
		animations[action]->playOnce();
	}

	if (states[1] == true) {
		moveX();
	}

}

void Character::idle() {
	if (isRight == true) {
		//std::cout << "FACING RIGHT" << std::endl;
	}
	else {
		//std::cout << "FACING LEFT" << std::endl;
	}
}

void Character::moveX() {
	float bound;
	if (isRight == true) {
		x += .01;
		for (aIterator tamy = animations.begin(); tamy != animations.end(); tamy++) {
			(*tamy)->setX((*tamy)->getX() + 0.01);
		}
	}
	else {
		x -= 0.01;
		for (aIterator tamy = animations.begin(); tamy != animations.end(); tamy++) {
			(*tamy)->setX((*tamy)->getX() - 0.01);
		}
	}

	if (x > rBound) {
		bound = rBound;
	}
	else if (x < lBound) {
		bound = lBound;
	}

	if (x > rBound || x < lBound) {
		x = bound;
		for (aIterator tamy = animations.begin(); tamy != animations.end(); tamy++) {
			(*tamy)->setX(bound);
		}
	}

}

bool Character::contains(float px, float py) {
	return px >= x && px <= x + w && py <= y && py >= y - h;
}

void Character::draw() {
	for (aIterator tamy = animations.begin(); tamy < animations.end(); tamy++) {
		(*tamy)->draw(z);
	}
}

float Character::getX() const{
	return x;
}

float Character::getY() const {
	return y;
}

bool Character::leftORright() {
	return isRight;
}

Character::~Character() {
	for (int i = 0; i < animations.size(); i++) {
		std::cout << "Deleted element: " << i << std::endl;
		delete animations[i];
		animations[i] = nullptr;
	}
}


