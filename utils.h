//
// Created by pascal on 12/01/2026.
//

#ifndef MINI_PROJECT_C_3_UTILS_H
#define MINI_PROJECT_C_3_UTILS_H

typedef struct {
    unsigned char r;
    unsigned char g;
    unsigned char b;
} color;

typedef struct {
    int x;
    int y;
} coord;


typedef struct {
    unsigned int width;
    unsigned int height;
    color * TabPixel;
}picture;

picture* new_pic(int width, int height);

void save_pic(picture* pic,char* FileName);

void set_pixel(picture* pic, int x, int y, color color );

void set_all_pixel(picture* pic,color color);

void draw_line(picture* pic, int x1, int y1, int x2, int y2, color color);

void sierpinski(picture* pic, int x, int y, int size, color color);

void sierpinski_div(picture* pic, int x, int y, int size, color color);
color hsv_to_rgb(float h, float s, float v);

void sierpinski_div_rainbow(picture* pic, int x, int y, int size, float hue);

#endif //MINI_PROJECT_C_3_UTILS_H