#pragma once

#include <glm/glm.hpp>

class camera {
public:
	camera();
	~camera();

	glm::mat4 Get_View();
	void Process_Input(unsigned char key, int a, int b);
	glm::vec3 GetCameraPosition();

	glm::vec3 position;
protected:
	bool view_selection; // Check if the view is set from topdown or to front

	float yaw;
	float pitch;

	glm::mat4 view;
	glm::vec3 direction;
};