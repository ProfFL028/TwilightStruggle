// Compile: clang++ -std=c++17 09_lines.cpp -o 09_lines

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

std::tuple<float, float, float> h_to_rgb(float h)
{
    float r=0.0f; float g=0.0f; float b=0.0f; float H=0.0f; float s=0.9f; float v=1.0f;
    float f=0.0f; float p=0.0f; float q=0.0f; float t=0.0f;
    int i=0;

    H=h*360;

    if (H == 360)
        H = 0;
    else
        H = H / 60;

    i = (int)std::trunc(H);
    f = H - i;

    p = v * (1.0 - s);
    q = v * (1.0 - (s * f));
    t = v * (1.0 - (s * (1.0 - f)));

    switch (i)
    {
        case 0:
            r = v;
            g = t;
            b = p;
            break;
        case 1:
            r = q;
            g = v;
            b = p;
            break;
        case 2:
            r = p;
            g = v;
            b = t;
            break;
        case 3:
            r = p;
            g = q;
            b = v;
            break;
        case 4:
            r = t;
            g = p;
            b = v;
            break;
        default:
            r = v;
            g = p;
            b = q;
            break;
    }

    return std::make_tuple(r,g,b);
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
    // Draw random lines (with line clipping).
    std::vector<std::tuple<float, float, float>> image;

    std::random_device rd;
    std::mt19937 mt(rd());

    std::uniform_int_distribution<> dist1(-100,740);
    std::uniform_int_distribution<> dist2(-100,460);
    std::uniform_real_distribution<float> dist3(0.0, 1.0);

    std::tuple<float,float,float> color;
    std::tuple<int, int, int, int> coords1;
    std::tuple<int, int, int, int> coords2;

    int width=640;
    int height=360;
    int x1=0,y1=0,x2=0,y2=0;
    float h=0.0f;

    image.resize(calc_size(width, height));
    clear_image(image,width,height);

    for (int i=0;i<15000;++i)
    {
        x1=dist1(mt);
        y1=dist2(mt);
        x2=dist1(mt);
        y2=dist2(mt);
        coords1=std::make_tuple(x1,y1,x2,y2);
        h=dist3(mt);
        color=h_to_rgb(h);
        if (clip_line(coords1,coords2,width,height)) {
            draw_line(image,coords2,color,width,height);
        }
    }

    save_image(image,width,height,"09_random_lines.ppm");

    // Draw damped sine.
    image.clear();
    width=1920;height=640;
    image.resize(calc_size(width, height));
    clear_image(image,width,height);

    double numb_of_samples=1920.0;
    int y=0; int ox=0; int oy=0;

    std::tuple<float,float,float> black=std::make_tuple(0.0,0.0,0.0);
    std::tuple<float,float,float> grey=std::make_tuple(0.5,0.5,0.5);
    std::tuple<float,float,float> red=std::make_tuple(1.0,0.0,0.0);

    coords1=std::make_tuple(0,height/2,width,height/2);
    draw_line(image,coords1,red,width,height);

    for (int x=0;x<width;++x) {
        y=639-(319.0-(339.0*pow(1.0-(1.0/339.0),x))*sin(2*M_PI*x*(15.0/numb_of_samples)-1.0)+0);
        if (x == 0) {ox=x;oy=y;}
        coords1=std::make_tuple(x,y,ox,oy);
        draw_line(image,coords1,black,width,height);
        ox=x;oy=y;
    }

    for (int x=0;x<width;x++) {
        y=319.0-(339.0*pow(1.0-(1.0/339.0),x));
        if (x == 0) {ox=x;oy=y;}
        coords1=std::make_tuple(x,y,ox,oy);
        draw_line(image,coords1,grey,width,height);
        ox=x;oy=y;
    }

    save_image(image,width,height,"09_damped_sine.ppm");

    return 0;
}