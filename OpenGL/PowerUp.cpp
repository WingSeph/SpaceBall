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
	m_mesh = std::make_unique<Mesh>(t_filepath, t_shader);
	Pawn::Init(t_filepath, t_position, t_rotation, t_scale, t_shader, t_isFixed, t_colliderShape, t_world);

	lifespan = 3.0f;
	lifetimer = 0.0f;
	isactive = false;
}

void PowerUp::Update(float t_deltaTime, glm::mat4 t_view, glm::mat4 t_projection, glm::vec3 t_cameraPos)
{
	m_location = glm::vec3(m_physicsBody->GetPosition().x, m_physicsBody->GetPosition().y, 0);

	lifetimer = isactive ? lifetimer -= t_deltaTime : lifetimer += t_deltaTime;
	isactive = lifetimer <= 0 ? false : lifetimer > lifespan ? true : isactive;

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