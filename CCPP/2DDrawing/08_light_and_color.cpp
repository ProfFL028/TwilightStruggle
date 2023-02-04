// Compile: clang++ -std=c++17 08_light_and_color.cpp -o 08_light_and_color

#include <iostream>
#include <fstream>
#include <tuple>
#include <vector>

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

void negative_image(std::vector<std::tuple<float, float, float>> &image, int width, int height)
{
    std::tuple<float, float, float> oldColor=std::make_tuple(0.0f,0.0f,0.0f);
    for (int y=0;y<height;++y) {
        for (int x=0;x<width;++x) {
            oldColor=image[get_index(x,y,width)];
            image[get_index(x,y,width)]=std::make_tuple(1.0f-std::get<0>(oldColor), 1.0f-std::get<1>(oldColor), 1.0f-std::get<2>(oldColor));
        }
    }
}

void double_as_dark(std::vector<std::tuple<float, float, float>> &image, int width, int height)
{
    std::tuple<float, float, float> oldColor=std::make_tuple(0.0f,0.0f,0.0f);
    for (int y=0;y<height;++y) {
        for (int x=0;x<width;++x) {
            oldColor=image[get_index(x,y,width)];
            image[get_index(x,y,width)]=std::make_tuple(std::get<0>(oldColor) / 2.0f, std::get<1>(oldColor) / 2.0f, std::get<2>(oldColor) / 2.0f);
        }
    }
}

void onefive_as_dark(std::vector<std::tuple<float, float, float>> &image, int width, int height)
{
    std::tuple<float, float, float> oldColor=std::make_tuple(0.0f,0.0f,0.0f);
    for (int y=0;y<height;++y) {
        for (int x=0;x<width;++x) {
            oldColor=image[get_index(x,y,width)];
            image[get_index(x,y,width)]=std::make_tuple(std::get<0>(oldColor) / 1.5f, std::get<1>(oldColor) / 1.5f, std::get<2>(oldColor) / 1.5f);
        }
    }
}

void twice_as_bright(std::vector<std::tuple<float, float, float>> &image, int width, int height)
{
    std::tuple<float, float, float> oldColor=std::make_tuple(0.0f,0.0f,0.0f);
    float r=0.0; float g=0.0; float b=0.0;
    for (int y=0;y<height;++y) {
        for (int x=0;x<width;++x) {
            oldColor=image[get_index(x,y,width)];
            r=std::get<0>(oldColor) * 2.0f; g=std::get<1>(oldColor) * 2.0f; b=std::get<2>(oldColor) * 2.0f;
            if (r > 1.0) {r=1.0f;} if (g > 1.0) {g=1.0f;} if (b > 1.0) {b=1.0f;}
            image[get_index(x,y,width)]=std::make_tuple(r, g, b);
        }
    }
}

void add_for_brighter(std::vector<std::tuple<float, float, float>> &image, int width, int height)
{
    std::tuple<float, float, float> oldColor=std::make_tuple(0.0f,0.0f,0.0f);
    float r=0.0; float g=0.0; float b=0.0;
    for (int y=0;y<height;++y) {
        for (int x=0;x<width;++x) {
            oldColor=image[get_index(x,y,width)];
            r=std::get<0>(oldColor) + 0.2f; g=std::get<1>(oldColor) + 0.2f; b=std::get<2>(oldColor) + 0.2f;
            if (r > 1.0) {r=1.0f;} if (g > 1.0) {g=1.0f;} if (b > 1.0) {b=1.0f;}
            image[get_index(x,y,width)]=std::make_tuple(r, g, b);
        }
    }
}

void sub_for_darker(std::vector<std::tuple<float, float, float>> &image, int width, int height)
{
    std::tuple<float, float, float> oldColor=std::make_tuple(0.0f,0.0f,0.0f);
    float r=0.0; float g=0.0; float b=0.0;
    for (int y=0;y<height;++y) {
        for (int x=0;x<width;++x) {
            oldColor=image[get_index(x,y,width)];
            r=std::get<0>(oldColor) - 0.2f; g=std::get<1>(oldColor) - 0.2f; b=std::get<2>(oldColor) - 0.2f;
            if (r < 0.0) {r=0.0f;} if (g < 0.0) {g=0.0f;} if (b < 0.0) {b=0.0f;}
            image[get_index(x,y,width)]=std::make_tuple(r, g, b);
        }
    }
}

void greyscale_image(std::vector<std::tuple<float, float, float>> &image, int width, int height)
{
    std::tuple<float, float, float> color=std::make_tuple(0.0f,0.0f,0.0f);
    float c=0.0;
    for (int y=0;y<height;++y) {
        for (int x=0;x<width;++x) {
            color=image[get_index(x,y,width)];
            c=(0.2126 * std::get<0>(color))+(0.7152 * std::get<1>(color))+(0.0722 * std::get<2>(color));
            if (c > 1.0) {c=1.0f;}
            image[get_index(x,y,width)]=std::make_tuple(c, c, c);
        }
    }
}

