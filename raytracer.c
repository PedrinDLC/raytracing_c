#include <stdio.h>
#include "vec3.h"
#include "color.h"
#include "ray.h"

color ray_color(ray ray)
{
    vec3 unit_diretion = vec3normalized(ray.dir);
    float t = 0.5 * (unit_diretion.y+1.0);
    
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
