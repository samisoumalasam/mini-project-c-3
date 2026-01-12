#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#define HEIGHT 1080
#define WIDTH 1920

#define COORD_X 960
#define COORD_Y 1080

int main(void) {
    color black = { 0, 0, 0 };
    color white = { 255, 255, 255 };
    color red = { 255, 0, 0 };
    color green = { 0, 255, 0 };
    color blue = { 0, 0, 255 };
    color magenta = { 255, 0, 255 };




    picture* photo = new_pic(WIDTH, HEIGHT);
    set_all_pixel(photo, white);
     // draw_line(photo, 2, 2, 7, 7, red);
     // draw_line(photo, 2, 7, 7, 4, blue);
     // draw_line(photo, 1, 2, 1, 7, green);
     // draw_line(photo, 8, 2, 8, 7, green);
     // draw_line(photo, 2, 1, 7, 1, magenta);
     // draw_line(photo, 2, 8, 7, 8, magenta);

    sierpinski_div_rainbow(photo,COORD_X,COORD_Y , 800,0.5f);
    char * fileName = "test.ppm";
    save_pic(photo, fileName);
}

