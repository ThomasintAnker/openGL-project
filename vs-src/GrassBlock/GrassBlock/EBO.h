#pragma once

#include <glad/glad.h>

class EBO {	
public:
	EBO(GLuint* indices, GLsizeiptr size);
	virtual ~EBO() = default;
public:
	void bind();
	void unbind();
	void deleteEBO();
public:
	GLuint ID;
};