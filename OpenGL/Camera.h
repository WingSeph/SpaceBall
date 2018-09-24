#pragma once

#include "Dependencies/glm/vec3.hpp"
#include "Dependencies/glm/mat4x4.hpp"

class Camera
{
public:
	Camera();
	~Camera();
	glm::mat4 GetView() { return view; }
	void SetView(glm::mat4 t_view) { view = t_view; }
	glm::mat4 GetProjection() { return projection; }
	void SetProjection(glm::mat4 t_projection) { projection = t_projection; }
	glm::vec3 GetLocation() { return location; }
	void SetLocation(glm::vec3 t_location) { location = t_location; }
private:
	glm::vec3
		location,
		facing,
		up;
	glm::mat4
		view,
		projection;
};
