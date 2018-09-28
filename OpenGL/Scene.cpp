#pragma once
#include "Scene.h"
#include "Dependencies/freeglut/freeglut.h"
#include "Ball.h"
#include "Wall.h"
#include "Goal.h"
#include "Background.h"
#include "Player.h"
#include "Player2.h"
#include "ContactListener.h"

MyContactListener g_myContactListenerInstance;

Scene::Scene()
{
	shader =
		shaderloader.CreateProgram("Resources/Shaders/3D.vs", "Resources/Shaders/3D.fs");
	camera =
		std::make_unique<Camera>();

	label =
		std::make_unique<TextLabel>("Player Score: " + std::to_string(gametimer), "Resources/Fonts/arial.ttf", glm::vec2(10, 15));

	ball =
		std::make_unique<Ball>();
	wallU =
		std::make_unique<Wall>();
	wallD =
		std::make_unique<Wall>();
	wallL =
		std::make_unique<Wall>();
	wallR =
		std::make_unique<Wall>();
	goalL =
		std::make_unique<Goal>();
	goalR =
		std::make_unique<Goal>();
	//background =
	//	std::make_shared<Background>();
	player =
		std::make_unique<Player>();
	player2 =
		std::make_unique<Player2>();

	gameobjects =
		std::make_unique<std::vector<std::unique_ptr<Pawn>>>();
}

Scene::~Scene()
{
}

void Scene::Init()
{
	m_world.SetContactListener(&g_myContactListenerInstance);

	ball->Init("Resources/Textures/ball.png", glm::vec3(5.0f, 5.0f, 0.0f), 0.0f, glm::vec3(0.35, 0.35, 1), shader, false, COLLIDER_CIRCLE, m_world);

	wallU->Init("Resources/Textures/Wall.bmp", glm::vec3(10, 15, 0.0f), 0.0f, glm::vec3(10, 0.25, 1.0f), shader, true, COLLIDER_SQUARE, m_world);
	wallD->Init("Resources/Textures/Wall.bmp", glm::vec3(10, 0, 0.0f), 0.0f, glm::vec3(10, 0.25, 1.0f), shader, true, COLLIDER_SQUARE, m_world);
	wallL->Init("Resources/Textures/Wall.bmp", glm::vec3(0, 8, 0.0f), 0.0f, glm::vec3(0.25, 10, 1.0f), shader, true, COLLIDER_SQUARE, m_world);
	wallR->Init("Resources/Textures/Wall.bmp", glm::vec3(20, 8, 0.0f), 0.0f, glm::vec3(0.25, 10, 1.0f), shader, true, COLLIDER_SQUARE, m_world);

	goalL->Init("Resources/Textures/MainMenu.bmp", glm::vec3(0, 8, 0.0f), 0.0f, glm::vec3(0.5f, 1.0f, 1.0f), shader, true, COLLIDER_SQUARE, m_world);
	goalR->Init("Resources/Textures/MainMenu.bmp", glm::vec3(20, 8, 0.0f), 0.0f, glm::vec3(0.5f, 1.0f, 1.0f), shader, true, COLLIDER_SQUARE, m_world);
	//background->Init("Resources/Textures/Background.bmp",	glm::vec3(10, 5.0f, 1),			0.0f,			glm::vec3(10, 10, 1.0f), shader, m_world);
	player->Init("Resources/Textures/ship.png", glm::vec3(6.0f, 6.0f, 0.0f), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f), shader, false, COLLIDER_CIRCLE, m_world);
	player2->Init("Resources/Textures/ship.png", glm::vec3(8.0f, 8.0f, 0.0f), 200.0f, glm::vec3(1.0f, 1.0f, 1.0f), shader, false, COLLIDER_CIRCLE, m_world);

	gameobjects->push_back(std::move(ball));
	gameobjects->push_back(std::move(wallU));
	gameobjects->push_back(std::move(wallD));
	gameobjects->push_back(std::move(wallL));
	gameobjects->push_back(std::move(wallR));
	gameobjects->push_back(std::move(goalL));
	gameobjects->push_back(std::move(goalR));
	//gameobjects->push_back(background);
	gameobjects->push_back(std::move(player));
	gameobjects->push_back(std::move(player2));

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
	if (firstrun == false)
	{
		previousTime = static_cast<float>(glutGet(GLUT_ELAPSED_TIME));
		firstrun = true;
	}
	float currentTime = static_cast<float>(glutGet(GLUT_ELAPSED_TIME));
	deltaTime = (currentTime - previousTime) * 0.001f;
	previousTime = currentTime;

	for (auto&& pawn : *gameobjects)
	{
		if (pawn)
		{
			pawn->Update(deltaTime, camera->GetView(), camera->GetProjection(), camera->GetLocation());
		}
	}

	gametimer -= deltaTime;
	label->Update(std::to_string(static_cast<int>(gametimer)));


	m_timeStep = deltaTime;
	m_world.Step(m_timeStep, m_velocityInterations, m_positionIterations);
}

void Scene::Render()
{
	/***ONLY FOR DEBUG****/
	//m_world.DrawDebugData();
	/***ONLY FOR DEBUG****/

	for (auto&& pawn : *gameobjects)
	{
		if (pawn)
		{
			pawn->Render();
		}
	}
	label->Render();
}