// Compile: clang++ -std=c++17 14_animation11.cpp -o 14_animation11

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

void clear_image(std::vector<std::tuple<float, float, float>> &image, std::tuple<float,float,float> &colorRGB, int width, int height)
{
    for (int y=0;y<height;++y) {
        for (int x=0;x<width;++x) {
            image[get_index(x,y,width)]=colorRGB;
        }
    }
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

std::tuple<int,int,int,int,float,float,float,float> parse_rect_line(const std::string str)
{
    size_t start;
    size_t end = 0;
    std::vector<std::string> out;

    while ((start = str.find_first_not_of(' ', end)) != std::string::npos)
    {
        end = str.find(' ', start);
        out.push_back(str.substr(start, end - start));
    }

    int x1=stoi(out[1]);
    int y1=stoi(out[2]);
    int x2=stoi(out[3]);
    int y2=stoi(out[4]);
    float rf=stof(out[5]);
    float gf=stof(out[6]);
    float bf=stof(out[7]);
    float af=stof(out[8]);

    return std::make_tuple(x1,y1,x2,y2,rf,gf,bf,af);
}

std::tuple<float,float,float> blend_colors(std::tuple<float,float,float> &colorBGRGB, std::tuple<float,float,float,float> &colorRGBA)
{
    float r=0.0f; float g=0.0f; float b=0.0f;
    r = (std::get<0>(colorRGBA) * std::get<3>(colorRGBA)) + (std::get<0>(colorBGRGB) * (1.0 - std::get<3>(colorRGBA)));
    g = (std::get<1>(colorRGBA) * std::get<3>(colorRGBA)) + (std::get<1>(colorBGRGB) * (1.0 - std::get<3>(colorRGBA)));
    b = (std::get<2>(colorRGBA) * std::get<3>(colorRGBA)) + (std::get<2>(colorBGRGB) * (1.0 - std::get<3>(colorRGBA)));

    return std::make_tuple(r,g,b);
}

void draw_filled_rect(int x1,int y1,int x2,int y2, std::vector<std::tuple<float, float, float>> &image, std::tuple<float,float,float,float> &colorRGBA, int width, int height)
{
    for (int i = y1; i < y2; i++) {
        for (int j = x1; j < x2; j++) {
            image[get_index(j,i,width)]=blend_colors(image[get_index(j,i,width)],colorRGBA);
        }
    }
}

std::string get_filname(int ctr)
{
    std::stringstream ss;
    ss << "anim11/" << std::setfill ('0') << std::setw(3) << ctr << "-swye11.ppm";

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
    fs::create_directory("anim11");
    std::ifstream infile("11_squint_with_your_eyes.txt");
    std::string line;
    std::tuple<int,int,int,int,float,float,float,float> rect;
    std::tuple<int,int,float,float,float> bginfo;
    std::tuple<float,float,float> colorBGRGB;
    std::tuple<float,float,float,float> colorRGBA;
    int width,height,x1,y1,x2,y2;
    float rf,gf,bf,af;
    float bg_rf,bg_gf,bg_bf;
    std::vector<std::tuple<float, float, float>> image;
    int ctr=0;
    std::string fn="";
    while (getline(infile, line))
    {
        if (startsWithCaseInsensitive(line,"r")) {
            rect=parse_rect_line(line);
            std::tie(x1,y1,x2,y2,rf,gf,bf,af) = rect;
            colorRGBA=std::make_tuple(rf,gf,bf,af);
            draw_filled_rect(x1,y1,x2,y2,image,colorRGBA,width,height);
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

    // ffmpeg -framerate 15 -i %3d-swye11.ppm -c:v libx264 -r 30 swye11.mp4

    return 0;
}