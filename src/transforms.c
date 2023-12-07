///
#include "transforms.h"

void translate(float x, float y, float z, float vertices[], int len) {
	for (int i = 0; i < len - 5; i += 6) {
		vertices[i] += x;
		vertices[i + 1] += y;
		vertices[i + 2] += z;
	}
}
