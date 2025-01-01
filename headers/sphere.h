// sphere.h
#pragma once

#ifndef SPHERE
#define SPHERE
#include "ray.h"
#include "hittable.h"
char sph_ht (float *, interval, float, ray *, hit_rc *);			// 对于球体的碰撞检测，利用x² + y² + z² = r²
#endif
