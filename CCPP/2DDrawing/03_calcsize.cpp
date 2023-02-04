// Compile: clang++ -std=c++17 03_calcsize.cpp -o 03_calcsize

#include <iostream>
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

int main()
{
    std::vector<std::tuple<float, float, float>> image;
    std::tuple<float, float, float> color=std::make_tuple(0.0f,0.0f,0.0f);
    int width=640;
    int height=360;

    image.resize(calc_size(width, height));
    std::cout << "Created a vector with the size: " << calc_size(width, height) << std::endl;
    clear_image(image,color,width,height);
    std::cout << "Cleared image with black color." << std::endl;

    return 0;
}