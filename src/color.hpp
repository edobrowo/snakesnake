#ifndef __COLOR__
#define __COLOR__

class Color {
public:
    Color();

    Color(float r, float g, float b);
    Color(float r, float g, float b, float a);

    Color(int r, int g, int b);
    Color(int r, int g, int b, int a);

    Color(const Color& other);
    Color operator=(const Color& other);

    float r;
    float g;
    float b;
    float a;
};

#endif
