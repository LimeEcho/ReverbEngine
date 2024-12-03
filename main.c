#include <stdio.h>
#include "vec3.h"
#include "color.h"
#include "ray.h"
#include "hittable.h"
#include "sphere.h"
#include "camera.h"

int main(void){
	initalize ();
	add_obj(&objsh, &objst, req(0, 0, -1), 0.5);										// add_obj可以添加物体
	add_obj(&objsh, &objst, req(0, -100.5, -1), 100);
	render ();
}
