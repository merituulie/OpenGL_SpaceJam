#include "planetRing.h"
#include "glsl.h"
#include <glm\gtc\type_ptr.hpp>
#include "objloader.h"
#include "texture.h"

planetRing::planetRing()
{
    fragmentshader_name = "fragmentshaderphong.fsh";
    vertexshader_name = "vertexshader.vsh";
    objectfile_name = "Objects/saturnRing.obj";
    texture = "Textures/saturnring.bmp";

    vsh_id = 0;
    fsh_id = 0;
    texture_id = 0;

    ambient_color = glm::vec3(0, 0, 0);
    diffuse_color = glm::vec3(0, 0, 0);
    specular = glm::vec3(0, 0, 0);
    power = 0;

    bool loaderResponse = false;
}

planetRing::~planetRing()
{
    delete _planet;
}

void planetRing::SetPlanet(planet* planet)
{
    _planet = planet;
}

GLuint planetRing::InitShaders()
{
    // Create shaderprogram according to vertexshader and fragmentshader
    char* vertexshader = glsl::readFile(vertexshader_name);
    char* fragshader = glsl::readFile(fragmentshader_name);

    vsh_id = glsl::makeVertexShader(vertexshader);
    fsh_id = glsl::makeFragmentShader(fragshader);
    return program_id = glsl::makeShaderProgram(vsh_id, fsh_id);
}

GLuint planetRing::InitObject()
{
    loaderResponse = loadOBJ(objectfile_name, vertices, uvs, normals);
    return texture_id = loadBMP(texture);
}

void planetRing::InitLightingAndPosition()
{
    // Set lighting of the object
    ambient_color = glm::vec3(0.5, 0.5, 0.5);
    diffuse_color = glm::vec3(0.0, 1.0, 0.0);
    specular = glm::vec3(0.1f);
    power = 2;

    // Set the scale of the ring bigger, set its position according to it's planet
    SetScale(3.0f);
    Update_Model();
}

void planetRing::Animation()
{
}

void planetRing::Render(glm::mat4 view)
{
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