// vec3.h

#ifndef VEC_3
#define VEC_3

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <fcntl.h>
#include <unistd.h>
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

inline float rx (float *e){
	return e[0];
}

inline float ry (float *e){
	return e[1];
}

inline float rz (float *e){
	return e[2];
}

inline float *opo (float *e){									// 关于世界原点中心对成
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

inline float *divi (float *e1, float d){
	return mul (e1, 1 / d);
}

inline float square(float *e){
	return squ(rx(e)) + squ(ry(e)) + squ(rz(e));
}

inline float length (float *e){
	return sqrt (square (e));
}

float *edot (float *u, float *v){
	float x = rx (u) * rx (v);
	float y = ry (u) * ry (v);
	float z = rz (u) * rz (v);
	return req (x, y, z);
}

inline float dot (float *u, float *v){
	return rx (u) * rx (v)
		+ ry (u) * ry (v)
		+ rz (u) * rz (v);
}

inline float *cross (float *u, float *v) {
	return req(ry (u) * rz (v) - rz (u) * rz (v),
			rz (u) * rx (v) - rx (u) * rz (v),
			rx (u) * ry (v) - ry (u) * rx (v));
}

inline float *unit_vec (float *e){
	return divi (e, length (e));
}

inline float randomb (float min, float max){
	return min + drand48 () * (max - min);
}

inline float *randoml (void){
	return req (drand48(), drand48(), drand48());
}

inline float *randomlb (float min, float max){
	return req (randomb(min, max), randomb(min, max), randomb(min, max));
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

inline char too_small (float *e){
	return (rx (e) < epsilon) && (ry (e) < epsilon) && (rz (e) < epsilon);
}

inline float *reflect(float *v, float *n) {
	return sub (v, mul (n, 2 * dot (v, n)));
}
#endif
