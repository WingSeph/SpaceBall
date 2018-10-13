#pragma once
#include "Pawn.h"
#include "Dependencies/glm/vec3.hpp"
#include <string>
#include "Dependencies/glew/glew.h"
#include "TextLabel.h"

class Camera;

class BallSplit :
	public Pawn
{
public:
	BallSplit();
	~BallSplit();
	virtual void Init(std::string t_filepath, glm::vec3 t_position, float t_rotation, glm::vec3 t_scale, GLuint& t_shader, bool t_isFixed, EColliderShape t_colliderShape, b2World& t_world);
	virtual void Update(float t_deltaTime, glm::mat4 t_view, glm::mat4 t_projection, glm::vec3 t_cameraPos);
	virtual void Render();
	virtual void OnCollisionEnter(Pawn* _other) override;
	void checkgate(b2Vec2 _gate, int &playerscore);
	void Respawn();

	std::unique_ptr<TextLabel> timer;

	int maxlifetime;
	float m_deltaTime = 0;
	float m_previousTime = 0;
};
