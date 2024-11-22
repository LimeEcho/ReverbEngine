#ifndef COLOR
#define COLOR

#include "vec3.h"

void write_color (float *color) {
	double r = rx (color);
	double g = ry (color);
	double b = rz (color);
	int R = (int)(255.999 * r);
	int G = (int)(255.999 * g);
	int B = (int)(255.999 * b);
	printf ("%d %d %d\n", R, G, B);
}

#endif
