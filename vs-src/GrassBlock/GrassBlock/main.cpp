#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shader.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800
#define WINDOW_NAME "Square"
#define WINDOW_MODE NULL //NULL == Windowed
#define WINDOW_SHARED_MODE NULL //NULL == Don't share resources

// Vertices coordinates
GLfloat vertices[] =
{
	-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower left corner
	0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower right corner
	0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f, // Upper corner
	-0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner left
	0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner right
	0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f // Inner down
};

// Indices for vertices order
GLuint indices[] =
{
	0, 3, 5, // Lower left triangle
	3, 2, 4, // Lower right triangle
	5, 4, 1 // Upper triangle
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
	vao.linkVBO(vbo, 0);
	// Unbind all to prevent accidental modification
	vao.unbind();
	vbo.unbind();
	ebo.unbind();

	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		// Specify background color
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT);
		// Tell OpenGL which Shader Program we want to use
		shaderProgram.activateShader();
		// Tell opengl to use created program
		// Bind VAO so opengl knows how to use it
		vao.bind();
		//  Draw triangles using GL_TRIANGLES, x amount of coordinates, indice datatype, index of indice 
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		// Swap back buffer with front buffer
		glfwSwapBuffers(window);
		// Poll all GLFW events
		glfwPollEvents();
	}

	// Delete all created objects
	vao.deleteVAO();
	vbo.deleteVBO();
	ebo.deleteEBO();
	shaderProgram.deleteShaders();
	// Destroy window
	glfwDestroyWindow(window);
	// Terminate GLFW
	glfwTerminate();

	return 0;
}
