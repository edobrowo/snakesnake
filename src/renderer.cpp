#include "renderer.hpp"

struct RGB32 {
    Uint8 r;
    Uint8 g;
    Uint8 b;
    Uint8 a;
};

RGB32 toRgb32(const Color& color) {
    return RGB32{
        static_cast<Uint8>(color.r() * 255),
        static_cast<Uint8>(color.g() * 255),
        static_cast<Uint8>(color.b() * 255),
        static_cast<Uint8>(color.a() * 255)};
}

Renderer::Renderer() {}

void Renderer::init(std::weak_ptr<Window> win) {
    std::shared_ptr<Window> window_ref = win.lock();
    if (!window_ref) {
        std::string message = std::string("Invalid window weak_ptr");
        throw std::runtime_error(message);
    }

    m_windowWidth = window_ref->width();
    m_windowHeight = window_ref->height();

    SDL_Renderer* ren = SDL_CreateRenderer(window_ref->window(), -1, SDL_RENDERER_ACCELERATED);

    if (!ren) {
        std::string message = std::string("Failed to create SDL renderer: ") + SDL_GetError();
        throw std::runtime_error(message);
    }

    m_sdlRenderer.reset(ren);
}

void Renderer::render(const game::Snake& snake) {
    clear(m_colors.board);

    int board_width = snake.board().width();
    int board_height = snake.board().height();
    int pixel_width = m_windowWidth / board_width;
    int pixel_height = m_windowHeight / board_height;

    for (game::Pos::Coord y = 0; y < board_height; ++y) {
        for (game::Pos::Coord x = 0; x < board_width; ++x) {
            if (std::get_if<game::Empty>(&snake.board()(x, y))) {
                continue;
            }
            drawRectArea(x * pixel_width, y * pixel_height, pixel_width, pixel_height, m_colors.snake);
        }
    }

    game::Pos food = snake.food();
    drawRectArea(food.x() * pixel_width, food.y() * pixel_height, pixel_width, pixel_height, m_colors.food);

    SDL_RenderPresent(m_sdlRenderer.get());
}

void Renderer::drawRectArea(int x, int y, int w, int h, const Color& color) {
    RGB32 rgb = toRgb32(color);
    SDL_SetRenderDrawColor(m_sdlRenderer.get(), rgb.r, rgb.g, rgb.b, rgb.a);

    SDL_Rect fillRect = {x, y, w, h};
    SDL_RenderFillRect(m_sdlRenderer.get(), &fillRect);
}

void Renderer::clear(Color color) {
    RGB32 rgb = toRgb32(color);
    SDL_SetRenderDrawColor(m_sdlRenderer.get(), rgb.r, rgb.g, rgb.b, rgb.a);

    SDL_RenderClear(m_sdlRenderer.get());
}
