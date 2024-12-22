#ifndef MATERIAL
#define MATERIAL

typedef struct hit_record hit_rc;
char diffuse (float *albedo, ray *iray, hit_rc *rec, float **atten, ray **scattered){
	float *direction = add (rec->normal, rd_unit_vec());
	if (too_small (direction))
		direction = rec->normal;
	*scattered = reqray (rec->p, direction);
	*atten = albedo;
	return 1;
}

char metal (float *albedo, ray *iray, hit_rc *rec, float **atten, ray **scattered){
	float *reflected = reflect(direction(iray), rec->normal);
	*scattered = reqray(rec->p, reflected);
	*atten = albedo;
	return 1;
}
#endif
