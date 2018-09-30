#pragma once
#include "Pawn.h"
#include "PlayerShield.h"

class Player : public Pawn
{
public:
	Player();
	~Player();
	virtual void Init(std::string t_filepath, glm::vec3 t_position, float t_rotation, glm::vec3 t_scale, GLuint& t_shader, bool t_isFixed, EColliderShape t_colliderShape, b2World& t_world);
	virtual void Update(float t_deltaTime, glm::mat4 t_view, glm::mat4 t_projection, glm::vec3 t_cameraPos);
	virtual void Render();
	void OnCollisionEnter(Pawn* _other);

	void MovementChecker();

	void Die();

private:
	CPlayerShield m_shield;
};
