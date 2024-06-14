#include "GameObject.h"


GameObject::~GameObject()
{
	glDeleteBuffers(1, &vbo);
	glDeleteVertexArrays(1, &vao);
}

void GameObject::Render(Texture2D& texture, ShaderProgram& shader)
{
	shader.Bind();
	Move();
	shader.ChangeUniform("color", color);
	shader.ChangeUniform("transform", transform);
	texture.Bind();
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
	texture.Unbind();
	shader.Unbind();
}


void GameObject::Start(glm::vec4 color, glm::vec3 pos,glm::vec3 scale)
{

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertecies), vertecies, GL_STATIC_DRAW);


	glVertexAttribPointer(0, 4, GL_FLOAT, false, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 4, GL_FLOAT, false, 4 * sizeof(float), (void*)(2 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	this->color = color;
	transform = glm::mat4(1.0f);
	transform = glm::scale(transform, scale);
	size = scale;
	transform = glm::translate(transform, pos);
	position = pos;
}

void GameObject::Move()
{

	if (position.y + speed.y >= 400 || position.y + speed.y <= -400)
		return;

	transform = glm::translate(transform, glm::vec3(speed.x,speed.y,0.0)*Time::Get().DeltaTime());
	position += glm::vec3(speed.x, speed.y, 0.0);	
}

void GameObject::SetSpeed(glm::vec2 speed)
{
	this->speed = speed;
}

void Racket::Listen()
{
	InputManager::Get().AddListerners(upKey, std::bind(&Racket::UpKeyCallback, this, std::placeholders::_1));
	InputManager::Get().AddListerners(downKey, std::bind(&Racket::DownKeyCallback, this, std::placeholders::_1));
}

void Racket::UpKeyCallback(int action)
{
	if (action == GLFW_PRESS)
		upWasPressed = true;
	else if (action == GLFW_RELEASE)
		upWasPressed = false;
}

void Racket::DownKeyCallback(int action)
{
	if (action == GLFW_PRESS)
		downWasPressed = true;
	else if(action==GLFW_RELEASE)
		downWasPressed = false;	
}


void Racket::SetInputs(int upKey, int downKey)
{
	this->upKey = upKey;
	this->downKey = downKey;
	Listen();
}

void Racket::Render(Texture2D& texture, ShaderProgram& shader)
{
	HandleMovement();
	GameObject::Render(texture, shader);
}

void Racket::HandleMovement()
{
	if (upWasPressed == downWasPressed)
		SetSpeed(glm::vec2(0, 0));
	else
	{
		if (upWasPressed)
			SetSpeed(glm::vec2(0, UI::racketSpeed));
		else
			SetSpeed(glm::vec2(0, -1 * UI::racketSpeed));
	}
}
