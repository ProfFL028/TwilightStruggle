// Compile: clang++ -std=c++17 06_xor_and_or_texture.cpp -o 06_xor_and_or_texture

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

void draw_xor(std::vector<std::tuple<float, float, float>> &image, int width, int height)
{
    std::tuple<float, float, float> color;
    int c=0;

    for (int y=0;y<height;++y)
    {
        for (int x=0;x<width;++x) {
            c = x ^ y;// XOR
            color=std::make_tuple(float(c/255.0f), float(c/255.0f), float(c/255.0f));
            image[get_index(x, y, width)]=color;
        }
    }
}

void draw_and(std::vector<std::tuple<float, float, float>> &image, int width, int height)
{
    std::tuple<float, float, float> color;
    int c=0;

    for (int y=0;y<height;++y)
    {
        for (int x=0;x<width;++x) {
            c = x & y;// AND
            color=std::make_tuple(float(c/255.0f), float(c/255.0f), float(c/255.0f));
            image[get_index(x, y, width)]=color;
        }
    }
}

void draw_or(std::vector<std::tuple<float, float, float>> &image, int width, int height)
{
    std::tuple<float, float, float> color;
    int c=0;

    for (int y=0;y<height;++y)
    {
        for (int x=0;x<width;++x) {
            c = x | y;// OR
            color=std::make_tuple(float(c/255.0f), float(c/255.0f), float(c/255.0f));
            image[get_index(x, y, width)]=color;
        }
    }
}

int main()
{
    std::vector<std::tuple<float, float, float>> image;
    std::tuple<float, float, float> color=std::make_tuple(0.0f,0.0f,0.06666666667f);
    int width=256;
    int height=256;

    image.resize(calc_size(width, height));
    std::cout << "Created a vector with the size: " << calc_size(width, height) << std::endl;
    clear_image(image,color,width,height);
    std::cout << "Cleared image with dark blue color." << std::endl;
    // XOR Texture
    draw_xor(image,width,height);
    std::cout << "XOR Texture drawn." << std::endl;
    save_image(image,width,height,"06_xor_texture.ppm");
    std::cout << "Saved: 06_xor_texture.ppm" << std::endl;
    // AND Texture
    draw_and(image,width,height);
    std::cout << "AND Texture drawn." << std::endl;
    save_image(image,width,height,"06_and_texture.ppm");
    std::cout << "Saved: 06_and_texture.ppm" << std::endl;
    // OR Texture
    draw_or(image,width,height);
    std::cout << "OR Texture drawn." << std::endl;
    save_image(image,width,height,"06_or_texture.ppm");
    std::cout << "Saved: 06_or_texture.ppm" << std::endl;

    return 0;
}