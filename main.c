#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <float.h>
#include "vec3.h"
#include "color.h"
#include "ray.h"
#include "hittable.h"
#include "sphere.h"
#define im_w 600
#define RATIO ((float)16 / (float)9)
#define FL (float)1
#define vp_h (float)2

void add_obj(obj_info **objsh, obj_info **objst, float *ct, float radius) {				// 一个标准的操作链表函数（骄傲）∠( ᐛ 」∠)＿
:q
	obj_info *new_obj = malloc(sizeof(obj_info));

	new_obj->hit = &sph_ht;
	new_obj->ct = ct;
	new_obj->radius = radius;
	new_obj->next = NULL;

	if (*objsh == NULL) {
		*objsh = *objst =  new_obj;
	}else{
		(*objst)->next = new_obj;
		*objst = (*objst)->next;
	}
}

void ray_col (ray *iray, obj_info *objs){
	hit_rc *rec = malloc (sizeof (hit_rc));
	if (hit_ray (iray, 0, FLT_MAX, rec, objs)){											// 如果相交
		write_color (mul (add (rec->normal, req (1, 1, 1)), 0.5));
	}else{
		float *unit_dir = unit_vec (direction (iray));									// 渐变颜色，先使方向归一化
		float a = 0.5 * (ry (unit_dir) + 1.0);											// 渐变系数
		write_color (add (mul (req (1.0, 1.0, 1.0), (1.0 - a)), mul (req (0.5, 0.7, 1.0), a)));
		// blendedValue = (1 - a) * startValue + a * endValue
	}
}

int main(void){
	int im_h = ((int)(im_w / RATIO) < 1) ? 1 : (int)(im_w / RATIO);						// 根据比例计算图像高度

	obj_info *objsh = NULL;																// 构建场景物体集
	obj_info *objst = objsh;															// 链表结构
	add_obj(&objsh, &objst, req(0, 0, -1), 0.5);										// add_obj可以添加物体
	add_obj(&objsh, &objst, req(0, -100.5, -1), 100);

	float vp_w = vp_h * ((double)im_w / im_h);											// 视图宽度
	float *cm_ct = req (0.0, 0.0, 0.0);													// 相机中心

	float *vp_u = req (vp_w, 0.0, 0.0);													// 详见explanation/ViewPort.png
	float *vp_v = req (0.0, -vp_h, 0.0);

	float *px_dl_u = divi (vp_u, im_w);
	float *px_dl_v = divi (vp_v, im_h);

	float *vp_ul = sub(sub (cm_ct, req (0.0, 0.0, FL)), add (divi (vp_u, 2), divi (vp_v, 2)));	// 左上角像素，也就是P (0,0)
	float *px_00_lc = add (vp_ul, mul (add (px_dl_u, px_dl_v), 0.5));							// 左上角像素坐标
	printf ("P3\n%d %d\n255\n", im_w, im_h);
	for (int y = 0; y < im_h; y++){
		for (int x = 0; x < im_w; x++){
			float *px_ct = add (px_00_lc, add (mul (px_dl_u, x), mul (px_dl_v, y)));			// 像素中心坐标
			float *ray_dir = sub (px_ct, cm_ct);												// 发射射线
			ray *r = reqray (cm_ct, ray_dir);													// 创建
			ray_col (r, objsh);																	// 写出像素颜色（其中检测是否相交）
		}
	}
}
