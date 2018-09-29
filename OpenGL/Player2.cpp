#pragma once
#include "Player2.h"
#include "MeshCube.h"
#include "Utilities.h"

Player2::Player2()
{}

Player2::~Player2()
{}

void Player2::Init(std::string t_filepath, glm::vec3 t_position, float t_rotation, glm::vec3 t_scale, GLuint& t_shader, bool t_isFixed, EColliderShape t_colliderShape, b2World& t_world)
{
	m_mesh = std::make_unique<MeshCube>(t_filepath, t_shader);
	m_shield.Init("Resources/Textures/Player2Shield.png", t_position, t_rotation, t_scale, t_shader, t_isFixed, COLLIDER_CIRCLE, t_world);
	Pawn::Init(t_filepath, t_position, t_rotation, t_scale, t_shader, t_isFixed, t_colliderShape, t_world);
}

void Player2::Update(float t_deltaTime, glm::mat4 t_view, glm::mat4 t_projection, glm::vec3 t_cameraPos)
{
	float speed = 10.0f;
	MovementChecker();
	m_location = glm::vec3(m_physicsBody->GetPosition().x, m_physicsBody->GetPosition().y, 0);

	m_shield.Update(t_deltaTime, t_view, t_projection, t_cameraPos);
	
	Pawn::Update(t_deltaTime, t_view, t_projection, t_cameraPos);
}

void Player2::Render()
{
	Pawn::Render();

	m_shield.Render();
}

void Player2::MovementChecker()
{
	m_physicsBody->SetLinearDamping(0.5f);
	m_physicsBody->SetAngularDamping(1.0f);

	//'w' = Up
	if (GetButtonDown('i'))
	{
		// Move forwards
		b2Vec2 direction = b2Vec2(0, 1);
		RotateVector(direction, m_fRotation);
		direction *= 20;
		m_physicsBody->ApplyForce(direction, m_physicsBody->GetWorldCenter(), true);
	}
	// 's' = Down
	if (GetButtonDown('k'))
	{
		// Move backwards
		b2Vec2 direction = b2Vec2(0, 1);
		RotateVector(direction, m_fRotation);
		direction.Normalize();
		direction *= 20;
		m_physicsBody->ApplyForce(-direction, m_physicsBody->GetWorldCenter(), true);
	}

	// 'a' = Left
	if (GetButtonDown('j'))
	{
		// Rotate left
		m_physicsBody->SetAngularVelocity(100);
	}

	// 'd' = Right
	else if (GetButtonDown('l'))
	{
		// Rotate right
		m_physicsBody->SetAngularVelocity(-100);
	}

	m_shield.SetLocation(m_location);
}

void Player2::OnCollisionEnter(Pawn* _other)
{

}