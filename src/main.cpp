#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
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
	// GLfloat data[48] = {
	// 	// pos(x,y,z), normals(x,y,z)
	// 	-1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, ///
	// 	+1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, ///
	// 	-1.0f, +1.0f, 0.0f, 0.0f, 0.0f, 0.0f, ///
	// 	+1.0f, +1.0f, 0.0f, 0.0f, 0.0f, 0.0f, ///
	// 	///
	// 	-1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, ///
	// 	+1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, ///
	// 	-1.0f, +1.0f, 1.0f, 0.0f, 0.0f, 0.0f, ///
	// 	+1.0f, +1.0f, 1.0f, 0.0f, 0.0f, 0.0f, ///
	// };
	// translate(0., 0., -0.5, data, 48);
	GLfloat data[9] = {
		-1.0f, -1.0f, -0.5f, ///
		+1.0f, -1.0f, -0.5f, ///
		+1.0f, +1.0f, -0.5f, ///
	};
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			printf("%f ", data[i * 3 + j]);
		}
		printf("\n");
	}
	printf("\n");
	// rotate3PArray(M_PI / 4, ROT_Y, data, 48);
	// rotate3PArray(M_PI / 4, ROT_X, data, 24);
	glBufferData(GL_ARRAY_BUFFER, sizeof(data), &data, GL_STATIC_DRAW);

	unsigned int indexes[36] = {
		// 0, 1, 2
		// 0, 1, 2, 1, 2, 3, /// front
		// 4, 5, 6, 4, 6, 7, /// back
		// 0, 1, 4, 1, 4, 5, /// top
		// 2, 3, 6, 3, 6, 7, /// bottom
		// 0, 2, 4, 2, 4, 6, // left
		// 1, 3, 5, 3, 5, 7, /// right
	};
	GLuint ebo;
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	// glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexes), indexes,
	// 			 GL_STATIC_DRAW);

	// glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);
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
		glClear(GL_COLOR_BUFFER_BIT);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		// glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		// glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
		// inputHandler(window);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}
