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

void Font::RenderText(std::string text, Vector2 pos, TextAlignment align)
{
	//missing render for align
	for (int i = 0; i <= text.length() - 1; i++)
	{
		char c = text.at(i);

		if (c == ' ')
		{
			pos.x += this->getSpace(); 
			continue; 
		}

		LPSPRITE charsprite = this->GetChar(c); 

		charsprite->Draw(pos.x, pos.y);

		pos.x += charsprite->getSpriteWidth() + 3;
	}
}

void Font::setSpace(float x)
{
	this->Space = x; 
}

float Font::getSpace()
{
	return this->Space;
}
