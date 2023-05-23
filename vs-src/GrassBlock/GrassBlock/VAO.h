#pragma once

#include <glad/glad.h>
#include <iostream>
#include "VBO.h"

class VAO {
public:
	VAO();
	virtual ~VAO() = default;
public:
	void linkVBO(VBO& vbo, GLuint layout);
	void bind();
	void unbind();
	void deleteVAO();
public:
	GLuint ID;
};
