// Compile: clang++ -std=c++17 16_draw_table.cpp -o 16_draw_table

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
            image[get_index(x,y,(width+margin))]=std::make_tuple(1.0f,0.7647058824f,0.6235294118f);
        }
    }
}

void stamp(std::vector<std::tuple<float, float, float>> &image, std::vector<std::tuple<float, float, float>> &letter, int offsetx, int offsety, int inputwidth, int inputheight, int width)
{
    int inputx=0;
    int inputy=0;
    for (int y = offsety; y < offsety+inputheight; ++y)
    {
        for (int x = offsetx; x < offsetx+inputwidth; ++x)
        {
            image[get_index(x,y,width)]=letter[get_index(inputx,inputy,inputwidth)];
            inputx++;
        }
        inputy++;
        inputx=0;
    }
}

void get_line_points(std::vector<std::tuple<int,int>> &points, std::tuple<int, int, int, int> &coords, std::tuple<float,float,float> &color, int width, int height)
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
        get_line_points(points,coords,color,width,height);
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
        get_line_points(points,coords,color,width,height);
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
        get_line_points(points,coords,color,width,height);
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
        get_line_points(points,coords,color,width,height);
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
        get_line_points(points,coords,color,width,height);
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
        get_line_points(points,coords,color,width,height);
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
        get_line_points(points,coords,color,width,height);
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
        get_line_points(points,coords,color,width,height);
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
        get_line_points(points,coords,color,width,height);
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
        get_line_points(points,coords,color,width,height);
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
        get_line_points(points,coords,color,width,height);
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
        get_line_points(points,coords,color,width,height);
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
        get_line_points(points,coords,color,width,height);
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
        get_line_points(points,coords,color,width,height);
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
        get_line_points(points,coords,color,width,height);
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
        get_line_points(points,coords,color,width,height);
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
        get_line_points(points,coords,color,width,height);
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
        get_line_points(points,coords,color,width,height);
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
        get_line_points(points,coords,color,width,height);
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
        get_line_points(points,coords,color,width,height);
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
    std::ofstream out(filename, std::ios_base::out | std::ios_base::binary);
    out << "P6" << std::endl << width << ' ' << height << std::endl << "255" << std::endl;

    for (int i=0;i<(width*height);++i)
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
            image[get_index(std::get<0>(p),std::get<1>(p),width+margin)]=color;
        } else {
            draw_filled_circle(std::get<0>(p),std::get<1>(p),linesize,image,color,width,height,margin);
        }
    }
}

