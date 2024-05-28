#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>

#include <iostream>

#include "color.hpp"
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

int main(int argc, char* argv[]) {
    try {
        init();
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << "\n";
        return 1;
    }

    Window window = Window("smake snake", WINDOW_WIDTH, WINDOW_HEIGHT);

    Color color = Color(255, 255, 255);
    SDL_Surface* screen_surface = window.surface();
    SDL_FillRect(screen_surface, NULL, color.toSDL_RGB(screen_surface->format));

    window.update();

    // Hack to keep the window open
    SDL_Event e;
    bool quit = false;
    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }
    }

    close();
    return 0;
}
