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
	m_bIsFixed = t_isFixed;

	b2BodyDef bd;
	bd.type = b2_dynamicBody;

	bd.position = b2Vec2(t_position.x, t_position.y);
	m_physicsBody = t_world.CreateBody(&bd);

	m_location = t_position;
	m_fRotation = t_rotation;
	m_scale = t_scale;
	m_sTag = "";

	m_physicsBody->SetUserData(this);
}

void Effect::Update(float t_deltaTime, glm::mat4 t_view, glm::mat4 t_projection, glm::vec3 t_cameraPos)
{
	duration = duration - t_deltaTime;
	SetRotation(GetRotation() + (t_deltaTime * 500));
	SetScale(m_scale + (t_deltaTime * .3f));
	Pawn::Update(t_deltaTime, t_view, t_projection, t_cameraPos);
}

void Effect::Render()
{
	Pawn::Render();
}