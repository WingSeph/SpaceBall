#include "Input.h"

#include "Dependencies/freeglut/freeglut.h"

unsigned char g_keyState[255];
unsigned char g_mouseState[3];

void Keyboard_Down(unsigned char key, int x, int y)
{
	g_keyState[key] = INPUT_HOLD;
}

void Keyboard_Up(unsigned char key, int x, int y)
{
	g_keyState[key] = INPUT_RELEASED;
}

void Mouse(int _iButton, int _iGlutState, int _iX, int _iY)
{
	if (_iButton < 3)
	{
		g_mouseState[_iButton] = (_iGlutState == GLUT_DOWN) ? INPUT_HOLD : INPUT_RELEASED;
	}
}

bool GetButtonDown(unsigned char _cKey)
{
	return (g_keyState[_cKey] == INPUT_HOLD) ? true : false;
}

bool GetButtonUp(unsigned char _cKey)
{
	return (g_keyState[_cKey] == INPUT_RELEASED) ? true : false;
}

bool GetMouseButtonDown(int _iButton)
{
	if (_iButton <= 3)
	{
		return (g_mouseState[_iButton] == INPUT_HOLD) ? true : false;
	}
}

bool GetMouseButtonUp(int _iButton)
{
	if (_iButton <= 3)
	{
		return(g_mouseState[_iButton] == INPUT_RELEASED) ? true : false;
	}
}