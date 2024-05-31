#ifndef __RENDERER__
#define __RENDERER__

#include <SDL2/SDL.h>

#include <memory>

#include "color.hpp"
#include "snake.hpp"
#include "window.hpp"

class SDL_RendererDeleter {
public:
    void operator()(SDL_Renderer* renderer) const {
        if (renderer) {
            SDL_DestroyRenderer(renderer);
        }
    }
};

class Window;

class Renderer {
public:
    Renderer(Window* win);

    void render(const game::Snake& snake);

private:
    void drawRectArea(int x, int y, int w, int h, const Color& color);
    void clear(Color color);

    std::unique_ptr<SDL_Renderer, SDL_RendererDeleter> renderer;
    int windowWidth;
    int windowHeight;

    Color snakeColor;
    Color boardColor;
};

#endif
