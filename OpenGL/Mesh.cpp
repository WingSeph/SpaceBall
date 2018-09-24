#pragma once
#include "Mesh.h"
#include "Camera.h"
#include "Dependencies/glm/gtc/matrix_transform.hpp"
#include "Dependencies/glm/gtc/type_ptr.hpp"
#include "Dependencies/soil/SOIL.h"
#define _USE_MATH_DEFINES
#include <math.h>

Mesh::Mesh()
{
}

Mesh::Mesh(std::string t_filepath, GLuint& t_shader)
	: filePath(t_filepath), shader(t_shader)
{
	Init();
}

Mesh::~Mesh()
{
}

void Mesh::Init()
{
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
	int width, height;
	unsigned char* image = SOIL_load_image(
		filePath.c_str(),
		&width,
		&height,
		0,
		SOIL_LOAD_RGBA);
	glTexImage2D(
		GL_TEXTURE_2D,
		0,
		GL_RGBA,
		width,
		height,
		0,
		GL_RGBA,
		GL_UNSIGNED_BYTE,
		image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	GLfloat vertices[] =
	{
		// Front Face
		-1.0f, 1.0f, 1.0f,		1.0f, 1.0f, 1.0f,	0.0f, 0.0f,
		1.0f, 1.0f, 1.0f,		1.0f, 1.0f, 0.0f,	1.0f, 0.0f,
		1.0f, -1.0f, 1.0f,		0.0f, 1.0f, 1.0f,	1.0f, 1.0f,
		-1.0f, -1.0f, 1.0f,		1.0f, 0.0f, 1.0f,	0.0f, 1.0f,

		// Right Face
		1.0f, 1.0f, 1.0f,		1.0f, 1.0f, 0.0f,	0.0f, 0.0f,
		1.0f, 1.0f, -1.0f,		0.0f, 1.0f, 0.0f,	1.0f, 0.0f,
		1.0f, -1.0f, -1.0f,		0.0f, 0.0f, 0.0f,	1.0f, 1.0f,
		1.0f, -1.0f, 1.0f,		0.0f, 1.0f, 1.0f,	0.0f, 1.0f,

		// Back Face
		1.0f, 1.0f, -1.0f,		0.0f, 1.0f, 0.0f,	0.0f, 0.0f,
		-1.0f, 1.0f, -1.0f,		1.0f, 0.0f, 0.0f,	1.0f, 0.0f,
		-1.0f, -1.0f, -1.0f,	0.0f, 0.0f, 1.0f,	1.0f, 1.0f,
		1.0f, -1.0f, -1.0f,		0.0f, 0.0f, 0.0f,	0.0f, 1.0f,

		// Left Face
		-1.0f, 1.0f, -1.0f,		1.0f, 0.0f, 0.0f,	0.0f, 0.0f,
		-1.0f, 1.0f, 1.0f,		1.0f, 1.0f, 1.0f,	1.0f, 0.0f,
		-1.0f, -1.0f, 1.0f,		1.0f, 0.0f, 1.0f,	1.0f, 1.0f,
		-1.0f, -1.0f, -1.0f,	0.0f, 0.0f, 1.0f,	0.0f, 1.0f,

		// Top Face
		-1.0f, 1.0f, -1.0f,		1.0f, 0.0f, 0.0f,	0.0f, 0.0f,
		1.0f, 1.0f, -1.0f,		0.0f, 1.0f, 0.0f,	1.0f, 0.0f,
		1.0f, 1.0f, 1.0f,		1.0f, 1.0f, 0.0f,	1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,		1.0f, 1.0f, 1.0f,	0.0f, 1.0f,

		// Bottom Face
		-1.0f, -1.0f, 1.0f,		1.0f, 0.0f, 1.0f,	0.0f, 0.0f,
		1.0f, -1.0f, 1.0f,		0.0f, 1.0f, 1.0f,	1.0f, 0.0f,
		1.0f, -1.0f, -1.0f,		0.0f, 0.0f, 0.0f,	1.0f, 1.0f,
		-1.0f, -1.0f, -1.0f,	0.0f, 0.0f, 1.0f,	0.0f, 1.0f,
	};

	GLuint indices[] = {
		// Front Face
		0, 1, 2,
		0, 2, 3,

		// Right Face
		4, 5, 6,
		4, 6, 7,

		// Back Face
		8, 9, 10,
		8, 10, 11,

		// Left Face
		12, 13, 14,
		12, 14, 15,

		// Top Face
		16, 17, 18,
		16, 18, 19,

		// Bottom Face
		20, 21, 22,
		20, 22, 23,
	};

	index = sizeof(vertices) / sizeof(GLuint);
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glVertexAttribPointer(
		0,
		3,
		GL_FLOAT,
		GL_FALSE,
		8 * sizeof(GLfloat),
		(GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(
		1,
		3,
		GL_FLOAT,
		GL_FALSE,
		8 * sizeof(GLfloat),
		(GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(
		2,
		2,
		GL_FLOAT,
		GL_FALSE,
		8 * sizeof(GLfloat),
		(GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
}

void Mesh::Update(glm::mat4 t_model, glm::mat4 t_view, glm::mat4 t_projection, glm::vec3 t_cameraPos)
{
	model = t_model;
	view = t_view;
	projection = t_projection;
	cameraPos = t_cameraPos;
	mvp = model * view * projection;
}

void Mesh::Render()
{
	glUseProgram(shader);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex);
	glUniform1i(glGetUniformLocation(shader, "tex"), 0);

	GLint MVP = glGetUniformLocation(shader, "mvp");
	glUniformMatrix4fv(MVP, 1, GL_FALSE, glm::value_ptr(mvp));

	glCullFace(GL_BACK);
	glFrontFace(GL_CW);
	glEnable(GL_CULL_FACE);

	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, index, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}