void zero_gb_image(std::vector<std::tuple<float, float, float>> &image, int width, int height)
{
    std::tuple<float, float, float> color=std::make_tuple(0.0f,0.0f,0.0f);
    for (int y=0;y<height;++y) {
        for (int x=0;x<width;++x) {
            color=image[get_index(x,y,width)];
            image[get_index(x,y,width)]=std::make_tuple(0.0f, std::get<1>(color), std::get<2>(color));
        }
    }
}

void r_zero_b_image(std::vector<std::tuple<float, float, float>> &image, int width, int height)
{
    std::tuple<float, float, float> color=std::make_tuple(0.0f,0.0f,0.0f);
    for (int y=0;y<height;++y) {
        for (int x=0;x<width;++x) {
            color=image[get_index(x,y,width)];
            image[get_index(x,y,width)]=std::make_tuple(std::get<0>(color), 0.0f, std::get<2>(color));
        }
    }
}

void rg_zero_image(std::vector<std::tuple<float, float, float>> &image, int width, int height)
{
    std::tuple<float, float, float> color=std::make_tuple(0.0f,0.0f,0.0f);
    for (int y=0;y<height;++y) {
        for (int x=0;x<width;++x) {
            color=image[get_index(x,y,width)];
            image[get_index(x,y,width)]=std::make_tuple(std::get<0>(color), std::get<1>(color), 0.0f);
        }
    }
}

void grb_image(std::vector<std::tuple<float, float, float>> &image, int width, int height)
{
    std::tuple<float, float, float> color=std::make_tuple(0.0f,0.0f,0.0f);
    for (int y=0;y<height;++y) {
        for (int x=0;x<width;++x) {
            color=image[get_index(x,y,width)];
            image[get_index(x,y,width)]=std::make_tuple(std::get<1>(color), std::get<0>(color), std::get<2>(color));
        }
    }
}

void bgr_image(std::vector<std::tuple<float, float, float>> &image, int width, int height)
{
    std::tuple<float, float, float> color=std::make_tuple(0.0f,0.0f,0.0f);
    for (int y=0;y<height;++y) {
        for (int x=0;x<width;++x) {
            color=image[get_index(x,y,width)];
            image[get_index(x,y,width)]=std::make_tuple(std::get<2>(color), std::get<1>(color), std::get<0>(color));
        }
    }
}

