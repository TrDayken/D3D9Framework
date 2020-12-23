#include "Font.h"
#include "SpriteManager.h"

Font::Font()
{
	Space = 24; 
}

void Font::LoadFont()
{
	this->data.clear();

	SpriteManager* sprite = SpriteManager::GetInstance(); 

	for (char c = '0'; c <= '9'; ++c)
		data[c] = sprite->GetSprite(XMLprefix + c);
	for (char c = 'A'; c <= 'Z'; ++c)
		data[c] = sprite->GetSprite(XMLprefix + c); 
}

LPSPRITE Font::GetChar(char c)
{
	return this->data[c];
}

void Font::setXMLprefix(std::string prefix)
{
	this->XMLprefix = prefix; 
}

void Font::setSpace(float x)
{
	this->Space = x; 
}
