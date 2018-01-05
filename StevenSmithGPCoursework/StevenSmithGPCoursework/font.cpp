#pragma warning ( disable : 4996 )
#include "font.h"
using namespace std;

//Sets font to null
font::font()
{
	theFont = NULL;
}
//Retrieves font
font::font(LPCSTR fontFileName, int fontSize)
{
	theFont = new FTTextureFont(fontFileName);

	if (theFont == NULL)
	{
		delete theFont;
	}

	if (!theFont->FaceSize(fontSize))
	{
		delete theFont;
	}
}

//Deconstructor
font::~font()
{
	delete theFont;
}
//Getter for font
FTFont* font::getFont()
{
	return theFont;
}
//Prints text
void font::printText(LPCSTR text, FTPoint textPos)
{
	glPushMatrix();

	glTranslatef(textPos.X(), textPos.Y(), 0);
	glScalef(1, -1, 1);
	glColor3f(0.0f, 255.0f, 0.0f);
	theFont->Render(text);

	glPopMatrix();
}
//Prints text and sets colour
void font::printText(LPCSTR text, FTPoint textPos, colour3f textColour)
{
	glPushMatrix();

	glTranslatef(textPos.X(), textPos.Y(), 0);
	glScalef(1, -1, 1);
	glColor3f(textColour.r, textColour.g, textColour.b);
	theFont->Render(text);

	glPopMatrix();
}
