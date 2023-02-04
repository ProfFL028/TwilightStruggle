// Compile: clang++ -std=c++17 15_draw_font.cpp -o 15_draw_font

#include <iostream>
#include <fstream>
#include <tuple>
#include <vector>
#include <random>
#include <cmath>

void get_width_from_height(int &width, int height)
{
    int half = height / 2;
    width = half * 3;
}

void get_margin_from_height(int &margin,int height)
{
    margin = int(float(height) * 0.3);
}

int get_index(int x, int y, int width)
{
    return x+width*y;
}

int calc_size(int width, int height, int margin)
{
    return (width+margin)*(height+margin);
}

void clear_image(std::vector<std::tuple<float, float, float>> &image, int width, int height, int margin)
{
    for (int y=0;y<(height+margin);++y) {
        for (int x=0;x<(width+margin);++x) {
            image[get_index(x,y,(width+margin))]=std::make_tuple(1.0f, 1.0f, 1.0f);
        }
    }
}

void draw_filled_circle(int x, int y, int radius, std::vector<std::tuple<float, float, float>> &image, std::tuple<float, float, float> &color, int width, int height, int margin)
{
    int x0 = 0;
    int y0 = radius;
    int d = 3 - 2 * radius;
    if (!radius) return;

    auto drawline = [&](int sx, int ex, int ny)
    {
        for (int i = sx; i <= ex; i++)
            image[get_index(i, ny, width+margin)]=color;
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

void get_line_points(std::vector<std::tuple<int,int>> &points, std::tuple<int, int, int, int> &coords, std::tuple<float,float,float> &color, int width, int height, int margin)
{
    int x1=std::get<0>(coords); int y1=std::get<1>(coords); int x2=std::get<2>(coords); int y2=std::get<3>(coords);
    int x, y, dx, dy, dx1, dy1, px, py, xe, ye, i;
    dx = x2 - x1; dy = y2 - y1;
    if (dx == 0)
    {
        if (y2 < y1) std::swap(y1, y2);
        for (y = y1; y <= y2; y++)
            points.push_back(std::make_tuple(x1,y));
        return;
    }
    if (dy == 0)
    {
        if (x2 < x1) std::swap(x1, x2);
        for (x = x1; x <= x2; x++)
            points.push_back(std::make_tuple(x,y1));
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
        points.push_back(std::make_tuple(x,y));
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
            points.push_back(std::make_tuple(x,y));
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
        points.push_back(std::make_tuple(x,y));
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
            points.push_back(std::make_tuple(x,y));
        }
    }
}

void draw_font_A(std::vector<std::tuple<int,int>> &points, std::tuple<float,float,float> &color, int width, int height, int margin)
{
    // A
    //points
    float arr[4][2] = {{0.0,1.0},{0.5,0.0},{1.0,1.0},{0.0,0.6}};
    //lines
    int arr2[3][2] = {{0,1},{1,2},{2,3}};
    std::tuple<int, int, int, int> coords;
    int halfmargin=margin/2;

    for (int i=0;i<3;++i) {
        coords=std::make_tuple(int(width*arr[arr2[i][0]][0])+halfmargin, int(height*arr[arr2[i][0]][1])+halfmargin, int(width*arr[arr2[i][1]][0])+halfmargin, int(height*arr[arr2[i][1]][1])+halfmargin);
        get_line_points(points,coords,color,width,height,margin);
    }
}

void draw_font_B(std::vector<std::tuple<int,int>> &points, std::tuple<float,float,float> &color, int width, int height, int margin)
{
    // B
    //points
    float arr[7][2] = {{0.0,0.0},{1.0,0.0},{1.0,0.4},{0.5,0.5},{1.0,0.6},{1.0,1.0},{0.0,1.0}};
    //lines
    int arr2[7][2] = {{0,1},{1,2},{2,3},{3,4},{4,5},{5,6},{6,0}};
    std::tuple<int, int, int, int> coords;
    int halfmargin=margin/2;

    for (int i=0;i<7;++i) {
        coords=std::make_tuple(int(width*arr[arr2[i][0]][0])+halfmargin, int(height*arr[arr2[i][0]][1])+halfmargin, int(width*arr[arr2[i][1]][0]+halfmargin), int(height*arr[arr2[i][1]][1])+halfmargin);
        get_line_points(points,coords,color,width,height,margin);
    }
}

void draw_font_C(std::vector<std::tuple<int,int>> &points, std::tuple<float,float,float> &color, int width, int height, int margin)
{
    // C
    //points
    float arr[4][2] = {{0.5,0.0},{0.0,0.0},{0.0,1.0},{1.0,1.0}};
    //lines
    int arr2[3][2] = {{0,1},{1,2},{2,3}};
    std::tuple<int, int, int, int> coords;
    int halfmargin=margin/2;

    for (int i=0;i<3;++i) {
        coords=std::make_tuple(int(width*arr[arr2[i][0]][0])+halfmargin, int(height*arr[arr2[i][0]][1])+halfmargin, int(width*arr[arr2[i][1]][0]+halfmargin), int(height*arr[arr2[i][1]][1])+halfmargin);
        get_line_points(points,coords,color,width,height,margin);
    }
}

void draw_font_D(std::vector<std::tuple<int,int>> &points, std::tuple<float,float,float> &color, int width, int height, int margin)
{
    // D
    //points
    float arr[4][2] = {{0.0,0.0},{0.0,1.0},{1.0,1.0},{1.0,0.4}};
    //lines
    int arr2[4][2] = {{0,1},{1,2},{2,3},{3,0}};
    std::tuple<int, int, int, int> coords;
    int halfmargin=margin/2;

    for (int i=0;i<4;++i) {
        coords=std::make_tuple(int(width*arr[arr2[i][0]][0])+halfmargin, int(height*arr[arr2[i][0]][1])+halfmargin, int(width*arr[arr2[i][1]][0]+halfmargin), int(height*arr[arr2[i][1]][1])+halfmargin);
        get_line_points(points,coords,color,width,height,margin);
    }
}

void draw_font_E(std::vector<std::tuple<int,int>> &points, std::tuple<float,float,float> &color, int width, int height, int margin)
{
    // E
    //points
    float arr[6][2] = {{1.0,0.0},{0.0,0.0},{0.0,0.5},{0.5,0.5},{0.0,1.0},{1.0,1.0}};
    //lines
    int arr2[4][2] = {{0,1},{1,2},{2,3},{4,5}};
    std::tuple<int, int, int, int> coords;
    int halfmargin=margin/2;

    for (int i=0;i<4;++i) {
        coords=std::make_tuple(int(width*arr[arr2[i][0]][0])+halfmargin, int(height*arr[arr2[i][0]][1])+halfmargin, int(width*arr[arr2[i][1]][0]+halfmargin), int(height*arr[arr2[i][1]][1])+halfmargin);
        get_line_points(points,coords,color,width,height,margin);
    }
}

void draw_font_F(std::vector<std::tuple<int,int>> &points, std::tuple<float,float,float> &color, int width, int height, int margin)
{
    // F
    //points
    float arr[5][2] = {{1.0,0.0},{0.0,0.0},{0.0,0.4},{0.5,0.4},{0.0,1.0}};
    //lines
    int arr2[4][2] = {{0,1},{1,2},{2,3},{2,4}};
    std::tuple<int, int, int, int> coords;
    int halfmargin=margin/2;

    for (int i=0;i<4;++i) {
        coords=std::make_tuple(int(width*arr[arr2[i][0]][0])+halfmargin, int(height*arr[arr2[i][0]][1])+halfmargin, int(width*arr[arr2[i][1]][0]+halfmargin), int(height*arr[arr2[i][1]][1])+halfmargin);
        get_line_points(points,coords,color,width,height,margin);
    }
}

void draw_font_G(std::vector<std::tuple<int,int>> &points, std::tuple<float,float,float> &color, int width, int height, int margin)
{
    // G
    //points
    float arr[6][2] = {{1.0,0.0},{0.0,0.0},{0.0,1.0},{1.0,1.0},{1.0,0.6},{0.5,0.6}};
    //lines
    int arr2[5][2] = {{0,1},{1,2},{2,3},{3,4},{4,5}};
    std::tuple<int, int, int, int> coords;
    int halfmargin=margin/2;

    for (int i=0;i<5;++i) {
        coords=std::make_tuple(int(width*arr[arr2[i][0]][0])+halfmargin, int(height*arr[arr2[i][0]][1])+halfmargin, int(width*arr[arr2[i][1]][0]+halfmargin), int(height*arr[arr2[i][1]][1])+halfmargin);
        get_line_points(points,coords,color,width,height,margin);
    }
}

void draw_font_H(std::vector<std::tuple<int,int>> &points, std::tuple<float,float,float> &color, int width, int height, int margin)
{
    // H
    //points
    float arr[6][2] = {{0.0,0.0},{0.0,1.0},{1.0,0.0},{1.0,1.0},{0.0,0.6},{1.0,0.6}};
    //lines
    int arr2[3][2] = {{0,1},{2,3},{4,5}};
    std::tuple<int, int, int, int> coords;
    int halfmargin=margin/2;

    for (int i=0;i<3;++i) {
        coords=std::make_tuple(int(width*arr[arr2[i][0]][0])+halfmargin, int(height*arr[arr2[i][0]][1])+halfmargin, int(width*arr[arr2[i][1]][0]+halfmargin), int(height*arr[arr2[i][1]][1])+halfmargin);
        get_line_points(points,coords,color,width,height,margin);
    }
}

void draw_font_I(std::vector<std::tuple<int,int>> &points, std::tuple<float,float,float> &color, int width, int height, int margin)
{
    // I
    //points
    float arr[2][2] = {{0.5,0.0},{0.5,1.0}};
    //lines
    int arr2[1][2] = {{0,1}};
    std::tuple<int, int, int, int> coords;
    int halfmargin=margin/2;

    for (int i=0;i<1;++i) {
        coords=std::make_tuple(int(width*arr[arr2[i][0]][0])+halfmargin, int(height*arr[arr2[i][0]][1])+halfmargin, int(width*arr[arr2[i][1]][0]+halfmargin), int(height*arr[arr2[i][1]][1])+halfmargin);
        get_line_points(points,coords,color,width,height,margin);
    }
}

void draw_font_J(std::vector<std::tuple<int,int>> &points, std::tuple<float,float,float> &color, int width, int height, int margin)
{
    // J
    //points
    float arr[4][2] = {{0.5,0.0},{0.5,1.0},{0.25,1.0},{0.0,0.6}};
    //lines
    int arr2[3][2] = {{0,1},{1,2},{2,3}};
    std::tuple<int, int, int, int> coords;
    int halfmargin=margin/2;

    for (int i=0;i<3;++i) {
        coords=std::make_tuple(int(width*arr[arr2[i][0]][0])+halfmargin, int(height*arr[arr2[i][0]][1])+halfmargin, int(width*arr[arr2[i][1]][0]+halfmargin), int(height*arr[arr2[i][1]][1])+halfmargin);
        get_line_points(points,coords,color,width,height,margin);
    }
}

void draw_font_K(std::vector<std::tuple<int,int>> &points, std::tuple<float,float,float> &color, int width, int height, int margin)
{
    // K
    //points
    float arr[5][2] = {{0.0,0.0},{0.0,0.4},{0.5,0.0},{1.0,1.0},{0.0,1.0}};
    //lines
    int arr2[4][2] = {{0,1},{1,2},{1,3},{1,4}};
    std::tuple<int, int, int, int> coords;
    int halfmargin=margin/2;

    for (int i=0;i<4;++i) {
        coords=std::make_tuple(int(width*arr[arr2[i][0]][0])+halfmargin, int(height*arr[arr2[i][0]][1])+halfmargin, int(width*arr[arr2[i][1]][0]+halfmargin), int(height*arr[arr2[i][1]][1])+halfmargin);
        get_line_points(points,coords,color,width,height,margin);
    }
}

void draw_font_L(std::vector<std::tuple<int,int>> &points, std::tuple<float,float,float> &color, int width, int height, int margin)
{
    // L
    //points
    float arr[3][2] = {{0.0,0.0},{0.0,1.0},{1.0,1.0}};
    //lines
    int arr2[2][2] = {{0,1},{1,2}};
    std::tuple<int, int, int, int> coords;
    int halfmargin=margin/2;

    for (int i=0;i<2;++i) {
        coords=std::make_tuple(int(width*arr[arr2[i][0]][0])+halfmargin, int(height*arr[arr2[i][0]][1])+halfmargin, int(width*arr[arr2[i][1]][0]+halfmargin), int(height*arr[arr2[i][1]][1])+halfmargin);
        get_line_points(points,coords,color,width,height,margin);
    }
}

void draw_font_M(std::vector<std::tuple<int,int>> &points, std::tuple<float,float,float> &color, int width, int height, int margin)
{
    // M
    //points
    float arr[5][2] = {{0.0,1.0},{0.0,0.0},{0.5,0.3},{1.0,0.0},{1.0,1.0}};
    //lines
    int arr2[4][2] = {{0,1},{1,2},{2,3},{3,4}};
    std::tuple<int, int, int, int> coords;
    int halfmargin=margin/2;

    for (int i=0;i<4;++i) {
        coords=std::make_tuple(int(width*arr[arr2[i][0]][0])+halfmargin, int(height*arr[arr2[i][0]][1])+halfmargin, int(width*arr[arr2[i][1]][0]+halfmargin), int(height*arr[arr2[i][1]][1])+halfmargin);
        get_line_points(points,coords,color,width,height,margin);
    }
}

void draw_font_N(std::vector<std::tuple<int,int>> &points, std::tuple<float,float,float> &color, int width, int height, int margin)
{
    // N
    //points
    float arr[6][2] = {{0.0,0.0},{0.0,1.0},{1.0,0.0},{1.0,1.0},{0.0,0.0},{1.0,1.0}};
    //lines
    int arr2[3][2] = {{0,1},{2,3},{4,5}};
    std::tuple<int, int, int, int> coords;
    int halfmargin=margin/2;

    for (int i=0;i<3;++i) {
        coords=std::make_tuple(int(width*arr[arr2[i][0]][0])+halfmargin, int(height*arr[arr2[i][0]][1])+halfmargin, int(width*arr[arr2[i][1]][0]+halfmargin), int(height*arr[arr2[i][1]][1])+halfmargin);
        get_line_points(points,coords,color,width,height,margin);
    }
}

void draw_font_O(std::vector<std::tuple<int,int>> &points, std::tuple<float,float,float> &color, int width, int height, int margin)
{
    // O
    //points
    float arr[4][2] = {{1.0,0.0},{1.0,1.0},{0.0,1.0},{0.0,0.0}};
    //lines
    int arr2[4][2] = {{0,1},{1,2},{2,3},{3,0}};
    std::tuple<int, int, int, int> coords;
    int halfmargin=margin/2;

    for (int i=0;i<4;++i) {
        coords=std::make_tuple(int(width*arr[arr2[i][0]][0])+halfmargin, int(height*arr[arr2[i][0]][1])+halfmargin, int(width*arr[arr2[i][1]][0]+halfmargin), int(height*arr[arr2[i][1]][1])+halfmargin);
        get_line_points(points,coords,color,width,height,margin);
    }
}

void draw_font_P(std::vector<std::tuple<int,int>> &points, std::tuple<float,float,float> &color, int width, int height, int margin)
{
    // P
    //points
    float arr[5][2] = {{0.0,1.0},{0.0,0.0},{1.0,0.0},{1.0,0.3},{0.0,0.6}};
    //lines
    int arr2[4][2] = {{0,1},{1,2},{2,3},{3,4}};
    std::tuple<int, int, int, int> coords;
    int halfmargin=margin/2;

    for (int i=0;i<4;++i) {
        coords=std::make_tuple(int(width*arr[arr2[i][0]][0])+halfmargin, int(height*arr[arr2[i][0]][1])+halfmargin, int(width*arr[arr2[i][1]][0]+halfmargin), int(height*arr[arr2[i][1]][1])+halfmargin);
        get_line_points(points,coords,color,width,height,margin);
    }
}

void draw_font_Q(std::vector<std::tuple<int,int>> &points, std::tuple<float,float,float> &color, int width, int height, int margin)
{
    // Q
    //points
    float arr[7][2] = {{1.0,0.6},{1.0,0.0},{0.0,0.0},{0.0,1.0},{0.5,1.0},{0.5,0.6},{1.0,1.0}};
    //lines
    int arr2[6][2] = {{0,1},{1,2},{2,3},{3,4},{4,0},{5,6}};
    std::tuple<int, int, int, int> coords;
    int halfmargin=margin/2;

    for (int i=0;i<6;++i) {
        coords=std::make_tuple(int(width*arr[arr2[i][0]][0])+halfmargin, int(height*arr[arr2[i][0]][1])+halfmargin, int(width*arr[arr2[i][1]][0]+halfmargin), int(height*arr[arr2[i][1]][1])+halfmargin);
        get_line_points(points,coords,color,width,height,margin);
    }
}

void draw_font_R(std::vector<std::tuple<int,int>> &points, std::tuple<float,float,float> &color, int width, int height, int margin)
{
    // R
    //points
    float arr[6][2] = {{0.0,1.0},{0.0,0.0},{1.0,0.0},{1.0,0.3},{0.0,0.6},{1.0,1.0}};
    //lines
    int arr2[5][2] = {{0,1},{1,2},{2,3},{3,4},{4,5}};
    std::tuple<int, int, int, int> coords;
    int halfmargin=margin/2;

    for (int i=0;i<5;++i) {
        coords=std::make_tuple(int(width*arr[arr2[i][0]][0])+halfmargin, int(height*arr[arr2[i][0]][1])+halfmargin, int(width*arr[arr2[i][1]][0]+halfmargin), int(height*arr[arr2[i][1]][1])+halfmargin);
        get_line_points(points,coords,color,width,height,margin);
    }
}

void draw_font_S(std::vector<std::tuple<int,int>> &points, std::tuple<float,float,float> &color, int width, int height, int margin)
{
    // S
    //points
    float arr[6][2] = {{1.0,0.0},{0.0,0.0},{0.0,0.4},{1.0,0.6},{1.0,1.0},{0.0,1.0}};
    //lines
    int arr2[5][2] = {{0,1},{1,2},{2,3},{3,4},{4,5}};
    std::tuple<int, int, int, int> coords;
    int halfmargin=margin/2;

    for (int i=0;i<5;++i) {
        coords=std::make_tuple(int(width*arr[arr2[i][0]][0])+halfmargin, int(height*arr[arr2[i][0]][1])+halfmargin, int(width*arr[arr2[i][1]][0]+halfmargin), int(height*arr[arr2[i][1]][1])+halfmargin);
        get_line_points(points,coords,color,width,height,margin);
    }
}

void draw_font_T(std::vector<std::tuple<int,int>> &points, std::tuple<float,float,float> &color, int width, int height, int margin)
{
    // T
    //points
    float arr[3][2] = {{0.0,0.0},{1.0,0.0},{1.0,1.0}};
    //lines
    int arr2[2][2] = {{0,1},{1,2}};
    std::tuple<int, int, int, int> coords;
    int halfmargin=margin/2;

    for (int i=0;i<2;++i) {
        coords=std::make_tuple(int(width*arr[arr2[i][0]][0])+halfmargin, int(height*arr[arr2[i][0]][1])+halfmargin, int(width*arr[arr2[i][1]][0]+halfmargin), int(height*arr[arr2[i][1]][1])+halfmargin);
        get_line_points(points,coords,color,width,height,margin);
    }
}

void draw_font_U(std::vector<std::tuple<int,int>> &points, std::tuple<float,float,float> &color, int width, int height, int margin)
{
    // U
    //points
    float arr[4][2] = {{0.0,0.0},{0.0,1.0},{1.0,1.0},{1.0,0.5}};
    //lines
    int arr2[3][2] = {{0,1},{1,2},{2,3}};
    std::tuple<int, int, int, int> coords;
    int halfmargin=margin/2;

    for (int i=0;i<3;++i) {
        coords=std::make_tuple(int(width*arr[arr2[i][0]][0])+halfmargin, int(height*arr[arr2[i][0]][1])+halfmargin, int(width*arr[arr2[i][1]][0]+halfmargin), int(height*arr[arr2[i][1]][1])+halfmargin);
        get_line_points(points,coords,color,width,height,margin);
    }
}

void draw_font_V(std::vector<std::tuple<int,int>> &points, std::tuple<float,float,float> &color, int width, int height, int margin)
{
    // V
    //points
    float arr[3][2] = {{0.0,0.0},{0.5,1.0},{1.0,0.0}};
    //lines
    int arr2[2][2] = {{0,1},{1,2}};
    std::tuple<int, int, int, int> coords;
    int halfmargin=margin/2;

    for (int i=0;i<2;++i) {
        coords=std::make_tuple(int(width*arr[arr2[i][0]][0])+halfmargin, int(height*arr[arr2[i][0]][1])+halfmargin, int(width*arr[arr2[i][1]][0]+halfmargin), int(height*arr[arr2[i][1]][1])+halfmargin);
        get_line_points(points,coords,color,width,height,margin);
    }
}

void draw_font_W(std::vector<std::tuple<int,int>> &points, std::tuple<float,float,float> &color, int width, int height, int margin)
{
    // W
    //points
    float arr[5][2] = {{0.0,0.0},{0.0,1.0},{0.5,0.7},{1.0,1.0},{1.0,0.0}};
    //lines
    int arr2[4][2] = {{0,1},{1,2},{2,3},{3,4}};
    std::tuple<int, int, int, int> coords;
    int halfmargin=margin/2;

    for (int i=0;i<4;++i) {
        coords=std::make_tuple(int(width*arr[arr2[i][0]][0])+halfmargin, int(height*arr[arr2[i][0]][1])+halfmargin, int(width*arr[arr2[i][1]][0]+halfmargin), int(height*arr[arr2[i][1]][1])+halfmargin);
        get_line_points(points,coords,color,width,height,margin);
    }
}

void draw_font_X(std::vector<std::tuple<int,int>> &points, std::tuple<float,float,float> &color, int width, int height, int margin)
{
    // X
    //points
    float arr[5][2] = {{0.5,0.6},{0.0,0.0},{1.0,0.0},{1.0,1.0},{0.0,1.0}};
    //lines
    int arr2[4][2] = {{0,1},{0,2},{0,3},{0,4}};
    std::tuple<int, int, int, int> coords;
    int halfmargin=margin/2;

    for (int i=0;i<4;++i) {
        coords=std::make_tuple(int(width*arr[arr2[i][0]][0])+halfmargin, int(height*arr[arr2[i][0]][1])+halfmargin, int(width*arr[arr2[i][1]][0]+halfmargin), int(height*arr[arr2[i][1]][1])+halfmargin);
        get_line_points(points,coords,color,width,height,margin);
    }
}

void draw_font_Y(std::vector<std::tuple<int,int>> &points, std::tuple<float,float,float> &color, int width, int height, int margin)
{
    // Y
    //points
    float arr[4][2] = {{0.5,0.6},{0.0,0.0},{1.0,0.0},{0.5,1.0}};
    //lines
    int arr2[3][2] = {{0,1},{0,2},{0,3}};
    std::tuple<int, int, int, int> coords;
    int halfmargin=margin/2;

    for (int i=0;i<3;++i) {
        coords=std::make_tuple(int(width*arr[arr2[i][0]][0])+halfmargin, int(height*arr[arr2[i][0]][1])+halfmargin, int(width*arr[arr2[i][1]][0]+halfmargin), int(height*arr[arr2[i][1]][1])+halfmargin);
        get_line_points(points,coords,color,width,height,margin);
    }
}

void draw_font_Z(std::vector<std::tuple<int,int>> &points, std::tuple<float,float,float> &color, int width, int height, int margin)
{
    // Z
    //points
    float arr[4][2] = {{0.0,0.0},{1.0,0.0},{0.0,1.0},{1.0,1.0}};
    //lines
    int arr2[3][2] = {{0,1},{1,2},{2,3}};
    std::tuple<int, int, int, int> coords;
    int halfmargin=margin/2;

    for (int i=0;i<3;++i) {
        coords=std::make_tuple(int(width*arr[arr2[i][0]][0])+halfmargin, int(height*arr[arr2[i][0]][1])+halfmargin, int(width*arr[arr2[i][1]][0]+halfmargin), int(height*arr[arr2[i][1]][1])+halfmargin);
        get_line_points(points,coords,color,width,height,margin);
    }
}

void draw_font_0(std::vector<std::tuple<int,int>> &points, std::tuple<float,float,float> &color, int width, int height, int margin)
{
    // 0
    //points
    float arr[6][2] = {{0.0,0.0},{0.0,1.0},{1.0,1.0},{1.0,0.0},{0.0,1.0},{1.0,0.0}};
    //lines
    int arr2[5][2] = {{0,1},{1,2},{2,3},{3,0},{4,5}};
    std::tuple<int, int, int, int> coords;
    int halfmargin=margin/2;

    for (int i=0;i<5;++i) {
        coords=std::make_tuple(int(width*arr[arr2[i][0]][0])+halfmargin, int(height*arr[arr2[i][0]][1])+halfmargin, int(width*arr[arr2[i][1]][0]+halfmargin), int(height*arr[arr2[i][1]][1])+halfmargin);
        get_line_points(points,coords,color,width,height,margin);
    }
}

void draw_font_1(std::vector<std::tuple<int,int>> &points, std::tuple<float,float,float> &color, int width, int height, int margin)
{
    // 1
    //points
    float arr[3][2] = {{0.0,0.0},{0.5,0.0},{0.5,1.0}};
    //lines
    int arr2[2][2] = {{0,1},{1,2}};
    std::tuple<int, int, int, int> coords;
    int halfmargin=margin/2;

    for (int i=0;i<2;++i) {
        coords=std::make_tuple(int(width*arr[arr2[i][0]][0])+halfmargin, int(height*arr[arr2[i][0]][1])+halfmargin, int(width*arr[arr2[i][1]][0]+halfmargin), int(height*arr[arr2[i][1]][1])+halfmargin);
        get_line_points(points,coords,color,width,height,margin);
    }
}

void draw_font_2(std::vector<std::tuple<int,int>> &points, std::tuple<float,float,float> &color, int width, int height, int margin)
{
    // 2
    //points
    float arr[6][2] = {{0.0,0.0},{1.0,0.0},{1.0,0.4},{0.0,0.6},{0.0,1.0},{1.0,1.0}};
    //lines
    int arr2[5][2] = {{0,1},{1,2},{2,3},{3,4},{4,5}};
    std::tuple<int, int, int, int> coords;
    int halfmargin=margin/2;

    for (int i=0;i<5;++i) {
        coords=std::make_tuple(int(width*arr[arr2[i][0]][0])+halfmargin, int(height*arr[arr2[i][0]][1])+halfmargin, int(width*arr[arr2[i][1]][0]+halfmargin), int(height*arr[arr2[i][1]][1])+halfmargin);
        get_line_points(points,coords,color,width,height,margin);
    }
}

void draw_font_3(std::vector<std::tuple<int,int>> &points, std::tuple<float,float,float> &color, int width, int height, int margin)
{
    // 3
    //points
    float arr[6][2] = {{0.0,0.0},{1.0,0.0},{1.0,0.4},{0.5,0.4},{0.0,1.0},{1.0,1.0}};
    //lines
    int arr2[4][2] = {{0,1},{1,2},{2,3},{4,5}};
    std::tuple<int, int, int, int> coords;
    int halfmargin=margin/2;

    for (int i=0;i<4;++i) {
        coords=std::make_tuple(int(width*arr[arr2[i][0]][0])+halfmargin, int(height*arr[arr2[i][0]][1])+halfmargin, int(width*arr[arr2[i][1]][0]+halfmargin), int(height*arr[arr2[i][1]][1])+halfmargin);
        get_line_points(points,coords,color,width,height,margin);
    }
}

void draw_font_4(std::vector<std::tuple<int,int>> &points, std::tuple<float,float,float> &color, int width, int height, int margin)
{
    // 4
    //points
    float arr[5][2] = {{0.0,0.0},{0.0,0.4},{1.0,0.6},{1.0,0.0},{1.0,1.0}};
    //lines
    int arr2[3][2] = {{0,1},{1,2},{3,4}};
    std::tuple<int, int, int, int> coords;
    int halfmargin=margin/2;

    for (int i=0;i<3;++i) {
        coords=std::make_tuple(int(width*arr[arr2[i][0]][0])+halfmargin, int(height*arr[arr2[i][0]][1])+halfmargin, int(width*arr[arr2[i][1]][0]+halfmargin), int(height*arr[arr2[i][1]][1])+halfmargin);
        get_line_points(points,coords,color,width,height,margin);
    }
}

void draw_font_5(std::vector<std::tuple<int,int>> &points, std::tuple<float,float,float> &color, int width, int height, int margin)
{
    // 5
    //points
    float arr[6][2] = {{1.0,0.0},{0.0,0.0},{0.0,0.5},{1.0,0.6},{1.0,1.0},{0.0,1.0}};
    //lines
    int arr2[5][2] = {{0,1},{1,2},{2,3},{3,4},{4,5}};
    std::tuple<int, int, int, int> coords;
    int halfmargin=margin/2;

    for (int i=0;i<5;++i) {
        coords=std::make_tuple(int(width*arr[arr2[i][0]][0])+halfmargin, int(height*arr[arr2[i][0]][1])+halfmargin, int(width*arr[arr2[i][1]][0]+halfmargin), int(height*arr[arr2[i][1]][1])+halfmargin);
        get_line_points(points,coords,color,width,height,margin);
    }
}

void draw_font_6(std::vector<std::tuple<int,int>> &points, std::tuple<float,float,float> &color, int width, int height, int margin)
{
    // 6
    //points
    float arr[6][2] = {{1.0,0.0},{0.0,0.0},{0.0,0.4},{1.0,0.6},{1.0,1.0},{0.0,1.0}};
    //lines
    int arr2[5][2] = {{0,1},{1,5},{5,4},{3,4},{3,2}};
    std::tuple<int, int, int, int> coords;
    int halfmargin=margin/2;

    for (int i=0;i<5;++i) {
        coords=std::make_tuple(int(width*arr[arr2[i][0]][0])+halfmargin, int(height*arr[arr2[i][0]][1])+halfmargin, int(width*arr[arr2[i][1]][0]+halfmargin), int(height*arr[arr2[i][1]][1])+halfmargin);
        get_line_points(points,coords,color,width,height,margin);
    }
}

void draw_font_7(std::vector<std::tuple<int,int>> &points, std::tuple<float,float,float> &color, int width, int height, int margin)
{
    // 7
    //points
    float arr[3][2] = {{0.0,0.0},{1.0,0.0},{1.0,1.0}};
    //lines
    int arr2[2][2] = {{0,1},{1,2}};
    std::tuple<int, int, int, int> coords;
    int halfmargin=margin/2;

    for (int i=0;i<2;++i) {
        coords=std::make_tuple(int(width*arr[arr2[i][0]][0])+halfmargin, int(height*arr[arr2[i][0]][1])+halfmargin, int(width*arr[arr2[i][1]][0]+halfmargin), int(height*arr[arr2[i][1]][1])+halfmargin);
        get_line_points(points,coords,color,width,height,margin);
    }
}

void draw_font_8(std::vector<std::tuple<int,int>> &points, std::tuple<float,float,float> &color, int width, int height, int margin)
{
    // 8
    //points
    float arr[6][2] = {{0.1,0.4},{0.9,0.6},{1.0,0.0},{0.0,0.0},{0.0,1.0},{1.0,1.0}};
    //lines
    int arr2[7][2] = {{0,1},{1,2},{2,3},{3,0},{0,4},{4,5},{5,1}};
    std::tuple<int, int, int, int> coords;
    int halfmargin=margin/2;

    for (int i=0;i<7;++i) {
        coords=std::make_tuple(int(width*arr[arr2[i][0]][0])+halfmargin, int(height*arr[arr2[i][0]][1])+halfmargin, int(width*arr[arr2[i][1]][0]+halfmargin), int(height*arr[arr2[i][1]][1])+halfmargin);
        get_line_points(points,coords,color,width,height,margin);
    }
}

void draw_font_9(std::vector<std::tuple<int,int>> &points, std::tuple<float,float,float> &color, int width, int height, int margin)
{
    // 9
    //points
    float arr[5][2] = {{1.0,1.0},{1.0,0.0},{0.0,0.0},{0.0,0.6},{1.0,0.4}};
    //lines
    int arr2[4][2] = {{0,1},{1,2},{2,3},{3,4}};
    std::tuple<int, int, int, int> coords;
    int halfmargin=margin/2;

    for (int i=0;i<4;++i) {
        coords=std::make_tuple(int(width*arr[arr2[i][0]][0])+halfmargin, int(height*arr[arr2[i][0]][1])+halfmargin, int(width*arr[arr2[i][1]][0]+halfmargin), int(height*arr[arr2[i][1]][1])+halfmargin);
        get_line_points(points,coords,color,width,height,margin);
    }
}

void draw_font_QA(std::vector<std::tuple<int,int>> &points, std::tuple<float,float,float> &color, int width, int height, int margin)
{
    // ?
    //points
    float arr[6][2] = {{0.0,0.0},{1.0,0.0},{1.0,0.4},{0.5,0.4},{0.5,0.8},{0.5,1.0}};
    //lines
    int arr2[4][2] = {{0,1},{1,2},{2,3},{4,5}};
    std::tuple<int, int, int, int> coords;
    int halfmargin=margin/2;

    for (int i=0;i<4;++i) {
        coords=std::make_tuple(int(width*arr[arr2[i][0]][0])+halfmargin, int(height*arr[arr2[i][0]][1])+halfmargin, int(width*arr[arr2[i][1]][0]+halfmargin), int(height*arr[arr2[i][1]][1])+halfmargin);
        get_line_points(points,coords,color,width,height,margin);
    }
}

void draw_font_PROCENT(std::vector<std::tuple<int,int>> &points, std::tuple<float,float,float> &color, int width, int height, int margin)
{
    // %
    //points
    float arr[10][2] = {{0.0,0.0},{0.3,0.0},{0.3,0.3},{0.0,0.3},{1.0,1.0},{0.7,1.0},{0.7,0.7},{1.0,0.7},{0.0,1.0},{1.0,0.0}};
    //lines
    int arr2[9][2] = {{0,1},{1,2},{2,3},{3,0},{4,5},{5,6},{6,7},{7,4},{8,9}};
    std::tuple<int, int, int, int> coords;
    int halfmargin=margin/2;

    for (int i=0;i<9;++i) {
        coords=std::make_tuple(int(width*arr[arr2[i][0]][0])+halfmargin, int(height*arr[arr2[i][0]][1])+halfmargin, int(width*arr[arr2[i][1]][0]+halfmargin), int(height*arr[arr2[i][1]][1])+halfmargin);
        get_line_points(points,coords,color,width,height,margin);
    }
}

void save_image(std::vector<std::tuple<float, float, float>> &image, int width, int height, int margin, std::string filename)
{
    std::tuple<float, float, float> color;
    std::ofstream out(filename, std::ios_base::out | std::ios_base::binary);
    out << "P6" << std::endl << (width+margin) << ' ' << (height+margin) << std::endl << "255" << std::endl;

    for (int i=0;i<((width+margin)*(height+margin));++i)
    {
        color=image[i];
        out << char(std::get<0>(color)*255.0f) << char(std::get<1>(color)*255.0f) << char(std::get<2>(color)*255.0f);
    }
    out.close();
}

void draw(std::vector<std::tuple<int,int>> points,std::vector<std::tuple<float, float, float>> &image, std::tuple<float,float,float> color, int width, int height, int margin, int linesize)
{
    for (auto& p : points) {
        if (linesize == 1) {
            image[get_index(std::get<0>(p),std::get<1>(p),width+margin)]=std::make_tuple(0.0f, 0.0f, 0.0f);
        } else {
            draw_filled_circle(std::get<0>(p),std::get<1>(p),linesize,image,color,width,height,margin);
        }
    }
}

void draw_and_save_font(std::vector<std::tuple<float, float, float>> &image, std::tuple<float,float,float> color, int width, int height, int margin, int linesize)
{
    std::vector<std::tuple<int,int>> points;
    draw_font_A(points,color,width,height,margin);
    draw(points,image,color,width,height,margin,linesize);
    save_image(image,width,height,margin,"15_draw_font_A.ppm");
    points.clear();clear_image(image,width,height,margin);
    draw_font_B(points,color,width,height,margin);
    draw(points,image,color,width,height,margin,linesize);
    save_image(image,width,height,margin,"15_draw_font_B.ppm");
    points.clear();clear_image(image,width,height,margin);
    draw_font_C(points,color,width,height,margin);
    draw(points,image,color,width,height,margin,linesize);
    save_image(image,width,height,margin,"15_draw_font_C.ppm");
    points.clear();clear_image(image,width,height,margin);
    draw_font_D(points,color,width,height,margin);
    draw(points,image,color,width,height,margin,linesize);
    save_image(image,width,height,margin,"15_draw_font_D.ppm");
    points.clear();clear_image(image,width,height,margin);
    draw_font_E(points,color,width,height,margin);
    draw(points,image,color,width,height,margin,linesize);
    save_image(image,width,height,margin,"15_draw_font_E.ppm");
    points.clear();clear_image(image,width,height,margin);
    draw_font_F(points,color,width,height,margin);
    draw(points,image,color,width,height,margin,linesize);
    save_image(image,width,height,margin,"15_draw_font_F.ppm");
    points.clear();clear_image(image,width,height,margin);
    draw_font_G(points,color,width,height,margin);
    draw(points,image,color,width,height,margin,linesize);
    save_image(image,width,height,margin,"15_draw_font_G.ppm");
    points.clear();clear_image(image,width,height,margin);
    draw_font_H(points,color,width,height,margin);
    draw(points,image,color,width,height,margin,linesize);
    save_image(image,width,height,margin,"15_draw_font_H.ppm");
    points.clear();clear_image(image,width,height,margin);
    draw_font_I(points,color,width,height,margin);
    draw(points,image,color,width,height,margin,linesize);
    save_image(image,width,height,margin,"15_draw_font_I.ppm");
    points.clear();clear_image(image,width,height,margin);
    draw_font_J(points,color,width,height,margin);
    draw(points,image,color,width,height,margin,linesize);
    save_image(image,width,height,margin,"15_draw_font_J.ppm");
    points.clear();clear_image(image,width,height,margin);
    draw_font_K(points,color,width,height,margin);
    draw(points,image,color,width,height,margin,linesize);
    save_image(image,width,height,margin,"15_draw_font_K.ppm");
    points.clear();clear_image(image,width,height,margin);
    draw_font_L(points,color,width,height,margin);
    draw(points,image,color,width,height,margin,linesize);
    save_image(image,width,height,margin,"15_draw_font_L.ppm");
    points.clear();clear_image(image,width,height,margin);
    draw_font_M(points,color,width,height,margin);
    draw(points,image,color,width,height,margin,linesize);
    save_image(image,width,height,margin,"15_draw_font_M.ppm");
    points.clear();clear_image(image,width,height,margin);
    draw_font_N(points,color,width,height,margin);
    draw(points,image,color,width,height,margin,linesize);
    save_image(image,width,height,margin,"15_draw_font_N.ppm");
    points.clear();clear_image(image,width,height,margin);
    draw_font_O(points,color,width,height,margin);
    draw(points,image,color,width,height,margin,linesize);
    save_image(image,width,height,margin,"15_draw_font_O.ppm");
    points.clear();clear_image(image,width,height,margin);
    draw_font_P(points,color,width,height,margin);
    draw(points,image,color,width,height,margin,linesize);
    save_image(image,width,height,margin,"15_draw_font_P.ppm");
    points.clear();clear_image(image,width,height,margin);
    draw_font_Q(points,color,width,height,margin);
    draw(points,image,color,width,height,margin,linesize);
    save_image(image,width,height,margin,"15_draw_font_Q.ppm");
    points.clear();clear_image(image,width,height,margin);
    draw_font_R(points,color,width,height,margin);
    draw(points,image,color,width,height,margin,linesize);
    save_image(image,width,height,margin,"15_draw_font_R.ppm");
    points.clear();clear_image(image,width,height,margin);
    draw_font_S(points,color,width,height,margin);
    draw(points,image,color,width,height,margin,linesize);
    save_image(image,width,height,margin,"15_draw_font_S.ppm");
    points.clear();clear_image(image,width,height,margin);
    draw_font_T(points,color,width,height,margin);
    draw(points,image,color,width,height,margin,linesize);
    save_image(image,width,height,margin,"15_draw_font_T.ppm");
    points.clear();clear_image(image,width,height,margin);
    draw_font_U(points,color,width,height,margin);
    draw(points,image,color,width,height,margin,linesize);
    save_image(image,width,height,margin,"15_draw_font_U.ppm");
    points.clear();clear_image(image,width,height,margin);
    draw_font_V(points,color,width,height,margin);
    draw(points,image,color,width,height,margin,linesize);
    save_image(image,width,height,margin,"15_draw_font_V.ppm");
    points.clear();clear_image(image,width,height,margin);
    draw_font_W(points,color,width,height,margin);
    draw(points,image,color,width,height,margin,linesize);
    save_image(image,width,height,margin,"15_draw_font_W.ppm");
    points.clear();clear_image(image,width,height,margin);
    draw_font_X(points,color,width,height,margin);
    draw(points,image,color,width,height,margin,linesize);
    save_image(image,width,height,margin,"15_draw_font_X.ppm");
    points.clear();clear_image(image,width,height,margin);
    draw_font_Y(points,color,width,height,margin);
    draw(points,image,color,width,height,margin,linesize);
    save_image(image,width,height,margin,"15_draw_font_Y.ppm");
    points.clear();clear_image(image,width,height,margin);
    draw_font_Z(points,color,width,height,margin);
    draw(points,image,color,width,height,margin,linesize);
    save_image(image,width,height,margin,"15_draw_font_Z.ppm");
    points.clear();clear_image(image,width,height,margin);
    draw_font_0(points,color,width,height,margin);
    draw(points,image,color,width,height,margin,linesize);
    save_image(image,width,height,margin,"15_draw_font_0.ppm");
    points.clear();clear_image(image,width,height,margin);
    draw_font_1(points,color,width,height,margin);
    draw(points,image,color,width,height,margin,linesize);
    save_image(image,width,height,margin,"15_draw_font_1.ppm");
    points.clear();clear_image(image,width,height,margin);
    draw_font_2(points,color,width,height,margin);
    draw(points,image,color,width,height,margin,linesize);
    save_image(image,width,height,margin,"15_draw_font_2.ppm");
    points.clear();clear_image(image,width,height,margin);
    draw_font_3(points,color,width,height,margin);
    draw(points,image,color,width,height,margin,linesize);
    save_image(image,width,height,margin,"15_draw_font_3.ppm");
    points.clear();clear_image(image,width,height,margin);
    draw_font_4(points,color,width,height,margin);
    draw(points,image,color,width,height,margin,linesize);
    save_image(image,width,height,margin,"15_draw_font_4.ppm");
    points.clear();clear_image(image,width,height,margin);
    draw_font_5(points,color,width,height,margin);
    draw(points,image,color,width,height,margin,linesize);
    save_image(image,width,height,margin,"15_draw_font_5.ppm");
    points.clear();clear_image(image,width,height,margin);
    draw_font_6(points,color,width,height,margin);
    draw(points,image,color,width,height,margin,linesize);
    save_image(image,width,height,margin,"15_draw_font_6.ppm");
    points.clear();clear_image(image,width,height,margin);
    draw_font_7(points,color,width,height,margin);
    draw(points,image,color,width,height,margin,linesize);
    save_image(image,width,height,margin,"15_draw_font_7.ppm");
    points.clear();clear_image(image,width,height,margin);
    draw_font_8(points,color,width,height,margin);
    draw(points,image,color,width,height,margin,linesize);
    save_image(image,width,height,margin,"15_draw_font_8.ppm");
    points.clear();clear_image(image,width,height,margin);
    draw_font_9(points,color,width,height,margin);
    draw(points,image,color,width,height,margin,linesize);
    save_image(image,width,height,margin,"15_draw_font_9.ppm");
    points.clear();clear_image(image,width,height,margin);
    draw_font_QA(points,color,width,height,margin);
    draw(points,image,color,width,height,margin,linesize);
    save_image(image,width,height,margin,"15_draw_font_?.ppm");
    points.clear();clear_image(image,width,height,margin);
    draw_font_PROCENT(points,color,width,height,margin);
    draw(points,image,color,width,height,margin,linesize);
    save_image(image,width,height,margin,"15_draw_font_\%.ppm");
}

int main()
{
    int width=0;int height=40;
    int margin=0;
    int linesize=3;
    std::vector<std::tuple<float, float, float>> image;
    std::tuple<float,float,float> color=std::make_tuple(0.0f,0.0f,0.0f);

    get_width_from_height(width,height);
    get_margin_from_height(margin,height);
    std::cout << "w: " << width << " h: " << height << " m: " << margin << " ls: " << linesize << std::endl;

    image.resize(calc_size(width, height, margin));
    clear_image(image,width,height,margin);

    draw_and_save_font(image,color,width,height,margin,linesize);

    return 0;
}