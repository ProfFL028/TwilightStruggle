// Compile: clang++ -std=c++17 12_wedge.cpp -o 12_wedge

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

void get_all_ys(std::vector<int> &ys,std::vector<std::tuple<int,int>> &coords)
{
    for (auto& c : coords) {
        ys.push_back(std::get<1>(c));
    }

    sort(ys.begin(), ys.end());
    ys.erase( unique( ys.begin(), ys.end() ), ys.end() );
}

void draw_line_coords(int x1, int y1, int x2, int y2,std::vector<std::tuple<int,int>> &coords)
{
    int x, y, dx, dy, dx1, dy1, px, py, xe, ye, i;
    dx = x2 - x1; dy = y2 - y1;
    if (dx == 0)
    {
        if (y2 < y1) std::swap(y1, y2);
        for (y = y1; y <= y2; y++)
            coords.push_back(std::make_tuple(x1,y));
        return;
    }
    if (dy == 0)
    {
        if (x2 < x1) std::swap(x1, x2);
        for (x = x1; x <= x2; x++)
            coords.push_back(std::make_tuple(x,y1));
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
        coords.push_back(std::make_tuple(x,y));
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
            coords.push_back(std::make_tuple(x,y));
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
        coords.push_back(std::make_tuple(x,y));
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
            coords.push_back(std::make_tuple(x,y));
        }
    }
}

void draw_wedge(int x_cen,int y_cen,int rad,int start_ang,int end_ang,std::vector<std::tuple<float, float, float>> &image,std::tuple<float, float, float> &color, int width, int height)
{
    std::vector<std::tuple<int,int>> coords;

    float ang=(((start_ang<=end_ang)?start_ang:end_ang)*(M_PI/180));
    float range=(((end_ang>start_ang)?end_ang:start_ang)*(M_PI/180));
    float x=(rad*cos(ang));
    float y=(rad*sin(ang));
    do
    {
        coords.push_back(std::make_tuple((int)(x_cen+x+0.5),(int)(y_cen-y+0.5)));
        ang+=0.001;
        x=(rad*cos(ang));
        y=(rad*sin(ang));
    }
    while(ang<=range);

    std::tuple<int,int> co1=coords.front();
    std::tuple<int,int> co2=coords.back();

    draw_line_coords(x_cen,y_cen,std::get<0>(co1),std::get<1>(co1),coords);
    draw_line_coords(x_cen,y_cen,std::get<0>(co2),std::get<1>(co2),coords);

    for (auto & e : coords) {
        image[get_index(std::get<0>(e),std::get<1>(e),width)]=color;
    }
}

void draw_filled_wedge(int x_cen,int y_cen,int rad,int start_ang,int end_ang,std::vector<std::tuple<float, float, float>> &image,std::tuple<float, float, float> &color, int width, int height)
{
    std::vector<std::tuple<int,int>> coords;

    float ang=(((start_ang<=end_ang)?start_ang:end_ang)*(M_PI/180));
    float range=(((end_ang>start_ang)?end_ang:start_ang)*(M_PI/180));
    float x=(rad*cos(ang));
    float y=(rad*sin(ang));
    do
    {
        coords.push_back(std::make_tuple((int)(x_cen+x+0.5),(int)(y_cen-y+0.5)));
        ang+=0.001;
        x=(rad*cos(ang));
        y=(rad*sin(ang));
    }
    while(ang<=range);

    std::tuple<int,int> co1=coords.front();
    std::tuple<int,int> co2=coords.back();

    draw_line_coords(x_cen,y_cen,std::get<0>(co1),std::get<1>(co1),coords);
    draw_line_coords(x_cen,y_cen,std::get<0>(co2),std::get<1>(co2),coords);

    std::vector<int> ys;
    std::vector<int> xs;
    get_all_ys(ys,coords);
    std::vector<std::tuple<int,int,int,int>> lines;

    for (int search=0;search<=ys.size();++search)
    {
        for (auto& c : coords) {
            if (std::get<1>(c) == ys[search]) {
                xs.push_back(std::get<0>(c));
            }
        }
        sort(xs.begin(), xs.end());
        lines.push_back(std::make_tuple(xs.front(),ys[search],xs.back(),ys[search]));
        xs.clear();
    }

    auto drawline = [&](int sx, int ex, int ny)
    {
        for (int i = sx; i <= ex; i++)
            image[get_index(i, ny, width)]=color;
    };

    for (auto& l : lines) {
        drawline(std::get<0>(l),std::get<2>(l),std::get<1>(l));
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

    std::vector<std::tuple<float, float, float>> image;
    std::tuple<float,float,float> color=std::make_tuple(0.0f,0.0f,0.0f);

    image.resize(calc_size(width, height));
    clear_image(image,width,height);

    int x_cen,y_cen,rad,start_ang,end_ang;
    x_cen=width/2;
    y_cen=height/2;
    rad=y_cen*0.8;
    start_ang=0;
    end_ang=348;
    image[get_index(x_cen,y_cen, width)]=color;
    draw_filled_wedge(x_cen,y_cen,rad,start_ang,end_ang,image,color,width,height);
    color=std::make_tuple(0.5f,0.5f,0.5f);
    draw_filled_wedge(x_cen,y_cen,rad/2,start_ang,end_ang,image,color,width,height);
    color=std::make_tuple(0.8f,0.0f,0.8f);
    draw_wedge(x_cen,y_cen,rad,start_ang,end_ang,image,color,width,height);

    save_image(image,width,height,"12_wedge.ppm");

    return 0;
}