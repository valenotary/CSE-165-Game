#pragma once
#ifndef CUSTOMFONTS_H
#define CUSTOMFONTS_H

//FreeType Headers
#include <ft2build.h>
#include <freetype/freetype.h>
#include <freetype/ftglyph.h>
#include <freetype/ftoutln.h>
#include <freetype/fttrigon.h>

//OpenGl Headers
#include <Windows.h>
#include <gl/freeglut.h>

//Some STL Headers

#include <vector>
#include <string>

#include <stdexcept>

#pragma warning(disable: 4786) 

namespace freetype {

	using std::vector;

	using std::string;

	struct font_data {
		float h;
		GLuint *textures;
		GLuint list_base;

		void init(const char*fname, unsigned int h);

		void clean();
	};

	void print(const font_data &ft_font, float x, float y, const char* fmt, ...);
}





#endif /*CUSTOMFONTS_H*/