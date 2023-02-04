// Pre: cp 15_weekchart.ppm 15_read_p6_ppm.ppm
// Compile: clang++ -std=c++17 15_read_p6_ppm.cpp -o 15_read_p6_ppm

#include <iostream>
#include <fstream>
#include <tuple>
#include <vector>
#include <random>
#include <cmath>

void load_image(std::vector<std::tuple<float, float, float>> &image, int &width, int &height, std::string filename)
{
    std::string magic;
    int max;
    uint8_t buffer[3];
    std::tuple<float,float,float> color;

    std::ifstream in(filename, std::ifstream::binary);

    if (!in.is_open())
    {
        std::cout << "Can't open " << filename << std::endl;
        exit(1);
    }

    in >> magic;
    in.seekg(1, in.cur);
    char c;
    in.get(c);
    if (c == '#')
    {
        // We got comments in the PPM image and skip the comments
        while (c != '\n')
        {
            in.get(c);
        }
    }
    else
    {
        in.seekg(-1, in.cur);
    }

    in >> width >> height >> max;

    if (max != 255) {
        std::cout << "Not 8 bit per rgb color." << std::endl;
        exit(1);
    }

    if (magic == "P6")
    {
        // Move curser once to skip '\n'
        in.seekg(1, in.cur);

        for (int i = 0; i < width * height; ++i)
        {
            in.read(reinterpret_cast<char *>(buffer), 3);
            color=std::make_tuple(float(float(buffer[0])/255.0),float(float(buffer[1])/255.0),float(float(buffer[2])/255.0));
            image.push_back(color);
        }
    } else {
        std::cout << "Not a P6 file." << std::endl;
        exit(1);
    }

    in.close();
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
    int width,height;

    std::cout << "loading: 15_read_p6_ppm.ppm" << std::endl;
    load_image(image,width,height,"15_read_p6_ppm.ppm");
    std::cout << "15_read_p6_ppm.ppm - w: " << width << " " << "h: " << height << std::endl;

    std::cout << "saving: 15_read_p6_ppm_.ppm." << std::endl;
    save_image(image,width,height,"15_read_p6_ppm_.ppm");

    return 0;
}