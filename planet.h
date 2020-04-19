#pragma once
#include "object.h"

class planet : public object
{
protected:
	bool loaderResponse;
public:
	planet();
	planet(const char* texturename);
	~planet();

	GLuint InitShaders() override;
	GLuint InitObject() override;
	void InitLightingAndPosition() override;
	void Animation() override;
	void Render(glm::mat4 view) override;
};