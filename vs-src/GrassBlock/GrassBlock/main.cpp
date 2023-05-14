#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800
#define WINDOW_NAME "Square"
#define WINDOW_MODE NULL //NULL == Windowed
#define WINDOW_SHARED_MODE NULL //NULL == Don't share resources

// Vertex Shader source code
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
//Fragment Shader source code
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";

int main() {

	// GLFW init specifying version and opengl profile
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Coordinates of 2 triangles to make a square
	GLfloat vertices[] = {
		-0.5f, -0.5f, 0.0f, //bottom left
		0.5f, -0.5f, 0.0f,	//bottom right
		-0.5f, 0.5f, 0.0f,	//top left
		-0.5f, 0.5f, 0.0f,	//top left
		0.5f, 0.5f, 0.0f,	//top right
		0.5f, -0.5f, 0.0f	//bottom right
	};

	// Create window
	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME, WINDOW_MODE, WINDOW_SHARED_MODE);

	if (window == NULL) 
	{
		std::cout << "Failed to create glfwWindow" << std::endl;
		glfwTerminate();
		return -1;
	}
	
	// Add window to current context
	glfwMakeContextCurrent(window);

	// Load glad which configures opengl
	gladLoadGL();

	// Specify port of opengl in window
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

	// Create and compile vertex shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	// Create and compile fragment shader	
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	// Create shader program object to link shaders to
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	// Delete shaders as they are not needed anymore
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// Create references for Vertex Aray Object and Vertex Buffer Object
	GLuint VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	// Bind created VAO to current VAO
	glBindVertexArray(VAO);

	// Bind VBO while specifying it's a opengl array buffer
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// Introduce vertices into VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Configure vertex attribute for opengl to read and enable said attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), NULL);
	glEnableVertexAttribArray(0);

	// Bind VAO and VBO to 0 to make sure they can't be modified
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	while (!glfwWindowShouldClose(window)) {
		// Specify background color
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clear back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT);
		// Tell opengl to use created program
		glUseProgram(shaderProgram);
		// Bind VAO so opengl knows how to use it
		glBindVertexArray(VAO);
		// Draw both triangles using GL_TRIANGLES with 6 coordinates
		glDrawArrays(GL_TRIANGLES, 0, 6);
		// Swap back buffer with front buffer
		glfwSwapBuffers(window);
		// Poll all GLFW events
		glfwPollEvents();
	}

	// Delete created objects
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);
	// Destroy window
	glfwDestroyWindow(window);
	// Terminate GLFW
	glfwTerminate();
	return 0;
}