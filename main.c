#define im_w 500
#define RATIO ((float)16 / (float)9)
#define FL (float)1
#define vp_h (float)2
#define sample 500

#include <stdio.h>
#include "vec3.h"
#include "color.h"
#include "ray.h"
#include "hittable.h"
#include "sphere.h"
#include "camera.h"

extern world *objsh;

int main(void){
	initalize ();
	add_obj(req(0, 0, -1), 0.5);										// add_obj可以添加物体
	add_obj(req(0, -100.5, -1), 100);
	render (objsh);
}
