#pragma once
#ifndef TEXRECT_H
#define TEXRECT_H

#include <gl/freeglut.h>
#include <SOIL/SOIL.h>

#include "Rect.h"

class TexRect : public Rect {
protected:
	GLuint texture_id;

public:
	TexRect(const char*, float, float, float, float);

	void draw(float z) const;
};

#endif /*TEXRECT_H*/
