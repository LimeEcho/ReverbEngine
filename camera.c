// camera.c
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include "headers/camera.h"
#include "headers/ray.h"
#include "headers/vec3.h"
#include "headers/material.h"
#include "headers/color.h"

// 在main最后include的，所以不需要include任何头文件
FILE *file;
int im_h;
float pix_samples_scale;
float vp_w;
float *cm_ct;
float *vp_u;
float *vp_v;
float *px_dl_u;
float *px_dl_v;
float *vp_ul;
float *px_00_lc;
float *weaken;
float *point_set;
ray *ray_set;
float **vusg;
char *vava;
long foremost;
ray **rusg;
char *rava;
long rforemost;
int all_frames;
int cur_frame;
long vam;
long rayam;
world *objsh;												// 构建场景物体集
world *objst;												// 链表结构
interval scene;

#define sp_in_sq() req (drand48() - 0.5, drand48() - 0.5, 0);		// 在一个正方形里
#define SEED 123
#define im_w 700						// 图像宽度
#define RATIO ((float)16 / (float)9)	// 长宽比
#define FL (float)0.9						// 焦距
#define vp_h (float)2					// 视图高度
#define sample 100						// 采样次数
#define max_depth 50					// 最高深度
#define GAMMA 0.6						// GAMMA预设
#define PMULT 12.5
#define RMULT 0.01

#include <stdarg.h>

material add_mat (char mat_type, float *RGB, ...){
	material *new_mat = (material *)malloc (sizeof (material));
	new_mat->mat_type = mat_type;
	if (mat_type == 1 || mat_type == 2){
		va_list args;
		va_start(args, RGB);
		new_mat->arg = (float)va_arg(args, double);
		va_end(args);
	}
	new_mat->RGB = RGB;
	return *new_mat;
}
void add_obj(float *ct, float radius, material mat) {								// 一个操作链表函数（骄傲）∠( ᐛ 」∠)＿
	world *new_obj = (world *)malloc(sizeof(world));

	new_obj->hit_type = 1;
	new_obj->ct = ct;
	new_obj->radius = radius;
	new_obj->mat_type = mat.mat_type;
	new_obj->albedo = mat.RGB;
	new_obj->arg = mat.arg;
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
	im_h = ((int)(im_w / RATIO) < 1) ? 1 : (int)(im_w / RATIO);		// 根据比例计算图像高度

	vam = im_h * im_w * sample * PMULT;
	rayam = im_h * im_w * sample * RMULT;
	point_set = (float *)malloc (vam * 3 * sizeof (float));
	ray_set = (ray *)malloc (rayam * sizeof (ray));

	vusg = (float **)malloc (vam * sizeof (float *));
	vava = (char *)malloc (vam * sizeof (char));
	char *temava = vava;
	float **temp = vusg;
	foremost = 0;
	for (int i = 0; i < vam; i++){
		temp[i] = point_set + i * 3;
		*(temava++) = AVA;
	}

	rusg = (ray **)malloc (rayam * sizeof (ray *));
	rava = (char *)malloc (rayam * sizeof (char));
	char *temrava = rava;
	ray **rtemp = rusg;
	rforemost = 0;
	for (int i = 0; i < rayam; i++){
		rtemp[i] = ray_set + i * 3;
		*(temrava++) = AVA;
	}
	weaken = req (0.8, 0.8, 0.8);

	objsh = NULL;
	objst = objsh;

	pix_samples_scale = 1.0 / sample;

	vp_w = vp_h * ((float)im_w / im_h);								// 视图宽度
	cm_ct = req (0.0, 0.0, 0.0);									// 相机中心

	vp_u = req (vp_w, 0.0, 0.0);									// 详见explanation/ViewPort.png
	vp_v = req (0.0, -vp_h, 0.0);

	px_dl_u = divi (vp_u, im_w);
	px_dl_v = divi (vp_v, im_h);

	float *temp1 = divi (vp_v, 2);
	float *temp2 = divi (vp_u, 2);
	float *temp3 = add (temp1, temp2);
	vfree (temp1);
	vfree (temp2);
	temp1 = req (0.0, 0.0, FL);
	temp2 = sub (cm_ct, temp1);
	vfree (temp1);
	vp_ul = sub(temp2, temp3);	// 左上角像素，也就是P (0,0)
	vfree (temp2);
	vfree (temp3);
	temp1 = add (px_dl_u, px_dl_v);
	temp2 = mul (temp1, 0.5);
	vfree (temp1);
	px_00_lc = add (vp_ul, temp2);							// 左上角像素坐标

	all_frames = im_h * im_w * sample;
	cur_frame = 0;

	scene.tmin = 0.001;
	scene.tmax = FLT_MAX;

	file = fopen ("renderOut.ppm", "w");
	fprintf (file, "P3\n%d %d\n255\n", im_w, im_h);
}

