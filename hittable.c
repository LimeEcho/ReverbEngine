// headers/hittable.h
#ifndef HITTABLE
#define HITTABLE

#include "headers/ray.h"
#include "headers/vec3.h"
#include <stdio.h>

typedef struct hit_record hit_rc;

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


char sph_ht (float *, interval, float, ray *, hit_rc *);											// 具体实现在headers/sphere.h中

char hit_ray(ray *iray, interval ray_t, hit_rc *ht, world *objs) {
	world *tos = objs;
	hit_rc *temp = malloc(sizeof(hit_rc));

	char hit_anything = 0;
	while (tos != NULL) {																			// 遍历所有的物体
		switch (tos->hit_type){
			case 1: {
						if (sph_ht(tos->ct, ray_t, tos->radius, iray, temp)) {						// 调用碰撞检测函数
							hit_anything = 1;														// 碰到了就是1
							ray_t.tmax = temp->t;													// 因为将“最近的”作为碰撞点最远的传给了hit函数，所以如果能进到这个if里就是更近的一个
							*ht = *temp;															// 将结果复制到传入的hit_record
							ht->albedo = tos->albedo;
							ht->mat_type = tos->mat_type;
						}
						break;
					}
			default:
					printf ("传入数据有误\n");
					exit (1);
		}
		tos = tos->next;  															// 移动到下一个物体
	}
	free(temp);
	return hit_anything;
}
#endif
