#pragma once
#include "Utilities.h"
#include "Dependencies/glm/gtc/matrix_transform.hpp"
#include "Dependencies/freeglut/freeglut.h"
#include <math.h>

#include <iostream>

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

float GetDeltaRotation()
{
	float deltaRotation = 0.0f;
	//'a' = Left
	if (g_keyState[(unsigned char)'a'] == INPUT_HOLD)
	{
		deltaRotation += 1.0f;
	}
	//'d' = Right
	if (g_keyState[(unsigned char)'d'] == INPUT_HOLD)
	{
		deltaRotation -= 1.0f;
	}
	return deltaRotation;
}

void ResetFalse()
{
	for (int i = 0; i < 255; i++)
	{
		g_keyState[i] = FALSE;
	}
}

void RotateVector(b2Vec2& _vector, float _fDeg)
{
	float pX = _vector.x * cosf(_fDeg / 180 * b2_pi) - _vector.y * sinf(_fDeg / 180 * b2_pi);
	float pY = _vector.x * sinf(_fDeg / 180 * b2_pi) + _vector.y * cosf(_fDeg / 180 * b2_pi);

	_vector.x = pX;
	_vector.y = pY;
}