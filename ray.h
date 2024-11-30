// ray.h

#ifndef RAY
#define RAY

#include <stdlib.h>

typedef struct ray{						// 一条射线，包含起点和方向向量
	float *orig;
	float *dir;
} ray;

ray *reqray (float *orig, float *dir){	// 发射一条射线
	ray *nray = malloc (sizeof (ray));
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

#endif
