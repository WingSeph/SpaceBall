#include "PowerUp.h"
//#include <iostream>

PowerUp::PowerUp()
{
}

PowerUp::~PowerUp()
{
}

void PowerUp::Init(std::string t_filepath, glm::vec3 t_position, float t_rotation, glm::vec3 t_scale, GLuint& t_shader, bool t_isFixed, EColliderShape t_colliderShape, b2World& t_world)
{
	m_mesh = std::make_unique<Mesh>(t_filepath, t_shader);
	Pawn::Init(t_filepath, t_position, t_rotation, t_scale, t_shader, t_isFixed, t_colliderShape, t_world);

	lifespan = 3.0f;
	lifetimer = 0.0f;
	isactive = false;

	m_physicsBody->SetActive(false);
}

void PowerUp::Update(float t_deltaTime, glm::mat4 t_view, glm::mat4 t_projection, glm::vec3 t_cameraPos)
{
	m_location = glm::vec3(m_physicsBody->GetPosition().x, m_physicsBody->GetPosition().y, 0);

	lifetimer = isactive ? lifetimer -= t_deltaTime : lifetimer += t_deltaTime;
	if (lifetimer <= 0)
	{
		m_physicsBody->SetTransform(b2Vec2(rand() % 18 + 1, rand() % 13 + 1), m_physicsBody->GetAngle());
	}
	isactive = lifetimer <= 0 ? false : lifetimer > lifespan ? true : isactive;
	
	Pawn::Update(t_deltaTime, t_view, t_projection, t_cameraPos);
}

void PowerUp::Render()
{
	if (isactive)
	{
		Pawn::Render();
	}



}

void PowerUp::OnCollisionEnter(Pawn * _other)
{
	//powerup disappears
	m_bIsDead = true;

	//otherpawn gets powerup
	_other->SetPowerUp(true, POWERUP1);
}

/*
	float PowerUpFactor;

	switch (m_PowerUpType)
	{
	case POWERUP1:
		//speed up player
		PowerUpFactor = 1.5f;
		break;

	case POWERUP2:
		//slow down opponent
		PowerUpFactor = 0.5f;
		break;

	case POWERUP3:
		//spawn ball at ball's origin & reverse velocity
		PowerUpFactor = 0.5f;
		break;

	case POWERUP4:
		//Sticky shield that can catch balls and shoot them in a chosen direction.
		if player 
		break;

	case POWERUP5:
		//Invincibility
		//player will not die
		break;

	case POWERUP6:
		//Bomb pick up that can be dropped that will push back the player who hits it.
		//bomb placed in front of players' shield
		break;

	default:
		PowerUpFactor = 1.0f;
		break;
	}

void Player::MovementChecker()
{
	direction *= 20 * PowerUpFactor;
	m_physicsBody->ApplyForce(direction, m_physicsBody->GetWorldCenter(), true);
}


*/