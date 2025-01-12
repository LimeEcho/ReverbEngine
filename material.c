// material.c
#include "headers/ray.h"
#include "headers/hittable.h"
#include "headers/material.h"
#include "headers/vec3.h"
char diffuse (float *albedo, ray *iray, hit_rc *rec, float **atten, ray **scattered){
	float *temp1 = rd_unit_vec();
	float *direction = add (rec->normal, temp1);
	vfree (temp1);
	if (too_small (direction)){
		vfree (direction);
		direction = rec->normal;
	}
	*scattered = reqray (rec->p, direction);
	*atten = edot (albedo, weaken);
	return 1;
}

char metal (float *albedo, ray *iray, hit_rc *rec, float **atten, ray **scattered, float fuzz){
	float *reflected = reflect(direction(iray), rec->normal);
	float *temp1 = rd_unit_vec();
	float *temp2 = mul(temp1, ((fuzz < 1) ? fuzz : 1));
	vfree (temp1);
	temp1 = unit_vec (reflected);
	reflected = add (temp1, temp2);
	vfree (temp1);
	vfree (temp2);
	*scattered = reqray(rec->p, reflected);
	*atten = edot (albedo, weaken);
	return (dot(direction(*scattered), rec->normal) > 0);
}

char dielectric(float *albedo, ray *iray, hit_rc *rec, float **atten, ray **scattered, float ref_index){
	*atten = albedo;
	float ri = rec->ft_fc ? (1.0 / ref_index) : ref_index;

	float *unit_dir = unit_vec (direction (iray));
	float *refracted = refract (unit_dir, rec->normal, ri);
	vfree (unit_dir);

	*scattered = reqray (rec->p, refracted);
	return 1;
}
