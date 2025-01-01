// material.h
#pragma once

#ifndef MATERIAL
#define MATERIAL
extern float *weaken;
typedef struct hit_record hit_rc;
char diffuse (float *, ray *, hit_rc *, float **, ray **);
char metal (float *, ray *, hit_rc *, float **, ray **, float);
char dielectric (float *, ray *, hit_rc *, float **, ray **, float);
#endif
