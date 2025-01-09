// ray.c
#include <float.h>
#include <stdlib.h>
#include "headers/ray.h"
#include "headers/vec3.h"
extern ray *ray_set;
extern vec_usg *rusg;
extern vec_usg *rforemost;

ray *reqray (float *orig, float *dir){	// 发射一条射线
	vec_usg *tem = rforemost;
	while (tem->state == UAVA)
		tem = tem->next;
	tem->state = UAVA;
	rforemost = tem;
	ray *nray = rforemost->add;
	nray->orig = orig;
	nray->dir = dir;
	return nray;
}

float *origin (ray *iray) {				// 返回起点
	return iray->orig;
}
float *direction (ray *iray) {			// 返回方向向量
	return iray->dir;
}

float *at (ray *iray, float t){			// 返回t时的点坐标
	float *orig = iray->orig;
	float *dir = iray->dir;
	return add (orig, mul (dir, t));
}

float clamp (interval input, float x){
	if (x < input.tmin)
		return input.tmin;
	if (x > input.tmax)
		return input.tmax;
	return x;
}

float size (interval input){
	return input.tmax - input.tmin;
}
char contain (interval input, float t){
	return input.tmin <= t && t <= input.tmax;
}
char surround (interval input, float t){
	return input.tmin < t && t < input.tmax;
}

interval empty (){
	interval empty;
	empty.tmin = FLT_MAX;
	empty.tmax = -FLT_MAX;
	return empty;
}

interval universe (){
	interval universe;
	universe.tmin = -FLT_MAX;
	universe.tmax = FLT_MAX;
	return universe;
}
