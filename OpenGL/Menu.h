#pragma once
#include "Scene.h"
class Menu :
	public Scene
{
public:
	Menu();
	~Menu();

	virtual void Init();
	virtual void Update();
	virtual void Render();
};
