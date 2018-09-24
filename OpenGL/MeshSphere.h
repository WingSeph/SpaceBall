#pragma once
#include "Mesh.h"
class MeshSphere :
	public Mesh
{
public:
	MeshSphere();
	MeshSphere(std::string t_filepath, GLuint& t_shader);
	~MeshSphere();
	virtual void Init();
	virtual void Update(glm::mat4 t_model, glm::mat4 t_view, glm::mat4 t_projection, glm::vec3 t_cameraPos);
	virtual void Render();
};

