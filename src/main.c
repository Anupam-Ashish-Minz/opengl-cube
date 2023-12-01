#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdbool.h>
#include <stdio.h>
///
#include "input.h"
#include "shader.h"

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
	GLfloat data[24] = {
		-0.75f, -0.75f, 0.0f, ///
		+0.75f, -0.75f, 0.0f, ///
		-0.75f, +0.75f, 0.0f, ///
		+0.75f, +0.75f, 0.0f, ///
		///
		-0.75f, -0.75f, 0.75f, ///
		+0.75f, -0.75f, 0.75f, ///
		-0.75f, +0.75f, 0.75f, ///
		+0.75f, +0.75f, 0.75f, ///
	};
	glBufferData(GL_ARRAY_BUFFER, sizeof(data), &data, GL_STATIC_DRAW);

	unsigned int indexes[36] = {
		0, 1, 2, 1, 2, 3, /// front
		4, 5, 6, 4, 6, 7, /// back
		0, 1, 4, 1, 4, 5, /// top
		2, 3, 6, 3, 6, 7, /// bottom
		0, 2, 4, 2, 4, 6, // left
		1, 3, 5, 3, 5, 7, /// right
	};
	GLuint ebo;
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexes), indexes,
				 GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);

	GLuint vs = readShader("shaders/vertex.glsl", GL_VERTEX_SHADER);
	GLuint fs = readShader("shaders/fragment.glsl", GL_FRAGMENT_SHADER);
	GLuint program = glCreateProgram();
	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glUseProgram(program);

	int fragmentScreenSize = glGetUniformLocation(program, "screenSize");
	glUniform2f(fragmentScreenSize, WINDOW_WIDTH, WINDOW_HEIGHT);

	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT);
		// glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
		inputHandler(window);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}
