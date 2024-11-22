#ifndef RAY
#define RAY

#include <stdlib.h>

typedef struct ray{
	float *orig;
	float *dir;
} ray;

ray *reqray (float *orig, float *dir){
	ray *nray = malloc (sizeof (ray));
	nray->orig = orig;
	nray->dir = dir;
	return nray;
}

float *origin (ray *iray) {
	return iray->orig;
}

float *direction (ray *iray) {
	return iray->dir;
}

float *at (ray *iray, float t){
	float *orig = iray->orig;
	float *dir = iray->dir;
	return add (orig, mul (dir, t));
}

#endif
