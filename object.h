#pragma once

#include <GL\glew.h>
#include <glm/glm.hpp>
#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace std;

class object {
protected:
	GLuint vsh_id;
	GLuint fsh_id;
	GLuint texture_id;
	GLuint vao;
	GLuint uniform_mv;
	GLuint uniform_view;
	GLuint uniform_material_ambient;
	GLuint uniform_material_diffuse;
	GLuint uniform_specular;
	GLuint uniform_material_power;

	glm::mat4 mv;
	glm::mat4 view;

	const char* vertexshader_name;
	const char* fragmentshader_name;
	const char* texture;
	const char* objectfile_name;

	vector<glm::vec3> normals;
	vector<glm::vec3> vertices;
	vector<glm::vec2> uvs;

	glm::vec3 ambient_color;
	glm::vec3 diffuse_color;
	glm::vec3 specular;

	float power;
	bool loaderResponse;

public:
	glm::mat4 model;
	glm::vec3 rotation;
	glm::vec3 scale;
	glm::vec3 position;

	GLuint uniform_proj;
	GLuint uniform_light_pos;

	object();
	~object();

	virtual GLuint InitShaders();
	glm::mat4 InitModel(glm::mat4 view); // matrices
	virtual GLuint InitObject();
	virtual void Render(glm::mat4 view);
	virtual void InitLightingAndPosition();
	virtual void Animation();

	void SetPositionX(float x);
	void SetPositionY(float y);
	void SetPositionZ(float z);

	virtual void SetScale(float newScale);
	void SetScaleX(float x);
	void SetScaleY(float y);
	void SetScaleZ(float z);
	virtual void SetRotation(glm::vec3 newRotation);
	virtual void Update_Model();

	virtual void InitBuffers();
	void MakeUniformVars(glm::mat4 view);

	GLuint program_id;
};

