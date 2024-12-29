// ray.h
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
inline float *origin (ray *iray) {				// 返回起点
	return iray->orig;
}
inline float *direction (ray *iray) {			// 返回方向向量
	return iray->dir;
}
float *at (ray *, float);			// 返回t时的点坐标
inline float size (interval input){
		return input.tmax - input.tmin;
}
inline char contain (interval input, float t){
		return input.tmin <= t && t <= input.tmax;
}
inline char surround (interval input, float t){
		return input.tmin < t && t < input.tmax;
}
float clamp (interval, float);
interval empty ();
interval universe ();
#endif