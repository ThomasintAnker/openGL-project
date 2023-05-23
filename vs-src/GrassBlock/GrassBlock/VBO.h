#pragma once

#include <glad/glad.h>

class VBO {
public:
	VBO(GLfloat* vertices, GLsizeiptr size);
	virtual ~VBO() = default;
public:
	void bind();
	void unbind();
	void deleteVBO();
public:
	GLuint ID;
};