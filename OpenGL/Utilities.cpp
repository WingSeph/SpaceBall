#pragma once
#include "Utilities.h"
#include "Dependencies/glm/gtc/matrix_transform.hpp"
#include "Dependencies/freeglut/freeglut.h"
#include <math.h>

unsigned char keyState[255];

void Keyboard_Down(unsigned char key, int x, int y)
{
	keyState[key] = INPUT_HOLD;
}

void Keyboard_Up(unsigned char key, int x, int y)
{
	keyState[key] = INPUT_RELEASED;
}

void GetDeltaPosition(b2Body* _body, float _fAngle)
{
	_body->SetLinearDamping(0.5f);
	_body->SetAngularDamping(1.0f);

	//'w' = Up
	if (keyState[(unsigned char)'w'] == INPUT_HOLD)
	{
		// Move forwards
		//_body->ApplyForce(, true);
	}
	// 's' = Down
	if (keyState[(unsigned char)'s'] == INPUT_HOLD)
	{
		// Move backwards
		_body->ApplyForce(b2Vec2(cos(_body->GetAngle()), sin(-_body->GetAngle())), b2Vec2(_body->GetPosition().x, _body->GetPosition().y), true);
	}

	// 'a' = Left
	if (keyState[(unsigned char)'a'] == INPUT_HOLD)
	{
		// Rotate left
		_body->SetAngularVelocity(50);
	}

	// 'd' = Right
	else if (keyState[(unsigned char)'d'] == INPUT_HOLD)
	{
		// Rotate right
		_body->SetAngularVelocity(-50);
	}
}

void GetDeltaPosition2(b2Body* _body)
{
	//'i' = Up
	if (keyState[(unsigned char)'i'] == INPUT_HOLD)
	{
		// Move forwards
		_body->ApplyForce(b2Vec2(0, 1), b2Vec2(_body->GetPosition().x, _body->GetPosition().y + 1), true);
	}
	// 'k' = Down
	if (keyState[(unsigned char)'k'] == INPUT_HOLD)
	{
		// Move backwards
		_body->ApplyForce(b2Vec2(0, -1), b2Vec2(_body->GetPosition().x, _body->GetPosition().y - 1), true);
	}

	// 'j' = Left
	if (keyState[(unsigned char)'j'] == INPUT_HOLD)
	{
		// Rotate left
		
	}

	// 'l' = Right
	if (keyState[(unsigned char)'l'] == INPUT_HOLD)
	{
		// Rotate right
		
	}
}

float GetDeltaRotation()
{
	float deltaRotation = 0.0f;
	//'a' = Left
	if (keyState[(unsigned char)'a'] == INPUT_HOLD)
	{
		deltaRotation += 1.0f;
	}
	//'d' = Right
	if (keyState[(unsigned char)'d'] == INPUT_HOLD)
	{
		deltaRotation -= 1.0f;
	}
	return deltaRotation;
}

void ResetFalse()
{
	for (int i = 0; i < 255; i++)
	{
		keyState[i] = FALSE;
	}
}