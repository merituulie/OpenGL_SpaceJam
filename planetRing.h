#pragma once

#include "object.h"
#include "planet.h"

class planetRing : public object
{
protected:
	bool loaderResponse;
public:
	planetRing();
	~planetRing();

	planet* _planet;

	GLuint InitShaders() override;
	GLuint InitObject() override;
	void InitLightingAndPosition() override;
	void Animation() override;
	void Render(glm::mat4 view) override;
	void SetPlanet(planet* planet);
};

