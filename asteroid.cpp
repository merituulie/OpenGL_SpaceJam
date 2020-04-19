#include "asteroid.h"
#include "glsl.h"
#include <glm\gtc\type_ptr.hpp>
#include "objloader.h"
#include "texture.h"

asteroid::asteroid()
{
    fragmentshader_name = "fragmentshaderlambert.fsh";
    vertexshader_name = "vertexshader.vsh";
    objectfile_name = "Objects/asteroid.obj";
    texture = "Textures/asteroids.bmp";

    vsh_id = 0;
    fsh_id = 0;
    texture_id = 0;

    ambient_color = glm::vec3(0, 0, 0);
    diffuse_color = glm::vec3(0, 0, 0);

    bool loaderResponse = false;
}

asteroid::~asteroid()
{

}

GLuint asteroid::InitShaders()
{
    // Create shaderprogram according to vertexshader and fragmentshader
    char* vertexshader = glsl::readFile(vertexshader_name);
    char* fragshader = glsl::readFile(fragmentshader_name);

    vsh_id = glsl::makeVertexShader(vertexshader);
    fsh_id = glsl::makeFragmentShader(fragshader);
    return program_id = glsl::makeShaderProgram(vsh_id, fsh_id);
}

GLuint asteroid::InitObject()
{
    loaderResponse = loadOBJ(objectfile_name, vertices, uvs, normals);
    return texture_id = loadBMP(texture);
}

void asteroid::InitLightingAndPosition()
{
    // Set lighting of the object
    ambient_color = glm::vec3(0.5, 0.5, 0.5);
    diffuse_color = glm::vec3(0.0, 1.0, 0.0);

    // Set the scale of the moon smaller, set its position according to it's planet
    SetScale(0.5f);
    Update_Model();
}

void asteroid::Animation()
{
    // Make the moon orbit around the planet, radian used to calculate the turnrate of the object
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.1f));
    model = glm::rotate_slow(model, glm::radians(0.3f), glm::vec3(0.0f, 0.1f, 0.1f));
}

void asteroid::Render(glm::mat4 view)
{
    glUseProgram(program_id);

    mv = view * model;

    Animation();

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


