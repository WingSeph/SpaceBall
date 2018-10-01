#pragma once

#include <ctime>
#include <cstdlib>

#include "Player.h"
#include "MeshCube.h"
#include "Utilities.h"

Player::Player()
{}

Player::~Player()
{}

void Player::Init(std::string t_filepath, glm::vec3 t_position, float t_rotation, glm::vec3 t_scale, GLuint& t_shader, b2World& t_world)
{
	m_mesh = std::make_unique<MeshCube>(t_filepath, t_shader);
	m_shield.Init("Resources/Textures/Player1Shield.png", t_position, t_rotation, t_scale, t_shader, false, COLLIDER_CIRCLE, t_world);
	Pawn::Init(t_filepath, t_position, t_rotation, t_scale, t_shader, false, COLLIDER_CIRCLE, t_world);

	SetTrigger(true);
}

void Player::Update(float t_deltaTime, glm::mat4 t_view, glm::mat4 t_projection, glm::vec3 t_cameraPos)
{
	float speed = 10.0f;
	MovementChecker();
	m_location = glm::vec3(m_physicsBody->GetPosition().x, m_physicsBody->GetPosition().y, 0);

	m_shield.Update(t_deltaTime, t_view, t_projection, t_cameraPos, m_physicsBody->GetAngle());

	Pawn::Update(t_deltaTime, t_view, t_projection, t_cameraPos);

	if (m_location.x <= 1.25f || m_location.x >= 18.76f || m_location.y >= 13.76f || m_location.y <= 1.25f)
	{
		Die();
	}
}

void Player::Render()
{
	Pawn::Render();

	m_shield.Render();
}

void Player::MovementChecker()
{
	m_physicsBody->SetLinearDamping(0.8f);
	m_physicsBody->SetAngularDamping(2.0f);

	//'w' = Up
	if (GetButtonDown('w'))
	{
		// Move forwards
		b2Vec2 direction = b2Vec2(0, 1);
		RotateVector(direction, m_fRotation);
		direction *= 10;
		m_physicsBody->ApplyForce(direction, m_physicsBody->GetWorldCenter(), true);
	}
	// 's' = Down
	if (GetButtonDown('s'))
	{
		// Move backwards
		b2Vec2 direction = b2Vec2(0, 1);
		RotateVector(direction, m_fRotation);
		direction.Normalize();
		direction *= 10;
		m_physicsBody->ApplyForce(-direction, m_physicsBody->GetWorldCenter(), true);
	}

	// 'a' = Left
	if (GetButtonDown('a'))
	{
		// Rotate left
		m_physicsBody->SetAngularVelocity(100);
	}

	// 'd' = Right
	else if (GetButtonDown('d'))
	{
		// Rotate right
		m_physicsBody->SetAngularVelocity(-100);
	}

	m_shield.GetBody()->SetTransform(m_physicsBody->GetPosition() + b2Vec2(1.0f, 0), -90);
}

void Player::Die()
{
	m_bIsDead = true;
	m_bCanRender = false;
	m_physicsBody->SetTransform(b2Vec2(6.0f, 6.0f), m_physicsBody->GetAngle());
	m_physicsBody->SetLinearVelocity(b2Vec2(0, 0));
	m_physicsBody->SetActive(false);

	m_shield.SetIsDead(true);
	m_shield.SetCanRender(false);
	m_shield.GetBody()->SetTransform(b2Vec2(12.0f, 6.0f), m_physicsBody->GetAngle());
	m_shield.GetBody()->SetLinearVelocity(b2Vec2(0, 0));
	m_shield.GetBody()->SetActive(false);
}

void Player::Respawn()
{
	m_bIsDead = false;
	m_bCanRender = true;
	m_physicsBody->SetActive(true);

	m_shield.SetIsDead(false);
	m_shield.SetCanRender(true);
	m_shield.GetBody()->SetActive(true);
}

void Player::OnCollisionEnter(Pawn* _other)
{
}