#pragma once
#include "References.h"
#include "Shader.h"
#include "Texture.h"
#include "UserInterface.h"

namespace Effects {

	extern bool shake;
	extern float shakeTime;

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
	float deltaTime;
};



