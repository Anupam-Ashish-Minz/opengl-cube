#ifndef _ROTATION_H
#define _ROTATION_H

enum ROT_DIRECTION {
	ROT_X,
	ROT_Y,
	ROT_Z,
};

// void rotateX(float rad, int *x, int *y, int *z);
// void rotateY(float rad, int *x, int *y, int *z);
// void rotateZ(float rad, int *x, int *y, int *z);

void rotate3PArray(float rad, enum ROT_DIRECTION direction, float points[],
				   int pointsLen);

#endif
