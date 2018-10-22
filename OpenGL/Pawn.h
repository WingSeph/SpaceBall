#pragma once

#include <memory>
#include "Mesh.h"
#include "Utilities.h"

enum EColliderShape
{
	COLLIDER_SQUARE = 1,
	COLLIDER_CIRCLE = 2
};

enum PowerUpType
{
	POWERUP1,
	POWERUP2,
	POWERUP3
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

	glm::vec3 GetLocation() { return m_location; }
	void SetLocation(glm::vec3 t_location) { m_location = t_location; }

	float GetRotation() { return m_fRotation; }
	void SetRotation(float t_rotation) { m_fRotation = t_rotation; }

	glm::vec3 GetScale() { return m_scale; }
	void SetScale(glm::vec3 t_scale) { m_scale = t_scale; }

	b2Body* GetBody();

	void startContact() { m_bIsContacting = true; }
	void endContact() { m_bIsContacting = false; }

	virtual void OnCollisionEnter(Pawn* _other);

	bool IsDead();
	bool HasPowerUp() { return m_bHasPowerUp; }
	void SetPowerUp(bool t_bHasPowerUp, PowerUpType t_poweruptype);

	void SetTrigger(bool _b);

	std::string GetTag() { return m_sTag; }
	void SetTag(std::string _sTag) { m_sTag = _sTag; }

	void SetIsDead(bool _b) { m_bIsDead = _b; }
	void SetCanRender(bool _b) { m_bCanRender = _b; }

protected:
	std::unique_ptr<Mesh> m_mesh;

	glm::vec3 m_location, m_scale;
	float m_fRotation;

	glm::vec3 m_velocity;
	glm::vec3 m_acceleration;

	float m_r;
	float m_maxforce;
	float m_maxspeed;

	b2Body* m_physicsBody;

	EColliderShape m_colliderShape;

	bool m_bIsContacting = false;
	bool m_bIsDead = false;
	bool m_bCanRender = true;
	bool m_bIsFixed;
	bool m_bHasPowerUp = false;
	std::string m_sTag;

	PowerUpType m_PowerUpType;
};
