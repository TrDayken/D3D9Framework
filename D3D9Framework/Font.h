#ifndef __FONT_H__
#define __FONT_H__

#include <unordered_map>

#include "SpriteManager.h"

class Font
{
private:

	std::unordered_map<char, LPSPRITE> data;

	std::string XMLprefix;

	float Space;

public:

	Font();

	//run this before import the font
	void LoadFont();

	//use this to get the desired character font; 
	LPSPRITE GetChar(char c);

	//use this to change prefix for font in XML, in this case spr-font-
	void setXMLprefix(std::string prefix); 

	void setSpace(float x); 
};

#endif