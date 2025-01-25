#include <stdio.h>

int main(int argc, char const *argv[])
{
    // Image

    int width = 256;
    int height = 256;

    // Render

    printf("P3\n%d %d\n255\n", width,height);

    for (int i = height-1; i >= 0; i--){
        for (int j = 0; j < width; j++){
            double r,g,b;
            int ir,ig,ib;

            r = (double)j / (width-1);
            g = (double)i / (height-1);
            b = .25;

            ir = (int) (r*255);
            ig = (int) (g*255);
            ib = (int) (b*255);

            printf("%d %d %d\n", ir, ig, ib);
        }
    }
    
    return 0;
}
