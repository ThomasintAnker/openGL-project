#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "texture.h"
#include "shader.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800
#define WINDOW_NAME "Grass Block"
#define WINDOW_MODE NULL			//NULL	== Windowed
#define WINDOW_SHARED_MODE NULL		//NULL	== Don't share resources
#define SCALE 0.0f					//0		== Original size

// Vertices coordinates
GLfloat vertices[] =
{ //	COORDINATES		/		COLORS		/	TEXTURE COORDS	//
	// FRONT SQUARE
	-0.5f, -0.5f, 0.0f,		1.0f, 0.0f, 0.0f,	 0.0f, 0.0f,	// Front lower left corner	- 0
	-0.5f,  0.5f, 0.0f,		0.0f, 1.0f, 0.0f,	 0.0f, 1.0f,	// Front upper left corner	- 1
	 0.5f,  0.5f, 0.0f,		0.0f, 0.0f, 1.0f,	 1.0f, 1.0f,	// Front upper right corner - 2
	 0.5f, -0.5f, 0.0f,		1.0f, 1.0f, 1.0f,	 1.0f, 0.0f,	// Front lower right corner - 3 
	 // BACK SQUARE
	-0.5f, -0.5f, 1.0f,		1.0f, 0.0f, 0.0f,	 0.0f, 0.0f,	// Back lower left corner	- 4
	-0.5f,  0.5f, 1.0f,		0.0f, 1.0f, 0.0f,	 0.0f, 1.0f,	// Back upper left corner	- 5
	 0.5f,  0.5f, 1.0f,		0.0f, 0.0f, 1.0f,	 1.0f, 1.0f,	// Back upper right corner	- 6
	 0.5f, -0.5f, 1.0f,		1.0f, 1.0f, 1.0f,	 1.0f, 0.0f,	// Back lower right corner	- 7
	 // RIGHT SQUARE
	 0.5f,  0.5f, 0.0f,		0.0f, 0.0f, 1.0f,	 1.0f, 1.0f,	// Front upper right corner	- 8
	 0.5f, -0.5f, 0.0f,		1.0f, 1.0f, 1.0f,	 1.0f, 0.0f,	// Front lower right corner	- 9 
	 0.5f,  0.5f, 1.0f,		0.0f, 0.0f, 1.0f,	 0.0f, 1.0f,	// Back upper right corner	- 10
	 0.5f, -0.5f, 1.0f,		1.0f, 1.0f, 1.0f,	 0.0f, 0.0f,	// Back lower right corner	- 11
	 // LEFT SQUARE
	-0.5f, -0.5f, 0.0f,		1.0f, 0.0f, 0.0f,	 0.0f, 0.0f,	// Front lower left corner	- 12
	-0.5f,  0.5f, 0.0f,		0.0f, 1.0f, 0.0f,	 0.0f, 1.0f,	// Front upper left corner	- 13
	-0.5f, -0.5f, 1.0f,		1.0f, 0.0f, 0.0f,	 1.0f, 0.0f,	// Back lower left corner	- 14
	-0.5f,  0.5f, 1.0f,		0.0f, 1.0f, 0.0f,	 1.0f, 1.0f,	// Back upper left corner	- 15
	// UPPER SQUARE
	-0.5f,  0.5f, 0.0f,		0.0f, 1.0f, 0.0f,	 1.0f, 1.0f,	// Front upper left corner	- 16
	 0.5f,  0.5f, 0.0f,		0.0f, 0.0f, 1.0f,	 1.0f, 1.0f,	// Front upper right corner	- 17
	-0.5f,  0.5f, 1.0f,		0.0f, 1.0f, 0.0f,	 1.0f, 0.0f,	// Back upper left corner	- 18
	 0.5f,  0.5f, 1.0f,		0.0f, 0.0f, 1.0f,	 1.0f, 0.0f,	// Back upper right corner	- 19
	// LOWER SQUARE
	-0.5f, -0.5f, 0.0f,		1.0f, 0.0f, 0.0f,	 0.0f, 0.0f,	// Front lower left corner	- 20
	 0.5f, -0.5f, 0.0f,		1.0f, 1.0f, 1.0f,	 0.0f, 0.0f,	// Front lower right corner	- 21
	-0.5f, -0.5f, 1.0f,		1.0f, 0.0f, 0.0f,	 0.0f, 0.0f,	// Back lower left corner	- 22
	 0.5f, -0.5f, 1.0f,		1.0f, 1.0f, 1.0f,	 0.0f, 0.0f,	// Back lower right corner	- 23

};

// Indices for vertices order
GLuint indices[] =
{
	0, 1, 2,	// Upper triangle - 1st square - Front
	0, 2, 3,	// Lower triangle - 1st square	
	8, 10, 9,	// Upper triangle - 2nd square - Right
	9, 10, 11,	// Lower triangle - 2nd square
	5, 6, 7,	// Upper triangle - 3rd square - Back
	4, 5, 7,	// Lower triangle - 3rd square 
	14, 15, 13,	// Upper triangle - 4th square - Left
	14, 13, 12,	// Lower triangle - 4th square
	16, 17, 18,	// Upper triangle - 5th square - Upper
	18, 17, 19,	// Lower triangle - 5th square
	20, 21, 22,	// Upper triangle - 6th square - Lower
	22, 21, 23	// Lower triangle - 6th square
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

	float rotation = 0.0f;
	double prevTime = glfwGetTime();

	glEnable(GL_DEPTH_TEST);

	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		// Specify background color
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// Tell OpenGL which Shader Program we want to use
		shaderProgram.activateShader();

		double crntTime = glfwGetTime();
		if (crntTime - prevTime >= 0.002) {
			rotation += 0.5f;
			prevTime = crntTime;
		}

		// Initialize matrix
		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 proj = glm::mat4(1.0f);

		model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
		view = glm::translate(view, glm::vec3(0.0f, -1.0, -5.0));
		proj = glm::perspective(glm::radians(90.0f), (float)(WINDOW_WIDTH / WINDOW_HEIGHT), 0.1f, 100.0f);

		int modelLoc = glGetUniformLocation(shaderProgram.ID, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		int viewLoc = glGetUniformLocation(shaderProgram.ID, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		int projLoc = glGetUniformLocation(shaderProgram.ID, "proj");
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));

		glUniform1f(uniID, SCALE);
		// Bind texture to make sure it renders in
		grass_block.bind();
		// Tell opengl to use created program
		// Bind VAO so opengl knows how to use it
		vao.bind();
		//  Draw triangles using GL_TRIANGLES, x amount of coordinates, indice datatype, index of indice 
		glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(int), GL_UNSIGNED_INT, 0);
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
