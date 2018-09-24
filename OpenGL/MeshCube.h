#pragma once
#include "Mesh.h"
class MeshCube :
	public Mesh
{
public:
	MeshCube();
	MeshCube(std::string t_filepath, GLuint& t_shader);
	~MeshCube();
	virtual void Init();
	virtual void Update(glm::mat4 t_model, glm::mat4 t_view, glm::mat4 t_projection, glm::vec3 t_cameraPos);
	virtual void Render();
};

