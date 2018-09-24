#pragma once
#include "Scene.h"
class GameOver :
	public Scene
{
public:
	GameOver();
	~GameOver();

	virtual void Init();
	virtual void Update();
	virtual void Render();
};
