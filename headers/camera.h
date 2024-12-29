// camera.h
#ifndef CAMERA
#define CAMERA
#include "ray.h"
#include "hittable.h"
void add_obj(float *, float, char, float *);								// 一个操作链表函数（骄傲）∠( ᐛ 」∠)＿
void initalize (void);
float *ray_col (ray *, world *, int);
void render (world *);
#endif
