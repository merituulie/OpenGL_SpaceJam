#pragma once

#include "object.h"

class asteroid : public object
{
protected:
	bool loaderResponse;
public:
	asteroid();
	~asteroid();

	GLuint InitShaders() override;
	GLuint InitObject() override;
	void InitLightingAndPosition() override;
	void Animation() override;
	void Render(glm::mat4 view) override;
};

