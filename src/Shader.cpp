#include "Shader.h"

Shader::Shader(const char* filePath, unsigned int shaderType)
{
	std::string src=ReadFromFile(filePath);
	_shaderSource = src.c_str();
	object_id = glCreateShader(shaderType);
	glShaderSource(object_id, 1, &_shaderSource, NULL);
	glCompileShader(object_id);
	ValidateShader();
}

Shader::~Shader()
{
	glDeleteShader(object_id);
}

std::string Shader::ReadFromFile(const char* filePath)
{
	std::ifstream stream(filePath);
	if (!stream.is_open()) {
		std::cout << "Unable to open shader file at " << filePath << "\n";
		return "";
	}

	std::string buffer, out="";

	while (std::getline(stream,buffer))
	{
		out += buffer+'\n';
	}

	return out;
}

void Shader::ValidateShader() const
{
	int success;
	glGetShaderiv(object_id, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		char log[1024];
		glGetShaderInfoLog(object_id, 255, NULL, log);
		std::cout << log << "\n";
		return;
	}
}

ShaderProgram::ShaderProgram(Shader vertexShader, Shader fragmentShader)
{
	object_id = glCreateProgram();
	glAttachShader(object_id, vertexShader.GetShader());
	glAttachShader(object_id, fragmentShader.GetShader());

	glLinkProgram(object_id);

}

ShaderProgram::~ShaderProgram()
{
	glDeleteProgram(object_id);
}

void ShaderProgram::Bind() const
{
	glUseProgram(object_id);
}

void ShaderProgram::Unbind() const
{
	glUseProgram(0);
}

void ShaderProgram::ChangeUniform(const char* name, float data) const
{
	unsigned int location = glGetUniformLocation(object_id, name);
	glUniform1f(location, data);
}

void ShaderProgram::ChangeUniform(const char* name, int i1) const
{
	unsigned int location = glGetUniformLocation(object_id, name);
	glUniform1i(location, i1);
}

void ShaderProgram::ChangeUniform(const char* name, float f1, float f2, float f3,float f4)
{
	unsigned int location = glGetUniformLocation(object_id, name);
	glUniform4f(location, f1, f2, f3, f4);
}

void ShaderProgram::ChangeUniform(const char* name, float f1, float f2, float f3)
{
	unsigned int location = glGetUniformLocation(object_id, name);
	glUniform3f(location, f1, f2, f3);
}

void ShaderProgram::ChangeUniform(const char* name, glm::vec3 value)
{
	unsigned int location = glGetUniformLocation(object_id, name);
	glUniform3f(location, value.x, value.y, value.z);
}

void ShaderProgram::ChangeUniform(const char* name, glm::mat4 value)
{
	unsigned int location = glGetUniformLocation(object_id, name);
	glUniformMatrix4fv(location, 1, false, glm::value_ptr(value));
}

void ShaderProgram::Validate() const
{
	int success;
	glGetProgramiv(object_id, GL_LINK_STATUS, &success);
	if (!success) {
		char log[255];
		glGetProgramInfoLog(object_id, 255, NULL, log);
		std::cout << log<<"\n";
		return;
	}
}
