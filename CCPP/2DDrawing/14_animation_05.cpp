// Compile: clang++ -std=c++17 14_animation05.cpp -o 14_animation05

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

void clear_image(std::vector<std::tuple<float, float, float>> &image, std::tuple<float, float, float> &color, int width, int height)
{
    for (int y=0;y<height;++y) {
        for (int x=0;x<width;++x) {
            image[get_index(x,y,width)]=color;
        }
    }
}

std::string get_filname(int ctr)
{
    std::stringstream ss;
    ss << "anim05/" << std::setfill ('0') << std::setw(4) << ctr << "-swye05.ppm";

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

std::tuple<int,int> get_width_and_height(const std::string str)
{
    size_t start;
    size_t end = 0;
    std::vector<std::string> out;

    while ((start = str.find_first_not_of(' ', end)) != std::string::npos)
    {
        end = str.find(' ', start);
        out.push_back(str.substr(start, end - start));
    }

    int w=stoi(out[0]);
    int h=stoi(out[1]);

    return std::make_tuple(w,h);
}

std::tuple<int,int,int> get_color(const std::string str)
{
    size_t start;
    size_t end = 0;
    std::vector<std::string> out;

    while ((start = str.find_first_not_of(' ', end)) != std::string::npos)
    {
        end = str.find(' ', start);
        out.push_back(str.substr(start, end - start));
    }

    int r=stoi(out[0]);
    int g=stoi(out[1]);
    int b=stoi(out[2]);

    return std::make_tuple(r,g,b);
}

void read_image(std::vector<std::tuple<float, float, float>> &image, int &width, int &height, std::string filename)
{
    std::ifstream infile(filename);
    std::tuple<int, int, int> rcolor;
    std::tuple<float, float, float> wcolor;
    std::tuple<int,int> widthnheight;
    std::string line;
    int state=0;
    bool done = false;

    while (getline(infile, line))
    {
        if (startsWithCaseInsensitive(line,"P3") && state == 0) {
            state=1;
        }

        if (!startsWithCaseInsensitive(line,"#") && !startsWithCaseInsensitive(line,"P3") && state == 1) {
            widthnheight=get_width_and_height(line);
            width=std::get<0>(widthnheight);
            height=std::get<1>(widthnheight);
            state=2;
        }

        if (startsWithCaseInsensitive(line,"255") && state == 2) {
            state=3;
        }

        if (!(line.compare("255") == 0) && state == 3) {
            rcolor=get_color(line);
            wcolor=std::make_tuple(float(std::get<0>(rcolor)/255.0f), float(std::get<1>(rcolor)/255.0f), float(std::get<2>(rcolor)/255.0f));
            image.push_back(wcolor);
            done = true;
        }
    }
    infile.close();
}

void update_x_and_y(int r, std::tuple<int,int> &walk1, std::tuple<int,int> &walk2, int width, int height)
{
    int x1,y1,x2,y2;
    std::tie(x1,y1) = walk1;
    std::tie(x2,y2) = walk2;

    switch(r) {
        case 0:
            x1+=1;
            x2-=1;
            break;
        case 1:
            x1-=1;
            x2+=1;
            break;
        case 2:
            y1+=1;
            y2-=1;
            break;
        case 3:
            y1-=1;
            y2+=1;
            break;
    }

    if (x1 < 0) {
        x1 = 0;
    } else if (x1 > width-1) {
        x1=width-1;
    }

    if (x2 < 0) {
        x2 = 0;
    } else if (x2 > width-1) {
        x2=width-1;
    }

    if (y1 < 0) {
        y1 = 0;
    } else if (y1 > height-1) {
        y1 = height-1;
    }

    if (y2 < 0) {
        y2 = 0;
    } else if (y2 > height-1) {
        y2 = height-1;
    }

    walk1=std::make_tuple(x1,y1);
    walk2=std::make_tuple(x2,y2);
}

void blended_two_images(std::vector<std::tuple<float, float, float>> &blend1,std::vector<std::tuple<float, float, float>> &blend2,int width,int height,float alpha)
{
    std::tuple<float, float, float> color1=std::make_tuple(0.0f,0.0f,0.0f);
    std::tuple<float, float, float> color2=std::make_tuple(0.0f,0.0f,0.0f);
    float r=0.0f; float g=0.0f; float b=0.0f;

    for (int y=0;y<height;++y) {
        for (int x=0;x<width;++x) {
            color1=blend1[get_index(x,y,width)];
            color2=blend2[get_index(x,y,width)];
            r = (std::get<0>(color2) * alpha) + (std::get<0>(color1) * (1.0f - alpha));
            g = (std::get<1>(color2) * alpha) + (std::get<1>(color1) * (1.0f - alpha));
            b = (std::get<2>(color2) * alpha) + (std::get<2>(color1) * (1.0f - alpha));
            blend1[get_index(x,y,width)]=std::make_tuple(r, g, b);
        }
    }
}

void walker(std::vector<std::tuple<float, float, float>> &image1, std::vector<std::tuple<float, float, float>> &image2, int width, int height)
{
    // Randomize and draw walkers
    std::tuple<float, float, float> color;
    int x1=width/2;
    int y1=height/2;
    int x2=width/2;
    int y2=height/2;

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<> dist(0, 3);

    std::tuple<int,int> walk1=std::make_tuple(x1,y1);
    std::tuple<int,int> walk2=std::make_tuple(x2,y2);

    int ctr=0;
    std::string fn="";
    fn=get_filname(ctr++);
    std::cout << fn << std::endl;
    save_image(image2,width,height,fn);

    int r=0;
    for (int i=0;i<100000;++i) {
        r=dist(mt);
        update_x_and_y(r,walk1,walk2,width,height);
        color=image1[get_index(std::get<0>(walk1), std::get<1>(walk1), width)];
        image2[get_index(std::get<0>(walk1), std::get<1>(walk1), width)]=color;
        color=image1[get_index(std::get<0>(walk2), std::get<1>(walk2), width)];
        image2[get_index(std::get<0>(walk2), std::get<1>(walk2), width)]=color;
        if (i%100 == 0) {
            fn=get_filname(ctr++);
            std::cout << fn << std::endl;
            save_image(image2,width,height,fn);
        }
    }
}

int main()
{
    fs::create_directory("anim05");
    std::vector<std::tuple<float, float, float>> image1;
    std::vector<std::tuple<float, float, float>> image2;
    std::tuple<float, float, float> color=std::make_tuple(0.0f,0.0f,0.06666666667f);
    int width=0;
    int height=0;

    read_image(image1, width, height, "04_helloworld.ppm");

    image2.resize(calc_size(width, height));
    clear_image(image2,color,width,height);
    blended_two_images(image2,image1,width,height,0.2);
    // Random Walker
    walker(image1,image2,width,height);

    // ffmpeg -framerate 15 -i %4d-swye05.ppm -c:v libx264 -r 30 swye05.mp4

    return 0;
}