#include <iostream>
#include <vector>
#include <GL\glew.h>
#include <glm/glm.hpp>
#include <glm\gtc\type_ptr.hpp>
#include "particle.h"
#include "glsl.h"
#include "objloader.h"
#include "texture.h"

particle::particle()
{
    fragmentshader_name = "fragmentshaderprimitive.fsh";
    vertexshader_name = "vertexshaderprimitive.vsh";

    texture = "Textures/robot.bmp";

    vsh_id = 0;
    fsh_id = 0;
    texture_id = 0;
    vao = 0;

    ambient_color = glm::vec3(0, 0, 0);
    diffuse_color = glm::vec3(0, 0, 0);
    specular = glm::vec3(0, 0, 0);
    power = 0;

    bool loaderResponse = false;
}

particle::~particle()
{
}

GLuint particle::InitShaders()
{
    char* vertexshader = glsl::readFile(vertexshader_name);
    char* fragshader = glsl::readFile(fragmentshader_name);

    vsh_id = glsl::makeVertexShader(vertexshader);
    fsh_id = glsl::makeFragmentShader(fragshader);
    return program_id = glsl::makeShaderProgram(vsh_id, fsh_id);
}

GLuint particle::InitObject()
{
    //loaderResponse = loadOBJ(objectfile_name, vertices, uvs, normals);
    vertices = {
        // front
        -0.1, -0.1, 0.1,
        0.1, -0.1, 0.1,
        0.1, 0.1, 0.1,
        -0.1, 0.1, 0.1,
        // back
        -0.1, -0.1, -0.1,
        0.01, -0.01, -0.1,
        0.1, 0.1, -0.1,
        -0.1, 0.1, -0.1
    };

    colors = {
        // front colors
        1.0, 1.0, 0.0,
        0.0, 1.0, 0.0,
        0.0, 0.0, 1.0,
        1.0, 1.0, 1.0,
        // back colors
        0.0, 1.0, 1.0,
        1.0, 0.0, 1.0,
        1.0, 0.0, 0.0,
        1.0, 1.0, 0.0
    };

    cube_elements_solid = {
    0,1,2, //front 1
    0,2,3, //front 2
    0,5,1, //bottom 1
    0,4,5, //bottom 2
    1,5,2, //right 1
    2,5,6, //right 2
    0,3,4, //left 1
    3,7,4, //left 2
    4,6,5, //back 1
    4,7,6, //back 2
    2,7,3, //top 1
    2,6,7 // top 2
    };

    return texture_id = 0;
}

void particle::InitBuffers() {

    GLuint vbo_vertices, vbo_colors, ibo_cube_elements;
    GLuint position_id, color_id;

    // vbo for vertices
    glGenBuffers(1, &vbo_vertices);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_vertices);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), &vertices[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // vbo for colors
    glGenBuffers(1, &vbo_colors);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_colors);
    glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(GLfloat), &colors[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    //ibo for cube_elements_solid
    glGenBuffers(1, &ibo_cube_elements);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_cube_elements);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, cube_elements_solid.size() * sizeof(GLushort), &cube_elements_solid[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    position_id = glGetAttribLocation(program_id, "position");
    color_id = glGetAttribLocation(program_id, "color");

    // Allocate memory for vao
    glGenVertexArrays(1, &vao);

    // Bind to vao
    glBindVertexArray(vao);

    // Bind vertices to vao
    glBindBuffer(GL_ARRAY_BUFFER, vbo_vertices);
    glVertexAttribPointer(position_id, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(position_id);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Bind colors to vao
    glBindBuffer(GL_ARRAY_BUFFER, vbo_colors);
    glVertexAttribPointer(color_id, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(color_id);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Bind ibo to vao
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_cube_elements);

    glBindVertexArray(0);
}

void particle::InitLightingAndPosition()
{
    ambient_color = glm::vec3(0.1f, 0.1f, 0.1f);
    diffuse_color = glm::vec3(0.0f, 0.1f, 0.0f);
}

void particle::Animation()
{
}

void particle::Render(glm::mat4 view) 
{

    glUseProgram(program_id);

    mv = view * model;

    // Send mv
    glUniformMatrix4fv(uniform_mv, 1, GL_FALSE, glm::value_ptr(mv));

    // Fill uniform vars for material
    glUniform3fv(uniform_material_ambient, 1, glm::value_ptr(ambient_color));
    glUniform3fv(uniform_material_diffuse, 1, glm::value_ptr(diffuse_color));
    glUniform1f(uniform_material_power, power);

    // Send vao
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, cube_elements_solid.size(), GL_UNSIGNED_SHORT, 0);
    glBindVertexArray(0);
}