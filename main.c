// main.c
#include <stdio.h>
#include "headers/vec3.h"
#include "headers/ray.h"
#include "headers/hittable.h"
#include "headers/sphere.h"
#include "headers/color.h"
#include "headers/material.h"
#include "headers/camera.h"

FILE *file;
int im_h;								// 图像高度
float pix_samples_scale;				// 像素采样率
float vp_w;								// 视图宽度
float *cm_ct;							// 相机中心
float *vp_u;							// 视图横坐标
float *vp_v;							// 视图纵坐标
float *px_dl_u;							// 像素宽度
float *px_dl_v;							// 像素高度
float *vp_ul;							// 视图左上角
float *px_00_lc;						// 第一个像素位置
float *all_zero;						// 全0的vec
float *weaken;						// 全0的vec
int all_frames;							// 像素总数
int cur_frame;							// 现在像素
world *objsh;							// 构建场景物体集
world *objst;
interval scene;							// 场景深度

#define DEF 0
#define MET 1

int main(void){
	initalize ();						// 初始化上述数据
	add_obj(req(-0.55, 0, -1), 0.5, MET, req(0.140486, 0.80181, 0.529821));		// add_obj可以添加物体
	add_obj(req(0.55, 0, -1), 0.5, DEF, req(0.425464, 0.028545, 0.803165));
	add_obj(req(0, -100.5, -1), 100, DEF, req(0.803776, 0.784217, 0.000836));
	render (objsh);						// 渲染选中物体集
}
