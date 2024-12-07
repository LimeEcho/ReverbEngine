#define im_w 500
#define RATIO ((float)16 / (float)9)
#define FL (float)1
#define vp_h (float)2
#define sample 100

#include <stdio.h>
#include "vec3.h"
#include "color.h"
#include "ray.h"
#include "hittable.h"
#include "sphere.h"
#include "camera.h"

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
world *objsh;														// 构建场景物体集
world *objst;														// 链表结构

int main(void){
	initalize ();
	add_obj(req(-0.5, 0, -1), 0.5);										// add_obj可以添加物体
	add_obj(req(0, -100.5, -1), 100);
	render (objsh);
}
