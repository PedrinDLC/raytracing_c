#include <stdio.h>
#include "vec3.h"
#include "color.h"
#include "ray.h"

float hit_sphere(point3 center, float radius, ray ray)
{   
    vec3 oc = vec3sum(ray.origin, vec3multscalar(center, -1.0));
    float a = vec3normsquared(ray.dir);
    float half_b = vec3dot(oc, ray.dir);
    float c = vec3normsquared(oc) - radius*radius;
    float discriminant = half_b*half_b - a*c;
    if(discriminant < 0)
        return -1.0;
    else{
        return (-half_b-sqrt(discriminant)) / a;
    }
}

color ray_color(ray ray)
{
    point3 center = {0., 0., -1.};
    float t = hit_sphere(center, 0.5, ray);

    if(t > 0.0){
        vec3 N = vec3normalized(vec3sum(ray_at(ray, t), vec3multscalar(center, -1.)));
        N.x++;
        N.y++;
        N.z++;
        N = vec3multscalar(N, 0.5);

        return N;
    }
    vec3 unit_diretion = vec3normalized(ray.dir);
    t = 0.5 * (unit_diretion.y+1.0);
    
    color white = {1., 1., 1.};
    color blue = {0.5, 0.7, 1.0};

    return vec3sum(vec3multscalar(white, 1.0-t), vec3multscalar(blue, t));
}

int main(int argc, char const *argv[])
{
    // Image

    float aspect_ratio = 16.0 / 9;
    int width = 400;
    int height = (int) (width / aspect_ratio);

    // Camera

    float viewport_height = 2.0;
    float viewport_width =  aspect_ratio * viewport_height;
    float focal_lenght = 1.0;

    point3 origin = {0.};
    vec3 horizontal = {viewport_width, 0., 0.};
    vec3 vertical = {0., viewport_height, 0.};
    point3 lower_left_corner = {
        origin.x - horizontal.x/2,
        origin.y - vertical.y/2,
        -focal_lenght
    };

    // Render

    printf("P3\n%d %d\n255\n", width,height);

    for (int i = height-1; i >= 0; i--){
        fprintf(stderr, "Remaining %d\n", i);
        for (int j = 0; j < width; j++){
            
            float u, v;
            u = (double)j / (width-1);
            v = (double)i / (height-1);
            
            vec3 temp1 = vec3sum(lower_left_corner, vec3multscalar(horizontal, u));
            vec3 temp2 = vec3sum(temp1, vec3multscalar(vertical, v));
            vec3 temp3 = vec3sum(temp2, vec3multscalar(origin, -1.));

            ray ray = {0};
            ray.dir.x = temp3.x;
            ray.dir.y = temp3.y;
            ray.dir.z = temp3.z;

            color color = ray_color(ray); 
            write_color(color);

        }
    }
    fprintf(stderr, "Done \n");
    
    return 0;
}
