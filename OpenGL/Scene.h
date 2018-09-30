#pragma once
#include <memory>
#include <vector>
#include "Dependencies/glew/glew.h"
#include "ShaderLoader.h"
#include "Camera.h"
#include "Pawn.h"
#include "Player.h"
#include "Player2.h"
#include "TextLabel.h"

class Scene
{
public:
	Scene();
	~Scene();

	virtual void Init();
	virtual void Update();
	virtual void Render();

	void DeletionCheck();

private:
	ShaderLoader m_shaderloader;
	GLuint m_shader;

	std::unique_ptr<Camera> m_camera;

	std::unique_ptr<Player> m_player;
	std::unique_ptr<Player2> m_player2;

	std::unique_ptr<Pawn>
		m_ball,
		m_bgm,
		m_wallU,
		m_wallD,
		m_wallL,
		m_wallR,
		m_goalL,
		m_goalR,
		m_background;

	std::unique_ptr<std::vector<std::unique_ptr<Pawn>>> m_gameobjects;

	std::unique_ptr<TextLabel> m_timer, m_player1Score, m_player2Score;

	float m_gametimer = 60;
	float m_player1respawn = 0;
	float m_player2respawn = 0;
	bool m_firstrun = false;
	float m_deltaTime = 0;
	float m_previousTime = 0;

	b2World m_world = b2World(b2Vec2(0, 0));
	b2Body* m_worldbody;

	float32 m_timeStep;
	int32 m_velocityInterations = 10;
	int32 m_positionIterations = 8;

	b2GLDraw m_debugDraw;
};
