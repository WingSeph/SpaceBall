#pragma once
#include "Scene.h"
#include "Dependencies/freeglut/freeglut.h"
#include "Ball.h"
#include "Wall.h"
#include "Goal.h"
#include "Background.h"

#include "Player2.h"
#include "ContactListener.h"
#include "Dependencies/FMOD/fmod.hpp"

FMOD::System* audioMgr; 
FMOD::Sound* fxThump; 
FMOD::Sound* bgmTheme;

bool InitFmod() {
	FMOD_RESULT result; result = FMOD::System_Create(&audioMgr); if (result != FMOD_OK) { return false; }
	result = audioMgr->init(50, FMOD_INIT_NORMAL, 0); if (result != FMOD_OK) { return false; } return true;
}
const bool LoadAudio() {
	FMOD_RESULT result;
	result = audioMgr->createSound("Resources/Sounds/SFX/DEMOLISH.wav", FMOD_DEFAULT, 0, &fxThump); 
	result = audioMgr->createSound("Resources/Sounds/Music/BGM.wav", FMOD_DEFAULT, 0, &bgmTheme);
	bgmTheme->setMode(FMOD_LOOP_NORMAL);
	return true;
}

MyContactListener g_myContactListenerInstance;

Scene::Scene()
{
	m_shader = m_shaderloader.CreateProgram("Resources/Shaders/3D.vs", "Resources/Shaders/3D.fs");
	m_camera = std::make_unique<Camera>();

	m_timer = std::make_unique<TextLabel>("Timer", "Resources/Fonts/arial.ttf", glm::vec2(WINDOW_WIDTH/2, WINDOW_HEIGHT - 50), glm::vec3(0,0,0));
	m_player1Score = std::make_unique<TextLabel>("P2Score", "Resources/Fonts/arial.ttf", glm::vec2(WINDOW_WIDTH - 50, WINDOW_HEIGHT - 50), glm::vec3(0, 1, 0));
	m_player2Score = std::make_unique<TextLabel>("P2Score", "Resources/Fonts/arial.ttf", glm::vec2(20, WINDOW_HEIGHT - 50), glm::vec3(1, 0, 0));

	m_ball = std::make_unique<Ball>();

	m_wallU = std::make_unique<Wall>();

	m_wallD = std::make_unique<Wall>();

	m_wallL = std::make_unique<Wall>();

	m_wallR = std::make_unique<Wall>();

	m_goalL = std::make_unique<Goal>();
	m_goalL->SetTag("Goal");

	m_goalR = std::make_unique<Goal>();
	m_wallU->SetTag("Goal");

	//m_background = std::make_shared<Background>();
	m_player = std::make_unique<Player>();
	m_player2 = std::make_unique<Player2>();

	m_gameobjects = std::make_unique<std::vector<std::unique_ptr<Pawn>>>();


}

Scene::~Scene()
{
}

