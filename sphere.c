// sphere.c
#include <math.h>
#include "headers/sphere.h"
#include "headers/vec3.h"
#include "headers/hittable.h"
#include "headers/ray.h"
char sph_ht (float *ct, interval ray_t, float radius, ray *iray, hit_rc *ht){			// 对于球体的碰撞检测，利用x² + y² + z² = r²
	float *oc = sub (ct, origin (iray));												// 将射线的起点变为0
	/* 
	   x² + y² + z² = r²
	   (Cₓ - x)² + (Cy - y)² + (Cz - z)² = r²
	   (C - P)²) = (Cₓ - x)² + (Cy - y)² + (Cz - z)²
	   (C - P)² = r²
	   (C - P(t))² = r²
	   (C - (Q + td))² = r²
	   (-td + (C - Q))² = r²
	   t²d * d - 2td * (C - Q) + (C - Q)² = r²
	   t²d * d - 2td * (C - Q) + (C - Q)² - r² = 0
	   这样子就是一个标准的一元二次方程了，利用求根公式即可求出t
	   只需要求出Δ即可
	   如果Δ < 0（原方程无实数根）
	   那么光线不相交
	   如果Δ = 0（原方程有两个相等的实数根）
	   那么光线“擦着边”相交
	   如果Δ > 0（原方程有两个不相等的实数根）
	   那么光线可以穿过球体（两个交点）
	   只需要知道是否相交，所以要知道Δ是不是非负数即可
	 */
	float a = square (direction (iray));
	float h = dot (direction (iray), oc);
	float c = square (oc) - squ(radius);
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
	ht->normal = divi (sub (ht->p, ct), radius);
	float *ot_nm = divi (sub (ht->p, ct), radius);
	st_fc_nm (iray, ot_nm, ht);
	return 1;
}
