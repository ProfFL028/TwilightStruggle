// Compile: clang++ -std=c++17 14_animation12.cpp -o 14_animation12

#include <iostream>
#include <fstream>
#include <tuple>
#include <vector>
#include <random>
#include <cmath>
#include <sstream>
#include <iomanip>
#include <filesystem>
namespace fs = std::filesystem;

bool startsWithCaseInsensitive(std::string mainStr, std::string toMatch)
{
    // Convert mainStr to lower case
    std::transform(mainStr.begin(), mainStr.end(), mainStr.begin(), ::tolower);
    // Convert toMatch to lower case
    std::transform(toMatch.begin(), toMatch.end(), toMatch.begin(), ::tolower);
    if(mainStr.find(toMatch) == 0)
        return true;
    else
        return false;
}

int get_index(int x, int y, int width)
{
    return x+width*y;
}

int calc_size(int width, int height)
{
    return width*height;
}

void clear_image(std::vector<std::tuple<float, float, float>> &image, std::tuple<float,float,float> &color, int width, int height)
{
    for (int y=0;y<height;++y) {
        for (int x=0;x<width;++x) {
            image[get_index(x,y,width)]=color;
        }
    }
}

std::tuple<int,int,int,float,float,float,float> parse_circle_line(const std::string str)
{
    size_t start;
    size_t end = 0;
    std::vector<std::string> out;

    while ((start = str.find_first_not_of(' ', end)) != std::string::npos)
    {
        end = str.find(' ', start);
        out.push_back(str.substr(start, end - start));
    }

    int dx=stoi(out[1]);
    int dy=stoi(out[2]);
    int r=stoi(out[3]);
    float rf=stof(out[4]);
    float gf=stof(out[5]);
    float bf=stof(out[6]);
    float af=stof(out[7]);

    return std::make_tuple(dx,dy,r,rf,gf,bf,af);
}

std::tuple<int,int,float,float,float> parse_bginfo_line(const std::string str, int &width, int &height)
{
    size_t start;
    size_t end = 0;
    std::vector<std::string> out;

    while ((start = str.find_first_not_of(' ', end)) != std::string::npos)
    {
        end = str.find(' ', start);
        out.push_back(str.substr(start, end - start));
    }

    width=stoi(out[1]);
    height=stoi(out[2]);
    float rf=stof(out[3]);
    float gf=stof(out[4]);
    float bf=stof(out[5]);

    return std::make_tuple(width,height,rf,gf,bf);
}

std::tuple<float,float,float> blend_colors(std::tuple<float,float,float> &colorBGRGB, std::tuple<float,float,float,float> &colorRGBA)
{
    float r=0.0f; float g=0.0f; float b=0.0f;
    r = (std::get<0>(colorRGBA) * std::get<3>(colorRGBA)) + (std::get<0>(colorBGRGB) * (1.0 - std::get<3>(colorRGBA)));
    g = (std::get<1>(colorRGBA) * std::get<3>(colorRGBA)) + (std::get<1>(colorBGRGB) * (1.0 - std::get<3>(colorRGBA)));
    b = (std::get<2>(colorRGBA) * std::get<3>(colorRGBA)) + (std::get<2>(colorBGRGB) * (1.0 - std::get<3>(colorRGBA)));

    return std::make_tuple(r,g,b);
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

void draw_filled_circle(int x, int y, int radius, std::vector<std::tuple<float, float, float>> &image, std::tuple<float, float, float, float> &colorRGBA, int width, int height)
{
    int x0 = 0;
    int y0 = radius;
    int d = 3 - 2 * radius;
    std::tuple<int, int, int, int> coords1;
    std::tuple<int, int, int, int> coords2;
    if (!radius) return;

    auto drawline = [&](int sx, int ex, int ny)
    {
        coords1=std::make_tuple(sx,ny,ex,ny);
        if (clip_line(coords1,coords2,width,height)) {
            sx=std::get<0>(coords2);
            ny=std::get<1>(coords2);
            ex=std::get<2>(coords2);
            for (int i = sx; i <= ex; i++) {
                image[get_index(i, ny, width)]=blend_colors(image[get_index(i, ny, width)],colorRGBA);
            }
        }
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

std::string get_filname(int ctr)
{
    std::stringstream ss;
    ss << "anim12/" << std::setfill ('0') << std::setw(3) << ctr << "-swye12.ppm";

    return ss.str();
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
    fs::create_directory("anim12");
    std::ifstream infile("12_squint_with_your_eyes.txt");
    std::string line;
    std::tuple<int,int,int,float,float,float,float> circle;
    std::tuple<int,int,float,float,float> bginfo;
    std::tuple<float,float,float> colorBGRGB;
    std::tuple<float,float,float,float> colorRGBA;
    int width,height,xx,yy,r;
    float rf,gf,bf,af;
    float bg_rf,bg_gf,bg_bf;
    std::vector<std::tuple<float, float, float>> image;
    int ctr=0;
    std::string fn="";
    while (getline(infile, line))
    {
        if (startsWithCaseInsensitive(line,"c")) {
            circle=parse_circle_line(line);
            std::tie(xx,yy,r,rf,gf,bf,af) = circle;
            colorRGBA=std::make_tuple(rf,gf,bf,af);
            draw_filled_circle(xx,yy,r,image,colorRGBA,width,height);
            fn=get_filname(ctr++);
            std::cout << fn << std::endl;
            save_image(image,width,height,fn);
        }
        if (startsWithCaseInsensitive(line,"b")) {
            bginfo=parse_bginfo_line(line,width,height);
            std::tie(width,height,bg_rf,bg_gf,bg_bf) = bginfo;
            image.resize(calc_size(width, height));
            colorBGRGB=std::make_tuple(bg_rf,bg_gf,bg_bf);
            clear_image(image,colorBGRGB,width,height);
            fn=get_filname(ctr++);
            std::cout << fn << std::endl;
            save_image(image,width,height,fn);
        }
    }
    infile.close();

    // ffmpeg -framerate 15 -i %3d-swye12.ppm -c:v libx264 -r 30 swye12.mp4

    return 0;
}