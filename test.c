#include "vec3.c"
int im_h;
float **vusg;
char *vava;
long foremost;
long vam;
float *point_set;
#define sp_in_sq() req (drand48() - 0.5, drand48() - 0.5, 0);		// 在一个正方形里
#define SEED 123
#define im_w 200						// 图像宽度
#define RATIO ((float)16 / (float)9)	// 长宽比
#define FL (float)0.9						// 焦距
#define vp_h (float)2					// 视图高度
#define sample 10						// 采样次数
#define max_depth 50					// 最高深度
#define GAMMA 0.6						// GAMMA预设
#define PMULT 90
#define RMULT 20
void initalize (void){
	im_h = ((int)(im_w / RATIO) < 1) ? 1 : (int)(im_w / RATIO);		// 根据比例计算图像高度
	vam = im_h * im_w * sample * PMULT;
	point_set = (float *)malloc (vam * 3 * sizeof (float));
	vusg = (float **)malloc (vam * sizeof (float *));
	vava = (char *)malloc (vam * sizeof (char));
	char *temava = vava;
	float **temp = vusg;
	foremost = 0;
	for (int i = 0; i < vam; i++){
		temp[i] = point_set + i * 3;
		*(temava++) = AVA;
	}
}

int main(void){
	initalize ();
	for (int i = 0; i<412376; i++){
		req (1, 1, 1);
		printf ("%d\n", i);
	}
	float *a = req (1, 2, 3);
	vfree (a);
	int b = (a - point_set)/3;
	printf ("%d\n", b);
	printf ("%d\n", vava[b]);
}
