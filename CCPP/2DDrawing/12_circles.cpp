// Compile: clang++ -std=c++17 12_circle.cpp -o 12_circle

#include <iostream>
#include <fstream>
#include <tuple>
#include <vector>
#include <random>
#include <cmath>

int get_index(int x, int y, int width)
{
    return x+width*y;
}

int calc_size(int width, int height)
{
    return width*height;
}

void clear_image(std::vector<std::tuple<float, float, float>> &image, int width, int height)
{
    for (int y=0;y<height;++y) {
        for (int x=0;x<width;++x) {
            image[get_index(x,y,width)]=std::make_tuple(1.0f, 1.0f, 1.0f);
        }
    }
}

void draw_circle(int x, int y, int radius, std::vector<std::tuple<float, float, float>> &image, std::tuple<float, float, float> &color, int width, int height)
{
    int x0 = 0;
    int y0 = radius;
    int d = 3 - 2 * radius;
    int xx=0;
    int yy=0;
    unsigned char mask=255;
    if (!radius) return;

    while (y0 >= x0)
    {
        if (mask & 0x01) {xx=x + x0;yy=y - y0;image[get_index(xx, yy, width)]=color;}
        if (mask & 0x02) {xx=x + y0;yy=y - x0;image[get_index(xx, yy, width)]=color;}
        if (mask & 0x04) {xx=x + y0;yy=y + x0;image[get_index(xx, yy, width)]=color;}
        if (mask & 0x08) {xx=x + x0;yy=y + y0;image[get_index(xx, yy, width)]=color;}
        if (mask & 0x10) {xx=x - x0;yy=y + y0;image[get_index(xx, yy, width)]=color;}
        if (mask & 0x20) {xx=x - y0;yy=y + x0;image[get_index(xx, yy, width)]=color;}
        if (mask & 0x40) {xx=x - y0;yy=y - x0;image[get_index(xx, yy, width)]=color;}
        if (mask & 0x80) {xx=x - x0;yy=y - y0;image[get_index(xx, yy, width)]=color;}
        if (d < 0) d += 4 * x0++ + 6;
        else d += 4 * (x0++ - y0--) + 10;
    }
}

void draw_filled_circle(int x, int y, int radius, std::vector<std::tuple<float, float, float>> &image, std::tuple<float, float, float> &color, int width, int height)
{
    int x0 = 0;
    int y0 = radius;
    int d = 3 - 2 * radius;
    if (!radius) return;

    auto drawline = [&](int sx, int ex, int ny)
    {
        for (int i = sx; i <= ex; i++)
            image[get_index(i, ny, width)]=color;
    };

    while (y0 >= x0)
    {
        drawline(x - x0, x + x0, y - y0);
        drawline(x - y0, x + y0, y - x0);
        drawline(x - x0, x + x0, y + y0);
        drawline(x - y0, x + y0, y + x0);
        if (d < 0) d += 4 * x0++ + 6;
        else d += 4 * (x0++ - y0--) + 10;
    }
}

void save_image(std::vector<std::tuple<float, float, float>> &image, int width, int height,