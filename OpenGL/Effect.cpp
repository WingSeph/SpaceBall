#include "Effect.h"
#include "MeshCube.h"

Effect::Effect()
{
	duration = 3.0f;
}

Effect::~Effect()
{
}

void Effect::Init(std::string t_filepath, glm::vec3 t_position, float t_rotation, glm::vec3 t_scale, GLuint & t_shader, bool t_isFixed, EColliderShape t_colliderShape, b2World & t_world)
{
	m_mesh = std::make_unique<MeshCube>(t_filepath, t_shader);
	Pawn::Init(t_filepath, t_position, t_rotation, t_scale, t_shader, t_isFixed, t_colliderShape, t_world);
}

void Effect::Update(float t_deltaTime, glm::mat4 t_view, glm::mat4 t_projection, glm::vec3 t_cameraPos)
{
	duration = duration - t_deltaTime;
	SetRotation(GetRotation() + (t_deltaTime * 500));
	Pawn::Update(t_deltaTime, t_view, t_projection, t_cameraPos);
}

void Effect::Render()
{
	Pawn::Render();
}