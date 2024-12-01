// color.h

#ifndef COLOR
#define COLOR

#include "vec3.h"

extern FILE *file;
void write_color (float *color) {		// 为了ppm格式而写的
	double r = rx (color);
	double g = ry (color);
	double b = rz (color);
	int R = (int)(255.999 * r);
	int G = (int)(255.999 * g);
	int B = (int)(255.999 * b);
	fprintf (file, "%d %d %d\n", R, G, B);
}

#endif
