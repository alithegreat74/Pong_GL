#pragma once
#include "References.h"
#include "Shader.h"
#include "Texture.h"
#include "UserInterface.h"
#include "GameObject.h"

class Ball;

namespace Effects {

	extern bool shake;
	extern float shakeTime;

	static float vertexData[]{
		//Position     //TexCoords
		 0.5f,  0.5f,  1.0f,  1.0f, // top right
		 0.5f, -0.5f,  1.0f,  0.0f,  // bottom right
		-0.5f,  0.5f,  0.0f,  1.0f,  // top left 
		 0.5f, -0.5f,  1.0f,  0.0f,  // bottom right
		-0.5f,  0.5f,  0.0f,  1.0f,  // top left
		-0.5f, -0.5f,  0.0f,  0.0f   // bottom left
	};

	class Particle {
	public:
		glm::vec2 position, velocity;
		glm::vec4 color;
		float scale;
		float life;
		Particle();
		void Update();
	};
	class ParticleEmitter {
	public:
		ParticleEmitter();
		void RenderParticles(ShaderProgram&shader, Ball& ball,Texture2D&texture);
	private:
		void SpawnParticle(Particle& particle, Ball& object);
		unsigned int GetParticle();
		unsigned int defauleParticleNumber;
		unsigned int particleEmissionRate;
		unsigned int lastRenderedParticle;
		unsigned int vao, vbo;
		std::vector<Particle> particles;
		glm::vec2 CalculateParticleDirection(glm::vec2 dir);
	};
	void StartShake();
	void RenderEffects();
}

/// <summary>
/// The time class uses the singlton pattern so there's only one instance of it
/// It is used to calculate time and delta time
/// </summary>

class Time
{
public:
	//Gets the only instance of the Time class
	//If there is no instance, it creates a new one
	static Time& Get() {
		if (&instance == nullptr)
			instance = Time();

		return instance;
	}
	Time(const Time&) = delete;
	//Calculates the delta time
	void CalculateTime() {
		float time;
		time = (float)glfwGetTime();
		deltaTime = time - lastFrame;
		lastFrame = time;
	}
	float DeltaTime()const {return deltaTime;}

private:
	Time() { return; }
	static Time instance;
	float lastFrame=0.0f;
	float deltaTime=0.0f;
};



