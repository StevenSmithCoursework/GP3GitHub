#include "fontManager.h"
//Set instance to null
fontManager* fontManager::pInstance = NULL;
//Create instance
fontManager* fontManager::getInstance()
{
	if (pInstance == NULL)
	{
		pInstance = new fontManager();
	}
	return fontManager::pInstance;
}

//Constructor
fontManager::fontManager()
{

}

//Deconstructor
fontManager::~fontManager()
{
	deleteFont();
}
//Saves a font from file name
void fontManager::addFont(LPCSTR fontName, LPCSTR fileName, int fontSize)  // add font to the Font collection
{
	if (!getFont(fontName))
	{
		font * newFont = new font(fileName, fontSize);
		gameFonts.insert(make_pair(fontName, newFont));
	}
}
//Retrieves saved font
font* fontManager::getFont(LPCSTR fontName)
{
	map<LPCSTR, font*>::iterator theFont = gameFonts.find(fontName);
	if (theFont != gameFonts.end())
	{
		return theFont->second;
	}
	else
	{
		return NULL;
	}
}
//Deletes a selected font
void fontManager::deleteFont()
{
	for (map<LPCSTR, font*>::const_iterator theFont = gameFonts.begin(); theFont != gameFonts.end(); theFont++)
	{
		delete theFont->second;
	}
}
