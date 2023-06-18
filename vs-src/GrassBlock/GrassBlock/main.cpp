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
#include "camera.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800
#define WINDOW_NAME "Grass Block"
#define WINDOW_MODE NULL			//NULL	== Windowed
#define WINDOW_SHARED_MODE NULL		//NULL	== Don't share resources
#define SCALE 0.0f					//0		== Original size

// Vertices coordinates
GLfloat vertices[] =
{ //	COORDINATES		/		COLORS		/	TEXTURE COORDS	/		NORMALS		//
	// FRONT SQUARE
	-0.5f, -0.5f, 0.0f,		1.0f, 0.0f, 0.0f,	 0.0f, 0.0f,	0.0f, -0.5f, -0.8f,	// Front lower left corner	- 0
	-0.5f,  0.5f, 0.0f,		0.0f, 1.0f, 0.0f,	 0.0f, 1.0f,	0.0f, -0.5f, -0.8f,	// Front upper left corner	- 1
	 0.5f,  0.5f, 0.0f,		0.0f, 0.0f, 1.0f,	 1.0f, 1.0f,	0.0f, -0.5f, -0.8f,	// Front upper right corner - 2
	 0.5f, -0.5f, 0.0f,		1.0f, 1.0f, 1.0f,	 1.0f, 0.0f,	0.0f, -0.5f, -0.8f,	// Front lower right corner - 3 
	 // BACK SQUARE
	-0.5f, -0.5f, 1.0f,		1.0f, 0.0f, 0.0f,	 0.0f, 0.0f,	0.0f, 0.5f, -0.8f,	// Back lower left corner	- 4
	-0.5f,  0.5f, 1.0f,		0.0f, 1.0f, 0.0f,	 0.0f, 1.0f,	0.0f, 0.5f, -0.8f,	// Back upper left corner	- 5
	 0.5f,  0.5f, 1.0f,		0.0f, 0.0f, 1.0f,	 1.0f, 1.0f,	0.0f, 0.5f, -0.8f,	// Back upper right corner	- 6
	 0.5f, -0.5f, 1.0f,		1.0f, 1.0f, 1.0f,	 1.0f, 0.0f,	0.0f, 0.5f, -0.8f,	// Back lower right corner	- 7
	 // RIGHT SQUARE
	 0.5f,  0.5f, 0.0f,		0.0f, 0.0f, 1.0f,	 1.0f, 1.0f,	0.8f, -0.5f, 0.0f,	// Front upper right corner	- 8
	 0.5f, -0.5f, 0.0f,		1.0f, 1.0f, 1.0f,	 1.0f, 0.0f,	0.8f, -0.5f, 0.0f,	// Front lower right corner	- 9 
	 0.5f,  0.5f, 1.0f,		0.0f, 0.0f, 1.0f,	 0.0f, 1.0f,	0.8f, -0.5f, 0.0f,	// Back upper right corner	- 10
	 0.5f, -0.5f, 1.0f,		1.0f, 1.0f, 1.0f,	 0.0f, 0.0f,	0.8f, -0.5f, 0.0f,	// Back lower right corner	- 11
	 // LEFT SQUARE
	-0.5f, -0.5f, 0.0f,		1.0f, 0.0f, 0.0f,	 0.0f, 0.0f,	-0.8f, 0.5f, 0.0f,	// Front lower left corner	- 12
	-0.5f,  0.5f, 0.0f,		0.0f, 1.0f, 0.0f,	 0.0f, 1.0f,	-0.8f, 0.5f, 0.0f,	// Front upper left corner	- 13
	-0.5f, -0.5f, 1.0f,		1.0f, 0.0f, 0.0f,	 1.0f, 0.0f,	-0.8f, 0.5f, 0.0f,	// Back lower left corner	- 14
	-0.5f,  0.5f, 1.0f,		0.0f, 1.0f, 0.0f,	 1.0f, 1.0f,	-0.8f, 0.5f, 0.0f,	// Back upper left corner	- 15
	// UPPER SQUARE
	-0.5f,  0.5f, 0.0f,		0.0f, 1.0f, 0.0f,	 0.0f, 0.0f,	0.0f, -1.0f, 0.0f,	// Front upper left corner	- 16
	 0.5f,  0.5f, 0.0f,		0.0f, 0.0f, 1.0f,	 0.0f, 0.0f,	0.0f, -1.0f, 0.0f,	// Front upper right corner	- 17
	-0.5f,  0.5f, 1.0f,		0.0f, 1.0f, 0.0f,	 0.0f, 0.0f,	0.0f, -1.0f, 0.0f,	// Back upper left corner	- 18
	 0.5f,  0.5f, 1.0f,		0.0f, 0.0f, 1.0f,	 0.0f, 0.0f,	0.0f, -1.0f, 0.0f,	// Back upper right corner	- 19
	// LOWER SQUARE
	-0.5f, -0.5f, 0.0f,		1.0f, 0.0f, 0.0f,	 0.0f, 0.0f,	0.0f, 1.0f, 0.0f,	// Front lower left corner	- 20
	 0.5f, -0.5f, 0.0f,		1.0f, 1.0f, 1.0f,	 0.0f, 0.0f,	0.0f, 1.0f, 0.0f,	// Front lower right corner	- 21
	-0.5f, -0.5f, 1.0f,		1.0f, 0.0f, 0.0f,	 0.0f, 0.0f,	0.0f, 1.0f, 0.0f,	// Back lower left corner	- 22
	 0.5f, -0.5f, 1.0f,		1.0f, 1.0f, 1.0f,	 0.0f, 0.0f,	0.0f, 1.0f, 0.0f	// Back lower right corner	- 23
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

GLfloat lightVertices[] =
{ //     COORDINATES     //		0.2f difference
	 -0.4f,  -1.2f,  1.3f,
	 -0.4f,  -1.2f,  1.1f,
	 -0.6f,  -1.2f,  1.1f,
	 -0.6f,  -1.2f,  1.3f,
	 -0.4f,  -1.4f,  1.3f,
	 -0.4f,  -1.4f,  1.1f,
	 -0.6f,  -1.4f,  1.1f,
	 -0.6f,  -1.4f,  1.3f
};

GLuint lightIndices[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 4, 7,
	0, 7, 3,
	3, 7, 6,
	3, 6, 2,
	2, 6, 5,
	2, 5, 1,
	1, 5, 4,
	1, 4, 0,
	4, 5, 6,
	4, 6, 7
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
	vao.linkAttrib(vbo, 0, 3, GL_FLOAT, 11 * sizeof(float), NULL);
	vao.linkAttrib(vbo, 1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	vao.linkAttrib(vbo, 2, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float)));
	vao.linkAttrib(vbo, 3, 3, GL_FLOAT, 11 * sizeof(float), (void*)(8 * sizeof(float)));
	// Unbind all to prevent accidental modification
	vao.unbind();
	vbo.unbind();
	ebo.unbind();

	Shader lightShader("light.vert", "light.frag");

	VAO lightVao;
	lightVao.bind();

	VBO lightVbo(lightVertices, sizeof(lightVertices));
	EBO lightEbo(lightIndices, sizeof(lightIndices));

	lightVao.linkAttrib(lightVbo, 0, 3, GL_FLOAT, 3 * sizeof(float), NULL);
	lightVao.unbind();
	lightVbo.unbind();
	lightEbo.unbind();

	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

	glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);

	glm::vec3 blockPos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 blockModel = glm::mat4(1.0f);
	blockModel = glm::translate(blockModel, blockPos);
	
	lightShader.activateShader();
	glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
	glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	shaderProgram.activateShader();
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(blockModel));
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);


	// Load texture from jpg
	Texture grass_block("GrassBlock.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
	grass_block.texUnit(shaderProgram, "tex0", 0);

	// Enable depth buffer
	glEnable(GL_DEPTH_TEST);

	Camera camera(WINDOW_WIDTH, WINDOW_HEIGHT, glm::vec3(0.0f, 0.0f, 2.0f));

	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		// Specify background color
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		camera.inputs(window);
		camera.updateMatrix(45.0f, 0.1f, 100.0f);
		
		// Tell OpenGL which Shader Program we want to use
		shaderProgram.activateShader();
		glUniform3f(glGetUniformLocation(shaderProgram.ID, "camPos"), camera.position.x, camera.position.y, camera.position.z);
		
		camera.matrix(shaderProgram, "camMatrix");

		//// Bind texture to make sure it renders in
		grass_block.bind();
		// Tell opengl to use created program
		// Bind VAO so opengl knows how to use it
		vao.bind();
		//  Draw triangles using GL_TRIANGLES, x amount of coordinates, indice datatype, index of indice 
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);

		lightShader.activateShader();
		camera.matrix(lightShader, "camMatrix");
		lightVao.bind();
		glDrawElements(GL_TRIANGLES, sizeof(lightIndices) / sizeof(int), GL_UNSIGNED_INT, 0);

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

	lightVao.deleteVAO();
	lightVbo.deleteVBO();
	lightEbo.deleteEBO();
	lightShader.deleteShaders();

	// Destroy window
	glfwDestroyWindow(window);
	// Terminate GLFW
	glfwTerminate();

	return 0;
}
