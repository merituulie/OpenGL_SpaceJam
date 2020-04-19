#pragma once

#include "object.h"
#include "camera.h"

class ufo : public object
{
protected:
	bool loaderResponse;
	bool jitter;
public:
	ufo();
	~ufo();

	camera* _camera;

	GLuint InitShaders() override;
	GLuint InitObject() override;
	void InitLightingAndPosition() override;
	void Animation() override;
	void Render(glm::mat4 view) override;
	void SetCamera(camera* camera);
};

