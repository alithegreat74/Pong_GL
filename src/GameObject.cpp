#include "GameObject.h"


GameObject::GameObject():vao(0),vbo(0), transform(glm::mat4(1.0)), color(glm::vec4(0.0)), size(glm::vec3(0.0)), speed(glm::vec2(0))
{

}

GameObject::~GameObject()
{
	glDeleteBuffers(1, &vbo);
	glDeleteVertexArrays(1, &vao);
}

void GameObject::Render(Texture2D& texture, ShaderProgram& shader)
{
	shader.Bind();
	shader.ChangeUniform("color", color);
	shader.ChangeUniform("transform", transform);
	shader.ChangeSingleUniform("shake", (int)Effects::shake);
	shader.ChangeSingleUniform("shakeStrength", UI::shakeStrength);
	shader.ChangeSingleUniform("time", Effects::shakeTime);
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

}

void GameObject::Move()
{
	//Don't move the object if it's on pause mode
	if (GameManager::pause)
		return;

	transform = glm::translate(transform, glm::vec3(speed.x,speed.y,0.0) * Time::Get().DeltaTime());
}

void GameObject::SetSpeed(glm::vec2 speed)
{
	this->speed = glm::vec2(speed.x, speed.y);
}

Racket::Racket():GameObject(),upKey(0),downKey(0),upWasPressed(0),downWasPressed(0)
{
}

void Racket::Listen()
{
	//Set up the input for the rackets
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
	//Configure the input button for the up and down key
	this->upKey = upKey;
	this->downKey = downKey;
	Listen();
}

void Racket::Render(Texture2D& texture, ShaderProgram& shader)
{
	HandleMovement();
	Move();
	GameObject::Render(texture, shader);
}

void Racket::HandleMovement()
{
	//set the speed of the racket based on the current input
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

void Racket::Move()
{
	//If the racket reaches the bounds of the screen stop moving
	if (transform[3].y + speed.y *Time::Get().DeltaTime() >= 0.9 || transform[3].y + speed.y * Time::Get().DeltaTime() <= -0.9)
		return;

	GameObject::Move();
}

void Ball::Render(Texture2D& texture, ShaderProgram& shader)
{
	Move();
	GameObject::Render(texture,shader);
	GameObject* collider = Collision::CheckCollisions(this);
	//if there is no collsion with the ball don't do anything just return
	if (collider==NULL)
		return;
	if (glfwGetTime() - lastCollisonTime <= 0.5)
		return;
	//store the last collsion so we can avoid multiple collsions with the same objects
	lastCollisonTime = glfwGetTime();
	color = collider->color;
	//Play deflect sound
	Audio::PlayAudio("src/Audio/solid.wav", false);
	HorizontalReverse();
}

void Ball::Move()
{
	//Don't move the ball when it's on pause mode
	if (GameManager::pause)
		return;

	//If the ball is going out of bounds horizontally add The score and restart the game
	if ((transform[3].x >= 1.05 && direction.x > 0) || (transform[3].x <= -1.05f && direction.x < 0)) {
		if (direction.x > 0)
			UI::scoreA++;
		else
			UI::scoreB++;
		//Play Wining sound
		Audio::PlayAudio("src/Audio/bleep.wav", false);
		//Play the screen shake
		Effects::StartShake();
		HorizontalReverse();
		Restart();
	}
	//If the ball is going out of bounds vertically
	if ((transform[3].y>=1 && direction.y>0) || (transform[3].y<-1 && direction.y<0))
		VerticalReverse();

	transform = glm::translate(transform, glm::vec3(direction.x,direction.y,0) * UI::ballSpeed * Time::Get().DeltaTime());
}

void Ball::VerticalReverse()
{
	direction = glm::vec2(direction.x, -1 * direction.y);
}

void Ball::HorizontalReverse()
{
	direction = glm::vec2(-1 * direction.x, direction.y);
}

void Ball::Restart()
{
	color = glm::vec4(1.0, 1.0, 1.0, 1.0);
	transform = glm::mat4(1.0);
	transform = glm::scale(transform, size);
}
