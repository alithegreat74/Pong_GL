#pragma once
#include "References.h"
#include <iostream>
#include <fstream>
#include <string>

class Shader:RendererObject {
private:
	const char* _shaderSource;
public:
	Shader(const char* filePath,unsigned int shaderType);
	~Shader();

	std::string ReadFromFile(const char* filePath);
	void ValidateShader()const;
	unsigned int GetShader()const { return object_id; }
};

class ShaderProgram :RendererObject {
public:
	ShaderProgram(Shader vertexShader, Shader fragmentShader);
	~ShaderProgram();

	void Bind()const;
	void Unbind()const;
	void ChangeUniform(const char* name, float data)const;
	void ChangeUniform(const char* name, int i1)const;
	void ChangeUniform(const char* name, float f1, float f2, float f3, float f4);
	void ChangeUniform(const char* name, float f1, float f2, float f3);
	void ChangeUniform(const char* name, glm::vec3 value);
	void ChangeUniform(const char* name, glm::mat4 value);

	void Validate()const;
};