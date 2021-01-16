#include "Global_Variable.h"

Global_Variable* Global_Variable::_instance = NULL;

Global_Variable::Global_Variable()
{
	this->coin = 0;
	this->life = 4; 
	this->plevel = 0; 
	this->combo = 0; 
	this->score = 0; 
	this->time = 0; 
}

void Global_Variable::ComboUp()
{
	combo += 1; 
	if (combo >= 8)
		combo = 8;
}

void Global_Variable::ResetCombo()
{
	this->combo = 0; 
}

int Global_Variable::GetCombo()
{
	return this->combo;
}

void Global_Variable::ResetScore()
{
	this->score = 0; 
}

void Global_Variable::AddScore(long x)
{
	this->score += x;
}

void Global_Variable::AddCoin(int x)
{
	this->coin += x;
}

void Global_Variable::ResetCoin()
{
	this->coin = 0; 
}

void Global_Variable::AddLife(int x)
{
	this->life += x;
}

void Global_Variable::ResetLife()
{
	this->life = 4;
}

void Global_Variable::UpdatePmetter(int x)
{
	this->plevel = x; 
}

int Global_Variable::getPmetter()
{
	return this->plevel;
}

void Global_Variable::startPtime()
{
	this->Ptime_start = GetTickCount();
}

bool Global_Variable::isPtimeUp()
{
	return ((GetTickCount() - Ptime_start) <= PSWITCH_TIME);
}

DWORD Global_Variable::getPTimeLeft()
{
	return PSWITCH_TIME -(GetTickCount() - Ptime_start);
}

bool Global_Variable::getSecret()
{
	return this->isinsecret;
}

void Global_Variable::setSecret(bool se)
{
	this->isinsecret = se;
}

std::string Global_Variable::FormatScore()
{
	std::string format = std::to_string(score);

	while (format.length() < 7)
	{
		format = "0" + format; 
	}
	return format;
}

std::string Global_Variable::Formatcoin()
{
	return std::to_string(coin);
}

std::string Global_Variable::FormatLife()
{
	return std::to_string(life);
}

std::string Global_Variable::FormatTime()
{
	return std::to_string(getGameTimeLeft()/1000);
}

void Global_Variable::setCard(int cardid)
{
	this->Cards.push_back(cardid);
}

std::vector<int> Global_Variable::getCardCarousel()
{
	std::vector<int> card = this->Cards;

	if (this->Cards.size() < 3);
	{
		card = this->Cards;
	}

	for (int i = Cards.size(); i < 3; i++)
	{
		card.push_back(0);
	}

	return card;
}

DWORD Global_Variable::getGameTimeLeft()
{
	return GAME_TIME - (GetTickCount() - Game_time_start);
}

void Global_Variable::startGameTime()
{
	this->Game_time_start = GetTickCount();
}

Global_Variable* Global_Variable::GetInstance()
{
	if (_instance == NULL)
		_instance = new Global_Variable();
	return _instance;
}
