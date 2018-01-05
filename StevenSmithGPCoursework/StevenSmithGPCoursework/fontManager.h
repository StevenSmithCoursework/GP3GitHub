#pragma once

#include "font.h"
#include <map>
class fontManager
{
public:
	static fontManager* getInstance();

	fontManager();
	~fontManager();
	void addFont(LPCSTR fontName, LPCSTR fileName, int fontSize);
	font* getFont(LPCSTR fontName);
	void deleteFont();

private:

	static fontManager* pInstance;
	map<LPCSTR, font*> gameFonts;
};

