#include <stdio.h>
#include <math.h>
#include "vec3.h"
#include "color.h"
#include "ray.h"
#define im_w 400
#define RATIO ((float)16 / (float)9)
#define FL (float)1
#define vp_h (float)2
float hit (float *ct, float radius, ray *iray){				// 碰撞检测，利用x² + y² + z² = r²
	float *oc = sub (ct, origin (iray));					// 将射线的起点变为0
	/* 
	   x² + y² + z² = r²
	   (Cₓ - x)² + (Cy - y)² + (Cz - z)² = r²
	   (C - P)²) = (Cₓ - x)² + (Cy - y)² + (Cz - z)²
	   (C - P)² = r²
	   (C - P(t))² = r²
	   (C - (Q + td))² = r²
	   (-td + (C - Q))² = r²
	   t²d * d - 2td * (C - Q) + (C - Q)² = r²
	   t²d * d - 2td * (C - Q) + (C - Q)² - r² = 0
	   这样子就是一个标准的一元二次方程了，利用求根公式即可求出t
	   只需要求出Δ即可
	   如果Δ < 0（原方程无实数根）
	   那么光线不相交
	   如果Δ = 0（原方程有两个相等的实数根）
	   那么光线“擦着边”相交
	   如果Δ > 0（原方程有两个不相等的实数根）
	   那么光线可以穿过球体（两个交点）
	   只需要知道是否相交，所以要知道Δ是不是非负数即可
	 */
	float a = dot (direction (iray), direction (iray));
	float b = -2.0 * dot (direction (iray), oc);
	float c = dot (oc, oc) - radius * radius;
	float delta = squ (b) - 4 * a * c;

	if (delta < 0){											// 如果不相交
		return -1.0;
	}else{													// 相交
		float t = (-b - sqrt (delta)) / ((float)2 * a);		// 求出方程的解（t）
		return t;
	}
}

void ray_col (ray *iray){
	float *sph_ct = req (0.0, 0.0, -1.0);					// 球体中心
	float t = hit (sph_ct, 0.5, iray);						// t值
	if (t > 0.0){											// 如果相交
		float *normal = unit_vec (sub (at (iray, t), sph_ct));
		write_color (mul(req (rx (normal) + 1.0, ry (normal) + 1.0, rz (normal) + 1), 0.5));	// 那么根据法线向量计算颜色
	}else{
		float *unit_dir = unit_vec (direction (iray));		// 渐变颜色，先使方向归一化
		float a = 0.5 * (ry (unit_dir) + 1.0);				// 渐变系数
		write_color (add (mul (req (1.0, 1.0, 1.0), (1.0 - a)), mul (req (0.5, 0.7, 1.0), a)));
		// blendedValue = (1 - a) * startValue + a * endValue
	}
}

int main(void){
	int im_h = ((int)(im_w / RATIO) < 1) ? 1 : (int)(im_w / RATIO);	// 根据比例计算图像高度

	float vp_w = vp_h * ((double)im_w / im_h);						// 视图宽度
	float *cm_ct = req (0.0, 0.0, 0.0);								// 相机中心

	float *vp_u = req (vp_w, 0.0, 0.0);								// 详见explanation/ViewPort.png
	float *vp_v = req (0.0, -vp_h, 0.0);

	float *px_dl_u = divi (vp_u, im_w);
	float *px_dl_v = divi (vp_v, im_h);

	float *vp_ul = sub(sub (cm_ct, req (0.0, 0.0, FL)), add (divi (vp_u, 2), divi (vp_v, 2)));	// 左上角像素，也就是P (0,0)
	float *px_00_lc = add (vp_ul, mul (add (px_dl_u, px_dl_v), 0.5));							// 左上角像素坐标

	printf ("P3\n%d %d\n255\n", im_w, im_h);													// 下面开始渲染
	for (int y = 0; y < im_h; y++){
		for (int x = 0; x < im_w; x++){
			float *px_ct = add (px_00_lc, add (mul (px_dl_u, x), mul (px_dl_v, y)));			// 像素中心坐标
			float *ray_dir = sub (px_ct, cm_ct);												// 发射射线
			ray *r = reqray (cm_ct, ray_dir);													// 创建
			ray_col (r);																		// 写出像素颜色（其中检测是否相交）
		}
	}
}
