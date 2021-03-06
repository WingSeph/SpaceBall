#pragma once
#include <memory>
#include <vector>
#include "Dependencies/glew/glew.h"
#include "ShaderLoader.h"
#include "Camera.h"
#include "Pawn.h"
#include "Player.h"
#include "Player2.h"
#include "Ball.h"
#include "BallSplit.h"
#include "TextLabel.h"
#include "PowerUp.h"
#include "Effect.h"

class Scene
{
public:
	Scene();
	~Scene();

	virtual void Init();
	virtual void Update();
	virtual void Render();

	void DeletionCheck();

	bool GameOver();
	int WhoWon();

	void CreateAnimationEffect(b2Vec2 t_location);
	void CreateAnimationEffect(b2Vec2 t_location, float duration);
	void CreateAnimationEffect(b2Vec2 t_location, float duration, std::string filepath);
	void CreateAnimationEffect(glm::vec2 t_location, float duration, std::string filepath);

	GameState GetCurrentScene();
	void SetCurrentScene(GameState _state);

private:
	ShaderLoader m_shaderloader;
	GLuint m_shader;

	std::unique_ptr<Camera> m_camera;
	std::unique_ptr<Player> m_player;
	std::unique_ptr<Player2> m_player2;
	std::unique_ptr<Ball> m_ball1;
	std::unique_ptr<PowerUp> m_powerup;
	BallSplit *m_splitball;

	std::unique_ptr<Pawn>
		m_bgm,
		m_goalL,
		m_goalR;

	std::unique_ptr<std::vector<std::unique_ptr<Pawn>>> m_gameobjects;
	std::vector<Effect*> m_effects;

	std::vector<BallSplit*> m_ballsplits;

	std::unique_ptr<TextLabel> m_timer, m_player1Score, m_player2Score;

	float m_gametimer = 60;
	float m_player1respawn = 0;
	float m_player2respawn = 0;
	bool m_firstrun = false;
	bool m_player1canspeedup = true;
	bool m_player2canspeedup = true;
	float m_deltaTime = 0;
	float m_previousTime = 0;
	float m_speedpoweruplifetimep1 = 0;
	float m_speedpoweruplifetimep2 = 0;
	float fSpeedOriginp1;
	float fSpeedOriginp2;
	int player1score = 0;
	int player2score = 0;

	b2World m_world = b2World(b2Vec2(0, 0));
	b2Body* m_worldbody;
	float32 m_timeStep;
	int32 m_velocityInterations = 10;
	int32 m_positionIterations = 8;
	b2GLDraw m_debugDraw;

	GameState m_currentScene;
};
