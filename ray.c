// ray.c
#include <float.h>
#include <stdlib.h>
#include "headers/ray.h"
#include "headers/vec3.h"

extern ray *ray_set;
extern ray **rusg;
extern char *rava;
extern long rforemost;
extern long rayam;

ray *reqray (float *orig, float *direction){
	for (; rava[rforemost] == UAVA; rforemost++);
	rava[rforemost] = UAVA;
	rusg[rforemost]->orig = orig;
	rusg[rforemost]->dir = direction;
	return rusg[rforemost];
}

void rfree (ray *e){
	if (e == NULL)
		return;
	long step = (e - ray_set) / 3;
	rava[step] = AVA;
	rforemost = step;
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
	float *temp1 = mul (dir, t);
	float *temp2 = add (orig, temp1);
	vfree (temp1);
	return temp2;
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
