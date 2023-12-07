#ifndef _TRANSFORMS_H
#define _TRANSFORMS_H

enum AXIS {
	AXIS_X,
	AXIS_Y,
	AXIS_Z,
};

void translate(float x, float y, float z, float vertices[], int len);

#endif
