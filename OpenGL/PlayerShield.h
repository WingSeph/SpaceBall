#ifndef __PLAYERSHIELD_H__
#define __PLAYERSHIELD_H__

#include "Pawn.h"

class CPlayerShield : public Pawn
{
public:
	CPlayerShield();
	~CPlayerShield();

	virtual void Init(std::string _filepath, glm::vec3 _position, float _rotation, glm::vec3 _scale, GLuint& _shader, bool _isFixed, EColliderShape _colliderShape, b2World& _world);
	virtual void Update(float _deltaTime, glm::mat4 _view, glm::mat4 _projection, glm::vec3 _cameraPos);
	virtual void Render();
	virtual void OnCollisionEnter(Pawn* _other);

private:

};

#endif // !__PLAYERSHIELD_H__
