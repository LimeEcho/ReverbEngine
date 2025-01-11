// sphere.c
#include <math.h>
#include "headers/sphere.h"
#include "headers/vec3.h"
#include "headers/hittable.h"
#include "headers/ray.h"
char sph_ht (float *ct, interval ray_t, float radius, ray *iray, hit_rc *ht){			// 对于球体的碰撞检测，利用x² + y² + z² = r²
	float *oc = sub (ct, origin (iray));												// 将射线的起点变为0
	float a = square (direction (iray));
	float h = dot (direction (iray), oc);
	float c = square (oc) - squ(radius);
	vfree (oc);
	float delta = squ(h) - a * c;

	if (delta < 0)																		// 如果不相交
		return 0;
	float t = (h - sqrt (delta)) / a;													// 求出方程的解（t1）
	if (!surround (ray_t, t)){
		if (!surround (ray_t, t)){
			t = (h + sqrt (delta)) / a;
			return 0;
		}
	}
	ht->t = t;
	ht->p = at (iray, t);
	float *temp1 = sub (ht->p, ct);
	ht->normal = divi (temp1, radius);
	float *ot_nm = divi (temp1, radius);
	vfree (temp1);
	st_fc_nm (iray, ot_nm, ht);
	return 1;
}
