#pragma once

#include <glad/glad.h>
#include <iostream>
#include "VBO.h"

class VAO {
public:
	VAO();
	virtual ~VAO() = default;
public:
	void linkAttrib(VBO& vbo, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);
	void bind();
	void unbind();
	void deleteVAO();
public:
	GLuint ID;
};
