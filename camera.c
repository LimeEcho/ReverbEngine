// camera.c
#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include "headers/camera.h"
#include "headers/ray.h"
#include "headers/vec3.h"
#include "headers/material.h"
#include "headers/color.h"

// 在main最后include的，所以不需要include任何头文件
extern FILE *file;
extern int im_h;
extern float pix_samples_scale;
extern float vp_w;
extern float *cm_ct;
extern float *vp_u;
extern float *vp_v;
extern float *px_dl_u;
extern float *px_dl_v;
extern float *vp_ul;
extern float *px_00_lc;
extern float *all_zero;
extern float *weaken;
extern int all_frames;
extern int cur_frame;
extern world *objsh;												// 构建场景物体集
extern world *objst;												// 链表结构
extern interval scene;

#define sp_in_sq() req (drand48() - 0.5, drand48() - 0.5, 0);		// 在一个正方形里
#define SEED 123
#define im_w 700						// 图像宽度
#define RATIO ((float)16 / (float)9)	// 长宽比
#define FL (float)1						// 焦距
#define vp_h (float)2					// 视图高度
#define sample 30						// 采样次数
#define max_depth 200					// 最高深度
#define GAMMA 0.6						// GAMMA预设

void add_obj(float *ct, float radius, char mat_type, float *RGB) {								// 一个操作链表函数（骄傲）∠( ᐛ 」∠)＿
	world *new_obj = (world *)malloc(sizeof(world));

	new_obj->hit_type = 1;
	new_obj->ct = ct;
	new_obj->radius = radius;
	new_obj->mat_type = mat_type;
	new_obj->albedo = req (rx(RGB), ry(RGB), rz(RGB));
	new_obj->next = NULL;

	if (objsh == NULL) {
		objsh = objst = new_obj;
	}else{
		objst->next = new_obj;
		objst = objst->next;
	}
}

void initalize (void){
	srand48 (SEED);

	all_zero = req (0, 0, 0);
	weaken = req (0.8, 0.8, 0.8);

	objsh = NULL;
	objst = objsh;

	im_h = ((int)(im_w / RATIO) < 1) ? 1 : (int)(im_w / RATIO);		// 根据比例计算图像高度

	pix_samples_scale = 1.0 / sample;

	vp_w = vp_h * ((float)im_w / im_h);								// 视图宽度
	cm_ct = req (0.0, 0.0, 0.0);									// 相机中心

	vp_u = req (vp_w, 0.0, 0.0);									// 详见explanation/ViewPort.png
	vp_v = req (0.0, -vp_h, 0.0);

	px_dl_u = divi (vp_u, im_w);
	px_dl_v = divi (vp_v, im_h);

	vp_ul = sub(sub (cm_ct, req (0.0, 0.0, FL)), add (divi (vp_u, 2), divi (vp_v, 2)));	// 左上角像素，也就是P (0,0)
	px_00_lc = add (vp_ul, mul (add (px_dl_u, px_dl_v), 0.5));							// 左上角像素坐标

	all_frames = im_h * im_w;
	cur_frame = 0;

	scene.tmin = 0.001;
	scene.tmax = FLT_MAX;

	file = fopen ("renderOut.ppm", "w");
	fprintf (file, "P3\n%d %d\n255\n", im_w, im_h);
}
float *ray_col (ray *iray, world *objs, int depth){
	if (depth <= 0)
		return all_zero;
	hit_rc *rec = malloc (sizeof (hit_rc));
	float *color;
	if (hit_ray (iray, scene, rec, objs)){												// 如果相交
		ray *scattered;
		float *atten = rec->albedo;
		switch (rec->mat_type){
			case 1: {
						if (metal(atten, iray, rec, &atten, &scattered)){
							return edot (atten, ray_col(scattered, objs, depth - 1));
						}else{
							return all_zero;
						}
					}
			case 0: {
						if (diffuse(atten, iray, rec, &atten, &scattered)){
							return edot (atten, ray_col(scattered, objs, depth - 1));
						}else{
							return all_zero;
						}
					}
			default: {
						 printf ("传入数据错误\n");
						 exit (1);
					 }
		}
	}else{
		float *unit_dir = unit_vec (direction (iray));									// 渐变颜色，先使方向归一化
		float a = 0.5 * (ry (unit_dir) + 1.0);											// 渐变系数
		color = add (mul (req (1.0, 1.0, 1.0), (1.0 - a)), mul (req (0.5, 0.7, 1.0), a));
		// blendedValue = (1 - a) * startValue + a * endValue
	}
	free (rec);
	return color;
}

void render (world *world){
	for (int y = 0; y < im_h; y++){
		for (int x = 0; x < im_w; x++){
			if (cur_frame++ % 1000 == 0)
				printf ("process: %5d / %5d\n", cur_frame / 1000, all_frames / 1000);
			float *pix_c = all_zero;
			for (int sa = 0; sa < sample; sa++){
				float *offset = sp_in_sq ();
				float *px_ct = add (px_00_lc, add (mul (px_dl_u, rx (offset) + x), mul (px_dl_v, ry (offset) + y)));	// 像素中心坐标
				float *ray_dir = sub (px_ct, cm_ct);																	// 发射射线
				free (offset);
				ray *r = reqray (cm_ct, ray_dir);
				float *col = ray_col (r, world, max_depth);
				free (r);
				pix_c = add (pix_c, col);
			}
			wt_c (mul (pix_c, pix_samples_scale));															// 写出像素颜色（其中检测是否相交）
			free (pix_c);
		}
	}
	printf ("\rCurrent: 100.0%%\n");
}
