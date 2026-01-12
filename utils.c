//
// Created by pascal on 12/01/2026.
//

#include "utils.h"

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#define MAX_VALUE_COLOR 255
#define FILENAME "test.ppm"


void initPXL(color *pixel,unsigned char r, unsigned char g, unsigned char b) {
    pixel->r = r;
    pixel->g = g;
    pixel->b = b;
}

void makeAllUniqueColor(color *tabpixel,int sizeOfTab,  color color) {
    for (int i = 0; i < sizeOfTab; i++) {
        tabpixel[i] = color;
    }
}

picture* new_pic(int width, int height) {
    picture* pic = (picture*)malloc(sizeof(picture));
    pic->width = width;
    pic->height = height;
    pic->TabPixel = malloc(width * height * sizeof(color));
    return pic;
}

void save_pic(picture* pic,char* FileName) {
    FILE *file = fopen(FileName, "wb");

    if (file == NULL) return;

    // Header
    fprintf(file, "P6\n%d %d\n%d\n",
            pic->width, pic->height, MAX_VALUE_COLOR);

    color *tabPixel = malloc(sizeof(color) * pic->width * pic->height);
    if (tabPixel == NULL) {
        perror("malloc tabPixel");
        fclose(file);
        return;
    }

    int npix = pic->width * pic->height;
    for (int i = 0; i < npix; i++) {
        tabPixel[i] = pic->TabPixel[i];
    }

    fwrite(tabPixel, sizeof(color), npix, file);
    free(tabPixel);
    fclose(file);
}

void set_pixel(picture* pic, int x, int y, color color ) {

    if (x < 0 || y < 0 || x >= pic->width || y >= pic->height) return;
    pic->TabPixel[y * pic->width + x] = color;
}
void set_all_pixel(picture* pic,color color) {
    int height = pic->height;
    int width = pic->width;
    for (int i = 0; i<height*width; i++ ) {
        pic->TabPixel[i] = color;
    }
}

void draw_line(picture* pic, int x1, int y1, int x2, int y2, color color) {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int n = (dx > dy ? dx : dy) + 1;  // max(dx, dy) + 1

    // Calcul des incréments
    float x_inc = (float)(x2 - x1) / (float)n;
    float y_inc = (float)(y2 - y1) / (float)n;

    // Position de départ
    float x = (float)x1;
    float y = (float)y1;

    // Dessiner n points
    for (int i = 0; i <= n; i++) {
        set_pixel(pic, (int)(x + 0.5f), (int)(y + 0.5f), color);
        x += x_inc;
        y += y_inc;
    }
}

void sierpinski(picture* pic, int x, int y, int size, color color) {
    int sommetX1 = x+size -1;
    int sommetY1 = y;
    int sommetX2 = x+size/2;
    int sommetY2 = y-size*sqrt(3)/2;

    draw_line(pic,x,y,sommetX1,sommetY1,color);
    draw_line(pic,x,y,sommetX2,sommetY2,color);
    draw_line(pic,sommetX1,sommetY1,sommetX2,sommetY2,color);
}

void sierpinski_div(picture* pic, int x, int y, int size, color color) {
    if (size < 25) {
        sierpinski(pic,x,y,size,color);
    } else {
        int truesize = size/2;

        coord triangleBasGauche = {x,y};
        coord triangleBasDroite = {x+truesize,y};
        coord triangeHaut = {x+size/4,y-size*sqrt(3)/4};


        sierpinski_div(pic,triangleBasGauche.x,triangleBasGauche.y,truesize,color);
        sierpinski_div(pic,triangleBasDroite.x,triangleBasDroite.y,truesize,color);
        sierpinski_div(pic,triangeHaut.x,triangeHaut.y,truesize,color);
    }

}

void sierpinski_div_rainbow(picture* pic, int x, int y, int size, float hue) {
    if (size < 25) {
        // Convertir la teinte HSV en RGB
        color rainbowColor = hsv_to_rgb(hue, 1.0f, 1.0f);
        sierpinski(pic, x, y, size, rainbowColor);
    } else {
        int truesize = size / 2;

        coord triangleBasGauche = {x, y};
        coord triangleBasDroite = {x + truesize, y};
        coord triangeHaut = {x + size/4, y - size*sqrt(3)/4};

        // Incrémenter la teinte pour créer l'effet arc-en-ciel
        // 360 degrés divisé par le nombre de niveaux pour un cycle complet
        float newHue = fmod(hue + 40.0f, 360.0f);

        sierpinski_div_rainbow(pic, triangleBasGauche.x, triangleBasGauche.y, truesize, newHue);
        sierpinski_div_rainbow(pic, triangleBasDroite.x, triangleBasDroite.y, truesize, newHue);
        sierpinski_div_rainbow(pic, triangeHaut.x, triangeHaut.y, truesize, newHue);
    }
}

color hsv_to_rgb(float h, float s, float v) {
    color rgb;
    float c = v * s;
    float x = c * (1 - fabs(fmod(h / 60.0f, 2) - 1));
    float m = v - c;

    float r, g, b;

    if (h < 60) {
        r = c; g = x; b = 0;
    } else if (h < 120) {
        r = x; g = c; b = 0;
    } else if (h < 180) {
        r = 0; g = c; b = x;
    } else if (h < 240) {
        r = 0; g = x; b = c;
    } else if (h < 300) {
        r = x; g = 0; b = c;
    } else {
        r = c; g = 0; b = x;
    }

    rgb.r = (unsigned char)((r + m) * 255);
    rgb.g = (unsigned char)((g + m) * 255);
    rgb.b = (unsigned char)((b + m) * 255);

    return rgb;
}