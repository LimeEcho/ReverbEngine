// vec3.c
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
long vmalloc;
extern float *point_set;
float *set_pt;

float *req (float e1, float e2, float e3){				// 获取，在C++里用class，但是我就是喜欢C！(♯｀∧´)
	if (set_pt == NULL)
		set_pt = point_set;
	++vmalloc;
	float *e = set_pt;
	set_pt += 3;
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
float *opo (float *e){									// 关于世界原点中心对成
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
float randomb (float min, float max){
	return min + drand48 () * (max - min);
}
float *randoml (void){
	return req (drand48(), drand48(), drand48());
}
float *randomlb (float min, float max){
	return req (randomb(min, max), randomb(min, max), randomb(min, max));
}

float *rd_unit_vec (void){
	float *p = NULL;
	float lensq;
	while (!(epsilon < lensq && lensq <= 1)){
		//free (p);
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

char too_small (float *e){
	return (rx (e) < epsilon) && (ry (e) < epsilon) && (rz (e) < epsilon);
}

float *reflect(float *v, float *n) {
	return sub (v, mul (n, 2 * dot (v, n)));
}

float *refract(float *uv, float *n, float etai_over_etat) {
	float temp = dot(opo(uv), n);
	float cos_theta = (temp < 0) ? 1.0 : temp;
	float *r_out_perp = add (uv, mul (n, cos_theta));
	float *r_out_parallel = mul (n, -(float)sqrt(fabs(1.0 - length (r_out_perp))));
	return add (r_out_perp, r_out_parallel);
}
