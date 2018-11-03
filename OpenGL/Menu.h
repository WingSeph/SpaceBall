#pragma once
#include "Scene.h"
#include "Background.h"
class Menu :
	public Scene
{
public:
	Menu();
	~Menu();

	virtual void Init();
	virtual void Update();
	virtual void Render();


private:
	ShaderLoader shaderloader;
	GLuint shader;
	std::unique_ptr<Camera> camera;
	std::unique_ptr<TextLabel> text;
	std::unique_ptr<Background> menu;

	b2World m_world = b2World(b2Vec2(0, 0));
	b2Body* m_worldbody;

	int m_iCurrMenuSelection = 0;
};