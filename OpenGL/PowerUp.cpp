#include "PowerUp.h"
#include <iostream>

PowerUp::PowerUp()
{
}

PowerUp::~PowerUp()
{
}

void PowerUp::Init(std::string t_filepath, glm::vec3 t_position, float t_rotation, glm::vec3 t_scale, GLuint& t_shader, bool t_isFixed, EColliderShape t_colliderShape, b2World& t_world)
{
	mesh = std::make_unique<Mesh>(t_filepath, t_shader);
	Pawn::Init(t_filepath, t_position, t_rotation, t_scale, t_shader, t_isFixed, t_colliderShape, t_world);

	lifespan = 3.0f;
	lifetimer = lifespan;
	isactive = true;
}

void PowerUp::Update(float t_deltaTime, glm::mat4 t_view, glm::mat4 t_projection, glm::vec3 t_cameraPos)
{
	float speed = 10.0f;
	GetDeltaPosition(m_physicsBody, rotation);
	location = glm::vec3(m_physicsBody->GetPosition().x, m_physicsBody->GetPosition().y, 0);

	if (isactive)
	{
		lifetimer -= t_deltaTime;


		//if collision
		//*destroy
		//*player gets powerup

	}
	if (isactive == false)
	{
		lifetimer += t_deltaTime;

		//powerup has no collisionboxes
	}

	if (lifetimer <= 0)
	{
		isactive = false;

		//m_physicsBody->DestroyFixture();
	}
	if (lifetimer > lifespan)
	{
		isactive = true;

		/*b2PolygonShape objectShape;
		objectShape.SetAsBox(scale.x, scale.y);
		b2FixtureDef fixtureDef;
		fixtureDef.shape = &objectShape;
		fixtureDef.density = 1.0f;
		fixtureDef.friction = 1000.0f;
		m_physicsBody->CreateFixture(&fixtureDef);*/
	}



	std::cout << lifetimer << "\n";
	
	
	
	
	Pawn::Update(t_deltaTime, t_view, t_projection, t_cameraPos);
}

void PowerUp::Render()
{
	if (isactive)
	{
		Pawn::Render();
	}
	
}