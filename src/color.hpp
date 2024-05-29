#ifndef __COLOR__
#define __COLOR__

#include <SDL2/SDL.h>

class Color {
public:
    Color();

    // Clamps to [0.0, 1.0]
    Color(float r, float g, float b);
    Color(float r, float g, float b, float a);

    // Clamps to [0, 255]
    Color(int r, int g, int b);
    Color(int r, int g, int b, int a);

    Color(const Color& other);
    Color operator=(const Color& other);

    float r;
    float g;
    float b;
    float a;
};

Uint32 toSDL_RGB(const Color& color, SDL_PixelFormat* pf);

#endif
