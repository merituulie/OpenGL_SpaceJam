#include <iostream>
#include <list>

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "camera.h"
#include "teapot.h"
#include "object.h"
#include "skybox.h"
#include "planet.h"
#include "moon.h"
#include "ufo.h"
#include "planetRing.h"
#include "asteroid.h"
#include "asteroidManager.h"
#include "satellite.h"
#include "particle.h"

using namespace std;

//--------------------------------------------------------------------------------
// Consts
//--------------------------------------------------------------------------------

const int WIDTH = 1000, HEIGHT = 800;

unsigned const int DELTA_TIME = 10;

//--------------------------------------------------------------------------------
// Variables
//--------------------------------------------------------------------------------

// Matrices for view and projection
glm::mat4 view, projection;

// Lighting
glm::vec3 light_position;

// Objects
camera* _camera = new camera();
asteroidManager* _asteroidManager = new asteroidManager();
vector<object*> _objects;

//--------------------------------------------------------------------------------
// Keyboard handling
//--------------------------------------------------------------------------------

void keyboardHandler(unsigned char key, int a, int b)
{
    if (key == 27)
        glutExit();

    // Handle the input to move the camera accordingly
    _camera->Process_Input(key, a, b);
}


//--------------------------------------------------------------------------------
// Rendering
//--------------------------------------------------------------------------------

void Render()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Update the view each frame
    view = _camera->Get_View();

    // Render through objects
    for (object* obj : _objects)
    {
        obj->Render(view);
    }
        glutSwapBuffers();
}


//------------------------------------------------------------
// void Render(int n)
// Render method that is called by the timer function
//------------------------------------------------------------

void Render(int n)
{
    Render();
    glutTimerFunc(DELTA_TIME, Render, 0);
}


//------------------------------------------------------------
// void InitGlutGlew(int argc, char **argv)
// Initializes Glut and Glew
//------------------------------------------------------------

void InitGlutGlew(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Hello OpenGL");
    glutDisplayFunc(Render);
    glutKeyboardFunc(keyboardHandler);
    glutTimerFunc(DELTA_TIME, Render, 0);

    //glEnable(GL_MULTISAMPLE);
    //glEnable(GL_DEPTH_TEST);
    //glClear(GL_DEPTH_BUFFER_BIT);

    glewInit();
}

//------------------------------------------------------------
// InitObjectsList() to create objects for the scene
//------------------------------------------------------------
void InitObjectsList()
{
    skybox* _skybox = new skybox();
    _objects.push_back(_skybox);

    ufo* _ufo = new ufo();
    _ufo->SetCamera(_camera);
    _objects.push_back(_ufo);

    planet* _planet = new planet();
    _objects.push_back(_planet);

    moon* _moon = new moon();
    _moon->SetPlanet(_planet);
    _objects.push_back(_moon);

    const char* texture_name = "Textures/venus.bmp";
    planet* _planet1 = new planet(texture_name);
    _objects.push_back(_planet1);

    const char* texture_name1 = "Textures/jupiter.bmp";
    planet* _planet2 = new planet(texture_name1);
    _objects.push_back(_planet2);

    planetRing* _planetRing = new planetRing();
    _planetRing->SetPlanet(_planet2);
    _objects.push_back(_planetRing);

    const char* texture_name3 = "Textures/neptune.bmp";
    planet* _planet3 = new planet(texture_name3);
    _objects.push_back(_planet3);

    satellite* _satellite = new satellite();
    _objects.push_back(_satellite);

    particle* _particle = new particle();
    _objects.push_back(_particle);

    for (int i = 0; i < _asteroidManager->asteroidCount; i++)
    {
        _objects.push_back(_asteroidManager->CreateAsteroid());
    }
}


//------------------------------------------------------------
// void InitShaders()
// Initializes the fragmentshader and vertexshader
//------------------------------------------------------------

void InitShaders(object* obj)
{
    obj->InitShaders();
}

void InitLights(object* obj)
{
    light_position = glm::vec3(10, 10, 0);

    obj->InitLightingAndPosition();
}

//------------------------------------------------------------
// void InitMatrices()
//------------------------------------------------------------

void InitMatrices(object* obj)
{
    // Get the view from the camera.cpp and set projection
    view = _camera->Get_View();
    projection = glm::perspective(
        glm::radians(45.0f),
        1.0f * WIDTH / HEIGHT, 0.1f,
        10000.0f);

    // Initialize model with view
    obj->InitModel(view);
}

//------------------------------------------------------------
// void InitBuffers()
// Allocates and fills buffers
//------------------------------------------------------------

void InitBuffers(object* obj)
{
    obj->InitBuffers();
    obj->MakeUniformVars(view);

    // Attach to program
    glUseProgram(obj->program_id);

        // Fill uniform vars
    glUniformMatrix4fv(obj->uniform_proj, 1, GL_FALSE, glm::value_ptr(projection));
    glUniform3fv(obj->uniform_light_pos, 1, glm::value_ptr(light_position));
}

void InitObjects(object* obj)
{
    obj->InitObject();
}

// Set Positions of the objects now that models are set
void SetObjectsFinal()
{
    _objects[4]->SetPositionX(30.0);
    _objects[4]->SetPositionZ(30.0);
    _objects[4]->SetPositionY(-20.0);
    _objects[4]->SetScale(8.0);
    _objects[5]->SetPositionX(5.0);
    _objects[5]->SetPositionY(-5.0);
    _objects[5]->SetPositionZ(-50.0);
    _objects[5]->SetScale(3.0);
    _objects[6]->SetPositionX(5.0);
    _objects[6]->SetPositionY(-5.0);
    _objects[6]->SetPositionZ(-50.0);
    _objects[7]->SetPositionX(-50.0);
    _objects[7]->SetPositionY(10.0);
    _objects[8]->SetPositionZ(-30.0);
    _objects[8]->SetPositionX(-40.0);
    _objects[8]->SetPositionY(12.0);

    _objects[10]->SetPositionX(100.0);
    _objects[10]->SetPositionZ(-100.0);
    _objects[10]->SetPositionY(-100.0);

    for (int i = 11; i < _asteroidManager->asteroidCount; i++)
    {
        _asteroidManager->RandomizePosition(_objects[10], _objects[i]);
    }

}


int main(int argc, char** argv)
{
    InitGlutGlew(argc, argv);
    InitObjectsList();

    // Loop through the initialization of objects to render them later
    for (object* obj : _objects)
    {
        InitShaders(obj);
        InitMatrices(obj);
        InitObjects(obj);
        InitLights(obj);
        InitBuffers(obj);
    }

    SetObjectsFinal();

    glEnable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    // Hide console window
    HWND hWnd = GetConsoleWindow();
    ShowWindow(hWnd, SW_SHOW);

    // Main loop
    glutMainLoop();

    return 0;
}
