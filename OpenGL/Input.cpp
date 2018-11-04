#include "Input.h"

#include "Dependencies/freeglut/freeglut.h"

unsigned char g_keyState[255];
unsigned char g_mouseState[3];

void Keyboard_Down(unsigned char key, int x, int y)
{
	if (g_keyState[key] != INPUT_HOLD && g_keyState[key] != INPUT_FIRST_PRESS)
	{
		g_keyState[key] = INPUT_FIRST_PRESS;
	}
	else
	{
		g_keyState[key] = INPUT_HOLD;
	}
}

void Keyboard_Up(unsigned char key, int x, int y)
{
	if (g_keyState[key] != INPUT_RELEASED || g_keyState[key] != INPUT_FIRST_RELEASE)
	{
		g_keyState[key] = INPUT_FIRST_RELEASE;
	}
	else
	{
		g_keyState[key] = INPUT_RELEASED;
	}
}

void Mouse(int _iButton, int _iGlutState, int _iX, int _iY)
{
	if (_iButton < 3)
	{
		g_mouseState[_iButton] = (_iGlutState == GLUT_DOWN) ? INPUT_HOLD : INPUT_RELEASED;
	}
}

bool CInput::GetButtonDown(unsigned char _cKey)
{
	return (g_keyState[_cKey] == INPUT_FIRST_PRESS);
}

bool CInput::GetButtonUp(unsigned char _cKey)
{
	return (g_keyState[_cKey] == INPUT_FIRST_RELEASE);
}

bool CInput::GetButton(unsigned char _cKey)
{
	return (g_keyState[_cKey] == INPUT_HOLD);
}

bool CInput::GetMouseButtonDown(int _iButton)
{
	if (_iButton <= 3)
	{
		return (g_mouseState[_iButton] == INPUT_FIRST_PRESS);
	}
	return false;
}

bool CInput::GetMouseButtonUp(int _iButton)
{
	if (_iButton <= 3)
	{
		return(g_mouseState[_iButton] == INPUT_FIRST_RELEASE);
	}
	return false;
}

bool CInput::GetMouseButton(int _iButton)
{
	return(g_mouseState[_iButton] == INPUT_HOLD);
}

void CInput::Update()
{
	for (unsigned char& key : g_keyState)
	{
		if (key == INPUT_FIRST_PRESS)
		{
			key = INPUT_HOLD;
		}
	}

	for (unsigned char& key : g_mouseState)
	{
		if (key == INPUT_FIRST_RELEASE)
		{
			key = INPUT_RELEASED;
		}
	}
}