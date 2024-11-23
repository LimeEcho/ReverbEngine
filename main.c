#include <stdio.h>
#include "vec3.h"
#include "color.h"
#include "ray.h"
#define W 1000
#define RATIO ((float)16 / (float)9)
#define FL (float)1
#define VH 2

int hit (float *ct, float radius, ray *iray){
	float *oc = sub (ct, origin (iray));
	float a = dot (direction (iray), direction (iray));
	float b = -2.0 * dot (direction (iray), oc);
	float c = dot (oc, oc) - radius * radius;
	float ihit = squ (b) - 4 * a * c;
	return (ihit >= 0);
}

void ray_col (ray *iray){
	if (hit (req (0.0, 0.0, -1.0), 0.5, iray)){
		write_color (req (0.0, 1.0, 0.0));
	}else{
		float *unit_dir = unit_vec (direction (iray));
		float a = 0.5 * (ry (unit_dir) + 1.0);
		write_color (add (mul (req (1.0, 1.0, 1.0), (1.0 - a)), mul (req (0.5, 0.7, 1.0), a)));
	}
}

int main(void){
	int im_h = ((int)(W / RATIO) < 1) ? 1 : (int)(W / RATIO);

	float vp_h = (float)VH;
	float vp_w = vp_h * ((double)W / im_h);
	float *cm_ct = req (0.0, 0.0, 0.0);

	float *vp_u = req (vp_w, 0.0, 0.0);
	float *vp_v = req (0.0, -vp_h, 0.0);

	float *px_dl_u = divi (vp_u, W);
	float *px_dl_v = divi (vp_v, im_h);

	float *vp_ul = sub(sub (cm_ct, req (0.0, 0.0, FL)), add (divi (vp_u, 2), divi (vp_v, 2)));
	float *px_00_lc = add (vp_ul, mul (add (px_dl_u, px_dl_v), 0.5));

	// Render

	printf ("P3\n%d %d\n255\n", W, im_h);
	for (int y = 0; y < im_h; y++){
		for (int x = 0; x < W; x++){
			float *px_ct = add (px_00_lc, add (mul (px_dl_u, x), mul (px_dl_v, y)));
			float *ray_dir = sub (px_ct, cm_ct);
			ray *r = reqray (cm_ct, ray_dir);

			ray_col (r);
		}
	}
}
