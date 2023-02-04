// Compile: clang++ -std=c++17 16_draw_donut_chart.cpp -o 16_draw_donut_chart

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

void clear_image(std::vector<std::tuple<float, float, float>> &image, int width, int height, int margin)
{
    for (int y=0;y<(height+margin);++y) {
        for (int x=0;x<(width+margin);++x) {
            image[get_index(x,y,(width+margin))]=std::make_tuple(1.0f,0.7647058824f,0.6235294118f);
        }
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

void draw_filled_circle2(int x, int y, int radius, std::vector<std::tuple<float, float, float>> &image, std::tuple<float, float, float> &color, int width, int height)
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
            image[get_index(std::get<0>(p),std::get<1>(p),width+margin)]=std::make_tuple(0.0f, 0.0f, 0.0f);
        } else {
            draw_filled_circle(std::get<0>(p),std::get<1>(p),linesize,image,color,width,height,margin);
        }
    }
}

void draw2(std::vector<std::tuple<int,int>> points,std::vector<std::tuple<float, float, float>> &image, std::tuple<float,float,float> color, int width, int height, int linesize)
{
    for (auto& p : points) {
        if (linesize == 1) {
            image[get_index(std::get<0>(p),std::get<1>(p),width)]=std::make_tuple(0.0f, 0.0f, 0.0f);
        } else {
            draw_filled_circle2(std::get<0>(p),std::get<1>(p),linesize,image,color,width,height);
        }
    }
}

