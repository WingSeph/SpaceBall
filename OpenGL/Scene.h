#pragma once
#include <memory>
#include <vector>
#include "Dependencies/glew/glew.h"
#include "ShaderLoader.h"
#include "Camera.h"
#include "Pawn.h"
#include "TextLabel.h"

class Scene
{
public:
	Scene();
	~Scene();

	virtual void Init();
	virtual void Update();
	virtual void Render();

private:
	ShaderLoader
		shaderloader;
	GLuint
		shader;
	std::unique_ptr<Camera>
		camera;
	std::unique_ptr<Pawn>
		ball,
		player,
		player2,
		wallU,
		wallD,
		wallL,
		wallR,
		goalL,
		goalR,
		background;

	std::unique_ptr<std::vector<std::unique_ptr<Pawn>>>
		gameobjects;

	std::unique_ptr<TextLabel>
		label;

	float gametimer =
		60;
	bool firstrun =
		false;
	float deltaTime =
		0;
	float previousTime =
		0;

	b2World m_world = b2World(b2Vec2(0, 0));

	float32 m_timeStep;
	int32 m_velocityInterations = 10;
	int32 m_positionIterations = 8;

	b2GLDraw m_debugDraw;
};
