#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>

#include <iostream>
#include <map>

#include "color.hpp"
#include "player_action.hpp"
#include "snake.hpp"
#include "snake_controller.hpp"
#include "window.hpp"

constexpr int WINDOW_WIDTH = 640;
constexpr int WINDOW_HEIGHT = 480;

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

const std::map<SDL_Keycode, game::PlayerAction> actionMapping =
    {{SDLK_UP, game::PlayerAction::moveUp},
     {SDLK_w, game::PlayerAction::moveUp},
     {SDLK_DOWN, game::PlayerAction::moveDown},
     {SDLK_s, game::PlayerAction::moveDown},
     {SDLK_LEFT, game::PlayerAction::moveLeft},
     {SDLK_a, game::PlayerAction::moveLeft},
     {SDLK_RIGHT, game::PlayerAction::moveRight},
     {SDLK_d, game::PlayerAction::moveRight},
     {SDLK_ESCAPE, game::PlayerAction::quit}};

game::PlayerAction handleEvent(const SDL_Event& event) noexcept {
    if (event.type == SDL_QUIT) {
        return game::PlayerAction::quit;
    } else if (event.type == SDL_KEYDOWN) {
        if (actionMapping.find(event.key.keysym.sym) != actionMapping.end()) {
            return actionMapping.at(event.key.keysym.sym);
        }
    }
    return game::PlayerAction::invalid;
}

int main(int argc, char* argv[]) {
    try {
        init();
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << "\n";
        return 1;
    }

    game::Snake snake = game::Snake();
    game::SnakeController sc = game::SnakeController();

    Window window = Window("smake snake", WINDOW_WIDTH, WINDOW_HEIGHT);

    Color color = Color(255, 255, 255);
    SDL_Surface* screen_surface = window.surface();
    SDL_FillRect(screen_surface, NULL, toSDL_RGB(color, screen_surface->format));

    window.update();

    SDL_Event event_buffer;
    bool quit = false;
    while (!quit) {
        while (SDL_PollEvent(&event_buffer)) {
            game::PlayerAction action = handleEvent(event_buffer);
            if (action == game::PlayerAction::quit) {
                quit = true;
            }
            sc.handleAction(action, snake);
        }
    }

    close();
    return 0;
}
