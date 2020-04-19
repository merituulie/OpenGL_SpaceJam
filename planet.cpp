#include "planet.h"

#include <iostream>
#include <vector>
#include <GL\glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "planet.h"
#include "glsl.h"
#include "objloader.h"
#include "texture.h"

planet::planet()
{
    fragmentshader_name = "fragmentshaderphong.fsh";
    vertexshader_name = "vertexshader.vsh";
    objectfile_name = "Objects/sphere.obj";
    texture = "Textures/mars.bmp";

    vsh_id = 0;
    fsh_id = 0;
    texture_id = 0;

    ambient_color = glm::vec3(0, 0, 0);
    diffuse_color = glm::vec3(0, 0, 0);
    specular = glm::vec3(0, 0, 0);
    power = 0;

    bool loaderResponse = false;
}

planet::planet(const char* texturename)
{
    fragmentshader_name = "fragmentshaderphong.fsh";
    vertexshader_name = "vertexshader.vsh";
    objectfile_name = "Objects/sphere.obj";
    texture = texturename;

    vsh_id = 0;
    fsh_id = 0;
    texture_id = 0;

    ambient_color = glm::vec3(0, 0, 0);
    diffuse_color = glm::vec3(0, 0, 0);
    specular = glm::vec3(0, 0, 0);
    power = 0;

    bool loaderResponse = false;
}

planet::~planet()
{
}

GLuint planet::InitShaders()
{
    char* vertexshader = glsl::readFile(vertexshader_name);
    char* fragshader = glsl::readFile(fragmentshader_name);

    vsh_id = glsl::makeVertexShader(vertexshader);
    fsh_id = glsl::makeFragmentShader(fragshader);
    return program_id = glsl::makeShaderProgram(vsh_id, fsh_id);
}

GLuint planet::InitObject()
{
    loaderResponse = loadOBJ(objectfile_name, vertices, uvs, normals);
    return texture_id = loadBMP(texture);
}

void planet::InitLightingAndPosition()
{
    // Set lighting of the object
    ambient_color = glm::vec3(0.2, 0.2, 0.2);
    diffuse_color = glm::vec3(0.0, 0.5, 0.0);
    specular = glm::vec3(0.5f);
    power = 1;

    // Set the scale and position of the planet
    SetPositionX(50.0f);
    SetScale(3.0f);
}

void planet::Animation()
{
    // Animation to make the planet to rotate around y-axis
    if (rotation.y > 0.1f)
        rotation.y = 0.01f;
    else 
        rotation.y -= 0.02f;
}

void planet::Render(glm::mat4 view)
{
    Animation();
    Update_Model();

    glUseProgram(program_id);

    mv = view * model;

    // Send mvp
    glUniformMatrix4fv(uniform_mv, 1, GL_FALSE, glm::value_ptr(mv));

    // Fill uniform vars for material
    glUniform3fv(uniform_material_ambient, 1, glm::value_ptr(ambient_color));
    glUniform3fv(uniform_material_diffuse, 1, glm::value_ptr(diffuse_color));
    glUniform3fv(uniform_specular, 1, glm::value_ptr(specular));
    glUniform1f(uniform_material_power, power);

    glBindTexture(GL_TEXTURE_2D, texture_id);

    // Send vao
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, vertices.size());

    glBindVertexArray(0);
}