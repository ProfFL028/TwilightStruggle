// Compile: clang++ -std=c++20 10_curved_lines.cpp -o 10_curved_lines

#include <iostream>
#include <fstream>
#include <tuple>
#include <vector>
#include <random>
#include <cmath>

void linear_bezier_curves(std::tuple<int, int, int, int> &coords, int split, std::vector<std::tuple<int,int>>& xy)
{
    float t=0.0;
    float delta=(float(1)/float(split));
    int x=0;
    int y=0;

    for (int i=0;i<split;++i)
    {
        x = std::lerp(std::get<0>(coords),std::get<2>(coords),t);
        y = std::lerp(std::get<1>(coords),std::get<3>(coords),t);
        xy.push_back(std::make_tuple(x,y));
        t+=delta;
    }
}

void quadratic_bezier_curves(int px0, int py0, int px1, int py1, int px2, int py2, int split, std::vector<std::tuple<int,int>>& xy)
{
    double t=0.0;
    double delta=(double(1)/double(split));
    int x=0;
    int y=0;
    int x1=0;
    int y1=0;
    int x2=0;
    int y2=0;
    for (int i=0;i<split;++i)
    {
        x1 = std::lerp(px0,px1,t);
        y1 = std::lerp(py0,py1,t);
        x2 = std::lerp(px1,px2,t);
        y2 = std::lerp(py1,py2,t);
        x = std::lerp(x1,x2,t);
        y = std::lerp(y1,y2,t);
        xy.push_back(std::make_tuple(x,y));
        t+=delta;
    }
}

void cubic_bezier_curves(int px0, int py0, int px1, int py1, int px2, int py2, int px3, int py3, int split, std::vector<std::tuple<int,int>>& xy)
{
    float t=0.0;
    float delta=(float(1)/float(split));
    int x=0;
    int y=0;
    int x1=0;
    int y1=0;
    int x2=0;
    int y2=0;
    int x3=0;
    int y3=0;
    int x4=0;
    int y4=0;
    int xx1=0;
    int yy1=0;
    int xx2=0;
    int yy2=0;
    for (int i=0;i<split;++i)
    {
        x1 = std::lerp(px0,px1,t);
        y1 = std::lerp(py0,py1,t);
        x2 = std::lerp(px1,px2,t);
        y2 = std::lerp(py1,py2,t);

        x3 = std::lerp(px1,px2,t);
        y3 = std::lerp(py1,py2,t);
        x4 = std::lerp(px2,px3,t);
        y4 = std::lerp(py2,py3,t);

        xx1 = std::lerp(x1,x2,t);
        yy1 = std::lerp(y1,y2,t);
        xx2 = std::lerp(x3,x4,t);
        yy2 = std::lerp(y3,y4,t);

        x = std::lerp(xx1,xx2,t);
        y = std::lerp(yy1,yy2,t);
        xy.push_back(std::make_tuple(x,y));
        t+=delta;
    }
}

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

void draw_xy_line(std::vector<std::tuple<float, float, float>> &image,std::tuple<float,float,float> &color,std::vector<std::tuple<int,int>>& xy,int width,int height,int x_stop,int y_stop)
{
    std::tuple<int, int> temp=xy[0];
    std::tuple<int, int> store;
    store=std::make_tuple(x_stop,y_stop);
    xy.push_back(store);
    std::vector<std::tuple<int,int,int,int>> xyxy;
    for (int i=1;i<xy.size();++i)
    {
        store=xy[i];
        xyxy.push_back(std::make_tuple(std::get<0>(temp),std::get<1>(temp),std::get<0>(store),std::get<1>(store)));
        temp=xy[i];
    }

    for (auto& li : xyxy)
    {
        draw_line(image,li,color,width,height);
    }
}

void draw_xy_dots(std::vector<std::tuple<float, float, float>> &image,std::tuple<float,float,float> &color,std::vector<std::tuple<int,int>>& xy,int width,int height)
{
    for (auto& pt : xy)
    {
        image[get_index(std::get<0>(pt),std::get<1>(pt),width)]=color;
    }
}

