#include "ufo.h"

#include "glsl.h"
#include <glm\gtc\type_ptr.hpp>
#include "objloader.h"
#include "texture.h"

ufo::ufo()
{
    fragmentshader_name = "fragmentshaderphong.fsh";
    vertexshader_name = "vertexshader.vsh";
    objectfile_name = "Objects/ufo.obj";
    texture = "Textures/redMetal.bmp";

    vsh_id = 0;
    fsh_id = 0;
    texture_id = 0;

    ambient_color = glm::vec3(0, 0, 0);
    diffuse_color = glm::vec3(0, 0, 0);
    specular = glm::vec3(0, 0, 0);
    power = 0;

    bool loaderResponse = false;
    jitter = false;
}

ufo::~ufo()
{
}

void ufo::SetCamera(camera* camera)
{
    //Attach the ufo to the camera
    _camera = camera;
}

GLuint ufo::InitShaders()
{
    // Create shaderprogram according to vertexshader and fragmentshader
    char* vertexshader = glsl::readFile(vertexshader_name);
    char* fragshader = glsl::readFile(fragmentshader_name);

    vsh_id = glsl::makeVertexShader(vertexshader);
    fsh_id = glsl::makeFragmentShader(fragshader);
    return program_id = glsl::makeShaderProgram(vsh_id, fsh_id);
}

GLuint ufo::InitObject()
{
    loaderResponse = loadOBJ(objectfile_name, vertices, uvs, normals);
    return texture_id = loadBMP(texture);
}

void ufo::InitLightingAndPosition()
{
    // Set lighting of the object
    ambient_color = glm::vec3(0.1, 0.1, 0.1);
    diffuse_color = glm::vec3(0.1, 0.1, 0.1);
    specular = glm::vec3(2.0f);
    power = 5;

}

void ufo::Animation()
{
}

void ufo::Render(glm::mat4 view)
{

    glUseProgram(program_id);

    // Commented mv out, so the ufo is bound to the camera view
    //mv = view * model;

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