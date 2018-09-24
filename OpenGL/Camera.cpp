#pragma once
#include "Camera.h"
#include "Dependencies/glm/gtc/matrix_transform.hpp"
#include "Utilities.h"

Camera::Camera()
{
	location =
		glm::vec3(0.0f, 0.0f, 3.0f);
	facing =
		glm::vec3(0.0f, 0.0f, 2.0f);
	up =
		glm::vec3(0.0f, 1.0f, 0.0f);

	view =
		glm::lookAt(
			location,
			facing,
			up);

	projection = glm::ortho(0.0f, static_cast<float>(WINDOW_WIDTH) / 40, 0.0f, static_cast<float>(WINDOW_HEIGHT) / 40, 0.1f, 100.0f);
}

Camera::~Camera()
{
}