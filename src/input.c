#include <GLFW/glfw3.h>
#include <stdbool.h>
///
#include "input.h"

void inputHandler(GLFWwindow *window) {
	// physical buttons
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}
