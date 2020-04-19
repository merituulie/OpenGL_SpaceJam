#pragma once

#include "object.h"
#include "planet.h"

class moon : public object
{
protected:
	bool loaderResponse;
public:
	moon();
	~moon();

	planet* _planet;

	GLuint InitShaders() override;
	GLuint InitObject() override;
	void InitLightingAndPosition() override;
	void Animation() override;
	void Render(glm::mat4 view) override;
	void SetPlanet(planet* planet);
};

