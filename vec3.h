#ifndef VEC_3
#define VEC_3

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define squ(x) ((x)*(x))
float *req (float e1, float e2, float e3){
	float *e = (float *)(malloc (3 * sizeof (float)));
	e[0] = e1;
	e[1] = e2;
	e[2] = e3;
	return e;
}

float rx (float *e){
	return e[0];
}

float ry (float *e){
	return e[1];
}

float rz (float *e){
	return e[2];
}

float *opo (float *e){
	return req (-rx(e), -ry(e), -rz(e));
}

float indr (float *e, int i){
	if (i < 0 || i > 2)
		return 0;
	return e[i];
}

float *indw (float *e, int i){
	if (i < 0 || i > 2)
		return NULL;
	return &e[i];
}

float *add (float *e1, float *e2){
	float x = rx (e1) + rx (e2);
	float y = ry (e1) + ry (e2);
	float z = rz (e1) + rz (e2);
	return req (x, y, z);
}

float *sub (float *e1, float *e2){
	float x = rx (e1) - rx (e2);
	float y = ry (e1) - ry (e2);
	float z = rz (e1) - rz (e2);
	return req (x, y, z);
}

float *mul (float *e1, float m){
	float x = rx (e1) * m;
	float y = ry (e1) * m;
	float z = rz (e1) * m;
	return req (x, y, z);
}

float *divi (float *e1, float d){
	return mul (e1, 1 / d);
}

float square(float *e){
	return squ(rx(e)) + squ(ry(e)) + squ(rz(e));
}

float length (float *e){
	return sqrt (square (e));
}

float *edot (float *u, float *v){
	float x = rx (u) * rx (v);
	float y = ry (u) * ry (v);
	float z = rz (u) * rz (v);
	return req (x, y, z);
}

float dot (float *u, float *v){
	return rx (u) * rx (v)
		+ ry (u) * ry (v)
		+ rz (u) * rz (v);
}

float *cross (float *u, float *v) {
	return req(ry (u) * rz (v) - rz (u) * rz (v),
			rz (u) * rx (v) - rx (u) * rz (v),
			rx (u) * ry (v) - ry (u) * rx (v));
}

float *unit_vec (float *e){
	return divi (e, length (e));
}

void out (float *e){
	printf ("x: %f\ty: %f\tz: %f\n", rx (e), ry (e), rz (e));
}

#endif
