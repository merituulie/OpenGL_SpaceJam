#pragma once
#include "object.h"

class particle : public object
{
protected:
	bool loaderResponse = false;
public:
	particle();
	~particle();

	vector<GLfloat> vertices;
	vector<GLfloat> colors;
	vector<GLushort> cube_elements_solid;

	GLuint InitShaders() override;
	GLuint InitObject() override;
	void InitBuffers() override;
	void InitLightingAndPosition() override;
	void Animation() override;
	void Render(glm::mat4 view) override;
};
