#pragma once

#include "FTGL\ftgl.h"
#include "GL\glew.h"
#include <Windows.h>

using namespace std;

struct colour3f
{
	colour3f(float _r = 0.0f, float _g = 0.0f, float _b = 0.0f) : r(_r), g(_g), b(_b) {}

	float r;	// Red
	float g;	// Green
	float b;	// Blue
};

class font
{
public:
	font();
	font(LPCSTR fontFileName, int fontSize);
	~font();
	FTFont* getFont();
	void printText(LPCSTR text, FTPoint textPos);
	void printText(LPCSTR text, FTPoint textPos, colour3f textColour);

private:
	FTFont* theFont;

private:
};

