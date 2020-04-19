#pragma once
#include <vector>
#include <cstdlib>
#include "asteroid.h"

class asteroidManager
{
public:
	asteroidManager();
	~asteroidManager();

	asteroid* CreateAsteroid();
	void RandomizePosition(object* previousAsteroid, object* nextAsteroid);

	vector<asteroid*> _asteroids;

	int random;
	int asteroidCount;
};

