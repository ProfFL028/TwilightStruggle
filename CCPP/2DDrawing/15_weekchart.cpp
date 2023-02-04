// Compile: clang++ -std=c++17 15_radarchart.cpp -o 15_radarchart

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

void floodfill_algorithm(int x, int y, std::vector<std::tuple<float, float, float>> &image, std::tuple<float, float, float> &ocolor, std::tuple<float, float, float> &ncolor, int &width, int &height)
{
    if ((x > 0) && (x < width) && (y > 0) && (y < height)) {
        if (image[get_index(x,y,width)] == ocolor)
        {
            image[get_index(x,y,width)]=ncolor;
            floodfill_algorithm(x+1,y,image,ocolor,ncolor,width,height);
            floodfill_algorithm(x-1,y,image,ocolor,ncolor,width,height);
            floodfill_algorithm(x,y+1,image,ocolor,ncolor,width,height);
            floodfill_algorithm(x,y-1,image,ocolor,ncolor,width,height);
        }
        else return;
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

void draw_polygon(std::vector<std::tuple<int, int, int, int>> &polygon,std::vector<std::tuple<float, float, float>> &image,std::tuple<float, float, float> &color, int width, int height)
{
    std::vector<std::tuple<int,int>> coords;

    for (auto& po : polygon) {
        draw_line_coords(std::get<0>(po),std::get<1>(po),std::get<2>(po),std::get<3>(po),coords);
    }

    for (auto & e : coords) {
        image[get_index(std::get<0>(e),std::get<1>(e),width)]=color;
    }
}

void draw_filled_polygon(std::vector<std::tuple<int, int, int, int>> &polygon,std::vector<std::tuple<float, float, float>> &image,std::tuple<float, float, float> &color, int width, int height)
{
    std::vector<std::tuple<int,int>> coords;

    for (auto& po : polygon) {
        draw_line_coords(std::get<0>(po),std::get<1>(po),std::get<2>(po),std::get<3>(po),coords);
    }

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

int find_region(int x, int y, int width, int height)
{
    int code=0;
    if(y >= height)
        code |= 1; //top
    else if(y < 0)
        code |= 2; //bottom
    if(x >= width)
        code |= 4; //right
    else if (x < 0)
        code |= 8; //left
    return(code);
}

bool clip_line(std::tuple<int, int, int, int> &coords1, std::tuple<int, int, int, int> &coords2, int width, int height)
{
    int x1=std::get<0>(coords1); int y1=std::get<1>(coords1); int x2=std::get<2>(coords1); int y2=std::get<3>(coords1);
    int x3=0; int y3=0; int x4=0; int y4=0;
    int code1=0, code2=0, codeout=0;
    bool accept = 0, done=0;
    code1 = find_region(x1, y1, width, height); //the region outcodes for the endpoints
    code2 = find_region(x2, y2, width, height);
    do //In theory, this can never end up in an infinite loop, it'll always come in one of the trivial cases eventually
    {
        if(!(code1 | code2)) accept = done = 1;  //accept because both endpoints are in screen or on the border, trivial accept
        else if(code1 & code2) done = 1; //the line isn't visible on screen, trivial reject
        else  //if no trivial reject or accept, continue the loop
        {
            int x, y;
            codeout = code1 ? code1 : code2;
            if(codeout & 1) //top
            {
                x = x1 + (x2 - x1) * (height - y1) / (y2 - y1);
                y = height - 1;
            }
            else if(codeout & 2) //bottom
            {
                x = x1 + (x2 - x1) * -y1 / (y2 - y1);
                y = 0;
            }
            else if(codeout & 4) //right
            {
                y = y1 + (y2 - y1) * (width - x1) / (x2 - x1);
                x = width - 1;
            }
            else //left
            {
                y = y1 + (y2 - y1) * -x1 / (x2 - x1);
                x = 0;
            }
            if(codeout == code1) //first endpoint was clipped
            {
                x1 = x; y1 = y;
                code1 = find_region(x1, y1, width, height);
            }
            else //second endpoint was clipped
            {
                x2 = x; y2 = y;
                code2 = find_region(x2, y2, width, height);
            }
        }
    }
    while(done == 0);
    if(accept)
    {
        x3 = x1;
        x4 = x2;
        y3 = y1;
        y4 = y2;
        coords2=std::make_tuple(x3,y3,x4,y4);
        return 1;
    }
    else
    {
        x3 = x4 = y3 = y4 = 0;
        coords2=std::make_tuple(x3,y3,x4,y4);
        return 0;
    }
}

void get_angle_line(std::tuple<int, int, int, int> &coords,int x_cen,int y_cen,double degrees,int length)
{
    double angle = degrees * (M_PI / 180);
    coords=std::make_tuple(x_cen,y_cen,int(double(x_cen) + cos(angle)*double(length)),int(double(y_cen) + sin(angle)*double(length)));
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
    // Draw random lines (with line clipping).
    std::vector<std::tuple<float, float, float>> image;


    std::tuple<float,float,float> color=std::make_tuple(0.8470588235,0.8509803922,0.9137254902);
    std::tuple<int, int, int, int> coord;
    std::vector<std::tuple<int, int, int, int>> polygon;

    int width=1920;
    int height=1080;

    image.resize(calc_size(width, height));
    clear_image(image,width,height);

    int x_cen=width/2;
    int y_cen=height/2;
    int length=y_cen*0.8;
    double degrees=0.0;

    coord=std::make_tuple(1248,540,1113,693);
    polygon.push_back(coord);
    coord=std::make_tuple(1113,693,960,756);
    polygon.push_back(coord);
    coord=std::make_tuple(960,756,858,642);
    polygon.push_back(coord);
    coord=std::make_tuple(858,642,888,540);
    polygon.push_back(coord);
    coord=std::make_tuple(888,540,807,388);
    polygon.push_back(coord);
    coord=std::make_tuple(807,388,959,252);
    polygon.push_back(coord);
    coord=std::make_tuple(959,252,1214,285);
    polygon.push_back(coord);
    coord=std::make_tuple(1214,285,1248,540);
    polygon.push_back(coord);

    draw_filled_polygon(polygon,image,color,width,height);
    color=std::make_tuple(1.0,0.0,1.0);
    draw_polygon(polygon,image,color,width,height);

    //

    color=std::make_tuple(0.0,0.0,0.0);
    get_angle_line(coord,x_cen,y_cen,degrees,length);
    if (clip_line(coord,coord,width,height)) {
        draw_line(image,coord,color,width,height);
    }
    degrees=45.0;
    get_angle_line(coord,x_cen,y_cen,degrees,length);
    if (clip_line(coord,coord,width,height)) {
        draw_line(image,coord,color,width,height);
    }
    degrees=90.0;
    get_angle_line(coord,x_cen,y_cen,degrees,length);
    if (clip_line(coord,coord,width,height)) {
        draw_line(image,coord,color,width,height);
    }
    degrees=135.0;
    get_angle_line(coord,x_cen,y_cen,degrees,length);
    if (clip_line(coord,coord,width,height)) {
        draw_line(image,coord,color,width,height);
    }
    degrees=180.0;
    get_angle_line(coord,x_cen,y_cen,degrees,length);
    if (clip_line(coord,coord,width,height)) {
        draw_line(image,coord,color,width,height);
    }
    degrees=225.0;
    get_angle_line(coord,x_cen,y_cen,degrees,length);
    if (clip_line(coord,coord,width,height)) {
        draw_line(image,coord,color,width,height);
    }
    degrees=270.0;
    get_angle_line(coord,x_cen,y_cen,degrees,length);
    if (clip_line(coord,coord,width,height)) {
        draw_line(image,coord,color,width,height);
    }
    degrees=315.0;
    get_angle_line(coord,x_cen,y_cen,degrees,length);
    if (clip_line(coord,coord,width,height)) {
        draw_line(image,coord,color,width,height);
    }

    // 432;72
    draw_circle((width/2),(height/2),72,image,color,width,height);
    draw_circle((width/2),(height/2),72*2,image,color,width,height);
    draw_circle((width/2),(height/2),72*3,image,color,width,height);
    draw_circle((width/2),(height/2),72*4,image,color,width,height);
    draw_circle((width/2),(height/2),72*5,image,color,width,height);
    draw_circle((width/2),(height/2),72*6,image,color,width,height);

    color=std::make_tuple(1.0,1.0,1.0);
    draw_filled_circle(x_cen,y_cen,71,image,color,width,height);

    //
    std::tuple<float,float,float> ncolor=std::make_tuple(0.8470588235,0.8509803922,0.9137254902);
    floodfill_algorithm(x_cen,y_cen,image,color,ncolor,width,height);

    save_image(image,width,height,"15_radarchart.ppm");

    return 0;
}