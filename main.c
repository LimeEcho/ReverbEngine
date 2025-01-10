// main.c
#include <stdio.h>
#include "headers/vec3.h"
#include "headers/ray.h"
#include "headers/hittable.h"
#include "headers/sphere.h"
#include "headers/color.h"
#include "headers/material.h"
#include "headers/camera.h"

extern struct world *objsh;
#define DEF 0
#define MET 1
#define DIE 2

int main(void){
	initalize ();						// 初始化上述数据
	material mat1 = add_mat (DIE, req(1, 0, 0), 1.5);//0.140486, 0.80181, 0.529821), 1.5);
	material mat2 = add_mat (DEF, req(0.425464, 0.028545, 0.803165));
	material mat3 = add_mat (MET, req(0.803776, 0.784217, 0.000836), 0.7);
	material mat4 = add_mat (MET, req(0.140486, 0.80181, 0.529821), 0.05);

	add_obj(req(-0.8, -0.1, -1), 0.4, mat1);		// add_obj可以添加物体
	add_obj(req(0.8, -0.1, -1), 0.4, mat2);
	add_obj(req(0, -0.1, -1), 0.4, mat4);
	add_obj(req(0, -100.5, -1), 100, mat3);
	render (objsh);						// 渲染选中物体集
	int i;
	scanf ("%d", &i);
}
