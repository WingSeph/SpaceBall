#pragma once
#include "Pawn.h"
#include "Input.h"

class Player : public Pawn, CInput
{
public:
	Player();
	~Player();
	virtual void Init(std::string t_filepath, glm::vec3 t_position, float t_rotation, glm::vec3 t_scale, GLuint& t_shader, b2World& t_world);
	virtual void Update(float t_deltaTime, glm::mat4 t_view, glm::mat4 t_projection, glm::vec3 t_cameraPos);
	virtual void Render();
	void OnCollisionEnter(Pawn* _other);
	void Respawn();
	void MovementChecker();

	float GetMoveSpeed();
	void SetMoveSpeed(float _fMoveSpeed);

	void Die();

private:
	float m_fMoveSpeed;
};
