#include "color.hpp"

#include <SDL2/SDL.h>

float unit_clamp(float x) {
    if (x < 0.0)
        return 0.0;
    else if (x > 1.0)
        return 1.0;
    return x;
}

float unit_clamp(int x) {
    float y = static_cast<float>(x);
    if (y < 0.0)
        y = 0.0;
    else if (y > 255.0)
        return 255.0;
    return y / 255.0;
}

Color::Color() : r{0.0}, g{0.0}, b{0.0}, a{1.0} {}

Color::Color(float r, float g, float b)
    : r{unit_clamp(r)}, g{unit_clamp(g)}, b{unit_clamp(b)}, a{1.0} {}

Color::Color(float r, float g, float b, float a)
    : r{unit_clamp(r)}, g{unit_clamp(g)}, b{unit_clamp(b)}, a{unit_clamp(a)} {}

Color::Color(int r, int g, int b)
    : r{unit_clamp(r)}, g{unit_clamp(g)}, b{unit_clamp(b)}, a{1.0} {}

Color::Color(int r, int g, int b, int a)
    : r{unit_clamp(r)}, g{unit_clamp(g)}, b{unit_clamp(b)}, a{unit_clamp(a)} {}

Color::Color(const Color& other)
    : r{other.r}, g{other.g}, b{other.b}, a{other.a} {}

Color Color::operator=(const Color& other) {
    return Color(other);
}

Uint32 toSDL_RGB(const Color& color, SDL_PixelFormat* pf) {
    Uint8 r = static_cast<Uint8>(255 * color.r);
    Uint8 g = static_cast<Uint8>(255 * color.g);
    Uint8 b = static_cast<Uint8>(255 * color.b);

    return SDL_MapRGB(pf, r, g, b);
}
