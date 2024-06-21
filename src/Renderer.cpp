#include "Renderer.h"

bool Effects::shake = false;
float Effects::shakeTime = 0;

Time Time::instance;

void Effects::StartShake()
{
	//Set the shake components
	shake = true;
	shakeTime = UI::shakeTime;
}

//right now we only have the screen shake effect
void Effects::RenderEffects()
{
	//if the shake time is over stop the shake
	if (shakeTime <= 0) {
		shake = false;
		return;
	}
	//decrement shake time as it gets further
	shakeTime -= Time::Get().DeltaTime()*10;
}


Effects::Particle::Particle():position(glm::vec2(0.0)),velocity(glm::vec2(0.0)),color(glm::vec4(0.0)),scale(0), life(0)
{

}


void Effects::Particle::Update()
{
	life -= Time::Get().DeltaTime();
	if (life > 0) {
		position -= velocity*Time::Get().DeltaTime();
		color.a -= Time::Get().DeltaTime()*10;
	}
}


//Create 100 particles and store their pointers in a dynamic array 
Effects::ParticleEmitter::ParticleEmitter():defauleParticleNumber(100),particleEmissionRate(3),lastRenderedParticle(0), particles(particles)
{
	for (unsigned int i = 0; i < defauleParticleNumber; i++) {
		particles.push_back(Particle());
	}

	//Configure the vertex buffer and array buffer for the particle system

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Effects::vertexData), Effects::vertexData, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 4, GL_FLOAT, false, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 4, GL_FLOAT, false, 4 * sizeof(float), (void*)(2 * sizeof(float)));
	glEnableVertexAttribArray(1);
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}


void Effects::ParticleEmitter::RenderParticles(ShaderProgram& shader, Ball& ball, Texture2D& texture)
{
	for (unsigned int i = 0; i < particleEmissionRate; i++) {
		//Spawn new particles based on the emission rate
		unsigned int particleNumber = GetParticle();
		Particle& particle = particles[particleNumber];
		SpawnParticle(particle, ball);
	}
	//Render and update the particles that are alive
	for (auto& particle : particles) {
		if (particle.life <= 0)
			continue;
		shader.Bind();
		shader.ChangeUniform("color", particle.color);
		shader.ChangeUniform("offset", particle.position);
		shader.ChangeUniform("scale", glm::vec2(0.02f, 0.04));
		texture.Bind();
		glBindVertexArray(vao);

		glDrawArrays(GL_TRIANGLES, 0, 6);

		glBindVertexArray(0);
		texture.Unbind();
		shader.Unbind();

		particle.Update();
	}
}

void Effects::ParticleEmitter::SpawnParticle(Particle& particle, Ball& object)
{
	glm::vec2 dir = CalculateParticleDirection(object.direction);
	particle.position = glm::vec2(object.transform[3].x,object.transform[3].y);
	particle.color = glm::vec4(object.color.x, object.color.y, object.color.z, 1.0);
	particle.life = 1.0f;
	particle.velocity = object.direction * UI::ballSpeed * 0.1f;
}

//This function will search all the particles in the vector and finds and returns the first one that is not alive
unsigned int Effects::ParticleEmitter::GetParticle()
{
	//look for dead particles after the last rendered particle
	for (unsigned int i = lastRenderedParticle; i < defauleParticleNumber; i++) {
		if (particles[i].life <= 0.0) {
			lastRenderedParticle = i;
			return i;
		}
	}
	//Else look for dead particles from the start
	for (unsigned int i = 0; i < lastRenderedParticle; i++)
	{
		if (particles[i].life <= 0.0) {
			lastRenderedParticle = i;
			return i;
		}
	}
	//If there is no dead particle, overide the first one
	lastRenderedParticle = 0;
	return 0;
}

glm::vec2 Effects::ParticleEmitter::CalculateParticleDirection(glm::vec2 dir)
{
	float x,y;
	if (dir.x > 0)
		x = 1;
	else if (dir.x < 0)
		x = -1;
	else
		x = 0;

	if (dir.y > 0)
		y = 1;
	else if (dir.y < 0)
		y = -1;
	else
		y = 0;

	return glm::vec2(x, y);
}
