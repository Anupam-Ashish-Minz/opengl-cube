#include "rotation.h"
#include <math.h>

void matmul(float mat[4][4], float *x, float *y, float *z) {
	float xyz[4] = {*x, *y, *z, 1};
	float out[4];
	for (int i = 0; i < 4; i++) {
		out[i] = 0.0;
		for (int j = 0; j < 4; j++) {
			out[i] += mat[i][j] * xyz[j];
		}
	}
	*x = out[0];
	*y = out[1];
	*z = out[2];
}

void rotateX(float rad, float *x, float *y, float *z) {
	float mat[4][4] = {
		{1, 0, 0, 0},
		{0, cos(rad), -sin(rad), 0},
		{0, sin(rad), cos(rad), 0},
		{0, 0, 0, 1},
	};
	matmul(mat, x, y, z);
}

void rotateY(float rad, float *x, float *y, float *z) {
	float mat[4][4] = {
		{cos(rad), 0, sin(rad), 0},
		{0, 1, 0, 0},
		{-sin(rad), 0, cos(rad), 0},
		{0, 0, 0, 1},
	};
	matmul(mat, x, y, z);
}

void rotateZ(float rad, float *x, float *y, float *z) {
	float mat[4][4] = {
		{cos(rad), -sin(rad), 0, 0},
		{sin(rad), cos(rad), 0, 0},
		{0, 0, 1, 0},
		{0, 0, 0, 1},
	};
	matmul(mat, x, y, z);
}

void rotate3PArray(float rad, enum ROT_DIRECTION direction, float points[],
				   int pointsLen) {
	for (int i = 0; i < pointsLen - 2; i += 3) {
		if (direction == ROT_X) {
			rotateX(rad, &points[i], &points[i + 1], &points[i + 2]);
		} else if (direction == ROT_Y) {
			rotateY(rad, &points[i], &points[i + 1], &points[i + 2]);
		} else if (direction == ROT_Z) {
			rotateZ(rad, &points[i], &points[i + 1], &points[i + 2]);
		}
	}
}
