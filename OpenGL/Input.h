#pragma once

#include "Utilities.h"

enum InputState
{
	INPUT_FIRST_RELEASE,
	INPUT_RELEASED,
	INPUT_FIRST_PRESS,
	INPUT_HOLD,
};

enum InputMouse
{
	MOUSE_LEFT,
	MOUSE_MIDDLE,
	MOUSE_RIGHT
};

void Keyboard_Down(unsigned char key, int x, int y);
void Keyboard_Up(unsigned char key, int x, int y);

void Mouse(int _iButton, int _iGlutState, int _iX, int _iY);


bool GetButtonDown(unsigned char _cKey);
bool GetButtonUp(unsigned char _cKey);

bool GetMouseButtonDown(int _iButton);
bool GetMouseButtonUp(int _iButton);
