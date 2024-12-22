#define im_w 2000						// 图像宽度
#define RATIO ((float)16 / (float)9)	// 长宽比
#define FL (float)1						// 焦距
#define vp_h (float)2					// 视图高度
#define sample 100						// 采样次数
#define max_depth 1000					// 最高深度
#define GAMMA 0.6						// GAMMA预设
#define SEED 123

#include <stdio.h>
#include "vec3.h"
#include "ray.h"
#include "hittable.h"
#include "sphere.h"
#include "color.h"
#include "material.h"
#include "camera.h"

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
int all_frames;							// 像素总数
int cur_frame;							// 现在像素
world *objsh;							// 构建场景物体集
world *objst;
interval scene;							// 场景深度

int main(void){
	initalize ();						// 初始化上述数据
	add_obj(req(-0.6, 0, -2), 0.5, 1);		// add_obj可以添加物体
	add_obj(req(0.5, 0, -1), 0.5, 1);
	add_obj(req(0, -100.5, -1), 100, 1);
	render (objsh);						// 渲染选中物体集
}
