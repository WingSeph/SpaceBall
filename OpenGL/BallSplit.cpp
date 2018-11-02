#pragma once
#include "BallSplit.h"
#include "MeshCube.h"
#include <iostream>
#include "Dependencies/freeglut/freeglut.h"

BallSplit::BallSplit()
{}

BallSplit::~BallSplit()
{
}



void BallSplit::Init(std::string t_filepath, glm::vec3 t_position, float t_rotation, glm::vec3 t_scale, GLuint& t_shader, bool t_isFixed, EColliderShape t_colliderShape, b2World& t_world)
{
	m_mesh = std::make_unique<MeshCube>(t_filepath, t_shader);
	Pawn::Init(t_filepath, t_position, t_rotation, t_scale, t_shader, t_isFixed, t_colliderShape, t_world);

	m_physicsBody->GetFixtureList()->SetRestitution(1.0f);
	m_physicsBody->SetLinearDamping(0);
	m_physicsBody->SetAngularDamping(0);
	m_physicsBody->GetFixtureList()->SetFriction(0);
	m_physicsBody->SetBullet(true);

	m_sTag = "Ball";

	m_physicsBody->SetLinearVelocity(b2Vec2(10, 10));

	maxlifetime = 10;

	timer = std::make_unique<TextLabel>("timer", "Resources/Fonts/arial.ttf", glm::vec2(t_position.x, t_position.y), glm::vec3(1, 1, 1));
}

void BallSplit::Update(float t_deltaTime, glm::mat4 t_view, glm::mat4 t_projection, glm::vec3 t_cameraPos)
{
	if (m_physicsBody->GetPosition().y > 15.25f)
	{
		m_physicsBody->SetTransform(b2Vec2(m_physicsBody->GetPosition().x, 0), m_physicsBody->GetAngle());
	}
	else if (m_physicsBody->GetPosition().y < 0)
	{
		m_physicsBody->SetTransform(b2Vec2(m_physicsBody->GetPosition().x, 15.25f), m_physicsBody->GetAngle());
	}

	if (m_physicsBody->GetPosition().x > 20)
	{
		m_physicsBody->SetTransform(b2Vec2(0, m_physicsBody->GetPosition().y), m_physicsBody->GetAngle());
	}
	else if (m_physicsBody->GetPosition().x < 0)
	{
		m_physicsBody->SetTransform(b2Vec2(20, m_physicsBody->GetPosition().y), m_physicsBody->GetAngle());
	}



	maxlifetime = maxlifetime - 1 * t_deltaTime;


	/*timer->SetPosition(glm::vec2(m_physicsBody->GetWorldPoint(m_physicsBody->GetLocalCenter()).x, m_physicsBody->GetWorldPoint(m_physicsBody->GetLocalCenter()).y));
	timer->SetText(std::to_string(maxlifetime));*/
	Pawn::Update(t_deltaTime, t_view, t_projection, t_cameraPos);
}

void BallSplit::Render()
{
	Pawn::Render();
	//timer->Render();
}

void BallSplit::OnCollisionEnter(Pawn* _other)
{
	while (m_physicsBody->GetLinearVelocity().Length() < 10)
	{
		m_physicsBody->SetLinearVelocity(b2Vec2(m_physicsBody->GetLinearVelocity().x + 1, m_physicsBody->GetLinearVelocity().y + 1));
	}
}

void BallSplit::checkgate(b2Vec2 _gate, int &playerscore) {
	if (b2Distance(m_physicsBody->GetWorldCenter(), _gate) < 2) {
		playerscore++;
		m_bIsDead = true;
		m_bCanRender = false;
		m_physicsBody->SetTransform(b2Vec2(10.0f, 8.0f), m_physicsBody->GetAngle());
		m_physicsBody->SetLinearVelocity(b2Vec2(10, 10));
		m_physicsBody->SetActive(false);
	}
}

void BallSplit::Respawn() {
	m_bIsDead = false;
	m_bCanRender = true;
	m_physicsBody->SetActive(true);
}