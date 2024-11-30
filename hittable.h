#ifndef HITTABLE
#define HITTABLE

#include "ray.h"

typedef struct hit_record {
	float t;
	float *p;
	float *normal;
	char ft_fc;
} hit_rc;

typedef char (*func_ptr)(float *ct, float tmin, float tmax, float radius, ray *iray, hit_rc *ht);

typedef struct obj_info {
	func_ptr hit;
	float *ct;
	float radius;
	struct obj_info *next;
} obj_info;

void st_fc_nm (ray *iray, float *ot_nm, hit_rc *ht){
	// ot_nm默认已经有了归一化处理

	ht->ft_fc = dot (direction (iray), ot_nm) < 0;
	ht->normal = ht->ft_fc ? ot_nm : opo (ot_nm);
}

char hit_ray(ray *iray, float tmin, float tmax, hit_rc *ht, obj_info *objs) {
    obj_info *tos = objs;

    hit_rc *temp = malloc(sizeof(hit_rc));

    char hit_anything = 0;
    float closest = tmax;

    // 遍历所有的物体
    while (tos != NULL) {

        // 调用碰撞检测函数
        if ((tos->hit)(tos->ct, tmin, closest, tos->radius, iray, temp)) {
            hit_anything = 1;
            closest = temp->t;
            *ht = *temp;  // 确保将结果复制到传入的 hit_record
        }

        tos = tos->next;  // 移动到下一个物体
    }

    free(temp);  // 释放内存
    return hit_anything;
}
/*
char hit_ray (ray *iray, float tmin, float tmax, hit_rc *ht, obj_info *objs){
	hit_rc *temp = malloc(sizeof(hit_rc));
	if (temp == NULL) {
		fprintf(stderr, "Memory allocation failed for temp\n");
		return 0;
	}
	char hit_anything = 0;
	float closest = tmax;
	obj_info *tos = objs;
	while (tos++ != NULL){
		if ((tos->hit)(tos->ct, tmin, closest, tos->radius, iray, temp)){
			hit_anything = 1;
			closest = temp->t;
			ht->t = temp->t;
			ht->p = temp->p;
			ht->normal = temp->normal;
			ht->ft_fc = temp->ft_fc;
		}
		free(temp);
	}
	return hit_anything;
}
*/

// 对于C++，这里需要定义构造函数。但这是C，所以干脆就用一个个单个碰撞检测函数吧(･᷄ὢ･᷅)

#endif
