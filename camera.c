// camera.c
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <string.h>
#include "headers/camera.h"
#include "headers/ray.h"
#include "headers/vec3.h"
#include "headers/material.h"
#include "headers/color.h"

FILE *file;
float *weaken;
float *point_set;
ray *ray_set;
freed *vfreed;
freed *vfend;
long foremost;
freed *rfreed;
freed *rfend;
long rforemost;
world *objsh;
long vam;
long rayam;

static int im_h;
static float pix_samples_scale;
static float *w;
static float *u;
static float *v;
static float vp_h;
static float vp_w;
static float *cm_ct;
static float *vp_u;
static float *vp_v;
static float *px_dl_u;
static float *px_dl_v;
static float *vp_ul;
static float *px_00_lc;
static float *defocus_disk_u;
static float *defocus_disk_v;
static float *lookfrom;
static float *lookat;
static float *vup;
static int all_frames;
static int cur_frame;
static world *objst;
static interval scene;

#define sp_in_sq() req (drand48() - 0.5, drand48() - 0.5, 0);
#define SEED 123
#define im_w 700
#define RATIO (16.0 / 9.0)
#define vfov 20
#define DEFOCUS_ANGLE 10.0
#define FOCUS_DIST 3.4
#define sample 100
#define max_depth 5
#define GAMMA 0.6
#define WEAKEN 0.8
#define PMULT 20
#define RMULT 0.001

#include <stdarg.h>

material *add_mat (char mat_type, float *RGB, ...){
	material *new_mat = (material *)malloc (sizeof (material));
	new_mat->mat_type = mat_type;
	if (mat_type == 1 || mat_type == 2){
		va_list args;
		va_start(args, RGB);
		new_mat->arg = (float)va_arg(args, double);
		va_end(args);
	}
	new_mat->RGB = RGB;
	return new_mat;
}

void add_obj(float *ct, float radius, material *mat) {
	world *new_obj = (world *)malloc(sizeof(world));

	new_obj->hit_type = 1;
	new_obj->ct = ct;
	new_obj->radius = radius;
	new_obj->mat_type = mat->mat_type;
	new_obj->albedo = mat->RGB;
	new_obj->arg = mat->arg;
	new_obj->next = NULL;
	free (mat);

	if (objsh == NULL) {
		objsh = objst = new_obj;
	}else{
		objst->next = new_obj;
		objst = objst->next;
	}
}

void initialize (void){
	srand48 (SEED);
	im_h = ((int)(im_w / RATIO) < 1) ? 1 : (int)(im_w / RATIO);

	vam = im_h * im_w * sample * PMULT;
	rayam = im_h * im_w * sample * RMULT;
	point_set = (float *)malloc (vam * 3 * sizeof (float));
	memset (point_set, 0, vam * 3 * sizeof (float));
	ray_set = (ray *)malloc (rayam * sizeof (ray));
	memset (ray_set, 0, rayam * sizeof (ray));

	foremost = 0;

	vfreed = (freed *)malloc (sizeof (freed));
	vfend = vfreed;
	vfreed->add = NULL;
	vfreed->next = NULL;

	rforemost = 0;

	rfreed = (freed *)malloc (sizeof (freed));
	rfend = rfreed;
	rfreed->add = NULL;
	rfreed->next = NULL;

	weaken = req (WEAKEN, WEAKEN, WEAKEN);
	lookfrom = req (-2, 2, 1);
	lookat = req (0, 0, -1);
	vup = req (0, 1, 0);

	objsh = NULL;
	objst = objsh;

	pix_samples_scale = 1.0 / sample;

	float theta = de2ra (vfov);
	float h = tan (theta / 2);

	vp_h = 2 * h * FOCUS_DIST;
	vp_w = vp_h * ((float)im_w / im_h);
	cm_ct = lookfrom;

	float *temp1 = sub (lookfrom, lookat);
	w = unit_vec (temp1);
	vfree (temp1);
	temp1 = cross (vup, w);
	u = unit_vec (temp1);
	vfree (temp1);
	v = cross (w, u);

	vp_u = mul (u, vp_w);
	temp1 = opo (v);
	vp_v = mul (temp1, vp_h);
	vfree (temp1);

	px_dl_u = divi (vp_u, im_w);
	px_dl_v = divi (vp_v, im_h);

	temp1 = mul (w, FOCUS_DIST);
	float *temp2 = sub (cm_ct, temp1);
	vfree (temp1);
	temp1 = divi (vp_u, 2);
	float *temp3 = sub(temp2, temp1);
	vfree (temp2);
	vfree (temp1);
	temp1 = divi (vp_v, 2);
	vp_ul = sub (temp3, temp1);
	vfree (temp3);
	vfree (temp1);
	temp1 = add (px_dl_u, px_dl_v);
	temp2 = mul (temp1, 0.5);
	vfree (temp1);
	px_00_lc = add (vp_ul, temp2);

	float defocus_radius = FOCUS_DIST * tan (de2ra(DEFOCUS_ANGLE / 2));
	defocus_disk_u = mul (u, defocus_radius);
	defocus_disk_v = mul (v, defocus_radius);

	all_frames = im_h * im_w * sample;
	cur_frame = 0;

	scene.tmin = 0.001;
	scene.tmax = FLT_MAX;

	file = fopen ("renderOut.ppm", "w");
	fprintf (file, "P3\n%d %d\n255\n", im_w, im_h);
}

float *ray_col (ray *iray, world *objs, int depth){
	if (depth <= 0)
		return req(0,0,0);
	hit_rc *rec = malloc (sizeof (hit_rc));
	float *color;
	if (hit_ray (iray, scene, rec, objs)){
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
		free (rec);
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
		float *unit_dir = unit_vec (direction (iray));
		vfree (unit_dir);
		float a = 0.5 * (ry (unit_dir) + 1.0);
		float *temp1 = req (0.5, 0.7, 1.0);
		float *temp2 = mul (temp1, a);
		vfree (temp1);
		temp1 = req (1.0, 1.0, 1.0);
		float *temp3 = mul (temp1, (1.0 - a));
		vfree (temp1);
		color = add (temp3, temp2);
		vfree (temp2);
		vfree (temp3);

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
				float *px_ct = add (px_00_lc, temp3);
				vfree (temp3);
				float *ray_dir = sub (px_ct, cm_ct);
				float *ct;
				if (DEFOCUS_ANGLE <= 0){
					ct = cm_ct;
				}else{
					float *p = rd_in_unit_disk();
					temp1 = mul (defocus_disk_u, rx(p));
					temp2 = mul (defocus_disk_v, ry(p));
					temp3 = add (temp1, temp2);
					vfree (temp1);
					vfree (temp2);
					ct = add (cm_ct, temp3);
				}
				ray *r = reqray (ct, ray_dir);
				float *col = ray_col (r, world, max_depth);
				rfree (r);
				pix_c = add (pix_c, col);
				vfree (col);
			}
			wt_c (mul (pix_c, pix_samples_scale));
			vfree (pix_c);
		}
	}
	printf ("\rCurrent: 100.0%%\n");
}
