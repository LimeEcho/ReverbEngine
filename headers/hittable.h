// hittable.h
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
	char mat_type;
} hit_rc;
typedef struct world {
	char mat_type;
	char hit_type;
	float *ct;
	float radius;
	float *albedo;
	struct world *next;
} world;
inline void st_fc_nm (ray *iray, float *ot_nm, hit_rc *ht){
	// ot_nm默认已经有了归一化处理

	ht->ft_fc = dot (direction (iray), ot_nm) < 0;
	ht->normal = ht->ft_fc ? ot_nm : opo (ot_nm);
}
char hit_ray(ray *, interval, hit_rc *, world *);
#endif
