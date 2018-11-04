#pragma once
#include "Scene.h"
#include "Background.h"


class GameOver :
	public Scene
{
public:
	GameOver();
	~GameOver();

	virtual void Init(int winner);
	virtual void Update();
	virtual void Render();

private:
	ShaderLoader shaderloader;
	GLuint shader;
	std::unique_ptr<Camera> camera;
	std::unique_ptr<TextLabel> text;
	std::unique_ptr<Background> gameover;

	b2World m_world = b2World(b2Vec2(0, 0));
	b2Body* m_worldbody;

	int player1score = 0;
	int player2score = 0;

};