#include "asteroidManager.h"
#include "asteroid.h"

asteroidManager::asteroidManager()
{
	asteroidCount = 80;
}


asteroidManager::~asteroidManager()
{
}

//vector<asteroid*> asteroids;
asteroid* asteroidManager::CreateAsteroid()
{
	asteroid* _asteroid = new asteroid();
	return _asteroid;
}

// Randomize each asteroids position a little different to create flocklike behaviour
void asteroidManager::RandomizePosition(object* previousAsteroid, object* nextAsteroid)
{
	random = rand() % 10 + (-10);
	nextAsteroid->SetPositionX(previousAsteroid->position.x + random);
	random = rand() % 30 + (-30);
	nextAsteroid->SetPositionY(previousAsteroid->position.y - random);
	nextAsteroid->SetRotation(glm::vec3(random, random, random));
	random = rand() % 20 + (-20);
	nextAsteroid->SetPositionZ(previousAsteroid->position.z - random);
	nextAsteroid->Update_Model();
}