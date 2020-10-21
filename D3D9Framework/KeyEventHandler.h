#ifndef __KEYEVENTHANDLER_H__
#define __KEYEVENTHANDLER_H__

#include <Windows.h>

class KeyEventHandler
{
public:
	virtual void KeyState(BYTE* state) = 0;
	virtual void OnKeyDown(int KeyCode) = 0;
	virtual void OnKeyUp(int KeyCode) = 0;
};
typedef KeyEventHandler* LPKEYEVENTHANDLER;

#endif