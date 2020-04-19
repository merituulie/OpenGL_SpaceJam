#include <iostream>
#include <vector>
#include <GL\glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "skybox.h"
#include "glsl.h"
#include "objloader.h"
#include "texture.h"
#include "stb_image.h"

skybox::skybox()
{
	fragmentshader_name = "fragmentshaderskybox.fsh";
	vertexshader_name = "vertexshaderskybox.vsh";

	objectfile_name = "Objects/skybox.obj";

	faces = {
	"Textures/Skybox/right.jpg",
	"Textures/Skybox//left.jpg",
	"Textures/Skybox/top.jpg",
	"Textures/Skybox/bottom.jpg",
	"Textures/Skybox/front.jpg",
	"Textures/Skybox/back.jpg"
	};

	vsh_id = 0;
	fsh_id = 0;
	texture_id = 0;

	ambient_color = glm::vec3(0, 0, 0);
	diffuse_color = glm::vec3(0, 0, 0);
	specular = glm::vec3(0, 0, 0);
	power = 0;

	bool loaderResponse = false;
}

skybox::~skybox()
{
}

GLuint skybox::InitShaders()
{
    // Set shaderprogram according to vertex and fragmentshaders
	char* vertexshader = glsl::readFile(vertexshader_name);
	char* fragshader = glsl::readFile(fragmentshader_name);

	vsh_id = glsl::makeVertexShader(vertexshader);
	fsh_id = glsl::makeFragmentShader(fragshader);
	return program_id = glsl::makeShaderProgram(vsh_id, fsh_id);
}

// Load skyboxes faces from faces
GLuint skybox::loadCubeMap(vector<std::string> faces)
{
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    int width, height, nrChannels;
    for (unsigned int i = 0; i < faces.size(); i++)
    {
        unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
            );
            stbi_image_free(data);
        }
        else
        {
            std::cout << "Cubemap tex failed to load at path: " << faces[i] << std::endl;
            stbi_image_free(data);
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return textureID;
}

GLuint skybox::InitObject()
{
    loaderResponse = loadOBJ(objectfile_name, vertices, uvs, normals);
    return texture_id = loadCubeMap(faces);
}

void skybox::InitLightingAndPosition()
{
}

void skybox::Render(glm::mat4 view)
{
    glUseProgram(program_id);

    glUniformMatrix4fv(uniform_view, 1, GL_FALSE, glm::value_ptr(view));

    // Use cube mapping to map the texture of the skybox
    glBindVertexArray(vao);
    glBindTexture(GL_TEXTURE_CUBE_MAP, texture_id);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    glBindVertexArray(0);
}