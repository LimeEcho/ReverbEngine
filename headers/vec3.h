// vec3.h
#pragma once

#ifndef VEC_3
#define VEC_3

#define squ(x) ((x)*(x))
#define epsilon 1e-6f
#include <stdlib.h>
#include <math.h>

float *req (float, float, float);				// 获取，在C++里用class，但是我就是喜欢C！(♯｀∧´)
float rx (float *);
float ry (float *);
float rz (float *);
float *opo (float *);									// 关于世界原点中心对成
float indr (float *, int);
float *indw (float *, int);
float *add (float *, float *);
float *sub (float *, float *);
float *mul (float *, float);
float *divi (float *, float);
float square(float *);
float length (float *);
float *edot (float *, float *);
float dot (float *, float *);
float *cross (float *, float *);
float *unit_vec (float *);
float randomb (float, float);
float *randoml (void);
float *randomlb (float, float);
float *rd_unit_vec (void);
float *rd_on_he (float *);
char too_small (float *);
float *reflect(float *, float *);
float *refract(float *, float *, float);
#endif
