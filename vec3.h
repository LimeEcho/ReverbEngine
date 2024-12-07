// vec3.h

#ifndef VEC_3
#define VEC_3

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
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

float rx (float *e){									// 返回x值，下面ry，rz一样的
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

float randoms (void){
	return 1.0f / ((float)rand() / (RAND_MAX + 1.0));
}

float randomb (float min, float max){
	return min + randoms () * (max - min);
}

float *randoml (void){
	return req (randoms(), randoms(), randoms());
}

float *randomlb (float min, float max){
	return req (randomb(min, max), randomb(min, max), randomb(min, max));
}

float *rd_unit_vec (){
	float *p;
	float lensq;
	while (!(epsilion < lensq && lensq <= 1){
		free (p);
		p = randomlb (-1, 1);
		lensq = square (p);
	}
	return divi (p / sqrt (lensq));
}

#endif
