#pragma once

#include "References.h"
#include "Texture.h"
#include "Renderer.h"

static float vertecies[]{
	0.0f,0.0f,
	0.0f,1.0f,
	1.0f,0.0f,
	1.0f,0.0f,
	1.0f,1.0f,
	0.0f,1.0f
};

class GameObject {
public :
	GameObject(Texture2D& texture,ShaderProgram& shader);
	~GameObject();
	void Render();
private:
	glm::mat4 transform;
	glm::vec4 color;
	glm::vec2 size;
	Texture2D texture;
	VertexBufferObject& vbo;
	VertexArrayObject& vao;
	ShaderProgram shader;
};