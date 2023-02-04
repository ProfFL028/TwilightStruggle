// Compile: clang++ -std=c++17 11_rectangles.cpp -o 11_rectangles

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

void draw_line(std::vector<std::tuple<float, float, float>> &image, std::tuple<int, int, int, int> &coords, std::tuple<float,float,float> &color, int width, int height)
{
    int x1=std::get<0>(coords); int y1=std::get<1>(coords); int x2=std::get<2>(coords); int y2=std::get<3>(coords);
    int x, y, dx, dy, dx1, dy1, px, py, xe, ye, i;
    dx = x2 - x1; dy = y2 - y1;
    if (dx == 0)
    {
        if (y2 < y1) std::swap(y1, y2);
        for (y = y1; y <= y2; y++)
            image[get_index(x1,y,width)]=color;
        return;
    }
    if (dy == 0)
    {
        if (x2 < x1) std::swap(x1, x2);
        for (x = x1; x <= x2; x++)
            image[get_index(x,y1,width)]=color;
        return;
    }
    dx1 = abs(dx); dy1 = abs(dy);
    px = 2 * dy1 - dx1;	py = 2 * dx1 - dy1;
    if (dy1 <= dx1)
    {
        if (dx >= 0)
        {
            x = x1; y = y1; xe = x2;
        }
        else
        {
            x = x2; y = y2; xe = x1;
        }
        image[get_index(x,y,width)]=color;
        for (i = 0; x<xe; i++)
        {
            x = x + 1;
            if (px<0)
                px = px + 2 * dy1;
            else
            {
                if ((dx<0 && dy<0) || (dx>0 && dy>0)) y = y + 1; else y = y - 1;
                px = px + 2 * (dy1 - dx1);
            }
            image[get_index(x,y,width)]=color;
        }
    }
    else
    {
        if (dy >= 0)
        {
            x = x1; y = y1; ye = y2;
        }
        else
        {
            x = x2; y = y2; ye = y1;
        }
        image[get_index(x,y,width)]=color;
        for (i = 0; y<ye; i++)
        {
            y = y + 1;
            if (py <= 0)
                py = py + 2 * dx1;
            else
            {
                if ((dx<0 && dy<0) || (dx>0 && dy>0)) x = x + 1; else x = x - 1;
                py = py + 2 * (dx1 - dy1);
            }
            image[get_index(x,y,width)]=color;
        }
    }
}

void draw_rect(int x, int y, int w, int h, std::vector<std::tuple<float, float, float>> &image, std::tuple<float,float,float> &color, int width, int height)
{
    w=w-1;
    h=h-1;
    std::tuple<int, int, int, int> coords=std::make_tuple(x, y, x+w, y);
    draw_line(image, coords, color, width, height);
    coords=std::make_tuple(x+w, y, x+w, y+h);
    draw_line(image, coords, color, width, height);
    coords=std::make_tuple(x+w, y+h, x, y+h);
    draw_line(image, coords, color, width, height);
    coords=std::make_tuple(x, y+h, x, y);
    draw_line(image, coords, color, width, height);
}

void draw_filled_rect(int x, int y, int w, int h, std::vector<std::tuple<float, float, float>> &image, std::tuple<float,float,float> &color, int width, int height)
{
    int x2 = x + w;
    int y2 = y + h;

    if (x < 0) {x = 0;}
    if (x >= width) {x = width;}
    if (y < 0) {y = 0;}
    if (y >= height) {y = height;}

    if (x2 < 0) {x2 = 0;}
    if (x2 >= width) {x2 = width;}
    if (y2 < 0) {y2 = 0;}
    if (y2 >= height) {y2 = height;}

    for (int i = y; i < y2; i++) {
        for (int j = x; j < x2; j++) {
            image[get_index(j,i,width)]=color;
        }
    }
}

void save_image(std::vector<std::tuple<float, float, float>> &image, int width, int height, std::string filename)
{
    std::tuple<float, float, float> color;
    std::ofstream out(filename, std::ofstream::out);
    out << "P3\n" << width << " " << height << "\n255\n";
    for (int i=0;i<(width*height);++i)
    {
        color=image[i];
        out << int(std::get<0>(color)*255.0f) << " " << int(std::get<1>(color)*255.0f) << " " << int(std::get<2>(color)*255.0f) << '\n';
    }
    out.close();
}

int main()
{
    int width=640;
    int height=360;
    int x1=0; int y=0; int wh=0; int x2=0;

    wh=(height/2)*0.8;
    x1=(width-(wh*3))/2;
    y=(height-wh)/2;
    x2=width-x1-wh;

    std::vector<std::tuple<float, float, float>> image;
    std::tuple<float,float,float> color=std::make_tuple(0.0f,0.0f,0.0f);

    image.resize(calc_size(width, height));
    clear_image(image,width,height);

    draw_rect(x1,y,wh,wh,image,color,width,height);
    draw_filled_rect(x2,y,wh,wh,image,color,width,height);

    save_image(image,width,height,"11_rectangles.ppm");

    return 0;
}