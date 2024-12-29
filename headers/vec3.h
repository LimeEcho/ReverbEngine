// vec3.h

#ifndef VEC_3
#define VEC_3

#define squ(x) ((x)*(x))
#define epsilon 1e-6f
#include <stdlib.h>
#include <math.h>

float *req (float, float, float);				// 获取，在C++里用class，但是我就是喜欢C！(♯｀∧´)
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
float indr (float *, int);
float *indw (float *, int);
float *add (float *, float *);
float *sub (float *, float *);
float *mul (float *, float);
inline float *divi (float *e1, float d){
	return mul (e1, 1 / d);
}
inline float square(float *e){
	return squ(rx(e)) + squ(ry(e)) + squ(rz(e));
}
inline float length (float *e){
	return sqrt (square (e));
}
float *edot (float *, float *);
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
float *rd_unit_vec (void);
float *rd_on_he (float *);
inline char too_small (float *e){
	return (rx (e) < epsilon) && (ry (e) < epsilon) && (rz (e) < epsilon);
}
inline float *reflect(float *v, float *n) {
	return sub (v, mul (n, 2 * dot (v, n)));
}
#endif