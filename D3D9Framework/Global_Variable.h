#ifndef __GLOBAL_VARIABLES_H__
#define __GLOBAL_VARIABLES_H__

#include <d3dx9.h>
#include <directxmath.h>


#define D3DCOLOR_WHITE D3DCOLOR_XRGB(255, 255, 255)
#define BACKGROUND_COLOR D3DCOLOR_XRGB(181, 235, 242)
//#define BACKGROUND_COLOR D3DCOLOR_XRGB(21,155,65)
// window configuration
#define WINDOW_WIDTH 768 //640 //1920 //768
#define WINDOW_HEIGHT 672 //480 //1020 //672

#define WINDOW_TITLE L"Mario"
#define WINDOW_CLASS_NAME L"Game"
//camera configuration
#define CAMERA_WIDTH 768
#define CAMERA_HEIGHT 672

#define CAMERA_DEFAULT_SCROLLING_SPEED_VX 2.0f;
#define CAMERA_DEFAULT_SCROLLING_SPEED_VY 2.0f;

//game configuration
#define MAX_FRAME_RATE 180

#define KEYBOARD_BUFFER_SIZE 1024

#define PI 3.1614f

typedef D3DXVECTOR2 Vector2;
typedef D3DXVECTOR3 Vector3;
#define VectorZero Vector2(0.0f,0.0f);

enum Texture
{
	//mario texture
	TEX_MARIO = 1,

	//world texture
	TEX_WORLD_1_1 = 110
};

class Global_Variable
{
};

#endif