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
    Window(const std::string& title, unsigned int width, unsigned int height);

    SDL_Window* windowPtr() const;
    SDL_Surface* surfacePtr() const;
    void setRenderer(Renderer renderer);
    Renderer& rendererRef();
    int width() const;
    int height() const;

private:
    std::string title;
    unsigned int winWidth;
    unsigned int winHeight;

    std::unique_ptr<SDL_Window, SDL_WindowDeleter> sdlWindow;
    std::unique_ptr<Renderer> renderer;
};

#endif
