#include <SDL2/SDL.h>

#include <iostream>
#include <memory>
#include <variant>

#include "color.hpp"
#include "event_handling.hpp"
#include "snake.hpp"
#include "window.hpp"

struct WindowSettings {
    std::string title;
    size_t width;
    size_t height;
};

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

int main(int argc, char* argv[]) {
    try {
        init();
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << "\n";
        return 1;
    }

    game::Snake snake = game::Snake();

    const WindowSettings windowSettings{"smake", 640, 640};

    Window window{windowSettings.title, windowSettings.width, windowSettings.height};
    try {
        window.init();
        Renderer renderer = Renderer();
        std::shared_ptr<Window> window_ref(&window, [](auto) {});
        renderer.init(window_ref);
        window.setRenderer(std::move(renderer));
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << "\n";
        return 1;
    }

    Renderer& renderer = window.renderer();
    renderer.render(snake);

    SDL_Event event_buffer;
    bool quit = false;
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
                    std::cout << "game over\n";
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
