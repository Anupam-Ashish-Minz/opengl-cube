#include "read_shader.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

int main() {
	if (!glfwInit()) {
		fprintf(stderr, "failed to init glfw\n");
		return -1;
	}
	GLFWwindow *window = glfwCreateWindow(500, 500, "cubed", NULL, NULL);
	glfwMakeContextCurrent(window);
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "failed to init glew\n");
		return -1;
	}
	GLuint vertexArray, buffer;
	glGenVertexArrays(1, &vertexArray);
	glBindVertexArray(vertexArray);
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	GLfloat data[9] = {
		-1.0f, -1.0f, 0.0f, ///
		0.0f,  1.0f,  0.0f, ///
		1.0f,  -1.0f, 0.0f, ///
	};
	glBufferData(GL_ARRAY_BUFFER, sizeof(data), &data, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);

	GLuint vs = readShader("shaders/vertex.glsl", GL_VERTEX_SHADER);
	GLuint fs = readShader("shaders/fragment.glsl", GL_FRAGMENT_SHADER);
	GLuint program = glCreateProgram();
	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glUseProgram(program);

	while (!glfwWindowShouldClose(window)) {
		glfwSwapBuffers(window);
		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT);
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}

	return 0;
}
