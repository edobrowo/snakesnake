#ifndef __EVENT_HANDLER__
#define __EVENT_HANDLER__

#include <SDL2/SDL.h>

#include <map>

#include "player_action.hpp"
#include "snake.hpp"

namespace events {
    const std::map<SDL_Keycode, game::PlayerAction> EVENTS_TO_ACTIONS =
        {{SDLK_UP, game::PlayerAction::moveUp},
         {SDLK_w, game::PlayerAction::moveUp},
         {SDLK_DOWN, game::PlayerAction::moveDown},
         {SDLK_s, game::PlayerAction::moveDown},
         {SDLK_LEFT, game::PlayerAction::moveLeft},
         {SDLK_a, game::PlayerAction::moveLeft},
         {SDLK_RIGHT, game::PlayerAction::moveRight},
         {SDLK_d, game::PlayerAction::moveRight},
         {SDLK_ESCAPE, game::PlayerAction::quit}};

    game::PlayerAction processPlayerEvent(const SDL_Event& event) noexcept {
        if (event.type == SDL_QUIT) {
            return game::PlayerAction::quit;
        } else if (event.type == SDL_KEYDOWN) {
            if (EVENTS_TO_ACTIONS.find(event.key.keysym.sym) != EVENTS_TO_ACTIONS.end()) {
                return EVENTS_TO_ACTIONS.at(event.key.keysym.sym);
            }
        }
        return game::PlayerAction::invalid;
    }

    void performAction(game::PlayerAction action, game::Snake& snake) {
        switch (action) {
        case game::PlayerAction::moveUp:
            snake.setDirection(game::Direction::Up);
            break;
        case game::PlayerAction::moveDown:
            snake.setDirection(game::Direction::Down);
            break;
        case game::PlayerAction::moveLeft:
            snake.setDirection(game::Direction::Left);
            break;
        case game::PlayerAction::moveRight:
            snake.setDirection(game::Direction::Right);
            break;
        case game::PlayerAction::quit:
        case game::PlayerAction::invalid:
            return;
        }
    }
}

#endif
