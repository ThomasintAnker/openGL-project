#pragma once

#include<glad/glad.h>
#include<stb/stb_image.h>
#include"shader.h"

class Texture {
public:
	Texture(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType);
public:
	void texUnit(Shader& shader, const char* uniform, GLuint unit);
	void bind();
	void unbind();
	void deleteTexture();
public:
	GLuint ID;
	GLenum type;
};