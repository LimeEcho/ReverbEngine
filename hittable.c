// hittable.c
#include "headers/ray.h"
#include "headers/vec3.h"
#include "headers/hittable.h"
#include <stdio.h>

char sph_ht (float *, interval, float, ray *, hit_rc *);											

void st_fc_nm (ray *iray, float *ot_nm, hit_rc *ht){
	ht->ft_fc = dot (direction (iray), ot_nm) < 0;
	ht->normal = ht->ft_fc ? ot_nm : opo (ot_nm);
}

char hit_ray(ray *iray, interval ray_t, hit_rc *ht, world *objs) {
	world *tos = objs;
	hit_rc *temp = malloc(sizeof(hit_rc));
	char hit_anything = 0;
	while (tos != NULL) {																			
		switch (tos->hit_type){
			case 1: {
						if (sph_ht(tos->ct, ray_t, tos->radius, iray, temp)) {						
							hit_anything = 1;														
							ray_t.tmax = temp->t;													
							*ht = *temp;															
							ht->albedo = tos->albedo;
							ht->mat_type = tos->mat_type;
							ht->arg = tos->arg;
						}
						break;
					}
			default:
					printf ("传入数据有误\n");
					exit (1);
		}
		tos = tos->next;  															
	}
	free(temp);
	return hit_anything;
}
