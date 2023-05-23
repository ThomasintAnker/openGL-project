#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>

#include "texture.h"
#include "shader.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800
#define WINDOW_NAME "Grass Block"
#define WINDOW_MODE NULL		//NULL	== Windowed
#define WINDOW_SHARED_MODE NULL //NULL	== Don't share resources
#define SCALE 0.0f				//0		== Original size

// Vertices coordinates
GLfloat vertices[] =
{ //	COORDINATES		/		COLORS		//
	-0.5f, -0.5f, 0.0f,		1.0f, 0.0f, 0.0f,	 0.0f, 0.0f,	// Lower left corner
	-0.5f,  0.5f, 0.0f,		0.0f, 1.0f, 0.0f,	 0.0f, 1.0f,	// Upper left corner
	 0.5f,  0.5f, 0.0f,		0.0f, 0.0f, 1.0f,	 1.0f, 1.0f,	// Upper right corner
	 0.5f, -0.5f, 0.0f,		1.0f, 1.0f, 1.0f,	 1.0f, 0.0f		// Lower left corner
};

// Indices for vertices order
GLuint indices[] =
{
	0, 2, 1,	// Upper triangle
	0, 3, 2		// Lower triangle
};

int main()
{
	// GLFW init specifying version and opengl profile
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create window
	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME, WINDOW_MODE, WINDOW_SHARED_MODE);	// Error check if the window fails to create
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Add window to current context
	glfwMakeContextCurrent(window);

	//Load GLAD which configures OpenGL
	gladLoadGL();

	// Specify port of opengl in window
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

	// Generate Shader object using shaders defualt.vert and default.frag
	Shader shaderProgram("default.vert", "default.frag");

	// Generate and bind VAO
	VAO vao;
	vao.bind();

	// Generates and link VBO to vertices
	VBO vbo(vertices, sizeof(vertices));
	// Generates and link EBO to indices
	EBO ebo(indices, sizeof(indices));

	// Link VBO to VAO
	vao.linkAttrib(vbo, 0, 3, GL_FLOAT, 8 * sizeof(float), NULL);
	vao.linkAttrib(vbo, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	vao.linkAttrib(vbo, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	// Unbind all to prevent accidental modification
	vao.unbind();
	vbo.unbind();
	ebo.unbind();

	// Get ID of uniform 'scale'
	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

	Texture grass_block("GrassBlock.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
	grass_block.texUnit(shaderProgram, "tex0", 0);

	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		// Specify background color
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT);
		// Tell OpenGL which Shader Program we want to use
		shaderProgram.activateShader();
		glUniform1f(uniID, SCALE);
		// Bind texture to make sure it renders in
		grass_block.bind();
		// Tell opengl to use created program
		// Bind VAO so opengl knows how to use it
		vao.bind();
		//  Draw triangles using GL_TRIANGLES, x amount of coordinates, indice datatype, index of indice 
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		// Swap back buffer with front buffer
		glfwSwapBuffers(window);
		// Poll all GLFW events
		glfwPollEvents();
	}

	// Delete all created objects
	vao.deleteVAO();
	vbo.deleteVBO();
	ebo.deleteEBO();
	grass_block.deleteTexture();
	shaderProgram.deleteShaders();
	// Destroy window
	glfwDestroyWindow(window);
	// Terminate GLFW
	glfwTerminate();

	return 0;
}
