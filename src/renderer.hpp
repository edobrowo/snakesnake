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

struct Colors {
    Color snake;
    Color board;
    Color food;
};

class Window;

class Renderer {
public:
    Renderer();
    void init(Window* win);

    void render(const game::Snake& snake);

private:
    void drawRectArea(int x, int y, int w, int h, const Color& color);
    void clear(Color color);

    const Colors m_colors{Color(255, 255, 255), Color(0, 0, 0), Color(255, 255, 255)};

    std::unique_ptr<SDL_Renderer, SDL_RendererDeleter> m_sdlRenderer;
    int m_windowWidth;
    int m_windowHeight;
};

#endif
