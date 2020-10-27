#ifndef __GLOBAL_VARIABLES_H__
#define __GLOBAL_VARIABLES_H__

#include <d3dx9.h>
#include <directxmath.h>


#define D3DCOLOR_WHITE D3DCOLOR_XRGB(255, 255, 255)
#define BACKGROUND_COLOR D3DCOLOR_XRGB(181, 235, 242)
//#define BACKGROUND_COLOR D3DCOLOR_XRGB(21,155,65)

#define WINDOW_WIDTH 640 //640 //1920
#define WINDOW_HEIGHT 480 //480 //1020

#define CAMERA_WIDTH 640
#define CAMERA_HEIGHT 480

#define CAMERA_DEFAULT_SCROLLING_SPEED_VX 2.0f;
#define CAMERA_DEFAULT_SCROLLING_SPEED_VY 2.0f;

#define MAX_FRAME_RATE 60

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