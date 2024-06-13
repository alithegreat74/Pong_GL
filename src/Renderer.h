#pragma once
#include "References.h"
#include "Shader.h"
#include "Texture.h"

class VertexBufferObject:RendererObject {
public:
	//Creates a array buffer and loads the vertecies in the gpu
	VertexBufferObject(const void* verticies, unsigned int size);
	~VertexBufferObject();
	//Sets it as the current array
	void Bind()const;
	//Unset it as the current array
	void Unbind()const;
};

class VertexArrayObject :RendererObject {
public:
	//Creates a vertex array
	VertexArrayObject();
	~VertexArrayObject();
	//Set it as the current vertex array
	void Bind()const;
	//Unset it as the current vertex array
	void Unbind()const;
};

class ElementBufferObject :RendererObject {
public:
	//Creates an element array buffer and loads the indicies in the gpu
	ElementBufferObject(const void* indicies, unsigned int size);
	~ElementBufferObject();
	//Set it as the current element array
	void Bind()const;
	//Unset it as the current element array
	void Unbind()const;
};

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



