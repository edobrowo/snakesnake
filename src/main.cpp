#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>

#include <iostream>
#include <memory>
#include <variant>

#include "color.hpp"
#include "event_handling.hpp"
#include "snake.hpp"
#include "window.hpp"

constexpr int WINDOW_WIDTH = 640;
constexpr int WINDOW_HEIGHT = 640;

void init() {
    int err = SDL_Init(SDL_INIT_VIDEO);
    if (err != 0) {
        std::string message = std::string("Failed to update SDL window") + SDL_GetError();
        throw std::runtime_error(message);
    }
}

void close() noexcept {
    SDL_Quit();
}

Uint32 toSDL_RGB(const Color& color, SDL_PixelFormat* pf) {
    Uint8 r = static_cast<Uint8>(255 * color.r);
    Uint8 g = static_cast<Uint8>(255 * color.g);
    Uint8 b = static_cast<Uint8>(255 * color.b);

    return SDL_MapRGB(pf, r, g, b);
}

std::ostream& operator<<(std::ostream& os, const game::Snake& snake) {
    int h = snake.boardState().height();
    int w = snake.boardState().width();
    for (game::Pos::Coord y = 0; y < h; ++y) {
        for (game::Pos::Coord x = 0; x < w; ++x) {
            if (game::Pos(x, y) == snake.foodPos()) {
                os << 'F';
                continue;
            }

            if (std::get_if<game::Empty>(&snake.boardState()(x, y))) {
                os << '.';
                continue;
            }

            const game::SnakeBody& snake_body = std::get<game::SnakeBody>(snake.boardState()(x, y));
            const game::Direction direction = snake_body.direction;
            switch (direction) {
            case game::Direction::Up:
                os << 'U';
                break;
            case game::Direction::Down:
                os << 'D';
                break;
            case game::Direction::Left:
                os << 'L';
                break;
            case game::Direction::Right:
                os << 'R';
                break;
            }
        }
        os << '\n';
    }
    return os;
}

int main(int argc, char* argv[]) {
    try {
        init();
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << "\n";
        return 1;
    }

    game::Snake snake = game::Snake();

    std::unique_ptr<Window> window;
    try {
        window = std::make_unique<Window>("smake snake", WINDOW_WIDTH, WINDOW_HEIGHT);
        window->setRenderer(Renderer(window.get()));
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << "\n";
        return 1;
    }

    Renderer& renderer = window->rendererRef();

    SDL_Event event_buffer;
    bool quit = false;
    renderer.render(snake);
    while (!quit) {
        while (SDL_PollEvent(&event_buffer)) {
            game::PlayerAction action = events::processPlayerEvent(event_buffer);
            if (action == game::PlayerAction::quit) {
                quit = true;
            }

            events::performAction(action, snake);

            if (action != game::PlayerAction::quit && action != game::PlayerAction::invalid) {
                snake.update();
                if (!snake.isAlive()) {
                    std::cout << "game over" << std::endl;
                    quit = true;
                } else {
                    renderer.render(snake);
                }
            }
        }
    }

    close();
    return 0;
}
