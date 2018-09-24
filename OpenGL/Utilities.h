#pragma once
#include "Dependencies/glm/vec3.hpp"
#include "Dependencies/glm/vec2.hpp"
#include <Box2D\Box2D.h>
#include "Dependencies\Box2D\Common\b2Draw.h"
#include "b2GLDraw.h"

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

enum InputState
{
	INPUT_FIRST_RELEASE,
	INPUT_RELEASED,
	INPUT_FIRST_PRESS,
	INPUT_HOLD
};

void Keyboard_Down(unsigned char key, int x, int y);

void Keyboard_Up(unsigned char key, int x, int y);

void GetDeltaPosition(b2Body* _body, float _fAngle);

void GetDeltaPosition2(b2Body* _body);

float GetDeltaRotation();