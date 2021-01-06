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

Global_Variable* Global_Variable::GetInstance()
{
	if (_instance == NULL)
		_instance = new Global_Variable();
	return _instance;
}
