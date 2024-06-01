#include <SDL2/SDL.h>

#include <iostream>
#include <memory>
#include <variant>

#include "color.hpp"
#include "event_handling.hpp"
#include "renderer.hpp"
#include "snake.hpp"
#include "timer.hpp"
#include "window.hpp"

struct WindowSettings {
    std::string title;
    size_t width;
    size_t height;
};

int main(int argc, char* argv[]) {
    int err = SDL_Init(SDL_INIT_VIDEO);
    if (err != 0) {
        std::string message = std::string("Failed to update SDL window") + SDL_GetError();
        throw std::runtime_error(message);
    }

    const WindowSettings windowSettings{"smake", 640, 640};
    Window window{windowSettings.title, windowSettings.width, windowSettings.height};
    Renderer renderer = Renderer();

    try {
        window.init();
        std::shared_ptr<Window> window_ref(&window, [](auto) {});
        renderer.init(window_ref);
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << "\n";
        return 1;
    }

    game::Snake snake = game::Snake();

    Timer snake_update = Timer();
    const Uint32 msPerTile = static_cast<Uint32>(1000.0 / snake.tilesPerSecond());

    snake_update.start();
    renderer.render(snake);

    SDL_Event event_buffer;
    bool quit = false;
    bool end_state = false;
    while (!quit) {
        while (SDL_PollEvent(&event_buffer)) {
            game::PlayerAction action = events::processPlayerEvent(event_buffer);
            if (action == game::PlayerAction::quit) {
                quit = true;
            } else if (action == game::PlayerAction::restart) {
                end_state = false;
            }
            events::performAction(action, snake);
        }

        if (!end_state && snake_update.ticks() >= msPerTile) {
            snake.update();
            snake_update.restart();
        }

        if (!snake.isAlive()) {
            end_state = true;
        }

        renderer.render(snake);
    }

    SDL_Quit();
}
