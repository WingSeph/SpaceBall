#pragma once

#include <memory>
#include "Mesh.h"
#include "Utilities.h"

enum EColliderShape
{
	COLLIDER_SQUARE = 1,
	COLLIDER_CIRCLE = 2
};

class Pawn
{
public:
	Pawn();
	~Pawn();
	virtual void Init(std::string t_filepath, glm::vec3 t_position, float t_rotation, glm::vec3 t_scale, GLuint & t_shader, bool _isFixed, EColliderShape t_colliderShape, b2World& t_world);
	virtual void Update(float t_deltaTime, glm::mat4 t_view, glm::mat4 t_projection, glm::vec3 t_cameraPos);
	virtual void Render();

	void applyForce(glm::vec3 force);
	glm::vec3 limit(glm::vec3 vec, float max);
	void seek(glm::vec3 target);

	glm::vec3 GetLocation() { return location; }
	void SetLocation(glm::vec3 t_location) { location = t_location; }

	float GetRotation() { return rotation; }
	void SetRotation(float t_rotation) { rotation = t_rotation; }

	glm::vec3 GetScale() { return scale; }
	void SetScale(glm::vec3 t_scale) { scale = t_scale; }

	b2Body* GetBody();

protected:
	std::unique_ptr<Mesh>
		mesh;

	glm::vec3
		location,
		scale;
	float
		rotation;

	glm::vec3 velocity;
	glm::vec3 acceleration;

	float r;
	float maxforce;
	float maxspeed;

	b2Body* m_physicsBody;

	EColliderShape m_colliderShape;
};
