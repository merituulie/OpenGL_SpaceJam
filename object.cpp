#include "object.h"
#include "glsl.h"
#include "objloader.h"
#include "stb_image.h"
#include "texture.h"

object::object()
{
    char* vertexshader_name = nullptr;
    char* fragmentshader_name = nullptr;
    char* objectfile_name = nullptr;
    char* texture = nullptr;

	program_id = 0;
	vsh_id = 0;
	fsh_id = 0;
	texture_id = 0;
	vao = 0;

	model = glm::mat4();
	view = glm::mat4();
	mv = glm::mat4();
    position = glm::vec3(0, 0, 0);
    rotation = glm::vec3(0, 0, 0);
    scale = glm::vec3(1, 1, 1);

	ambient_color = glm::vec3(0, 0, 0);
	diffuse_color = glm::vec3(0, 0, 0);
	specular = glm::vec3(0, 0, 0);
	power = 0;

	bool loaderResponse = false;
}

object::~object()
{
}

GLuint object::InitShaders()
{
    return 0;
}

// Initialize the model according the view got from main.cpp
glm::mat4 object::InitModel(glm::mat4 view)
{
    model = glm::mat4();
    mv = view * model;
    return mv;
}

GLuint object::InitObject()
{
    return 0;
}

void object::Render(glm::mat4 view)
{
}

void object::InitLightingAndPosition()
{
}

void object::Animation()
{
}

void object::SetPositionX(float x)
{
    position.x = x;
    Update_Model();
}

void object::SetPositionY(float y)
{
    position.y = y;
    Update_Model();
}

void object::SetPositionZ(float z)
{
    position.z = z;
    Update_Model();
}

void object::SetScale(float newScale)
{
    scale = glm::vec3(newScale, newScale, newScale);
    Update_Model();
}

void object::SetScaleX(float x)
{
    scale.x = x;
    Update_Model();
}

void object::SetScaleY(float y)
{
    scale.y = y;
    Update_Model();
}

void object::SetScaleZ(float z)
{
    scale.z = z;
    Update_Model();
}

void object::SetRotation(glm::vec3 newRotation)
{
    rotation = newRotation;
    Update_Model();
}

// Initialize buffers to use shaders
void object::InitBuffers()
{
    GLuint position_id, uv_id, normal_id;
    GLuint vbo_vertices, vbo_uvs, vbo_normals;

    position_id = glGetAttribLocation(program_id, "position");
    normal_id = glGetAttribLocation(program_id, "normal");
    uv_id = glGetAttribLocation(program_id, "uv");

    glGenBuffers(1, &vbo_vertices);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_vertices);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0],
        GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // vbo for normals
    glGenBuffers(1, &vbo_normals);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_normals);
    glBufferData(GL_ARRAY_BUFFER,
        normals.size() * sizeof(glm::vec3),
        &normals[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // vbo for uvs
    glGenBuffers(1, &vbo_uvs);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_uvs);
    glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2),
        &uvs[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Allocate memory for vao
    glGenVertexArrays(1, &vao);

    // Bind to vao
    glBindVertexArray(vao);

    // Bind vertices to vao
    glBindBuffer(GL_ARRAY_BUFFER, vbo_vertices);
    glVertexAttribPointer(position_id, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(position_id);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Bind normals to vao
    glBindBuffer(GL_ARRAY_BUFFER, vbo_normals);
    glVertexAttribPointer(normal_id, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(normal_id);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Bind to vao
    glBindBuffer(GL_ARRAY_BUFFER, vbo_uvs);
    glVertexAttribPointer(uv_id, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(uv_id);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Stop bind to vao
    glBindVertexArray(0);
}

// Make uniform variables
void object::MakeUniformVars(glm::mat4 view)
{
    uniform_mv = glGetUniformLocation(program_id, "mv");
    uniform_view = glGetUniformLocation(program_id, "view");
    uniform_proj = glGetUniformLocation(program_id, "projection");
    uniform_light_pos = glGetUniformLocation(program_id, "light_pos");
    uniform_material_ambient = glGetUniformLocation(program_id, "mat_ambient");
    uniform_material_diffuse = glGetUniformLocation(program_id, "mat_diffuse");
    uniform_specular = glGetUniformLocation(program_id, "mat_specular");
    uniform_material_power = glGetUniformLocation(program_id, "mat_power");

}

void Render(glm::mat4 view)
{
}

// Update the model according to its position, rotation and scale
void object::Update_Model()
{
    model = glm::translate(glm::mat4(), position);
    model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1.0, 0.0, 0.0));
    model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0.0, 1.0, 0.0));
    model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0.0, 0.0, 1.0));
    model = glm::scale(model, scale);
}
