#ifndef HITTABLE
#define HITTABLE

typedef struct hit_record hit_rc;

typedef struct hit_record {
	float t;
	float *p;
	float *normal;
	char ft_fc;
} hit_rc;

typedef struct world {
	char mat_type;
	char hit_type;
	float *ct;
	float radius;
	struct world *next;
} world;

inline void st_fc_nm (ray *iray, float *ot_nm, hit_rc *ht){
	// ot_nm默认已经有了归一化处理

	ht->ft_fc = dot (direction (iray), ot_nm) < 0;
	ht->normal = ht->ft_fc ? ot_nm : opo (ot_nm);
}

char sph_ht (float *, interval, float, ray *, hit_rc *);											// 具体实现在sphere.h中

char hit_ray(ray *iray, interval ray_t, hit_rc *ht, world *objs) {
	world *tos = objs;
	hit_rc *temp = malloc(sizeof(hit_rc));

	char hit_anything = 0;
	while (tos != NULL) {																			// 遍历所有的物体
		switch (tos->hit_type){
			case 1: {
						if (sph_ht(tos->ct, ray_t, tos->radius, iray, temp)) {			// 调用碰撞检测函数
							hit_anything = 1;														// 碰到了就是1
							ray_t.tmax = temp->t;													// 因为将“最近的”作为碰撞点最远的传给了hit函数，所以如果能进到这个if里就是更近的一个
							*ht = *temp;															// 将结果复制到传入的hit_record
						}
						tos = tos->next;  															// 移动到下一个物体
						break;
					}
			default:
					printf ("传入数据有误\n");
					exit (1);
		}
	}
	free(temp);
	return hit_anything;
}
#endif
