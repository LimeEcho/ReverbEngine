#ifndef CAMERA
#define CAMERA

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
extern world *objsh;												// 构建场景物体集
extern world *objst;												// 链表结构

#define sp_in_sq() req (randoms() - 0.5, randoms() - 0.5, 0);

void add_obj(float *ct, float radius) {								// 一个标准的操作链表函数（骄傲）∠( ᐛ 」∠)＿
	world *new_obj = malloc(sizeof(world));

	new_obj->hit = &sph_ht;
	new_obj->ct = ct;
	new_obj->radius = radius;
	new_obj->next = NULL;

	if (objsh == NULL) {
		objsh = objst = new_obj;
	}else{
		objst->next = new_obj;
		objst = objst->next;
	}
}

void initalize (void){
	objsh = NULL;													// 构建场景物体集
	objst = objsh;													// 链表结构

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
	file = fopen ("renderOut.ppm", "w");
	fprintf (file, "P3\n%d %d\n255\n", im_w, im_h);
}

float *sp_in_sq (void) {
	return ;
}

ray *get_ray (int x, int y) {
	float *offset = sp_in_sq ();
	float *px_ct = add (px_00_lc, add (mul (px_dl_u, rx (offset) + x), mul (px_dl_v, ry (offset) + y)));	// 像素中心坐标
	float *ray_dir = sub (px_ct, cm_ct);																	// 发射射线
	return reqray (cm_ct, ray_dir);																			// 创建
}

void render (world *world){
	for (int y = 0; y < im_h; y++){
		for (int x = 0; x < im_w; x++){
			float *pix_c = req (0.0, 0.0, 0.0);
			for (int sa = 0; sa < sample; sa++){
				ray *r = get_ray (x, y);
				pix_c = add (pix_c, ray_col (r, world));
			}
			wt_c (mul (pix_c, pix_samples_scale));															// 写出像素颜色（其中检测是否相交）
		}
	}
	printf ("\rCurrent: 100.0%%\n");
}

#endif
