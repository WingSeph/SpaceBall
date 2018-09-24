#pragma once
#include "MeshPyramid.h"
#include "Dependencies/soil/SOIL.h"

MeshPyramid::MeshPyramid()
{
}

MeshPyramid::MeshPyramid(std::string t_filepath, GLuint& t_shader)
	: Mesh(t_filepath, t_shader)
{
	Init();
}

MeshPyramid::~MeshPyramid()
{
}

void MeshPyramid::Init()
{
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
	int width, height;
	unsigned char* image = SOIL_load_image(
		filePath.c_str(),
		&width,
		&height,
		0,
		SOIL_LOAD_RGB);
	glTexImage2D(
		GL_TEXTURE_2D,
		0,
		GL_RGB,
		width,
		height,
		0,
		GL_RGB,
		GL_UNSIGNED_BYTE,
		image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	GLfloat vertices[] =
	{
		-1.0f, 0.0f, -1.0f,		1.0f, 1.0f, 0.0f,		0.0f, 1.0f, // 0 // Base
		1.0f, 0.0f, -1.0f,		1.0f, 0.0f, 0.0f,		1.0f, 1.0f, // 1
		1.0f, 0.0f, 1.0f,		0.0f, 1.0f, 0.0f,		1.0f, 0.0f, // 2
		-1.0f, 0.0f, 1.0f,		0.0f, 0.0f, 1.0f,		0.0f, 0.0f, // 3

		-1.0f, 0.0f, -1.0f,		1.0f, 1.0f, 0.0f,		0.0f, 1.0f, // 4 // Side 1
		-1.0f, 0.0f, 1.0f,		0.0f, 0.0f, 1.0f,		1.0f, 1.0f, // 5

		-1.0f, 0.0f, 1.0f,		0.0f, 0.0f, 1.0f,		0.0f, 1.0f, // 6 // Side 2
		1.0f, 0.0f, 1.0f,		0.0f, 1.0f, 0.0f,		1.0f, 1.0f, // 7

		1.0f, 0.0f, 1.0f,		0.0f, 1.0f, 0.0f,		0.0f, 1.0f, // 8 // Side 3
		1.0f, 0.0f, -1.0f,		1.0f, 0.0f, 0.0f,		1.0f, 1.0f, // 9

		1.0f, 0.0f, -1.0f,		1.0f, 0.0f, 0.0f,		0.0f, 1.0f, // 10 // Side 4
		-1.0f, 0.0f, -1.0f,		1.0f, 1.0f, 0.0f,		1.0f, 1.0f, // 11

		0.0f, 1.0f, 0.0f,		0.0f, 1.0f, 1.0f,		0.5f, 0.0f, // 12 // Top Point
	};

	GLuint indices[] = {
		4, 12, 5, // Side 1
		6, 12, 7, // Side 2
		8, 12, 9, // Side 3
		10, 12, 11, // Side 4

		3, 2, 1, // Bottom Triangle 1
		3, 1, 0, // Bottom Triangle 2
	};
	index = sizeof(indices) / sizeof(GLuint);
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

void MeshPyramid::Update(glm::mat4 t_model, glm::mat4 t_view, glm::mat4 t_projection, glm::vec3 t_cameraPos)
{
	Mesh::Update(t_model, t_view, t_projection, t_cameraPos);
}

void MeshPyramid::Render()
{
	Mesh::Render();
}