void draw_marker(int x, int y, std::vector<std::tuple<float, float, float>> &image, std::tuple<float,float,float> &color, int width, int height)
{
    image[get_index(x-1,y-1,width)]=color;
    image[get_index(x,y-1,width)]=color;
    image[get_index(x+1,y-1,width)]=color;
    image[get_index(x+1,y,width)]=color;
    image[get_index(x+1,y+1,width)]=color;
    image[get_index(x,y+1,width)]=color;
    image[get_index(x-1,y+1,width)]=color;
    image[get_index(x-1,y,width)]=color;

    color=std::make_tuple(1.0f, 1.0f, 1.0f);
    image[get_index(x,y,width)]=color;
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
    std::vector<std::tuple<float, float, float>> image;
    std::tuple<float,float,float> color;

    image.resize(calc_size(width, height));
    clear_image(image,width,height);

    std::vector<std::tuple<int,int>> xy;
    std::tuple<int, int, int, int> coords;

    // Draw a line with Bezier.
    color=std::make_tuple(0.9296875, 0.9296875, 0.9296875);
    coords=std::make_tuple(20,90,300,90);
    draw_line(image,coords,color,width,height);
    linear_bezier_curves(coords,40,xy);
    color=std::make_tuple(0.7019607843, 0.2196078431, 0.6078431373);
    draw_xy_line(image,color,xy,width,height,300,90);
    xy.clear();
    coords=std::make_tuple(20,90,300,90);
    linear_bezier_curves(coords,10,xy);
    color=std::make_tuple(0.8784313725, 0.8784313725, 0.0);
    draw_xy_dots(image,color,xy,width,height);
    xy.clear();
    color=std::make_tuple(0.0, 0.8784313725, 0.0);
    draw_marker(20,90,image,color,width,height);
    color=std::make_tuple(0.0, 0.8784313725, 0.0);
    draw_marker(300,90,image,color,width,height);

    // Draw line as a curve 1.
    color=std::make_tuple(0.9296875, 0.9296875, 0.9296875);
    coords=std::make_tuple(340,90,480,2);
    draw_line(image,coords,color,width,height);
    coords=std::make_tuple(480,2,620,90);
    draw_line(image,coords,color,width,height);
    quadratic_bezier_curves(340,90,480,2,620,90,40,xy);
    color=std::make_tuple(0.7019607843, 0.2196078431, 0.6078431373);
    draw_xy_line(image,color,xy,width,height,620,90);
    xy.clear();
    quadratic_bezier_curves(340,90,480,2,620,90,10,xy);
    color=std::make_tuple(0.8784313725, 0.8784313725, 0.0);
    draw_xy_dots(image,color,xy,width,height);
    xy.clear();
    color=std::make_tuple(0.0, 0.8784313725, 0.0);
    draw_marker(340,90,image,color,width,height);
    color=std::make_tuple(0.0, 0.8784313725, 0.0);
    draw_marker(480,2,image,color,width,height);
    color=std::make_tuple(0.0, 0.8784313725, 0.0);
    draw_marker(620,90,image,color,width,height);

    // Draw line as a curve 2.
    xy.clear();
    color=std::make_tuple(0.9296875, 0.9296875, 0.9296875);
    coords=std::make_tuple(200,270,293,182);
    draw_line(image,coords,color,width,height);
    coords=std::make_tuple(386,357,480,270);
    draw_line(image,coords,color,width,height);
    cubic_bezier_curves(200,270,293,182,386,357,480,270,40,xy);
    color=std::make_tuple(0.7019607843, 0.2196078431, 0.6078431373);
    draw_xy_line(image,color,xy,width,height,480,270);
    xy.clear();
    cubic_bezier_curves(200,270,293,182,386,357,480,270,10,xy);
    color=std::make_tuple(0.8784313725, 0.8784313725, 0.0);
    draw_xy_dots(image,color,xy,width,height);
    xy.clear();
    color=std::make_tuple(0.0, 0.8784313725, 0.0);
    draw_marker(200,270,image,color,width,height);
    color=std::make_tuple(0.0, 0.8784313725, 0.0);
    draw_marker(293,182,image,color,width,height);
    color=std::make_tuple(0.0, 0.8784313725, 0.0);
    draw_marker(386,357,image,color,width,height);
    color=std::make_tuple(0.0, 0.8784313725, 0.0);
    draw_marker(480,270,image,color,width,height);

    save_image(image,width,height,"10_curved_lines.ppm");

    return 0;
}