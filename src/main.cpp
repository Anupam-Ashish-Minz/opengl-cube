#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
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

	GLuint VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	float data[32] = {
		0.0f, 0.0f, 0.0f, ///
		0.0f, 1.0f, 0.0f, ///
		1.0f, 0.0f, 0.0f, ///
		1.0f, 1.0f, 0.0f, ///
						  ///
		0.0f, 0.0f, 1.0f, ///
		0.0f, 1.0f, 1.0f, ///
		1.0f, 0.0f, 1.0f, ///
		1.0f, 1.0f, 1.0f, ///
	};
	glBufferData(GL_ARRAY_BUFFER, sizeof(data), &data, GL_STATIC_DRAW);

	unsigned int indexes[36] = {
		0, 1, 2, 2, 3, 1, /// front face
		4, 5, 6, 6, 7, 4, /// back
		0, 4, 1, 1, 5, 4, /// top
		3, 6, 4, 4, 7, 6, /// bottom
		0, 4, 6, 6, 2, 0, /// left
		2, 5, 7, 7, 3, 2  /// right
	};
	GLuint EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexes), indexes,
				 GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(0);

	GLuint vs = readShader("shaders/vertex.glsl", GL_VERTEX_SHADER);
	GLuint fs = readShader("shaders/fragment.glsl", GL_FRAGMENT_SHADER);
	GLuint program = glCreateProgram();
	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glUseProgram(program);

	unsigned int uModel = glGetUniformLocation(program, "model");
	unsigned int uView = glGetUniformLocation(program, "view");
	unsigned int uProj = glGetUniformLocation(program, "projection");

	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 proj = glm::mat4(1.0f);
	view = glm::translate(view, glm::vec3(-0.5f, -0.5f, -3.0f));
	proj = glm::perspective(glm::radians(45.0f),
							(float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f,
							100.0f);

	glUniformMatrix4fv(uView, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(uProj, 1, GL_FALSE, glm::value_ptr(proj));

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT);

		// glBindVertexArray(VAO);
		// glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::rotate(model, (float)glfwGetTime(),
							glm::vec3(0.5f, 1.0f, 0.0f));
		glUniformMatrix4fv(uModel, 1, GL_FALSE, glm::value_ptr(model));

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
		// inputHandler(window);

		glfwSwapBuffers(window);
	}
	glfwTerminate();
	return 0;
}
