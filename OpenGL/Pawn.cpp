#pragma once
#include "Pawn.h"
#include "Dependencies/glm/gtc/matrix_transform.hpp"

#include <iostream>

Pawn::Pawn()
{}

Pawn::~Pawn()
{}

void Pawn::Init(std::string t_filepath, glm::vec3 t_position, float t_rotation, glm::vec3 t_scale, GLuint & t_shader, bool t_isFixed, EColliderShape t_colliderShape, b2World& t_world)
{
	b2BodyDef bd;
	if (t_isFixed)
	{
		bd.type = b2_kinematicBody;
	}
	else
	{
		bd.type = b2_dynamicBody;
	}

	bd.position = b2Vec2(t_position.x, t_position.y);
	m_physicsBody = t_world.CreateBody(&bd);

	if (t_colliderShape == COLLIDER_CIRCLE)
	{
		m_colliderShape = t_colliderShape;
		b2CircleShape objectShape;
		objectShape.m_p.Set(0, 0);
		objectShape.m_radius = t_scale.x;
		b2FixtureDef fixtureDef;
		fixtureDef.shape = &objectShape;
		fixtureDef.density = 1.0f;
		fixtureDef.friction = 1000.0f;
		m_physicsBody->CreateFixture(&fixtureDef);
	}
	else if (t_colliderShape == COLLIDER_SQUARE)
	{
		m_colliderShape = t_colliderShape;
		b2PolygonShape objectShape;
		objectShape.SetAsBox(t_scale.x, t_scale.y);
		b2FixtureDef fixtureDef;
		fixtureDef.shape = &objectShape;
		fixtureDef.density = 1.0f;
		fixtureDef.friction = 1000.0f;
		m_physicsBody->CreateFixture(&fixtureDef);
	}

	m_physicsBody->SetFixedRotation(true);

	m_location = t_position;
	m_fRotation = t_rotation;
	m_scale = t_scale;
	m_sTag = "";

	m_physicsBody->SetUserData(this);
}

void Pawn::Update(float t_deltaTime, glm::mat4 t_view, glm::mat4 t_projection, glm::vec3 t_cameraPos)
{
	m_fRotation = m_physicsBody->GetAngle();
	m_location = glm::vec3(m_physicsBody->GetPosition().x, m_physicsBody->GetPosition().y, 0);
	//scale = 
	m_mesh->Update
	(
		t_projection,
		t_view,
		(
			glm::translate(glm::mat4(), m_location) *
			glm::rotate(glm::mat4(), glm::radians(m_fRotation), glm::vec3(0, 0, 1)) *
			glm::scale(glm::mat4(), m_scale)
			),
		t_cameraPos
	);
}

void Pawn::Render()
{
	if (m_bCanRender)
	{
		m_mesh->Render();
	}
}

void Pawn::applyForce(glm::vec3 force)
{
	m_acceleration += force;
}

void Pawn::seek(glm::vec3 target)
{
	applyForce(limit((glm::normalize(target - m_location) * m_maxspeed) - m_velocity, m_maxforce));
}

glm::vec3 Pawn::limit(glm::vec3 vec, float max)
{
	float magSq = glm::length(vec) * glm::length(vec);

	if (magSq > max * max)
	{
		if (vec != glm::vec3())
		{
			vec = glm::normalize(vec);
		}
		vec *= max;
	}
	return vec;
}

b2Body* Pawn::GetBody()
{
	return(m_physicsBody);
}

void Pawn::OnCollisionEnter(Pawn* _other)
{
	std::cout << "Collision hit" << std::endl;
}

bool Pawn::IsDead()
{
	return(m_bIsDead);
}