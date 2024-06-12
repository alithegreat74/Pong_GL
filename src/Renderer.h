#pragma once
#include "References.h"
#include "Shader.h"
#include "Texture.h"

class VertexBufferObject:RendererObject {
public:
	VertexBufferObject(const void* verticies, unsigned int size);
	~VertexBufferObject();

	void Bind()const;
	void Unbind()const;
};

class VertexArrayObject :RendererObject {
public:
	VertexArrayObject();
	~VertexArrayObject();

	void Bind()const;
	void Unbind()const;
};

class ElementBufferObject :RendererObject {
public:
	ElementBufferObject(const void* indicies, unsigned int size);
	~ElementBufferObject();

	void Bind()const;
	void Unbind()const;
};

class Time
{
public:
	static Time& Get() {
		if (&instance == nullptr)
			instance = Time();

		return instance;
	}
	Time(const Time&) = delete;
	void CalculateTime() {
		float time;
		time = (float)glfwGetTime();
		deltaTime = time - lastFrame;
		lastFrame = time;
	}
	float DeltaTime()const {return deltaTime;}

private:
	Time(){}
	static Time instance;
	float lastFrame=0.0f;
	float deltaTime;
};



