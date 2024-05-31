#include "window.hpp"

Window::Window(const std::string& title, unsigned int width, unsigned int height)
    : winWidth{width},
      winHeight{height} {
    SDL_Window* win = SDL_CreateWindow(title.c_str(),
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       winWidth, winHeight, 0);

    if (!win) {
        std::string message = std::string("Failed to create SDL window") + SDL_GetError();
        throw std::runtime_error(message);
    }

    sdlWindow.reset(win);
}

SDL_Window* Window::windowPtr() const {
    return sdlWindow.get();
}

SDL_Surface* Window::surfacePtr() const {
    return SDL_GetWindowSurface(sdlWindow.get());
}

void Window::setRenderer(Renderer ren) {
    renderer = std::make_unique<Renderer>(std::move(ren));
}

Renderer& Window::rendererRef() {
    return *renderer.get();
}

int Window::width() const {
    return winWidth;
}

int Window::height() const {
    return winHeight;
}
