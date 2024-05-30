#include "renderer.hpp"

Renderer::Renderer(Window* win)
    : snakeColor{Color(0, 0, 0)},
      boardColor{Color(255, 255, 255)} {
    window.reset(win);
    SDL_Renderer* ren = SDL_CreateRenderer(window->windowPtr(), -1, SDL_RENDERER_ACCELERATED);

    if (!ren) {
        std::string message = std::string("Failed to create SDL renderer") + SDL_GetError();
        throw std::runtime_error(message);
    }

    renderer.reset(ren);
}

void Renderer::render(const game::Snake& snake) {
    clear(boardColor);
    for (int i = 0; i < 64; ++i) {
        drawRectArea(i * 20, i * 20, 20, 20, snakeColor);
        drawRectArea((i + 1) * 20, i * 20, 20, 20, snakeColor);
    }
    SDL_RenderPresent(renderer.get());
}

void Renderer::drawRectArea(int x, int y, int w, int h, Color color) {
    SDL_Rect fillRect = {x, y, w, h};
    SDL_SetRenderDrawColor(renderer.get(), color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer.get(), &fillRect);
}

void Renderer::clear(Color color) {
    SDL_SetRenderDrawColor(renderer.get(), color.r, color.g, color.b, color.a);
    SDL_RenderClear(renderer.get());
}
