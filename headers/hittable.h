// hittable.h
#pragma once

#ifndef HITTABLE
#define HITTABLE
#include "ray.h"
#include "vec3.h"
typedef struct hit_record {
	float t;
	float *p;
	float *normal;
	char ft_fc;
	float *albedo;
	float arg;
	char mat_type;
} hit_rc;
typedef struct world {
	char mat_type;
	char hit_type;
	float *ct;
	float radius;
	float *albedo;
	float arg;
	struct world *next;
} world;
void st_fc_nm (ray *, float *, hit_rc *);
char hit_ray(ray *, interval, hit_rc *, world *);
#endif
