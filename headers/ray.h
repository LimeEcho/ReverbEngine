// ray.h
#pragma once

#ifndef RAY
#define RAY
typedef struct ray {						// 一条射线，包含起点和方向向量
	float *orig;
	float *dir;
} ray;
typedef struct interval {
	float tmin;
	float tmax;
} interval;
ray *reqray (float *, float *);	// 发射一条射线
float *origin (ray *);				// 返回起点
float *direction (ray *);			// 返回方向向量
float *at (ray *, float);			// 返回t时的点坐标
float size (interval);
char contain (interval, float);
char surround (interval, float);
float clamp (interval, float);
interval empty ();
interval universe ();
#endif
