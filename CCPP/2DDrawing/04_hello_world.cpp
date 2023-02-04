// Compile: clang++ -std=c++17 04_helloworld.cpp -o 04_helloworld

#include <iostream>
#include <fstream>
#include <tuple>
#include <vector>

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

void first_draw(std::vector<std::tuple<float, float, float>> &image, int width, int height)
{
    std::tuple<float, float, float> color;
    int ctr=0;
    for (int y=height-1;y>=0;--y)
    {
        for (int x=0;x<width;++x) {
            float r = float(x) / float(width);
            float g = float(y) / float(height);
            float b = 0.2;
            color=std::make_tuple(r, g, b);
            image[ctr]=color;
            ctr++;
        }
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
    std::vector<std::tuple<float, float, float>> image;
    std::tuple<float, float, float> color=std::make_tuple(0.0f,0.0f,0.06666666667f);
    int width=640;
    int height=360;

    image.resize(calc_size(width, height));
    std::cout << "Created a vector with the size: " << calc_size(width, height) << std::endl;
    clear_image(image,color,width,height);
    std::cout << "Cleared image with dark blue color." << std::endl;
    first_draw(image,width,height);
    std::cout << "Drawing the first image pixel by pixel" << std::endl;
    save_image(image,width,height,"04_helloworld.ppm");
    std::cout << "Saved: 04_helloworld.ppm" << std::endl;

    // Create square (for 08; blending colors).
    std::vector<std::tuple<float, float, float>> square;
    width=256;height=256;
    square.resize(calc_size(width, height));
    first_draw(square,width,height);
    save_image(square,width,height,"04_helloworld_square.ppm");

    return 0;
}