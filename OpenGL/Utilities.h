#pragma once
#include "Dependencies/glm/vec3.hpp"
#include "Dependencies/glm/vec2.hpp"
#include <Box2D\Box2D.h>
#include "Dependencies\Box2D\Common\b2Draw.h"
#include "b2GLDraw.h"

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

enum GameState
{
	MENU,
	SCENE,
	GAMEOVER
};

void RotateVector(b2Vec2& _vector, float _fDeg);