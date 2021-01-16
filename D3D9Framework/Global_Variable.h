#ifndef __GLOBAL_VARIABLES_H__
#define __GLOBAL_VARIABLES_H__

#include <d3dx9.h>
#include <directxmath.h>
#include <vector>
#include <string>


#define D3DCOLOR_WHITE D3DCOLOR_XRGB(255, 255, 255)
#define BACKGROUND_COLOR D3DCOLOR_XRGB(181, 235, 242)
//#define BACKGROUND_COLOR D3DCOLOR_XRGB(21,155,65)
// window configuration
#define WINDOW_WIDTH 776 //640 //1920 //768
#define WINDOW_HEIGHT 744 //480 //1020 //672

#define WINDOW_TITLE L"Super Mario"
#define WINDOW_CLASS_NAME L"Super Mario Bros 3"
//camera configuration
#define CAMERA_WIDTH 768
#define CAMERA_HEIGHT 672

#define CAMERA_DEFAULT_SCROLLING_SPEED_VX 2.0f
#define CAMERA_DEFAULT_SCROLLING_SPEED_VY 2.0f

//game configuration
#define MAX_FRAME_RATE 180

#define KEYBOARD_BUFFER_SIZE 1024

//game math configuration
#define PI 3.1614f

typedef D3DXVECTOR2 Vector2;
typedef D3DXVECTOR3 Vector3;
#define VectorZero Vector2(0.0f,0.0f);


#define PSWITCH_TIME  10000

#define GAME_TIME 300000

class Global_Variable
{
	static Global_Variable* _instance;

	long score; 

	int life, coin; 

	int combo; 

	int time;

	int plevel;

	DWORD Ptime_start; 

	DWORD Game_time_start;

	//store mario cards, unimplemented.
	std::vector<int> Cards;

	bool isinsecret = false;

public:

	Global_Variable();

	void ComboUp();
	void ResetCombo();
	int GetCombo(); 

	void ResetScore();
	void AddScore(long x); 


	void AddCoin(int x); 
	void ResetCoin();

	void AddLife(int x); 
	void ResetLife(); 

	void UpdatePmetter(int x);
	int getPmetter();

	void startPtime();
	bool isPtimeUp();
	DWORD getPTimeLeft();

	bool getSecret();
	void setSecret(bool se);

	std::string FormatScore();
	std::string Formatcoin(); 
	std::string FormatLife();
	std::string FormatTime(); 

	void setCard(int cardid);
	std::vector<int> getCardCarousel();

	DWORD getGameTimeLeft();
	void startGameTime();

	static Global_Variable* GetInstance(); 
};

#endif