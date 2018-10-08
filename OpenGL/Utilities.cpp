#pragma once
#include "Utilities.h"
#include "Dependencies/glm/gtc/matrix_transform.hpp"
#include "Dependencies/freeglut/freeglut.h"
#include <math.h>

#include <iostream>

void RotateVector(b2Vec2& _vector, float _fDeg)
{
	float pX = _vector.x * cosf(_fDeg / 180 * b2_pi) - _vector.y * sinf(_fDeg / 180 * b2_pi);
	float pY = _vector.x * sinf(_fDeg / 180 * b2_pi) + _vector.y * cosf(_fDeg / 180 * b2_pi);

	_vector.x = pX;
	_vector.y = pY;
}
