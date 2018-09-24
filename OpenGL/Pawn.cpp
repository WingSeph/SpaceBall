#pragma once
#include "Pawn.h"
#include "Dependencies/glm/gtc/matrix_transform.hpp"

Pawn::Pawn()
{
}

Pawn::~Pawn()
{
}

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

	location = t_position;
	rotation = t_rotation;
	scale = t_scale;
}

void Pawn::Update(float t_deltaTime, glm::mat4 t_view, glm::mat4 t_projection, glm::vec3 t_cameraPos)
{
	rotation = m_physicsBody->GetAngle();
	location = glm::vec3(m_physicsBody->GetPosition().x, m_physicsBody->GetPosition().y, 0);
	//scale = 
	mesh->Update
	(
		t_projection,
		t_view,
		(
			glm::translate(glm::mat4(), location) *
			glm::rotate(glm::mat4(), glm::radians(rotation), glm::vec3(0, 0, 1)) *
			glm::scale(glm::mat4(), scale)
			),
		t_cameraPos
	);
}

void Pawn::Render()
{
	mesh->Render();
}

void Pawn::applyForce(glm::vec3 force)
{
	acceleration += force;
}

void Pawn::seek(glm::vec3 target)
{
	applyForce(limit((glm::normalize(target - location) * maxspeed) - velocity, maxforce));
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