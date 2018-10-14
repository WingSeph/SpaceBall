#pragma once
#include "Scene.h"
#include "Dependencies/freeglut/freeglut.h"

#include "Wall.h"
#include "Goal.h"
#include "Background.h"

#include "ContactListener.h"
#include "Dependencies/FMOD/fmod.hpp"

FMOD::System* audioMgr; 
FMOD::Sound* fxThump; 
FMOD::Sound* fxlaugh;
FMOD::Sound* fxrespawn;
FMOD::Sound* bgmTheme;

bool InitFmod() {
	FMOD_RESULT result; result = FMOD::System_Create(&audioMgr); if (result != FMOD_OK) { return false; }
	result = audioMgr->init(50, FMOD_INIT_NORMAL, 0); if (result != FMOD_OK) { return false; } return true;
}
const bool LoadAudio() {
	FMOD_RESULT result;
	result = audioMgr->createSound("Resources/Sounds/SFX/WARP.wav", FMOD_DEFAULT, 0, &fxrespawn);
	result = audioMgr->createSound("Resources/Sounds/SFX/WoahahahaYes.wav", FMOD_DEFAULT, 0, &fxlaugh);
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
	m_timer = std::make_unique<TextLabel>("Timer", "Resources/Fonts/arial.ttf", glm::vec2(WINDOW_WIDTH/2, WINDOW_HEIGHT - 50), glm::vec3(1,1,1));
	m_player1Score = std::make_unique<TextLabel>("P2Score", "Resources/Fonts/arial.ttf", glm::vec2(20, WINDOW_HEIGHT - 50), glm::vec3(0, 0, 1));
	m_player2Score = std::make_unique<TextLabel>("P2Score", "Resources/Fonts/arial.ttf", glm::vec2(WINDOW_WIDTH - 50, WINDOW_HEIGHT - 50), glm::vec3(1, 0, 0));

	m_ball1 = std::make_unique<Ball>();
	m_ball1->SetTag("Ball");

	m_wallU = std::make_unique<Wall>();

	m_wallD = std::make_unique<Wall>();

	m_wallL = std::make_unique<Wall>();

	m_wallR = std::make_unique<Wall>();

	m_goalL = std::make_unique<Goal>();
	m_goalL->SetTag("Goal");

	m_goalR = std::make_unique<Goal>();
	m_goalR->SetTag("Goal2");

	m_powerup =	std::make_unique<PowerUp>();

	m_bgm = std::make_unique<Background>();
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
	
	m_ball1->Init("Resources/Textures/meteor.png", glm::vec3(10.0f, 8.0f, 0.0f), 0.0f, glm::vec3(0.35, 0.35, 1), m_shader, false, COLLIDER_CIRCLE, m_world);

	m_wallU->Init("Resources/Textures/Wall.bmp", glm::vec3(10, 15, 0.0f), 0.0f, glm::vec3(10, 0.25, 1.0f), m_shader, true, COLLIDER_SQUARE, m_world);
	m_wallD->Init("Resources/Textures/Wall.bmp", glm::vec3(10, 0, 0.0f), 0.0f, glm::vec3(10, 0.25, 1.0f), m_shader, true, COLLIDER_SQUARE, m_world);
	m_wallL->Init("Resources/Textures/Wall.bmp", glm::vec3(0, 8, 0.0f), 0.0f, glm::vec3(0.25, 10, 1.0f), m_shader, true, COLLIDER_SQUARE, m_world);
	m_wallR->Init("Resources/Textures/Wall.bmp", glm::vec3(20, 8, 0.0f), 0.0f, glm::vec3(0.25, 10, 1.0f), m_shader, true, COLLIDER_SQUARE, m_world);

	m_goalL->Init("Resources/Textures/MainMenu.bmp", glm::vec3(0, 8, 0.0f), 0.0f, glm::vec3(0.5f, 1.0f, 1.0f), m_shader, true, COLLIDER_SQUARE, m_world);
	m_goalR->Init("Resources/Textures/MainMenu.bmp", glm::vec3(20, 8, 0.0f), 0.0f, glm::vec3(0.5f, 1.0f, 1.0f), m_shader, true, COLLIDER_SQUARE, m_world);

	m_powerup->Init("Resources/Textures/splitballpowerup.png", glm::vec3(10.0f, 4.0f, 0.0f), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f), m_shader, false, COLLIDER_CIRCLE, m_world, 1);

	m_player->Init("Resources/Textures/ship1_blue.png", glm::vec3(6.0f, 6.0f, 0.0f), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f), m_shader, m_world);
	m_player2->Init("Resources/Textures/ship2_red.png", glm::vec3(16.0f, 6.0f, 0.0f), 200.0f, glm::vec3(1.0f, 1.0f, 1.0f), m_shader, m_world);

	m_world.SetContactListener(&g_myContactListenerInstance);
	m_bgm->Init("Resources/Textures/Background.bmp", glm::vec3(0.0f, 0.0f, 0.0f), 200.0f, glm::vec3(10.0f, 10.0f, 10.0f), m_shader, true, COLLIDER_CIRCLE, m_world);
	m_bgm->GetBody()->SetActive(false);
	m_gameobjects->push_back(std::move(m_wallU));
	m_gameobjects->push_back(std::move(m_wallD));
	m_gameobjects->push_back(std::move(m_wallL));
	m_gameobjects->push_back(std::move(m_wallR));

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

	m_ball1->Update(m_deltaTime, m_camera->GetView(), m_camera->GetProjection(), m_camera->GetLocation());
	for (auto&& pawn : *m_gameobjects)
	{
		if (pawn)
		{
			pawn->Update(m_deltaTime, m_camera->GetView(), m_camera->GetProjection(), m_camera->GetLocation());
		}
	}
	m_goalL->Update(m_deltaTime, m_camera->GetView(), m_camera->GetProjection(), m_camera->GetLocation());
	m_goalR->Update(m_deltaTime, m_camera->GetView(), m_camera->GetProjection(), m_camera->GetLocation());
	m_player ->Update(m_deltaTime, m_camera->GetView(), m_camera->GetProjection(), m_camera->GetLocation());
	m_player2->Update(m_deltaTime, m_camera->GetView(), m_camera->GetProjection(), m_camera->GetLocation());
	
	
	m_powerup->Update(m_deltaTime, m_camera->GetView(), m_camera->GetProjection(), m_camera->GetLocation());

	m_gametimer -= m_deltaTime;
	if (m_player1respawn > 0) {
		m_player1respawn -= m_deltaTime;
		if (m_player1respawn <= 0) {
			FMOD::Channel* channel;
			audioMgr->playSound(fxrespawn, 0, false, &channel);
			m_player->Respawn();
		}
	}
	if (m_player2respawn > 0) {
		m_player2respawn -= m_deltaTime;
		if (m_player2respawn <= 0) {
			FMOD::Channel* channel;
			audioMgr->playSound(fxrespawn, 0, false, &channel);
			m_player2->Respawn();
		}
	}

	m_timer->Update(std::to_string(static_cast<int>(m_gametimer)));
	m_player1Score->Update(std::to_string(player1score));
	m_player2Score->Update(std::to_string(player2score));

	m_timeStep = m_deltaTime;

	//powerup overlap check
	//if (IsOverlap(m_powerup->GetBody()))
	//{
	//	m_powerup->OnCollisionEnter(m_player.get());
	//}

	m_world.Step(m_timeStep, m_velocityInterations, m_positionIterations);
	m_ball1->checkgate(m_goalL->GetBody()->GetWorldCenter(), player2score);
	m_ball1->checkgate(m_goalR->GetBody()->GetWorldCenter(), player1score);

	if (m_powerup->isactive && m_powerup->type == 1) {
		if (m_powerup->CheckCollisionOnplayer(m_player->GetBody())) {
			m_player2->Die();
		}
		else if (m_powerup->CheckCollisionOnplayer(m_player2->GetBody())) {
			m_player->Die();
		}
	}

	if (m_powerup->isactive && m_powerup->type == 2) {
		if (m_powerup->CheckCollisionOnplayer(m_player->GetBody())) {
			
		}
		else if (m_powerup->CheckCollisionOnplayer(m_player2->GetBody())) {
			
		}
	}
	

	if (m_ball1->IsDead()) {
		FMOD::Channel* channel;
		audioMgr->playSound(fxlaugh, 0, false, &channel);
		m_ball1->Respawn();
	}

	DeletionCheck();

	for (auto&& pawn : *m_gameobjects)
	{
		if (pawn)
		{
			pawn->Update(m_deltaTime, m_camera->GetView(), m_camera->GetProjection(), m_camera->GetLocation());
		}
	}

	m_player->Update(m_deltaTime, m_camera->GetView(), m_camera->GetProjection(), m_camera->GetLocation());
	m_player2->Update(m_deltaTime, m_camera->GetView(), m_camera->GetProjection(), m_camera->GetLocation());
}

