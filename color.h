// color.h

#ifndef COLOR
#define COLOR

#include "vec3.h"
#include "ray.h"
#include "hittable.h"
#include <stdlib.h>

extern FILE *file;

void wt_c (float *color){
	double r = rx (color);
	double g = ry (color);
	double b = rz (color);
	interval intensity;
	intensity.tmin = 0.0;
	intensity.tmax = 0.9;
	int R = (int)(256 * clamp (intensity, r));
	int G = (int)(256 * clamp (intensity, g));
	int B = (int)(256 * clamp (intensity, b));
	fprintf (file, "%d %d %d\n", R, G, B);
}

float *ray_col (ray *iray, world *objs, int depth){
	if (depth <= 0)
		return req (0, 0, 0);
	hit_rc *rec = malloc (sizeof (hit_rc));
	interval world;
	world.tmin = 0;
	world.tmax = FLT_MAX;
	float *color;
	if (hit_ray (iray, world, rec, objs)){											// 如果相交
		float *dir = rd_on_he (rec->normal);
		color = mul (ray_col (reqray (rec->p, dir), objs, depth - 1), 0.5);//add (rec->normal, req (1, 1, 1)), 0.5);
	}else{
		float *unit_dir = unit_vec (direction (iray));									// 渐变颜色，先使方向归一化
		float a = 0.5 * (ry (unit_dir) + 1.0);											// 渐变系数
		color = add (mul (req (1.0, 1.0, 1.0), (1.0 - a)), mul (req (0.5, 0.7, 1.0), a));
		// blendedValue = (1 - a) * startValue + a * endValue
	}
	return color;
}
#endif
