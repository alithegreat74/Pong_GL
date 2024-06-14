#pragma once

#include "References.h"
#include "Texture.h"
#include "Renderer.h"
#include "Input.h"
#include "UserInterface.h"

/// <summary>
/// This file contains the data for every game object
/// Every game object has some of the same data
/// because we want to use sprites, we can use the same set of vericies to create a vertex buffer
/// The only difference in each sprite is it's texture and it's size and position
/// </summary>


static float vertecies[]{
	//Position     //TexCoords
	 0.5f,  0.5f,  1.0f,  1.0f, // top right
	 0.5f, -0.5f,  1.0f,  0.0f,  // bottom right
	-0.5f,  0.5f,  0.0f,  1.0f,  // top left 
	 0.5f, -0.5f,  1.0f,  0.0f,  // bottom right
	-0.5f,  0.5f,  0.0f,  1.0f,  // top left
	-0.5f, -0.5f,  0.0f,  0.0f   // bottom left
};


class GameObject {
public :
	//Creates and sets the buffers and textures and shaders for the gameobject
	~GameObject();
	//Renders the gameobject using with the given texture and shader
	virtual void Render(Texture2D& texture, ShaderProgram& shader);
	void Start(glm::vec4 color, glm::vec3 pos,glm::vec3 scale);
	void Move();
	void SetSpeed(glm::vec2 speed);
protected:
	unsigned int vbo, vao;
	glm::mat4 transform;
	glm::vec4 color;
	glm::vec3 size;
	glm::vec3 position;
	glm::vec2 speed;
};

class Racket :public GameObject {
public:
	void Listen();
	void UpKeyCallback(int action);
	void DownKeyCallback(int action);
	void SetInputs(int upKey, int downKey);
	void Render(Texture2D& texture, ShaderProgram& shader)override;
	void HandleMovement();
private:
	int upKey,downKey;
	bool upWasPressed, downWasPressed;
};