void Scene::Render()
{
	/***ONLY FOR DEBUG****/
	//m_world.DrawDebugData();
	/***ONLY FOR DEBUG****/
	m_bgm->Render();
	m_ball1->Render();
	for (auto&& pawn : *m_gameobjects)
	{
		if (pawn)
		{
			pawn->Render();
		}
	}
	if (m_goalL)
	{
		m_goalL->Render();
	}
	if (m_goalR)
	{
		m_goalR->Render();
	}
	if (m_player)
	{
		m_player->Render();
	}
	if (m_player2)
	{
		m_player2->Render();
	}
	if (m_timer)
	{
		m_timer->Render();
	}
	if (m_player1Score)
	{
		m_player1Score->Render();
	}
	if (m_player2Score)
	{
		m_player2Score->Render();
	}
	if (m_powerup)
	{
		m_powerup->Render();
	}
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

	if (m_player != nullptr && m_player2->IsDead() && m_player2respawn <= 0)
	{
		//m_player2 = nullptr;
		FMOD::Channel* channel;
		audioMgr->playSound(fxThump, 0, false, &channel);
		m_player2respawn = 5;
	}
}

/// Callback to check for overlap of given body.
//struct CheckOverlapCallback : b2QueryCallback
//{
//	CheckOverlapCallback(const b2Body* body) :
//		m_body(body), m_isOverlap(false) {}
//
//	// override
//	bool ReportFixture(b2Fixture* fixture)
//	{
//		// Skip self.
//		if (fixture->GetBody() == m_body)
//			return true;
//
//		for (const b2Fixture* bodyFixture = m_body->GetFixtureList(); bodyFixture;
//			bodyFixture = bodyFixture->GetNext())
//		{
//			if (b2TestOverlap(fixture->GetShape(), 0, bodyFixture->GetShape(), 0,
//				fixture->GetBody()->GetTransform(), m_body->GetTransform()))
//			{
//				m_isOverlap = true;
//				return false;
//			}
//		}
//	}
//
//	const b2Body* m_body;
//	bool m_isOverlap;
//};
//
///// Gets the combined AABB of all shapes of the given body.
//b2AABB Scene::GetBodyAABB(const b2Body* body)
//{
//	b2AABB result;
//	b2Transform trans = body->GetTransform();
//	const b2Fixture* first = body->GetFixtureList();
//
//	for (const b2Fixture* fixture = first; fixture; fixture = fixture->GetNext())
//	{
//		b2AABB aabb;
//		fixture->GetShape()->ComputeAABB(&aabb, trans, 0);
//		if (fixture == first)
//			result = aabb;
//		else
//			result.Combine(aabb);
//	}
//
//	return result;
//}
//
///// Returns true if the given body overlaps any other body in the world.
//bool Scene::IsOverlap(const b2Body* body)
//{
//	CheckOverlapCallback callback(body);
//	m_world.QueryAABB(&callback, GetBodyAABB(body));
//	return callback.m_isOverlap;
//}
//when the main timer reach 0 ends the game
bool Scene::GameOver()
{
	if (m_gametimer <= 0)
	{
		return true;
	}
	return false;
}

//I would like to know who won the game
//at the end of the match create a function to calculate which player has more score
int Scene::WhoWon()
{
	if (player1score > player2score)
	{
		return 1;
	}
	else if (player2score > player1score)
	{
		return 2;
	}
	return 0;
}

//create the sprite for the different type of powerups
//create different powerups class for all types
//create a spawner location at a random location with a random chance of different powerup selected