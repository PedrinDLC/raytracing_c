#ifndef RAY_H
#define RAY_H

#include "vec3.h"

typedef struct ray {
    point3 origin;
    vec3 dir;
} ray;

point3 ray_at(ray ray, float t)
{
    point3 ret = vec3sum(ray.origin, vec3multscalar(ray.dir, t));

    return ret;
}

#endif // RAY_H