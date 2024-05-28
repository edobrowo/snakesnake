#include "window.hpp"

Window::Window(const std::string& title, unsigned int width, unsigned int height) : width{width}, height{height} {
    SDL_Window* win = SDL_CreateWindow(this->title.c_str(),
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       this->width, this->height, 0);

    if (!win) {
        std::string message = std::string("Failed to create SDL window") + SDL_GetError();
        throw std::runtime_error(message);
    }

    this->sdlWindow.reset(win);
}

void Window::update() {
    int err = SDL_UpdateWindowSurface(sdlWindow.get());
    if (err != 0) {
        std::string message = std::string("Failed to update SDL window") + SDL_GetError();
        throw std::runtime_error(message);
    }
}

SDL_Surface* Window::surface() const {
    return SDL_GetWindowSurface(this->sdlWindow.get());
}