int main()
{
    std::vector<std::tuple<float, float, float>> image;
    std::vector<std::tuple<int,int>> points;
    std::tuple<int, int, int, int> coords;
    int width=1600,height=900;
    int margin=0;
    int linesize=2;
    int fwidth=0;
    int fheight=20;
    int label_x=0;

    get_width_from_height(fwidth,fheight);
    get_margin_from_height(margin,fheight);
    label_x=(fwidth+margin)/2;

    std::tuple<float,float,float> color0=std::make_tuple(1.0f,0.7647058824f,0.6235294118f);
    std::tuple<float,float,float> color1=std::make_tuple(0.968627451f,0.5882352941f,0.3607843137f);
    std::tuple<float,float,float> color2=std::make_tuple(0.262745098f, 0.262745098f, 0.262745098f);

    std::vector<std::tuple<float, float, float>> f_m;
    f_m.resize(calc_size(fwidth, fheight, margin));
    clear_image(f_m,fwidth,fheight,margin);
    draw_font_M(points,color2,fwidth,fheight,margin);
    draw(points,f_m,color2,fwidth,fheight,margin,linesize);
    points.clear();
    std::vector<std::tuple<float, float, float>> f_a;
    f_a.resize(calc_size(fwidth, fheight, margin));
    clear_image(f_a,fwidth,fheight,margin);
    draw_font_A(points,color2,fwidth,fheight,margin);
    draw(points,f_a,color2,fwidth,fheight,margin,linesize);
    points.clear();
    std::vector<std::tuple<float, float, float>> f_r;
    f_r.resize(calc_size(fwidth, fheight, margin));
    clear_image(f_r,fwidth,fheight,margin);
    draw_font_R(points,color2,fwidth,fheight,margin);
    draw(points,f_r,color2,fwidth,fheight,margin,linesize);
    points.clear();
    std::vector<std::tuple<float, float, float>> f_s;
    f_s.resize(calc_size(fwidth, fheight, margin));
    clear_image(f_s,fwidth,fheight,margin);
    draw_font_S(points,color2,fwidth,fheight,margin);
    draw(points,f_s,color2,fwidth,fheight,margin,linesize);
    points.clear();
    std::vector<std::tuple<float, float, float>> f_v;
    f_v.resize(calc_size(fwidth, fheight, margin));
    clear_image(f_v,fwidth,fheight,margin);
    draw_font_V(points,color2,fwidth,fheight,margin);
    draw(points,f_v,color2,fwidth,fheight,margin,linesize);
    points.clear();
    std::vector<std::tuple<float, float, float>> f_e;
    f_e.resize(calc_size(fwidth, fheight, margin));
    clear_image(f_e,fwidth,fheight,margin);
    draw_font_E(points,color2,fwidth,fheight,margin);
    draw(points,f_e,color2,fwidth,fheight,margin,linesize);
    points.clear();
    std::vector<std::tuple<float, float, float>> f_n;
    f_n.resize(calc_size(fwidth, fheight, margin));
    clear_image(f_n,fwidth,fheight,margin);
    draw_font_N(points,color2,fwidth,fheight,margin);
    draw(points,f_n,color2,fwidth,fheight,margin,linesize);
    points.clear();
    std::vector<std::tuple<float, float, float>> f_u;
    f_u.resize(calc_size(fwidth, fheight, margin));
    clear_image(f_u,fwidth,fheight,margin);
    draw_font_U(points,color2,fwidth,fheight,margin);
    draw(points,f_u,color2,fwidth,fheight,margin,linesize);
    points.clear();
    std::vector<std::tuple<float, float, float>> f_c;
    f_c.resize(calc_size(fwidth, fheight, margin));
    clear_image(f_c,fwidth,fheight,margin);
    draw_font_C(points,color2,fwidth,fheight,margin);
    draw(points,f_c,color2,fwidth,fheight,margin,linesize);
    points.clear();
    std::vector<std::tuple<float, float, float>> f_y;
    f_y.resize(calc_size(fwidth, fheight, margin));
    clear_image(f_y,fwidth,fheight,margin);
    draw_font_Y(points,color2,fwidth,fheight,margin);
    draw(points,f_y,color2,fwidth,fheight,margin,linesize);
    points.clear();
    std::vector<std::tuple<float, float, float>> f_p;
    f_p.resize(calc_size(fwidth, fheight, margin));
    clear_image(f_p,fwidth,fheight,margin);
    draw_font_P(points,color2,fwidth,fheight,margin);
    draw(points,f_p,color2,fwidth,fheight,margin,linesize);
    points.clear();
    std::vector<std::tuple<float, float, float>> f_t;
    f_t.resize(calc_size(fwidth, fheight, margin));
    clear_image(f_t,fwidth,fheight,margin);
    draw_font_T(points,color2,fwidth,fheight,margin);
    draw(points,f_t,color2,fwidth,fheight,margin,linesize);
    points.clear();

    image.resize(calc_size(width, height, margin));
    clear_image(image,width,height,margin);

    // 320, 640, 960, 1280
    draw_filled_circle2(320,height*0.4,92,image,color1,width,height);
    draw_filled_circle2(320,height*0.4,78,image,color2,width,height);
    draw_filled_circle2(320,height*0.4,72,image,color1,width,height);
    draw_filled_wedge(320,height*0.4,62,0,360,image,color2,width,height);
    draw_filled_circle2(320,height*0.4,31,image,color1,width,height);
    coords=std::make_tuple(320,436,320,436+38);
    get_line_points(points,coords,color2,width,height);
    draw2(points,image,color2,width,height,3);
    draw_filled_circle2(320,436+38+8,8,image,color2,width,height);
    draw_filled_circle2(320,436+38+8,3,image,color0,width,height);

    draw_filled_circle2(640,height*0.4,92,image,color1,width,height);
    draw_filled_circle2(640,height*0.4,78,image,color2,width,height);
    draw_filled_circle2(640,height*0.4,72,image,color1,width,height);
    draw_filled_wedge(640,height*0.4,62,90,360,image,color2,width,height);
    draw_filled_circle2(640,height*0.4,31,image,color1,width,height);
    coords=std::make_tuple(640,436,640,436+38);
    get_line_points(points,coords,color2,width,height);
    draw2(points,image,color2,width,height,3);
    draw_filled_circle2(640,436+38+8,8,image,color2,width,height);
    draw_filled_circle2(640,436+38+8,3,image,color0,width,height);

    draw_filled_circle2(960,height*0.4,92,image,color1,width,height);
    draw_filled_circle2(960,height*0.4,78,image,color2,width,height);
    draw_filled_circle2(960,height*0.4,72,image,color1,width,height);
    draw_filled_wedge(960,height*0.4,62,180,360,image,color2,width,height);
    draw_filled_circle2(960,height*0.4,31,image,color1,width,height);
    coords=std::make_tuple(960,436,960,436+38);
    get_line_points(points,coords,color2,width,height);
    draw2(points,image,color2,width,height,3);
    draw_filled_circle2(960,436+38+8,8,image,color2,width,height);
    draw_filled_circle2(960,436+38+8,3,image,color0,width,height);

    draw_filled_circle2(1280,height*0.4,92,image,color1,width,height);
    draw_filled_circle2(1280,height*0.4,78,image,color2,width,height);
    draw_filled_circle2(1280,height*0.4,72,image,color1,width,height);
    draw_filled_wedge(1280,height*0.4,62,270,360,image,color2,width,height);
    draw_filled_circle2(1280,height*0.4,31,image,color1,width,height);
    coords=std::make_tuple(1280,436,1280,436+38);
    get_line_points(points,coords,color2,width,height);
    draw2(points,image,color2,width,height,3);
    draw_filled_circle2(1280,436+38+8,8,image,color2,width,height);
    draw_filled_circle2(1280,436+38+8,3,image,color0,width,height);

    // Labels
    stamp(image,f_m,320-(4*label_x),512,(fwidth+margin),(fheight+margin),width);
    stamp(image,f_a,320-(4*label_x)+(1*(fwidth+margin)),512,(fwidth+margin),(fheight+margin),width);
    stamp(image,f_r,320-(4*label_x)+(2*(fwidth+margin)),512,(fwidth+margin),(fheight+margin),width);
    stamp(image,f_s,320-(4*label_x)+(3*(fwidth+margin)),512,(fwidth+margin),(fheight+margin),width);

    stamp(image,f_v,640-(5*label_x),512,(fwidth+margin),(fheight+margin),width);
    stamp(image,f_e,640-(5*label_x)+(1*(fwidth+margin)),512,(fwidth+margin),(fheight+margin),width);
    stamp(image,f_n,640-(5*label_x)+(2*(fwidth+margin)),512,(fwidth+margin),(fheight+margin),width);
    stamp(image,f_u,640-(5*label_x)+(3*(fwidth+margin)),512,(fwidth+margin),(fheight+margin),width);
    stamp(image,f_s,640-(5*label_x)+(4*(fwidth+margin)),512,(fwidth+margin),(fheight+margin),width);

    stamp(image,f_n,960-(7*label_x),512,(fwidth+margin),(fheight+margin),width);
    stamp(image,f_e,960-(7*label_x)+(1*(fwidth+margin)),512,(fwidth+margin),(fheight+margin),width);
    stamp(image,f_p,960-(7*label_x)+(2*(fwidth+margin)),512,(fwidth+margin),(fheight+margin),width);
    stamp(image,f_t,960-(7*label_x)+(3*(fwidth+margin)),512,(fwidth+margin),(fheight+margin),width);
    stamp(image,f_u,960-(7*label_x)+(4*(fwidth+margin)),512,(fwidth+margin),(fheight+margin),width);
    stamp(image,f_n,960-(7*label_x)+(5*(fwidth+margin)),512,(fwidth+margin),(fheight+margin),width);
    stamp(image,f_e,960-(7*label_x)+(6*(fwidth+margin)),512,(fwidth+margin),(fheight+margin),width);

    stamp(image,f_m,1280-(7*label_x),512,(fwidth+margin),(fheight+margin),width);
    stamp(image,f_e,1280-(7*label_x)+(1*(fwidth+margin)),512,(fwidth+margin),(fheight+margin),width);
    stamp(image,f_r,1280-(7*label_x)+(2*(fwidth+margin)),512,(fwidth+margin),(fheight+margin),width);
    stamp(image,f_c,1280-(7*label_x)+(3*(fwidth+margin)),512,(fwidth+margin),(fheight+margin),width);
    stamp(image,f_u,1280-(7*label_x)+(4*(fwidth+margin)),512,(fwidth+margin),(fheight+margin),width);
    stamp(image,f_r,1280-(7*label_x)+(5*(fwidth+margin)),512,(fwidth+margin),(fheight+margin),width);
    stamp(image,f_y,1280-(7*label_x)+(6*(fwidth+margin)),512,(fwidth+margin),(fheight+margin),width);

    std::cout << "saving: 16_draw_donut_chart.ppm." << std::endl;
    save_image(image,width,height,"16_draw_donut_chart.ppm");

    return 0;
}