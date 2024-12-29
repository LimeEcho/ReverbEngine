// headers/vec3.h
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <fcntl.h>
#include <unistd.h>
#include "headers/vec3.h"
#define squ(x) ((x)*(x))
#define dg2rd(x) (x*M_PI/180.0)
#define epsilon 1e-6f
float *req (float e1, float e2, float e3){				// 获取，在C++里用class，但是我就是喜欢C！(♯｀∧´)
	float *e = (float *)(malloc (3 * sizeof (float)));
	e[0] = e1;
	e[1] = e2;
	e[2] = e3;
	return e;
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

float *edot (float *u, float *v){
	float x = rx (u) * rx (v);
	float y = ry (u) * ry (v);
	float z = rz (u) * rz (v);
	return req (x, y, z);
}

float *rd_unit_vec (void){
	float *p = NULL;
	float lensq;
	while (!(epsilon < lensq && lensq <= 1)){
		free (p);
		p = randomlb (-1, 1);
		lensq = square (p);
	}
	return divi (p, (float)sqrt (lensq));
}

float *rd_on_he (float *normal){
	float * on = rd_unit_vec();
	if (dot (on, normal) > 0.0)
		return on;
	else
		return opo (on);
}
