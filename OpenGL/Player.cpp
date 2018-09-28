#pragma once
#include "Player.h"
#include "MeshCube.h"
#include "Utilities.h"

Player::Player()
{
}

Player::~Player()
{
}

void Player::Init(std::string t_filepath, glm::vec3 t_position, float t_rotation, glm::vec3 t_scale, GLuint& t_shader, bool t_isFixed, EColliderShape t_colliderShape, b2World& t_world)
{
	mesh = std::make_unique<MeshCube>(t_filepath, t_shader);
	Pawn::Init(t_filepath, t_position, t_rotation, t_scale, t_shader, t_isFixed, t_colliderShape, t_world);
}

void Player::Update(float t_deltaTime, glm::mat4 t_view, glm::mat4 t_projection, glm::vec3 t_cameraPos)
{
	float speed = 10.0f;
	MovementChecker();
	location = glm::vec3(m_physicsBody->GetPosition().x, m_physicsBody->GetPosition().y, 0);

	Pawn::Update(t_deltaTime, t_view, t_projection, t_cameraPos);
}

void Player::Render()
{
	Pawn::Render();
}


void Player::MovementChecker()
{
	m_physicsBody->SetLinearDamping(0.5f);
	m_physicsBody->SetAngularDamping(1.0f);

	//'w' = Up
	if (GetButtonDown('w'))
	{
		// Move forwards
		b2Vec2 direction = b2Vec2(0, 1);
		RotateVector(direction, rotation);
		direction *= 20;
		m_physicsBody->ApplyForce(direction, m_physicsBody->GetWorldCenter(), true);
	}
	// 's' = Down
	if (GetButtonDown('s'))
	{
		// Move backwards
		b2Vec2 direction = b2Vec2(0, 1);
		RotateVector(direction, rotation);
		direction.Normalize();
		direction *= 20;
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
}

void Player::OnCollisionEnter(Pawn* _other)
{

}