int main()
{
    std::vector<std::tuple<float, float, float>> image;
    std::vector<std::tuple<int,int>> points;
    std::tuple<float,float,float> color1=std::make_tuple(1.0f,1.0f,1.0f);
    std::tuple<float,float,float> color2=std::make_tuple(0.262745098f,0.262745098f,0.262745098f);
    std::tuple<float,float,float> color3=std::make_tuple(0.0f,0.0f,0.0f);
    int width=1600,height=900;
    int margin=0;
    int linesize=1;
    int fwidth=0;
    int fheight=10;

    get_width_from_height(fwidth,fheight);
    get_margin_from_height(margin,fheight);

    image.resize(calc_size(width, height, margin));
    clear_image(image,width,height,margin);

    std::vector<std::tuple<float, float, float>> f_m;
    f_m.resize(calc_size(fwidth, fheight, margin));
    clear_image(f_m,fwidth,fheight,margin);
    draw_font_M(points,color3,fwidth,fheight,margin);
    draw(points,f_m,color3,fwidth,fheight,margin,linesize);
    points.clear();
    std::vector<std::tuple<float, float, float>> f_a;
    f_a.resize(calc_size(fwidth, fheight, margin));
    clear_image(f_a,fwidth,fheight,margin);
    draw_font_A(points,color3,fwidth,fheight,margin);
    draw(points,f_a,color3,fwidth,fheight,margin,linesize);
    points.clear();
    std::vector<std::tuple<float, float, float>> f_r;
    f_r.resize(calc_size(fwidth, fheight, margin));
    clear_image(f_r,fwidth,fheight,margin);
    draw_font_R(points,color3,fwidth,fheight,margin);
    draw(points,f_r,color3,fwidth,fheight,margin,linesize);
    points.clear();
    std::vector<std::tuple<float, float, float>> f_s;
    f_s.resize(calc_size(fwidth, fheight, margin));
    clear_image(f_s,fwidth,fheight,margin);
    draw_font_S(points,color3,fwidth,fheight,margin);
    draw(points,f_s,color3,fwidth,fheight,margin,linesize);
    points.clear();
    std::vector<std::tuple<float, float, float>> f_e;
    f_e.resize(calc_size(fwidth, fheight, margin));
    clear_image(f_e,fwidth,fheight,margin);
    draw_font_E(points,color3,fwidth,fheight,margin);
    draw(points,f_e,color3,fwidth,fheight,margin,linesize);
    points.clear();
    std::vector<std::tuple<float, float, float>> f_u;
    f_u.resize(calc_size(fwidth, fheight, margin));
    clear_image(f_u,fwidth,fheight,margin);
    draw_font_U(points,color3,fwidth,fheight,margin);
    draw(points,f_u,color3,fwidth,fheight,margin,linesize);
    points.clear();
    std::vector<std::tuple<float, float, float>> f_c;
    f_c.resize(calc_size(fwidth, fheight, margin));
    clear_image(f_c,fwidth,fheight,margin);
    draw_font_C(points,color3,fwidth,fheight,margin);
    draw(points,f_c,color3,fwidth,fheight,margin,linesize);
    points.clear();
    std::vector<std::tuple<float, float, float>> f_y;
    f_y.resize(calc_size(fwidth, fheight, margin));
    clear_image(f_y,fwidth,fheight,margin);
    draw_font_Y(points,color3,fwidth,fheight,margin);
    draw(points,f_y,color3,fwidth,fheight,margin,linesize);
    points.clear();
    std::vector<std::tuple<float, float, float>> f_t;
    f_t.resize(calc_size(fwidth, fheight, margin));
    clear_image(f_t,fwidth,fheight,margin);
    draw_font_T(points,color3,fwidth,fheight,margin);
    draw(points,f_t,color3,fwidth,fheight,margin,linesize);
    points.clear();
    std::vector<std::tuple<float, float, float>> f_n;
    f_n.resize(calc_size(fwidth, fheight, margin));
    clear_image(f_n,fwidth,fheight,margin);
    draw_font_N(points,color3,fwidth,fheight,margin);
    draw(points,f_n,color3,fwidth,fheight,margin,linesize);
    points.clear();
    std::vector<std::tuple<float, float, float>> f_1;
    f_1.resize(calc_size(fwidth, fheight, margin));
    clear_image(f_1,fwidth,fheight,margin);
    draw_font_1(points,color3,fwidth,fheight,margin);
    draw(points,f_1,color3,fwidth,fheight,margin,linesize);
    points.clear();
    std::vector<std::tuple<float, float, float>> f_2;
    f_2.resize(calc_size(fwidth, fheight, margin));
    clear_image(f_2,fwidth,fheight,margin);
    draw_font_2(points,color3,fwidth,fheight,margin);
    draw(points,f_2,color3,fwidth,fheight,margin,linesize);
    points.clear();
    std::vector<std::tuple<float, float, float>> f_3;
    f_3.resize(calc_size(fwidth, fheight, margin));
    clear_image(f_3,fwidth,fheight,margin);
    draw_font_3(points,color3,fwidth,fheight,margin);
    draw(points,f_3,color3,fwidth,fheight,margin,linesize);
    points.clear();

    std::vector<std::tuple<float, float, float>> f_w0;
    f_w0.resize(calc_size(fwidth, fheight, margin));
    clear_image(f_w0,fwidth,fheight,margin);
    draw_font_0(points,color2,fwidth,fheight,margin);
    draw(points,f_w0,color2,fwidth,fheight,margin,linesize);
    points.clear();
    std::vector<std::tuple<float, float, float>> f_w1;
    f_w1.resize(calc_size(fwidth, fheight, margin));
    clear_image(f_w1,fwidth,fheight,margin);
    draw_font_1(points,color2,fwidth,fheight,margin);
    draw(points,f_w1,color2,fwidth,fheight,margin,linesize);
    points.clear();
    std::vector<std::tuple<float, float, float>> f_w2;
    f_w2.resize(calc_size(fwidth, fheight, margin));
    clear_image(f_w2,fwidth,fheight,margin);
    draw_font_2(points,color2,fwidth,fheight,margin);
    draw(points,f_w2,color2,fwidth,fheight,margin,linesize);
    points.clear();
    std::vector<std::tuple<float, float, float>> f_w3;
    f_w3.resize(calc_size(fwidth, fheight, margin));
    clear_image(f_w3,fwidth,fheight,margin);
    draw_font_3(points,color2,fwidth,fheight,margin);
    draw(points,f_w3,color2,fwidth,fheight,margin,linesize);
    points.clear();
    std::vector<std::tuple<float, float, float>> f_w4;
    f_w4.resize(calc_size(fwidth, fheight, margin));
    clear_image(f_w4,fwidth,fheight,margin);
    draw_font_4(points,color2,fwidth,fheight,margin);
    draw(points,f_w4,color2,fwidth,fheight,margin,linesize);
    points.clear();
    std::vector<std::tuple<float, float, float>> f_w5;
    f_w5.resize(calc_size(fwidth, fheight, margin));
    clear_image(f_w5,fwidth,fheight,margin);
    draw_font_5(points,color2,fwidth,fheight,margin);
    draw(points,f_w5,color2,fwidth,fheight,margin,linesize);
    points.clear();
    std::vector<std::tuple<float, float, float>> f_w6;
    f_w6.resize(calc_size(fwidth, fheight, margin));
    clear_image(f_w6,fwidth,fheight,margin);
    draw_font_6(points,color2,fwidth,fheight,margin);
    draw(points,f_w6,color2,fwidth,fheight,margin,linesize);
    points.clear();
    std::vector<std::tuple<float, float, float>> f_w7;
    f_w7.resize(calc_size(fwidth, fheight, margin));
    clear_image(f_w7,fwidth,fheight,margin);
    draw_font_7(points,color2,fwidth,fheight,margin);
    draw(points,f_w7,color2,fwidth,fheight,margin,linesize);
    points.clear();
    std::vector<std::tuple<float, float, float>> f_w8;
    f_w8.resize(calc_size(fwidth, fheight, margin));
    clear_image(f_w8,fwidth,fheight,margin);
    draw_font_8(points,color2,fwidth,fheight,margin);
    draw(points,f_w8,color2,fwidth,fheight,margin,linesize);
    points.clear();
    std::vector<std::tuple<float, float, float>> f_w9;
    f_w9.resize(calc_size(fwidth, fheight, margin));
    clear_image(f_w9,fwidth,fheight,margin);
    draw_font_9(points,color2,fwidth,fheight,margin);
    draw(points,f_w9,color2,fwidth,fheight,margin,linesize);
    points.clear();

    draw_filled_rect(402,322,796,5,image,color1,width,height);
    draw_filled_rect(402,418,796,5,image,color1,width,height);
    draw_filled_rect(402,514,796,5,image,color1,width,height);
    draw_filled_rect(402,611,796,5,image,color1,width,height);
    draw_filled_rect(402,707,796,5,image,color1,width,height);
    draw_filled_rect(402,322,5,390,image,color1,width,height);
    draw_filled_rect(557,322,5,390,image,color1,width,height);
    draw_filled_rect(769,322,5,390,image,color1,width,height);
    draw_filled_rect(970,322,5,390,image,color1,width,height);
    draw_filled_rect(1193,322,5,390,image,color1,width,height);

    // Labels
    stamp(image,f_m,420,460,(fwidth+margin),(fheight+margin),width);
    stamp(image,f_e,420+(1*(fwidth+margin)),460,(fwidth+margin),(fheight+margin),width);
    stamp(image,f_r,420+(2*(fwidth+margin)),460,(fwidth+margin),(fheight+margin),width);
    stamp(image,f_c,420+(3*(fwidth+margin)),460,(fwidth+margin),(fheight+margin),width);
    stamp(image,f_u,420+(4*(fwidth+margin)),460,(fwidth+margin),(fheight+margin),width);
    stamp(image,f_r,420+(5*(fwidth+margin)),460,(fwidth+margin),(fheight+margin),width);
    stamp(image,f_y,420+(6*(fwidth+margin)),460,(fwidth+margin),(fheight+margin),width);

    stamp(image,f_m,446,560,(fwidth+margin),(fheight+margin),width);
    stamp(image,f_a,446+(1*(fwidth+margin)),560,(fwidth+margin),(fheight+margin),width);
    stamp(image,f_r,446+(2*(fwidth+margin)),560,(fwidth+margin),(fheight+margin),width);
    stamp(image,f_s,446+(3*(fwidth+margin)),560,(fwidth+margin),(fheight+margin),width);

    stamp(image,f_s,426,660,(fwidth+margin),(fheight+margin),width);
    stamp(image,f_a,426+(1*(fwidth+margin)),660,(fwidth+margin),(fheight+margin),width);
    stamp(image,f_t,426+(2*(fwidth+margin)),660,(fwidth+margin),(fheight+margin),width);
    stamp(image,f_u,426+(3*(fwidth+margin)),660,(fwidth+margin),(fheight+margin),width);
    stamp(image,f_r,426+(4*(fwidth+margin)),660,(fwidth+margin),(fheight+margin),width);
    stamp(image,f_n,426+(5*(fwidth+margin)),660,(fwidth+margin),(fheight+margin),width);

    stamp(image,f_a,646,370,(fwidth+margin),(fheight+margin),width);
    stamp(image,f_1,646+(1*(fwidth+margin)),370,(fwidth+margin),(fheight+margin),width);

    stamp(image,f_a,846,370,(fwidth+margin),(fheight+margin),width);
    stamp(image,f_2,846+(1*(fwidth+margin)),370,(fwidth+margin),(fheight+margin),width);

    stamp(image,f_a,1056,370,(fwidth+margin),(fheight+margin),width);
    stamp(image,f_3,1056+(1*(fwidth+margin)),370,(fwidth+margin),(fheight+margin),width);

    stamp(image,f_w1,626,460,(fwidth+margin),(fheight+margin),width);
    stamp(image,f_w0,626+(1*(fwidth+margin)),460,(fwidth+margin),(fheight+margin),width);
    stamp(image,f_w8,626+(2*(fwidth+margin)),460,(fwidth+margin),(fheight+margin),width);
    stamp(image,f_w4,626+(3*(fwidth+margin)),460,(fwidth+margin),(fheight+margin),width);

    stamp(image,f_w6,836,460,(fwidth+margin),(fheight+margin),width);
    stamp(image,f_w5,836+(1*(fwidth+margin)),460,(fwidth+margin),(fheight+margin),width);
    stamp(image,f_w0,836+(2*(fwidth+margin)),460,(fwidth+margin),(fheight+margin),width);
    stamp(image,f_w2,836+(3*(fwidth+margin)),460,(fwidth+margin),(fheight+margin),width);

    stamp(image,f_w6,1036,460,(fwidth+margin),(fheight+margin),width);
    stamp(image,f_w8,1036+(1*(fwidth+margin)),460,(fwidth+margin),(fheight+margin),width);
    stamp(image,f_w0,1036+(2*(fwidth+margin)),460,(fwidth+margin),(fheight+margin),width);
    stamp(image,f_w0,1036+(3*(fwidth+margin)),460,(fwidth+margin),(fheight+margin),width);
    stamp(image,f_w0,1036+(4*(fwidth+margin)),460,(fwidth+margin),(fheight+margin),width);

    stamp(image,f_w6,646,560,(fwidth+margin),(fheight+margin),width);
    stamp(image,f_w4,646+(1*(fwidth+margin)),560,(fwidth+margin),(fheight+margin),width);

    stamp(image,f_w5,846,560,(fwidth+margin),(fheight+margin),width);
    stamp(image,f_w0,846+(1*(fwidth+margin)),560,(fwidth+margin),(fheight+margin),width);
    stamp(image,f_w0,846+(2*(fwidth+margin)),560,(fwidth+margin),(fheight+margin),width);

    stamp(image,f_w1,1046,560,(fwidth+margin),(fheight+margin),width);
    stamp(image,f_w5,1046+(1*(fwidth+margin)),560,(fwidth+margin),(fheight+margin),width);
    stamp(image,f_w4,1046+(2*(fwidth+margin)),560,(fwidth+margin),(fheight+margin),width);
    stamp(image,f_w1,1046+(3*(fwidth+margin)),560,(fwidth+margin),(fheight+margin),width);

    stamp(image,f_w1,626,660,(fwidth+margin),(fheight+margin),width);
    stamp(image,f_w0,626+(1*(fwidth+margin)),660,(fwidth+margin),(fheight+margin),width);
    stamp(image,f_w2,626+(2*(fwidth+margin)),660,(fwidth+margin),(fheight+margin),width);
    stamp(image,f_w4,626+(3*(fwidth+margin)),660,(fwidth+margin),(fheight+margin),width);

    stamp(image,f_w4,836,660,(fwidth+margin),(fheight+margin),width);
    stamp(image,f_w0,836+(1*(fwidth+margin)),660,(fwidth+margin),(fheight+margin),width);
    stamp(image,f_w9,836+(2*(fwidth+margin)),660,(fwidth+margin),(fheight+margin),width);
    stamp(image,f_w6,836+(3*(fwidth+margin)),660,(fwidth+margin),(fheight+margin),width);

    stamp(image,f_w8,1046,660,(fwidth+margin),(fheight+margin),width);
    stamp(image,f_w1,1046+(1*(fwidth+margin)),660,(fwidth+margin),(fheight+margin),width);
    stamp(image,f_w9,1046+(2*(fwidth+margin)),660,(fwidth+margin),(fheight+margin),width);
    stamp(image,f_w2,1046+(3*(fwidth+margin)),660,(fwidth+margin),(fheight+margin),width);

    std::cout << "saving: 16_draw_table.ppm." << std::endl;
    save_image(image,width,height,"16_draw_table.ppm");

    return 0;
}