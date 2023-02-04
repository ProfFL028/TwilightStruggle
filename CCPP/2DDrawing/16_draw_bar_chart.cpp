// Compile: clang++ -std=c++17 16_draw_bar_chart.cpp -o 16_draw_bar_chart

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

int calc_size(int width, int height, int margin)
{
    return (width+margin)*(height+margin);
}

void clear_image(std::vector<std::tuple<float, float, float>> &image, int width, int height, int margin)
{
    for (int y=0;y<(height+margin);++y) {
        for (int x=0;x<(width+margin);++x) {
            image[get_index(x,y,(width+margin))]=std::make_tuple(0.262745098f, 0.262745098f, 0.262745098f);
        }
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

int main()
{
    std::vector<std::tuple<float, float, float>> image;
    std::tuple<int, int, int, int> coords;
    std::tuple<float,float,float> color=std::make_tuple(1.0f,0.7647058824f,0.6235294118f);
    int width=1600,height=900;
    int margin=0;
    int linesize=3;

    image.resize(calc_size(width, height, margin));
    clear_image(image,width,height,margin);

    draw_filled_rect(560,268,74,420,image,color,width,height);
    draw_filled_rect(695,442,74,246,image,color,width,height);
    draw_filled_rect(831,571,74,117,image,color,width,height);
    draw_filled_rect(966,306,74,381,image,color,width,height);
    draw_filled_rect(463,687,674,4,image,color,width,height);

    // icon 1
    draw_filled_rect(577,714,3,39,image,color,width,height);
    draw_filled_rect(571,753,35,3,image,color,width,height);
    draw_filled_rect(571,756,3,14,image,color,width,height);
    draw_filled_rect(574,767,32,3,image,color,width,height);
    draw_filled_rect(603,756,3,11,image,color,width,height);
    draw_filled_rect(577,770,3,7,image,color,width,height);
    draw_filled_rect(580,774,43,3,image,color,width,height);
    draw_filled_rect(620,724,3,53,image,color,width,height);
    draw_filled_rect(580,714,33,3,image,color,width,height);
    draw_filled_rect(610,717,3,10,image,color,width,height);
    draw_filled_rect(613,724,8,3,image,color,width,height);
    draw_filled_rect(611,715,3,3,image,color,width,height);
    draw_filled_rect(612,716,3,3,image,color,width,height);
    draw_filled_rect(613,717,3,3,image,color,width,height);
    draw_filled_rect(614,718,3,3,image,color,width,height);
    draw_filled_rect(615,719,3,3,image,color,width,height);
    draw_filled_rect(616,720,3,3,image,color,width,height);
    draw_filled_rect(617,721,3,3,image,color,width,height);
    draw_filled_rect(618,722,3,3,image,color,width,height);
    draw_filled_rect(619,723,3,3,image,color,width,height);

    // icon 2
    draw_filled_rect(577+(1*136),714,3,39,image,color,width,height);
    draw_filled_rect(571+(1*136),753,35,3,image,color,width,height);
    draw_filled_rect(571+(1*136),756,3,14,image,color,width,height);
    draw_filled_rect(574+(1*136),767,32,3,image,color,width,height);
    draw_filled_rect(603+(1*136),756,3,11,image,color,width,height);
    draw_filled_rect(577+(1*136),770,3,7,image,color,width,height);
    draw_filled_rect(580+(1*136),774,43,3,image,color,width,height);
    draw_filled_rect(620+(1*136),724,3,53,image,color,width,height);
    draw_filled_rect(580+(1*136),714,33,3,image,color,width,height);
    draw_filled_rect(610+(1*136),717,3,10,image,color,width,height);
    draw_filled_rect(613+(1*136),724,8,3,image,color,width,height);
    draw_filled_rect(611+(1*136),715,3,3,image,color,width,height);
    draw_filled_rect(612+(1*136),716,3,3,image,color,width,height);
    draw_filled_rect(613+(1*136),717,3,3,image,color,width,height);
    draw_filled_rect(614+(1*136),718,3,3,image,color,width,height);
    draw_filled_rect(615+(1*136),719,3,3,image,color,width,height);
    draw_filled_rect(616+(1*136),720,3,3,image,color,width,height);
    draw_filled_rect(617+(1*136),721,3,3,image,color,width,height);
    draw_filled_rect(618+(1*136),722,3,3,image,color,width,height);
    draw_filled_rect(619+(1*136),723,3,3,image,color,width,height);

    // icon 3
    draw_filled_rect(577+(2*136),714,3,39,image,color,width,height);
    draw_filled_rect(571+(2*136),753,35,3,image,color,width,height);
    draw_filled_rect(571+(2*136),756,3,14,image,color,width,height);
    draw_filled_rect(574+(2*136),767,32,3,image,color,width,height);
    draw_filled_rect(603+(2*136),756,3,11,image,color,width,height);
    draw_filled_rect(577+(2*136),770,3,7,image,color,width,height);
    draw_filled_rect(580+(2*136),774,43,3,image,color,width,height);
    draw_filled_rect(620+(2*136),724,3,53,image,color,width,height);
    draw_filled_rect(580+(2*136),714,33,3,image,color,width,height);
    draw_filled_rect(610+(2*136),717,3,10,image,color,width,height);
    draw_filled_rect(613+(2*136),724,8,3,image,color,width,height);
    draw_filled_rect(611+(2*136),715,3,3,image,color,width,height);
    draw_filled_rect(612+(2*136),716,3,3,image,color,width,height);
    draw_filled_rect(613+(2*136),717,3,3,image,color,width,height);
    draw_filled_rect(614+(2*136),718,3,3,image,color,width,height);
    draw_filled_rect(615+(2*136),719,3,3,image,color,width,height);
    draw_filled_rect(616+(2*136),720,3,3,image,color,width,height);
    draw_filled_rect(617+(2*136),721,3,3,image,color,width,height);
    draw_filled_rect(618+(2*136),722,3,3,image,color,width,height);
    draw_filled_rect(619+(2*136),723,3,3,image,color,width,height);

    // icon 4
    draw_filled_rect(577+(3*136),714,3,39,image,color,width,height);
    draw_filled_rect(571+(3*136),753,35,3,image,color,width,height);
    draw_filled_rect(571+(3*136),756,3,14,image,color,width,height);
    draw_filled_rect(574+(3*136),767,32,3,image,color,width,height);
    draw_filled_rect(603+(3*136),756,3,11,image,color,width,height);
    draw_filled_rect(577+(3*136),770,3,7,image,color,width,height);
    draw_filled_rect(580+(3*136),774,43,3,image,color,width,height);
    draw_filled_rect(620+(3*136),724,3,53,image,color,width,height);
    draw_filled_rect(580+(3*136),714,33,3,image,color,width,height);
    draw_filled_rect(610+(3*136),717,3,10,image,color,width,height);
    draw_filled_rect(613+(3*136),724,8,3,image,color,width,height);
    draw_filled_rect(611+(3*136),715,3,3,image,color,width,height);
    draw_filled_rect(612+(3*136),716,3,3,image,color,width,height);
    draw_filled_rect(613+(3*136),717,3,3,image,color,width,height);
    draw_filled_rect(614+(3*136),718,3,3,image,color,width,height);
    draw_filled_rect(615+(3*136),719,3,3,image,color,width,height);
    draw_filled_rect(616+(3*136),720,3,3,image,color,width,height);
    draw_filled_rect(617+(3*136),721,3,3,image,color,width,height);
    draw_filled_rect(618+(3*136),722,3,3,image,color,width,height);
    draw_filled_rect(619+(3*136),723,3,3,image,color,width,height);

    // 35%
    coords=std::make_tuple(579,234,586,234);
    draw_line(image,coords,color,width,height);
    coords=std::make_tuple(586,252,586,234);
    draw_line(image,coords,color,width,height);
    coords=std::make_tuple(586,252,579,252);
    draw_line(image,coords,color,width,height);
    coords=std::make_tuple(586,242,580,242);
    draw_line(image,coords,color,width,height);
    coords=std::make_tuple(591,234,598,234);
    draw_line(image,coords,color,width,height);
    coords=std::make_tuple(591,242,598,242);
    draw_line(image,coords,color,width,height);
    coords=std::make_tuple(591,242,598,242);
    draw_line(image,coords,color,width,height);
    coords=std::make_tuple(591,252,598,252);
    draw_line(image,coords,color,width,height);
    coords=std::make_tuple(591,234,591,242);
    draw_line(image,coords,color,width,height);
    coords=std::make_tuple(598,242,598,252);
    draw_line(image,coords,color,width,height);
    coords=std::make_tuple(602,251,617,233);
    draw_line(image,coords,color,width,height);
    coords=std::make_tuple(602,234,608,234);
    draw_line(image,coords,color,width,height);
    coords=std::make_tuple(602,234,602,239);
    draw_line(image,coords,color,width,height);
    coords=std::make_tuple(602,239,608,239);
    draw_line(image,coords,color,width,height);
    coords=std::make_tuple(608,239,608,234);
    draw_line(image,coords,color,width,height);
    coords=std::make_tuple(611,246,616,246);
    draw_line(image,coords,color,width,height);
    coords=std::make_tuple(611,251,616,251);
    draw_line(image,coords,color,width,height);
    coords=std::make_tuple(611,251,611,246);
    draw_line(image,coords,color,width,height);
    coords=std::make_tuple(616,251,616,246);
    draw_line(image,coords,color,width,height);

    // 23%
    coords=std::make_tuple(715,409,722,409);
    draw_line(image,coords,color,width,height);
    coords=std::make_tuple(715,426,722,426);
    draw_line(image,coords,color,width,height);
    coords=std::make_tuple(722,409,722,417);
    draw_line(image,coords,color,width,height);
    coords=std::make_tuple(722,417,715,426);
    draw_line(image,coords,color,width,height);
    coords=std::make_tuple(726,409,733,409);
    draw_line(image,coords,color,width,height);
    coords=std::make_tuple(726,417,733,417);
    draw_line(image,coords,color,width,height);
    coords=std::make_tuple(726,426,733,426);
    draw_line(image,coords,color,width,height);
    coords=std::make_tuple(733,426,733,409);
    draw_line(image,coords,color,width,height);
    coords=std::make_tuple(737,409,737,414);
    draw_line(image,coords,color,width,height);
    coords=std::make_tuple(737,414,743,414);
    draw_line(image,coords,color,width,height);
    coords=std::make_tuple(743,414,743,409);
    draw_line(image,coords,color,width,height);
    coords=std::make_tuple(743,409,737,409);
    draw_line(image,coords,color,width,height);
    coords=std::make_tuple(746,421,746,426);
    draw_line(image,coords,color,width,height);
    coords=std::make_tuple(746,426,751,426);
    draw_line(image,coords,color,width,height);
    coords=std::make_tuple(751,426,751,421);
    draw_line(image,coords,color,width,height);
    coords=std::make_tuple(751,421,746,421);
    draw_line(image,coords,color,width,height);
    coords=std::make_tuple(737,426,751,409);
    draw_line(image,coords,color,width,height);

    // 10%
    coords=std::make_tuple(853,537,853,555);
    draw_line(image,coords,color,width,height);
    coords=std::make_tuple(857,537,857,555);
    draw_line(image,coords,color,width,height);
    coords=std::make_tuple(857,555,867,555);
    draw_line(image,coords,color,width,height);
    coords=std::make_tuple(867,555,867,537);
    draw_line(image,coords,color,width,height);
    coords=std::make_tuple(867,537,857,537);
    draw_line(image,coords,color,width,height);
    coords=std::make_tuple(871,555,886,537);
    draw_line(image,coords,color,width,height);
    coords=std::make_tuple(871,537,871,543);
    draw_line(image,coords,color,width,height);
    coords=std::make_tuple(871,543,877,543);
    draw_line(image,coords,color,width,height);
    coords=std::make_tuple(877,543,877,537);
    draw_line(image,coords,color,width,height);
    coords=std::make_tuple(877,537,871,537);
    draw_line(image,coords,color,width,height);
    coords=std::make_tuple(880,549,880,555);
    draw_line(image,coords,color,width,height);
    coords=std::make_tuple(880,555,885,555);
    draw_line(image,coords,color,width,height);
    coords=std::make_tuple(885,555,885,549);
    draw_line(image,coords,color,width,height);
    coords=std::make_tuple(885,549,880,549);
    draw_line(image,coords,color,width,height);

    // 32%
    coords=std::make_tuple(993,272,986,272);
    draw_line(image,coords,color,width,height);
    coords=std::make_tuple(993,280,986,280);
    draw_line(image,coords,color,width,height);
    coords=std::make_tuple(993,291,986,291);
    draw_line(image,coords,color,width,height);
    coords=std::make_tuple(993,291,993,272);
    draw_line(image,coords,color,width,height);
    coords=std::make_tuple(997,272,1005,272);
    draw_line(image,coords,color,width,height);
    coords=std::make_tuple(1005,272,1005,280);
    draw_line(image,coords,color,width,height);
    coords=std::make_tuple(1005,280,997,291);
    draw_line(image,coords,color,width,height);
    coords=std::make_tuple(997,291,1005,291);
    draw_line(image,coords,color,width,height);
    coords=std::make_tuple(1007,291,1023,272);
    draw_line(image,coords,color,width,height);
    coords=std::make_tuple(1008,272,1008,277);
    draw_line(image,coords,color,width,height);
    coords=std::make_tuple(1008,272,1008,277);
    draw_line(image,coords,color,width,height);
    coords=std::make_tuple(1008,277,1013,277);
    draw_line(image,coords,color,width,height);
    coords=std::make_tuple(1013,277,1013,272);
    draw_line(image,coords,color,width,height);
    coords=std::make_tuple(1013,272,1008,272);
    draw_line(image,coords,color,width,height);
    coords=std::make_tuple(1016,284,1016,289);
    draw_line(image,coords,color,width,height);
    coords=std::make_tuple(1016,289,1022,289);
    draw_line(image,coords,color,width,height);
    coords=std::make_tuple(1022,289,1022,284);
    draw_line(image,coords,color,width,height);
    coords=std::make_tuple(1022,284,1016,284);
    draw_line(image,coords,color,width,height);

    std::cout << "saving: 16_draw_bar_chart.ppm." << std::endl;
    save_image(image,width,height,"16_draw_bar_chart.ppm");

    return 0;
}