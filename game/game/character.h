#pragma once
#ifndef CHARACTER_H
#define CHARACTER_H

#include <iostream>
#include <string>
#include <vector>

#include "AnimatedRect.h"
#include "dataloader.h"

/*So far:
-Character is defined by XYZ pos, width/height, and then a
series of AnimatedRects that are swapped in being drawn
based on the current "state" of the character 
-On XYZ:
	-X = X
	-Y = Y
	-Z = -1 < Y < 0; Since it's 2D and we want the illusion of depth
	we define Z as that range that can only be traversed by W/S (up/down)
	need to find a way to isolate this movement from things like jumping
*/

typedef std::vector<AnimatedRect*> animation;

class Character {
	
	std::string name;
	float x, y, z, w, h;
	float initVel, vel;
	//bool left, right;
	bool isRight, isMoving, isJumping, isFalling, isHit, inAir, onLand;
	//int curr_state;
	//std::vector<std::string> string_states;
	int curr_state, action;
	std::vector<bool> states;
	animation animations;
	Character();
public:
	Character(std::string, float, float, float, float, float);

	void setName(std::string);
	void setX(float);
	void setY(float);
	void setZ(float);
	void setW(float);
	void setH(float);

	void updateState(int);

	void cBehavior();
	
	void idle();
	void moveX();
	void jump();
	void fall();

	std::string getName(std::string) const;
	float getX() const;
	float getY() const;
	float getZ() const;
	float getW() const;
	float getH() const;

	bool leftORright();
	bool onGround();

	void draw();

	~Character();

};

#endif /*CHARACTER_H*/