// sphere.c
#include <math.h>
#include "headers/sphere.h"
#include "headers/vec3.h"
#include "headers/hittable.h"
#include "headers/ray.h"
char sph_ht (float *ct, interval ray_t, float radius, ray *iray, hit_rc *ht){			
	float *oc = sub (ct, origin (iray));												
	float a = square (direction (iray));
	float h = dot (direction (iray), oc);
	float c = square (oc) - squ(radius);
	vfree (oc);
	float delta = squ(h) - a * c;

	if (delta < 0)																		
		return 0;
	float t = (h - sqrt (delta)) / a;													
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
