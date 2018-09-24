#pragma once
#include "Pawn.h"

#include "Dependencies/glm/vec3.hpp"
#include <string>
#include "Dependencies/glew/glew.h"

class Camera;

class Ball :
	public Pawn
{
public:
	Ball();
	~Ball();
	virtual void Init(std::string t_filepath, glm::vec3 t_position, float t_rotation, glm::vec3 t_scale, GLuint& t_shader, bool t_isFixed, EColliderShape t_colliderShape, b2World& t_world);
	virtual void Update(float t_deltaTime, glm::mat4 t_view, glm::mat4 t_projection, glm::vec3 t_cameraPos);
	virtual void Render();
};
