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
	initialize ();						// 初始化上述数据
	material ground = add_mat (DEF, req(0.8, 0.8, 0));
	material center = add_mat (DEF, req(0.1, 0.2, 0.5));
	material left = add_mat (DIE, req(1, 1, 1), 1.5);
	material bubble = add_mat (DIE, req(1, 1, 1), 1.0 / 1.5);
	material right = add_mat (MET, req(0.8, 0.6, 0.2), 1.0);

	add_obj (req(0.0, -100.5, -1.0), 100, ground);		// add_obj可以添加物体
	add_obj (req(0.0, 0.0, -1.2), 0.5, center);
	add_obj (req(-1.0, 0.0, -1.0), 0.5, left);
	add_obj (req(-1.0, 0.0, -1.0), 0.4, bubble);
	add_obj (req(1.0, 0.0, -1.0), 0.5, right);
	render (objsh);						// 渲染选中物体集
}