void rrb_image(std::vector<std::tuple<float, float, float>> &image, int width, int height)
{
    std::tuple<float, float, float> color=std::make_tuple(0.0f,0.0f,0.0f);
    for (int y=0;y<height;++y) {
        for (int x=0;x<width;++x) {
            color=image[get_index(x,y,width)];
            image[get_index(x,y,width)]=std::make_tuple(std::get<0>(color), std::get<0>(color), std::get<2>(color));
        }
    }
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
    int width=0;
    int height=0;

    // Negative Colors.
    std::cout << "Loading: '04_helloworld.ppm'." << std::endl;
    read_image(image, width, height, "04_helloworld.ppm");
    std::cout << "Making a negative color image." << std::endl;
    negative_image(image,width,height);
    std::cout << "Saving: '08_negative_image.ppm'." << std::endl;
    save_image(image,width,height,"08_negative_image.ppm");

    // Double as dark.
    std::cout << "Reverting to: '04_helloworld.ppm'." << std::endl;
    image.clear();
    read_image(image, width, height, "04_helloworld.ppm");
    std::cout << "Making a double as dark image." << std::endl;
    double_as_dark(image,width,height);
    std::cout << "Saving: '08_double_as_dark.ppm'." << std::endl;
    save_image(image,width,height,"08_double_as_dark.ppm");

    // OneFive times as dark.
    std::cout << "Reverting to: '04_helloworld.ppm'." << std::endl;
    image.clear();
    read_image(image, width, height, "04_helloworld.ppm");
    std::cout << "Making a 1.5 times as dark image." << std::endl;
    onefive_as_dark(image,width,height);
    std::cout << "Saving: '08_onefive_as_dark.ppm'." << std::endl;
    save_image(image,width,height,"08_onefive_as_dark.ppm");

    // Twice as bright.
    std::cout << "Reverting to: '04_helloworld.ppm'." << std::endl;
    image.clear();
    read_image(image, width, height, "04_helloworld.ppm");
    std::cout << "Twice as bright image." << std::endl;
    twice_as_bright(image,width,height);
    std::cout << "Saving: '08_twice_as_bright.ppm'." << std::endl;
    save_image(image,width,height,"08_twice_as_bright.ppm");

    // Add for brighter.
    std::cout << "Reverting to: '04_helloworld.ppm'." << std::endl;
    image.clear();
    read_image(image, width, height, "04_helloworld.ppm");
    std::cout << "Add for brighter image." << std::endl;
    add_for_brighter(image,width,height);
    std::cout << "Saving: '08_add_for_brighter.ppm'." << std::endl;
    save_image(image,width,height,"08_add_for_brighter.ppm");

    // Sub for darker.
    std::cout << "Reverting to: '04_helloworld.ppm'." << std::endl;
    image.clear();
    read_image(image, width, height, "04_helloworld.ppm");
    std::cout << "Sub for darker image." << std::endl;
    sub_for_darker(image,width,height);
    std::cout << "Saving: '08_sub_for_darker.ppm'." << std::endl;
    save_image(image,width,height,"08_sub_for_darker.ppm");

    // Greyscale image.
    std::cout << "Reverting to: '04_helloworld.ppm'." << std::endl;
    image.clear();
    read_image(image, width, height, "04_helloworld.ppm");
    std::cout << "Greyscale image." << std::endl;
    greyscale_image(image,width,height);
    std::cout << "Saving: '08_greyscale_image.ppm'." << std::endl;
    save_image(image,width,height,"08_greyscale_image.ppm");

    // Swapping and removing color channels.
    std::cout << "Reverting to: '04_helloworld.ppm'." << std::endl;
    image.clear();
    read_image(image, width, height, "04_helloworld.ppm");
    std::cout << "Swapping and removing color channels." << std::endl;
    zero_gb_image(image,width,height);
    std::cout << "Saving: '08_zero_gb_image.ppm'." << std::endl;
    save_image(image,width,height,"08_zero_gb_image.ppm");
    std::cout << "Reverting to: '04_helloworld.ppm'." << std::endl;
    image.clear();
    read_image(image, width, height, "04_helloworld.ppm");
    std::cout << "Swapping and removing color channels." << std::endl;
    r_zero_b_image(image,width,height);
    std::cout << "Saving: '08_r_zero_b_image.ppm'." << std::endl;
    save_image(image,width,height,"08_r_zero_b_image.ppm");
    std::cout << "Reverting to: '04_helloworld.ppm'." << std::endl;
    image.clear();
    read_image(image, width, height, "04_helloworld.ppm");
    std::cout << "Swapping and removing color channels." << std::endl;
    rg_zero_image(image,width,height);
    std::cout << "Saving: '08_rg_zero_image.ppm'." << std::endl;
    save_image(image,width,height,"08_rg_zero_image.ppm");
    std::cout << "Reverting to: '04_helloworld.ppm'." << std::endl;
    image.clear();
    read_image(image, width, height, "04_helloworld.ppm");
    std::cout << "Swapping and removing color channels." << std::endl;
    grb_image(image,width,height);
    std::cout << "Saving: '08_grb_image.ppm'." << std::endl;
    save_image(image,width,height,"08_grb_image.ppm");
    std::cout << "Reverting to: '04_helloworld.ppm'." << std::endl;
    image.clear();
    read_image(image, width, height, "04_helloworld.ppm");
    std::cout << "Swapping and removing color channels." << std::endl;
    bgr_image(image,width,height);
    std::cout << "Saving: '08_bgr_image.ppm'." << std::endl;
    save_image(image,width,height,"08_bgr_image.ppm");
    std::cout << "Reverting to: '04_helloworld.ppm'." << std::endl;
    image.clear();
    read_image(image, width, height, "04_helloworld.ppm");
    std::cout << "Swapping and removing color channels." << std::endl;
    rrb_image(image,width,height);
    std::cout << "Saving: '08_rrb_image.ppm'." << std::endl << std::endl;
    save_image(image,width,height,"08_rrb_image.ppm");

    // Blend colors
    std::vector<std::tuple<float, float, float>> blend1;
    std::vector<std::tuple<float, float, float>> blend2;
    read_image(blend1, width, height, "06_xor_texture.ppm");
    read_image(blend2, width, height, "04_helloworld_square.ppm");
    std::cout << "Blended two images." << std::endl;
    blended_two_images(blend1,blend2,width,height,0.5);
    std::cout << "Saving: '08_blended_two_images.ppm'." << std::endl << std::endl;
    save_image(blend1,width,height,"08_blended_two_images.ppm");
    blend1.clear(); blend2.clear();
    read_image(blend1, width, height, "05_randomwalker.ppm");
    read_image(blend2, width, height, "04_helloworld.ppm");
    std::cout << "Blended two images (2)." << std::endl;
    blended_two_images(blend1,blend2,width,height,0.2);
    std::cout << "Saving: '08_blended_two_images(2).ppm'." << std::endl << std::endl;
    save_image(blend1,width,height,"08_blended_two_images(2).ppm");

    return 0;
}