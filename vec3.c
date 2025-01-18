// vec3.c
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>
#include "headers/vec3.h"

extern float *point_set;
extern long vam;
extern long foremost;
extern freed *vfreed;
extern freed *vfend;

float *req (float e1, float e2, float e3){				
	if (e1 == 0 && e2 == 0 && e3 == 0)
		return NULL;
	if (vfreed->add != NULL){
		freed *temp = vfreed->next;
		float *vtemp = vfreed->add;
		free (vfreed);
		vfreed = temp;
		vtemp[0] = e1;
		vtemp[1] = e2;
		vtemp[2] = e3;
		return vtemp;
	}else{
		float *e = point_set + foremost * 3;
		/*if (e >= point_set + vam * 3){
			printf ("PMULT过小!\n");
			exit (1);
		}*/
		e[0] = e1;
		e[1] = e2;
		e[2] = e3;
		foremost++;
		return e;
	}
}

void vfree (float *e){
	if (e == NULL)
		return;
	vfend->add = e;
	freed *next = (freed *)malloc (sizeof (freed));
	next->add = NULL;
	next->next = NULL;
	vfend->next = next;
	vfend = vfend->next;
}

float rx (float *e){
	if (e == NULL)
		return 0;
	return e[0];
}
float ry (float *e){
	if (e == NULL)
		return 0;
	return e[1];
}
float rz (float *e){
	if (e == NULL)
		return 0;
	return e[2];
}
float *opo (float *e){									
	return req (-rx(e), -ry(e), -rz(e));
}

float indr (float *e, int i){
	if (i < 0 || i > 2)
		return 0;
	return e[i];
}

float *indw (float *e, int i){
	if (i < 0 || i > 2)
		return NULL;
	return &e[i];
}

float *add (float *e1, float *e2){
	float x = rx (e1) + rx (e2);
	float y = ry (e1) + ry (e2);
	float z = rz (e1) + rz (e2);
	return req (x, y, z);
}

float *sub (float *e1, float *e2){
	float x = rx (e1) - rx (e2);
	float y = ry (e1) - ry (e2);
	float z = rz (e1) - rz (e2);
	return req (x, y, z);
}

float *mul (float *e1, float m){
	float x = rx (e1) * m;
	float y = ry (e1) * m;
	float z = rz (e1) * m;
	return req (x, y, z);
}

float *divi (float *e1, float d){
	return mul (e1, 1 / d);
}
float square(float *e){
	return squ(rx(e)) + squ(ry(e)) + squ(rz(e));
}
float length (float *e){
	return sqrt (square (e));
}

float *edot (float *u, float *v){
	float x = rx (u) * rx (v);
	float y = ry (u) * ry (v);
	float z = rz (u) * rz (v);
	return req (x, y, z);
}

float dot (float *u, float *v){
	return rx (u) * rx (v)
		+ ry (u) * ry (v)
		+ rz (u) * rz (v);
}

float *cross(float *u, float *v) {
    return req(
        ry(u) * rz(v) - rz(u) * ry(v),
        rz(u) * rx(v) - rx(u) * rz(v),
        rx(u) * ry(v) - ry(u) * rx(v) 
    );
}

float *unit_vec (float *e){
	return divi (e, length (e));
}

float *rd_in_unit_disk (void){
	float *p = NULL;
	while (1){
		vfree (p);
		p = req (drand48(), drand48(), 0);
		if (length(p) < 1)
			return p;
	}
}

float randomb (float min, float max){
	return min + drand48 () * (max - min);
}
float *randoml (void){
	return req (drand48(), drand48(), drand48());
}
float *randomlb (float min, float max){
	return req (randomb(min, max), randomb(min, max), randomb(min, max));
}

float *rd_unit_vec (void){
	float *p = NULL;
	float lensq;
	while (!(epsilon < lensq && lensq <= 1)){
		vfree (p);
		p = randomlb (-1, 1);
		lensq = square (p);
	}
	return divi (p, (float)sqrt (lensq));
}

float *rd_on_he (float *normal){
	float *on = rd_unit_vec();
	if (dot (on, normal) > 0.0){
		return on;
	}else{
		float *temp1 = opo (on);
		vfree (on);
		return temp1;
	}
}

char too_small (float *e){
	return (rx (e) < epsilon) && (ry (e) < epsilon) && (rz (e) < epsilon);
}

float *reflect(float *v, float *n) {
	float *temp1 = mul (n, 2 * dot (v, n));
	float *temp2 = sub (v, temp1);
	vfree (temp1);
	return temp2;
}

float *refract(float *uv, float *n, float etai_over_etat) {
	float *temp1 = opo(uv);
	float temp = dot(temp1, n);
	vfree (temp1);
	float cos_theta = (temp < 0) ? 1.0 : temp;
	temp1 = mul (n, cos_theta);
	float *r_out_perp = add (uv, temp1);
	vfree (temp1);
	float *r_out_parallel = mul (n, -(float)sqrt(fabs(1.0 - length (r_out_perp))));
	temp1 = add (r_out_perp, r_out_parallel);
	vfree (r_out_perp);
	vfree (r_out_parallel);
	return temp1;
}
