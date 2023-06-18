#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "shader.h"

class Camera {
public:
	Camera(int _width, int _height, glm::vec3 _position);
	virtual ~Camera() = default;
public:
	void updateMatrix(float FOVdeg, float nearPlane, float farPlane);
	void matrix(Shader& shader, const char* uniform);
	void inputs(GLFWwindow* window);
public:
	int width;
	int height;
	float speed;
	float sensitivity;
	bool firstClick;
	
	glm::vec3 position;
	glm::vec3 orientation;
	glm::vec3 up;
	glm::mat4 cameraMatrix;

};