// material.h
#ifndef MATERIAL
#define MATERIAL
extern float *weaken;
typedef struct hit_record hit_rc;
char diffuse (float *, ray *, hit_rc *, float **, ray **);
char metal (float *, ray *, hit_rc *, float **, ray **);
#endif