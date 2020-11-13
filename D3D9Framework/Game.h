#ifndef __GAME_H__
#define __GAME_H__

#include <unordered_map>
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>

#include "Utils.h"
#include "Global_Variable.h"
#include "KeyEventHandler.h"

#define DIRECTINPUT_VERSION 0x0800

class Game
{
	static Game* __instance;
	HWND hWnd;									// Window handle

	LPDIRECT3D9 d3d = NULL;						// Direct3D handle
	LPDIRECT3DDEVICE9 d3ddv = NULL;				// Direct3D device object

	LPDIRECT3DSURFACE9 backBuffer = NULL;
	LPD3DXSPRITE spriteHandler = NULL;			// Sprite helper library to help us draw 2D image on the screen 

	LPDIRECTINPUT8       di;		// The DirectInput object         
	LPDIRECTINPUTDEVICE8 didv;		// The keyboard device 

	BYTE  keyStates[256];			// DirectInput keyboard state buffer 
	DIDEVICEOBJECTDATA keyEvents[KEYBOARD_BUFFER_SIZE];		// Buffered keyboard data

	LPKEYEVENTHANDLER keyHandler;
public:
	void InitKeyboard();
	void Init(HWND hWnd);
	void Draw(float x, float y, LPDIRECT3DTEXTURE9 texture, RECT Rect, Vector2 scale, float rotation, float centerx, float centery, int xpivot, int ypivot, int direction = 1, int flipy = 1, int alpha = 255);
	void Draw(float x, float y, LPDIRECT3DTEXTURE9 texture, int left, int top, int right, int bottom, int alpha = 255);
	void Draw(float x, float y, LPDIRECT3DTEXTURE9 texture, RECT* Rect);
	void SetKeyHandler(LPKEYEVENTHANDLER handler) { keyHandler = handler; }
	int IsKeyDown(int KeyCode);
	void ProcessKeyboard();

	static void SweptAABB(
		float ml,			// move left 
		float mt,			// move top
		float mr,			// move right 
		float mb,			// move bottom
		float dx,			// 
		float dy,			// 
		float sl,			// static left
		float st,
		float sr,
		float sb,
		float& t,
		float& nx,
		float& ny);

	LPDIRECT3DTEXTURE9 LoadTexture(LPCWSTR texturePath, D3DCOLOR TransColor);

	LPDIRECT3DDEVICE9 GetDirect3DDevice() { return this->d3ddv; }
	LPDIRECT3DSURFACE9 GetBackBuffer() { return backBuffer; }
	LPD3DXSPRITE GetSpriteHandler() { return this->spriteHandler; }

	static Game* GetInstance();

	~Game();
};

#endif