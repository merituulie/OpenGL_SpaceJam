#pragma once

#include "object.h"

class satellite : public object
{
protected:
	bool loaderResponse;
public:
	satellite();
	~satellite();

	GLuint InitShaders() override;
	GLuint InitObject() override;
	void InitLightingAndPosition() override;
	void Animation() override;
	void Render(glm::mat4 view) override;
};

