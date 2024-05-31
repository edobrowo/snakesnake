#include "renderer.hpp"

struct RGB32 {
    Uint8 r;
    Uint8 g;
    Uint8 b;
    Uint8 a;
};

RGB32 toRgb32(const Color& color) {
    return RGB32{
        static_cast<Uint8>(color.r * 255),
        static_cast<Uint8>(color.g * 255),
        static_cast<Uint8>(color.b * 255),
        static_cast<Uint8>(color.a * 255)};
}

Renderer::Renderer(Window* win)
    : windowWidth{win->width()},
      windowHeight{win->height()},
      snakeColor{Color(255, 255, 255)},
      boardColor{Color(0, 0, 0)} {
    SDL_Renderer* ren = SDL_CreateRenderer(win->windowPtr(), -1, SDL_RENDERER_ACCELERATED);

    if (!ren) {
        std::string message = std::string("Failed to create SDL renderer: ") + SDL_GetError();
        throw std::runtime_error(message);
    }

    renderer.reset(ren);
}

void Renderer::render(const game::Snake& snake) {
    clear(boardColor);
    int w = snake.boardState().width();
    int h = snake.boardState().height();
    int pixel_width = windowWidth / w;
    int pixel_height = windowHeight / h;
    for (game::Pos::Coord y = 0; y < h; ++y) {
        for (game::Pos::Coord x = 0; x < w; ++x) {
            if (game::Pos(x, y) == snake.foodPos()) {
                drawRectArea(x * pixel_width, y * pixel_height, pixel_width, pixel_height, snakeColor);
                continue;
            }

            if (std::get_if<game::Empty>(&snake.boardState()(x, y))) {
                continue;
            }

            drawRectArea(x * pixel_width, y * pixel_height, pixel_width, pixel_height, snakeColor);
        }
    }
    SDL_RenderPresent(renderer.get());
}

void Renderer::drawRectArea(int x, int y, int w, int h, const Color& color) {
    RGB32 rgb = toRgb32(color);
    SDL_Rect fillRect = {x, y, w, h};
    SDL_SetRenderDrawColor(renderer.get(), rgb.r, rgb.g, rgb.b, rgb.a);
    SDL_RenderFillRect(renderer.get(), &fillRect);
}

void Renderer::clear(Color color) {
    RGB32 rgb = toRgb32(color);
    SDL_SetRenderDrawColor(renderer.get(), rgb.r, rgb.g, rgb.b, rgb.a);
    SDL_RenderClear(renderer.get());
}
