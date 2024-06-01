#ifndef __WINDOW__
#define __WINDOW__

#include <SDL2/SDL.h>

#include <memory>
#include <string>

#include "renderer.hpp"

class SDL_WindowDeleter {
public:
    void operator()(SDL_Window* window) const {
        if (window) {
            SDL_FreeSurface(SDL_GetWindowSurface(window));
            SDL_DestroyWindow(window);
        }
    }
};

class Renderer;

class Window {
public:
    Window(const std::string& title, const size_t width, const size_t height);
    void init();

    SDL_Window* window() const;
    SDL_Surface* surface() const;
    void setRenderer(Renderer renderer);
    Renderer& renderer();
    size_t width() const;
    size_t height() const;

private:
    std::string m_title;
    size_t m_width;
    size_t m_height;

    std::unique_ptr<SDL_Window, SDL_WindowDeleter> m_sdlWindow;
    std::unique_ptr<Renderer> m_renderer;
};

#endif
