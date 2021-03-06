#pragma once
#include "Scene.h"
#include "Background.h"
#include "Input.h"
#include "Utilities.h"


class GameOver :
	public Scene, CInput
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

	TextLabel* m_titleText;
	TextLabel* m_retryButtonText;
	TextLabel* m_quitButtonText;

	b2World m_world = b2World(b2Vec2(0, 0));
	b2Body* m_worldbody;

	int player1score = 0;
	int player2score = 0;
	
	int m_iCurrMenuSelection;
};