long raycoltime;
float *ray_col (ray *iray, world *objs, int depth){
	if (depth <= 0)
		return req(0,0,0);
	++raycoltime;
	hit_rc *rec = malloc (sizeof (hit_rc));
	float *color;
	if (hit_ray (iray, scene, rec, objs)){												// 如果相交
		ray *scattered;
		float *atten = rec->albedo;
		int cont;
		switch (rec->mat_type){
			case 0: {
						cont = diffuse(atten, iray, rec, &atten, &scattered);
						break;
					}
			case 1: {
						cont = metal(atten, iray, rec, &atten, &scattered, rec->arg);
						break;
					}
			case 2: {
						cont = dielectric(atten, iray, rec, &atten, &scattered, rec->arg);
						break;
					}
			default: {
						 printf ("传入数据错误\n");
						 exit (1);
					 }
		}
		if (cont){
			float *temp1 = ray_col(scattered, objs, depth - 1);
			rfree (scattered);
			float *temp2 = edot (atten, temp1);
			vfree (temp1);
			return temp2;
		}else{
			return req(0,0,0);
		}
	}else{
		float *unit_dir = unit_vec (direction (iray));									// 渐变颜色，先使方向归一化
		vfree (unit_dir);
		float a = 0.5 * (ry (unit_dir) + 1.0);											// 渐变系数
		float *temp1 = req (0.5, 0.7, 1.0);
		float *temp2 = mul (temp1, a);
		vfree (temp1);
		temp1 = req (1.0, 1.0, 1.0);
		float *temp3 = mul (temp1, (1.0 - a));
		vfree (temp1);
		color = add (temp3, temp2);
		vfree (temp2);
		vfree (temp3);
		// blendedValue = (1 - a) * startValue + a * endValue
	}
	free (rec);
	return color;
}

void render (world *world){
	float *temp1;
	float *temp2;
	float *temp3;
	for (int y = 0; y < im_h; y++){
		for (int x = 0; x < im_w; x++){
			float *pix_c = req (0, 0, 0);
			for (int sa = 0; sa < sample; sa++){
				if (++cur_frame % 100000 == 0)
					printf ("process: %8d/%8d\n", cur_frame / 100000, all_frames / 100000);
				float *offset = sp_in_sq ();
				temp1 = mul (px_dl_v, ry (offset) + y);
				temp2 = mul (px_dl_u, rx (offset) + x);
				temp3 = add (temp2, temp1);
				vfree (temp1);
				vfree (temp2);
				float *px_ct = add (px_00_lc, temp3);	// 像素中心坐标
				vfree (temp3);
				float *ray_dir = sub (px_ct, cm_ct);																	// 发射射线
				ray *r = reqray (cm_ct, ray_dir);
				float *col = ray_col (r, world, max_depth);
				rfree (r);
				pix_c = add (pix_c, col);
				vfree (col);
			}
			wt_c (mul (pix_c, pix_samples_scale));															// 写出像素颜色（其中检测是否相交）
			vfree (pix_c);
		}
	}
	printf ("\rCurrent: 100.0%%\n");
}
