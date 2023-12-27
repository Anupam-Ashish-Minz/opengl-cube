#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
///
// #include "input.h"
// #include "rotation.h"
#include "shader.hpp"
// #include "transforms.h"

#define WINDOW_WIDTH 500
#define WINDOW_HEIGHT 500

void MessageCallback(GLenum source, GLenum type, GLenum id, GLenum severity,
					 GLsizei length, const GLchar *message,
					 const void *userParams) {
	fprintf(stderr,
			"GL CALLBACK: %s type = 0x%x, severity = 0x%x, message: %s\n",
			(type == GL_DEBUG_TYPE_ERROR) ? "** GL ERROR **" : "", type,
			severity, message);
}

int main() {
	if (!glfwInit()) {
		fprintf(stderr, "failed to init glfw\n");
		return -1;
	}
	GLFWwindow *window =
		glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "cubed", NULL, NULL);
	glfwMakeContextCurrent(window);
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "failed to init glew\n");
		return -1;
	}

	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(MessageCallback, 0);

	GLuint vertexArray, buffer;
	glGenVertexArrays(1, &vertexArray);
	glBindVertexArray(vertexArray);
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	unsigned int data[32] = {
		0, 0, 1, ///
		0, 1, 1, ///
		1, 0, 1, ///
		1, 1, 1, ///
		///
		0, 0, 0, ///
		0, 1, 0, ///
		1, 0, 0, ///
		1, 1, 0, ///
	};
	glBufferData(GL_ARRAY_BUFFER, sizeof(data), &data, GL_STATIC_DRAW);

	// glm::mat4 proj = glm::perspective(
	// 	glm::radians(45.0f), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f,
	// 	100.0f);

	unsigned int indexes[36] = {
		0, 1, 2, 2, 3, 1, /// front face
		4, 5, 6, 6, 7, 4, /// back
		0, 4, 1, 1, 5, 4, /// top
		3, 6, 4, 4, 7, 6, /// bottom
		0, 4, 6, 6, 2, 0, /// left
		2, 5, 7, 7, 3, 2  /// right
	};
	GLuint ebo;
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexes), indexes,
				 GL_STATIC_DRAW);

	// glVertexAttribPointer(0, 3, GL_UNSIGNED_INT, GL_FALSE,
	// 					  3 * sizeof(unsigned int), 0);
	glVertexAttribPointer(0, 3, GL_UNSIGNED_INT, GL_FALSE,
						  3 * sizeof(unsigned int), 0);
	glEnableVertexAttribArray(0);

	GLuint vs = readShader("shaders/vertex.glsl", GL_VERTEX_SHADER);
	GLuint fs = readShader("shaders/fragment.glsl", GL_FRAGMENT_SHADER);
	GLuint program = glCreateProgram();
	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glUseProgram(program);

	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT);
		// glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
		// inputHandler(window);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}
