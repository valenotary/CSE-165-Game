#include "character.h"
#include "dataloader.h"

typedef animation::iterator aIterator;
//constructor loads a vector of loadData called data loader
//then we populate the AnimatedRect* vector of state_animations
//with the dataloader vector
Character::Character(std::string name, float x = 0, float y = 0, float z = 0, float w = 0.1, float h = 0.2): name(name), x(x), y(y), z(z), w(w), h(h), isRight(true) {
	std::vector<cData> dataloader = loadData(name);
	const int NUM_OF_STATES = dataloader.size();
	std::cout << NUM_OF_STATES << std::endl;
	states.resize(NUM_OF_STATES);
	for (int i = 0; i < NUM_OF_STATES; i++) {
		std::cout << dataloader[i].imgName << std::endl;
		const char *c = dataloader[i].imgName.c_str();
		animations.push_back(new AnimatedRect(c, dataloader[i].row, dataloader[i].col, 200, this->x, this->y, this->w, this->h));
		//std::cout << state_animations[i]->done() << std::endl;
	}
	states[0] = true;
	cBehavior();
	if (states[0] == true) {
		std::cout << "Spawning in..." << std::endl;
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
	std::cout << state << std::endl;
	if (state % 2 == 0) {
		isRight = true;
	} else if (state % 2 == 1) {
		isRight = false;
	}
	if (states[state] != true) {
		states[state] = true;
		for (int i = 0; i < states.size(); i++) {
			if (i != state) {
				states[i] = false;
			}
		}
	}
}

void Character::cBehavior() {
	//state[1] == moving(right)
	/*if (states[1] == true) move();*/

	for (int i = 0; i < states.size(); i++) {
		if (states[i] == true) {
			for (aIterator tamy = animations.begin(); tamy != animations.end(); tamy++) {
				if ((*tamy) != animations[i]) {
					(*tamy)->cut();
				}
			}
			if (animations[i]->done()) {
				animations[i]->playOnce();
			}
		}
	}

	if (states[0] == true || states[1] == true) idle();
	if (states[2] == true || states[3] == true) moveX();

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
	if (isRight == true) {
		x += .005;
		for (aIterator tamy = animations.begin(); tamy != animations.end(); tamy++) {
			(*tamy)->setX((*tamy)->getX() + 0.005);
			std::cout << (*tamy)->getX() << std::endl;
		}
	}
	else {
		x -= 0.005;
		for (aIterator tamy = animations.begin(); tamy != animations.end(); tamy++) {
			(*tamy)->setX((*tamy)->getX() - 0.005);
			std::cout << (*tamy)->getX() << std::endl;
		}
	}
	//x += 0.005;
	//for (aIterator tamy = state_animations.begin(); tamy != state_animations.end(); tamy++) {
	//	(*tamy)->setX((*tamy)->getX() + 0.005);
	//	std::cout << (*tamy)->getX() << std::endl;
	//}
}

void Character::draw() {
	for (aIterator tamy = animations.begin(); tamy < animations.end(); tamy++) {
		(*tamy)->draw(z);
	}
}

float Character::getX() const{
	return x;
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


