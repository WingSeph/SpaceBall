#pragma once
#include "Pawn.h"
#include "Player.h"
#include "Player2.h"

class PowerUp : public Pawn
{
public:
	PowerUp();
	~PowerUp();
	virtual void Init(std::string t_filepath, glm::vec3 t_position, float t_rotation, glm::vec3 t_scale, GLuint& t_shader, bool t_isFixed, EColliderShape t_colliderShape, b2World& t_world, int _type);
	virtual void Update(float t_deltaTime, glm::mat4 t_view, glm::mat4 t_projection, glm::vec3 t_cameraPos);
	virtual void Render();

	bool CheckCollisionOnplayer(b2Body* _player);
	bool isactive;
	int type;

protected:
	float lifespan;
	float lifetimer;
	GLuint m_shader;

	glm::vec2 spawnpoint;
};
