#include "GameObject.h"

GameObject::GameObject(Texture2D& texture, ShaderProgram& shader)
	: texture(texture), shader(shader), vbo(vbo), vao(vao), transform(glm::mat4(1.0f)), color(glm::vec4(1.0f)), size(glm::vec2(1.0f))

{
	vao = VertexArrayObject();
	vbo = VertexBufferObject(vertecies, sizeof(vertecies));
	vbo.Unbind();
	vao.Unbind();
	this->shader = shader;
	this->texture = texture;
}



void GameObject::Render()
{
	shader.Bind();
	texture.Bind();
	vao.Bind();
	glDrawArrays(GL_TRIANGLES, 0, 4);
	vao.Unbind();
	texture.Unbind();
	shader.Unbind();
}
