#pragma once
#include "Dependencies/glm/vec3.hpp"
#include "Dependencies/glm/mat4x4.hpp"
#include <string>
#include "Dependencies/glew/glew.h"

class Camera;

class Mesh
{
public:
	Mesh();
	Mesh(std::string t_filepath, GLuint& t_shader);
	~Mesh();
	virtual void Init();
	virtual void Update(glm::mat4 t_model, glm::mat4 t_view, glm::mat4 t_projection, glm::vec3 t_cameraPos);
	virtual void Render();

protected:
	std::string
		filePath;
	GLuint
		vbo,
		vao,
		ebo,
		tex,
		index,
		shader;
	glm::mat4
		model,
		view,
		projection,
		mvp;
	glm::vec3
		cameraPos;
};
