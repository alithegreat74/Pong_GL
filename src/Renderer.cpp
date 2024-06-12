#include "Renderer.h"

VertexBufferObject::VertexBufferObject(const void* verticies, unsigned int size)
{
	glGenBuffers(1, &object_id);
	Bind();
	glBufferData(GL_ARRAY_BUFFER, size, verticies, GL_STATIC_DRAW);
}

VertexBufferObject::~VertexBufferObject()
{
	glDeleteBuffers(1, &object_id);
}

void VertexBufferObject::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, object_id);
}

void VertexBufferObject::Unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

VertexArrayObject::VertexArrayObject()
{
	glGenVertexArrays(1, &object_id);
	Bind();
}

VertexArrayObject::~VertexArrayObject()
{
	glDeleteVertexArrays(1, &object_id);
}

void VertexArrayObject::Bind() const
{
	glBindVertexArray(object_id);
}

void VertexArrayObject::Unbind() const
{
	glBindVertexArray(0);
}

ElementBufferObject::ElementBufferObject(const void* indicies, unsigned int size)
{
	glGenBuffers(1, &object_id);
	Bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indicies, GL_STATIC_DRAW);
}

ElementBufferObject::~ElementBufferObject()
{
	glDeleteBuffers(1, &object_id);
}

void ElementBufferObject::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, object_id);
}

void ElementBufferObject::Unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, object_id);
}

Time Time::instance;