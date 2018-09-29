#include "PlayerShield.h"
#include "MeshCube.h"
#include "Utilities.h"

CPlayerShield::CPlayerShield()
{}

CPlayerShield::~CPlayerShield()
{}

void CPlayerShield::Init(std::string _filepath, glm::vec3 _position, float _rotation, glm::vec3 _scale, GLuint& _shader, bool _isFixed, EColliderShape _colliderShape, b2World& _world)
{
	m_mesh = std::make_unique<MeshCube>(_filepath, _shader);
	Pawn::Init(_filepath, _position, _rotation, _scale, _shader, _isFixed, _colliderShape, _world);
	m_sTag = "Shield";
}

void CPlayerShield::Update(float _deltaTime, glm::mat4 _view, glm::mat4 _projection, glm::vec3 _cameraPos)
{
	m_physicsBody->SetTransform(b2Vec2(m_location.x, m_location.y), m_fRotation);
	Pawn::Update(_deltaTime, _view, _projection, _cameraPos);
}

void CPlayerShield::Render()
{
	Pawn::Render();
}

void CPlayerShield::OnCollisionEnter(Pawn* _other)
{

}