#include "camera.h"
#include <iostream>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

const float MOVING_SPEED = 0.5f;
const float TURNING_SPEED = 4.0f;

camera::camera()
{
	view_selection = false;
	yaw = 0.0f;
	pitch = 0.0f;

	position = glm::vec3(-5.0f, 1.75f, 0.0f);
	direction = glm::vec3(0.0f, 0.0f, 0.0f);
	view = glm::mat4();
}

camera::~camera()
{
}

glm::mat4 camera::Get_View()
{
	//Get view with direction by the Y- and X-axises
	direction = glm::vec3(
		cos(glm::radians(yaw) * cos(glm::radians(pitch))),
		sin(glm::radians(pitch)),
		sin(glm::radians(yaw)) * cos(glm::radians(pitch)));

	view = glm::mat4(glm::lookAt(
		position,								 // eye, position of the camera
		position + glm::normalize(direction),  // center, the direction the camera is pointed at
		glm::vec3(0.0, 0.1, 0.0)));				 // up

	return view;
}

void camera::Process_Input(unsigned char key, int a, int b)
{

	switch (key)
	{
	case 'c':
		// check, which one of the view setting was last and switch to another one
		view_selection = !view_selection;

		position = (view_selection) ? glm::vec3(-50.0f, 100.0f, 0.0f) : 
			glm::vec3(-10.0f, 2.0f, 0.0f);

		pitch = (view_selection) ? -120 : 0;
		break;
	case 'w': // Move forward
		position += (view_selection) ? glm::vec3(direction.x, 0.0f, direction.z) * MOVING_SPEED :
			glm::vec3(direction.x, 0.0f, direction.z) * MOVING_SPEED;
		break;
	case 's': // Move backwards
		position -= (view_selection) ? glm::vec3(direction.x, 0.0f, direction.z) * MOVING_SPEED :
			glm::vec3(direction.x, 0.0f, direction.z) * MOVING_SPEED;
		break;
	case 'a': // Move left
		position += (view_selection) ? glm::cross(glm::vec3(0.0f, 1.0f, 0.0), glm::vec3(direction.x, 0.0f, direction.z)) * MOVING_SPEED :
			glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(direction.x, 0.0f, direction.z)) * MOVING_SPEED;
		break;
	case 'd': // Move right
		position += (view_selection) ? glm::cross(glm::vec3(direction.x, 0.0f, direction.z), glm::vec3(0.0f, 1.0f, 0.0f)) * MOVING_SPEED :
			glm::cross(glm::vec3(direction.x, 0.0f, direction.z), glm::vec3(0.0f, 1.0f, 0.0f)) * MOVING_SPEED;
		break;
	case 'z': //Moves down
		if (view_selection) {
			position += glm::vec3(0.0f, -0.5f, 0.0f);
		}
		break;
	case 'x': //Moves up
		if (view_selection)
		{
			position += glm::vec3(0.0f, +0.5f, 0.0f);
		}
		break;
	case 'i': // Turn up
		pitch += TURNING_SPEED;
		if (pitch > 89.0f) // Avoid flipping
			pitch = 89.0f;
		break;
	case 'k': // Turn down
		pitch -= TURNING_SPEED;
		if (pitch < -89.0f) // Avoid flipping
			pitch = -89.0f;
		break;
	case 'j': // Turn left
		yaw -= TURNING_SPEED;
		if (yaw < -89.0f && view_selection) // Avoid too much turning if in skymode
			yaw = -89.0f;
		break;
	case 'l': // Turn right
		yaw += TURNING_SPEED;
		if (yaw > 89.0f && view_selection) // Avoid too much turning if in skymode
			yaw = 89.0f;
		break;
	}
}

glm::vec3 camera::GetCameraPosition()
{
	return position;
}