#pragma once
#include "Ball.h"
#include "MeshCube.h"
#include <iostream>

Ball::Ball()
{}

Ball::~Ball()
{}



void Ball::Init(std::string t_filepath, glm::vec3 t_position, float t_rotation, glm::vec3 t_scale, GLuint& t_shader, bool t_isFixed, EColliderShape t_colliderShape, b2World& t_world)
{
	m_mesh = std::make_unique<MeshCube>(t_filepath, t_shader);
	Pawn::Init(t_filepath, t_position, t_rotation, t_scale, t_shader, t_isFixed, t_colliderShape, t_world);

	m_physicsBody->GetFixtureList()->SetRestitution(0.8);

	m_sTag = "Ball";
}

void Ball::Update(float t_deltaTime, glm::mat4 t_view, glm::mat4 t_projection, glm::vec3 t_cameraPos)
{
	Pawn::Update(t_deltaTime, t_view, t_projection, t_cameraPos);
}

void Ball::Render()
{
	Pawn::Render();
}

void Ball::OnCollisionEnter(Pawn* _other) {

		std::cout << "hit";
	
}

void Ball::checkgate(b2Vec2 _gate, int &playerscore) {
	if (b2Distance(m_physicsBody->GetWorldCenter(), _gate) < 2) {
		playerscore++;
		m_bIsDead = true;
		m_bCanRender = false;
		m_physicsBody->SetTransform(b2Vec2(10.0f, 8.0f), m_physicsBody->GetAngle());
		m_physicsBody->SetLinearVelocity(b2Vec2(0, 0));
		m_physicsBody->SetActive(false);
	}
}

void Ball::Respawn() {
	m_bIsDead = false;
	m_bCanRender = true;
	m_physicsBody->SetActive(true);
}