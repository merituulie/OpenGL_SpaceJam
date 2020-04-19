#pragma once
#include "object.h"

// Correctly working objest as a test object
class teapot : public object
{
protected:
	bool loaderResponse;
public:
	teapot();
	~teapot();

	GLuint InitShaders() override;
	GLuint InitObject() override;
	void InitLightingAndPosition() override;
	void Render(glm::mat4 view) override;
};

