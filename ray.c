// ray.c
#include <float.h>
#include <stdlib.h>
#include <stdio.h>
#include "headers/ray.h"
#include "headers/vec3.h"

extern ray *ray_set;
extern long rayam;
extern long rforemost;
extern freed *rfreed;
extern freed *rfend;

ray *reqray (float *ori, float *dir){				
	if (rfreed->add != NULL){
		freed *temp = rfreed->next;
		ray *rtemp = rfreed->add;
		free (rfreed);
		rfreed = temp;
		rtemp->orig = ori;
		rtemp->dir = dir;
		return rtemp;
	}else{
		ray *r = ray_set + rforemost;
		/*if (r > ray_set + rayam){
			printf ("RMULT过小!\n");
			exit(1);
		}*/
		r->orig = ori;
		r->dir = dir;
		rforemost++;
		return r;
	}
}

void rfree (ray *e){
	if (e == NULL)
		return;
	vfree (e->orig);
	vfree (e->dir);
	rfend->add = e;
	freed *next = (freed *)malloc (sizeof (freed));
	rfend->next = next;
	rfend = rfend->next;
}

float *origin (ray *iray) {				
	return iray->orig;
}

float *direction (ray *iray) {			
	return iray->dir;
}

float *at (ray *iray, float t){			
	float *orig = origin(iray);
	float *dir = direction(iray);
	float *temp1 = mul (dir, t);
	float *temp2 = add (orig, temp1);
	vfree (temp1);
	return temp2;
}

float clamp (interval input, float x){
	if (x < input.tmin)
		return input.tmin;
	if (x > input.tmax)
		return input.tmax;
	return x;
}

float size (interval input){
	return input.tmax - input.tmin;
}
char contain (interval input, float t){
	return input.tmin <= t && t <= input.tmax;
}
char surround (interval input, float t){
	return input.tmin < t && t < input.tmax;
}

interval empty (){
	interval empty;
	empty.tmin = FLT_MAX;
	empty.tmax = -FLT_MAX;
	return empty;
}

interval universe (){
	interval universe;
	universe.tmin = -FLT_MAX;
	universe.tmax = FLT_MAX;
	return universe;
}
