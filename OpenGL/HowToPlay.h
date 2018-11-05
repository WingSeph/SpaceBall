#pragma once
#include "Scene.h"
#include "Background.h"
#include "Input.h"
#include "Utilities.h"
#include "Pawn.h"

class HowToPlay : public Scene, CInput
{
public:
	HowToPlay();
	~HowToPlay();

	virtual void Init();
	virtual void Update();
	virtual void Render();

private:
	ShaderLoader shaderloader;
	GLuint shader;
	std::unique_ptr<Camera> m_camera;
	std::unique_ptr<Camera> camera;
	std::unique_ptr<Background> controls;

	b2World m_world = b2World(b2Vec2(0, 0));
	b2Body* m_worldbody;

	TextLabel* m_titleText;
	TextLabel* m_backButtonText;

	float m_deltaTime = 0;
	float m_previousTime = 0;

	int m_iCurrMenuSelection;
};