#pragma once

#include "object.h"
#include <GL\glew.h>
#include <glm/glm.hpp>
#include <vector>

class skybox : public object
{
protected:
	vector<std::string> faces;
	float power;
public:
	skybox();
	~skybox();

	GLuint InitShaders() override;
	GLuint InitObject() override;
	void InitLightingAndPosition() override;
	void Render(glm::mat4 view) override;
	GLuint loadCubeMap(vector<std::string> faces);
};