void Scene::Init()
{

	InitFmod(); LoadAudio();
	FMOD::Channel* channel; 
	audioMgr->playSound(bgmTheme, 0, false, &channel);

	// Creating groundbody
	b2BodyDef bd;
	m_worldbody = m_world.CreateBody(&bd);
	m_world.SetContactListener(&g_myContactListenerInstance);

	m_ball->Init("Resources/Textures/ball.png", glm::vec3(5.0f, 5.0f, 0.0f), 0.0f, glm::vec3(0.35, 0.35, 1), m_shader, false, COLLIDER_CIRCLE, m_world);

	m_wallU->Init("Resources/Textures/Wall.bmp", glm::vec3(10, 15, 0.0f), 0.0f, glm::vec3(10, 0.25, 1.0f), m_shader, true, COLLIDER_SQUARE, m_world);
	m_wallD->Init("Resources/Textures/Wall.bmp", glm::vec3(10, 0, 0.0f), 0.0f, glm::vec3(10, 0.25, 1.0f), m_shader, true, COLLIDER_SQUARE, m_world);
	m_wallL->Init("Resources/Textures/Wall.bmp", glm::vec3(0, 8, 0.0f), 0.0f, glm::vec3(0.25, 10, 1.0f), m_shader, true, COLLIDER_SQUARE, m_world);
	m_wallR->Init("Resources/Textures/Wall.bmp", glm::vec3(20, 8, 0.0f), 0.0f, glm::vec3(0.25, 10, 1.0f), m_shader, true, COLLIDER_SQUARE, m_world);

	m_goalL->Init("Resources/Textures/MainMenu.bmp", glm::vec3(0, 8, 0.0f), 0.0f, glm::vec3(0.5f, 1.0f, 1.0f), m_shader, true, COLLIDER_SQUARE, m_world);
	m_goalR->Init("Resources/Textures/MainMenu.bmp", glm::vec3(20, 8, 0.0f), 0.0f, glm::vec3(0.5f, 1.0f, 1.0f), m_shader, true, COLLIDER_SQUARE, m_world);
	//background->Init("Resources/Textures/Background.bmp",	glm::vec3(10, 5.0f, 1),			0.0f,			glm::vec3(10, 10, 1.0f), m_shader, m_world);
	m_player->Init("Resources/Textures/ship.png", glm::vec3(6.0f, 6.0f, 0.0f), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f), m_shader, false, COLLIDER_CIRCLE, m_world);
	m_player2->Init("Resources/Textures/ship.png", glm::vec3(8.0f, 8.0f, 0.0f), 200.0f, glm::vec3(1.0f, 1.0f, 1.0f), m_shader, false, COLLIDER_CIRCLE, m_world);

	m_gameobjects->push_back(std::move(m_ball));
	m_gameobjects->push_back(std::move(m_wallU));
	m_gameobjects->push_back(std::move(m_wallD));
	m_gameobjects->push_back(std::move(m_wallL));
	m_gameobjects->push_back(std::move(m_wallR));
	m_gameobjects->push_back(std::move(m_goalL));
	m_gameobjects->push_back(std::move(m_goalR));
	//m_gameobjects->push_back(m_background);
	/*m_gameobjects->push_back(std::move(m_player));
	m_gameobjects->push_back(std::move(m_player2));*/

	m_world.SetDebugDraw(&m_debugDraw);
	uint32 flags = 0;
	flags += b2Draw::e_shapeBit;
	flags += b2Draw::e_jointBit;
	flags += b2Draw::e_aabbBit;
	flags += b2Draw::e_pairBit;
	flags += b2Draw::e_centerOfMassBit;
	m_debugDraw.SetFlags(flags);
}

void Scene::Update()
{
	
	//DeltaTime
	if (m_firstrun == false)
	{
		m_previousTime = static_cast<float>(glutGet(GLUT_ELAPSED_TIME));
		m_firstrun = true;
	}
	float currentTime = static_cast<float>(glutGet(GLUT_ELAPSED_TIME));
	m_deltaTime = (currentTime - m_previousTime) * 0.001f;
	m_previousTime = currentTime;

	for (auto&& pawn : *m_gameobjects)
	{
		if (pawn)
		{
			pawn->Update(m_deltaTime, m_camera->GetView(), m_camera->GetProjection(), m_camera->GetLocation());
		}
	}

	m_player ->Update(m_deltaTime, m_camera->GetView(), m_camera->GetProjection(), m_camera->GetLocation());
	m_player2->Update(m_deltaTime, m_camera->GetView(), m_camera->GetProjection(), m_camera->GetLocation());

	m_gametimer -= m_deltaTime;
	if (m_player1respawn > 0) {
		m_player1respawn -= m_deltaTime;
		if (m_player1respawn <= 0) {
			m_player->Respawn();
		}
	}
	if (m_player2respawn > 0) {
		m_player2respawn -= m_deltaTime;
	}

	m_timer->Update(std::to_string(static_cast<int>(m_gametimer)));
	m_player1Score->Update("0");
	m_player2Score->Update("0");

	m_timeStep = m_deltaTime;
	m_world.Step(m_timeStep, m_velocityInterations, m_positionIterations);

	DeletionCheck();
}

void Scene::Render()
{
	/***ONLY FOR DEBUG****/
	//m_world.DrawDebugData();
	/***ONLY FOR DEBUG****/

	for (auto&& pawn : *m_gameobjects)
	{
		if (pawn)
		{
			pawn->Render();
		}
	}
	m_player->Render();
	m_player2->Render();
	m_timer->Render();
	m_player1Score->Render();
	m_player2Score->Render();

	
}

void Scene::DeletionCheck()
{
	if (m_player != nullptr && m_player->IsDead() && m_player1respawn <= 0)
	{
		//m_player = nullptr;
		FMOD::Channel* channel;
		audioMgr->playSound(fxThump, 0, false, &channel);
		m_player1respawn = 5;
	}

	if (m_player != nullptr && m_player2->IsDead())
	{
		m_player2 = nullptr;
	}
}