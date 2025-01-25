#include <stdio.h>
#include "vec3.h"
#include "color.h"


int main(int argc, char const *argv[])
{
    // Image

    int width = 256;
    int height = 256;

    // Render

    printf("P3\n%d %d\n255\n", width,height);

    for (int i = height-1; i >= 0; i--){
        fprintf(stderr, "Remaining %d\n", i);
        for (int j = 0; j < width; j++){

            //printf("%.2f %.2f %.2f\n", minhacor.r, minhacor.g, minhacor.b);   

            color color = 
                {(double)j / (width-1), //r
                (double)i / (height-1), //g
                .25};                   //b
            
            write_color(color);

        }
    }
    fprintf(stderr, "Done \n");
    
    return 0;
}
