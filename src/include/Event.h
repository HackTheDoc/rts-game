#pragma once

#include <string>
#include <SDL2/SDL.h>

class Window;

class Event {
private:
    /// @brief owner window
    Window* window;

public:
    enum ID {
        UNKNOWN,

        SET_WINDOW_TO_FULLSCREEN,
        SET_WINDOW_TO_DEFAULT,

        // BUTTONS 

        QUIT,
        OPEN_MAIN_MENU,

        OPEN_OPTIONS,
        OPEN_GENERAL_SETTINGS,
        OPEN_CONTROLS_SETTINGS,

        OPEN_CREDITS,

        OPEN_GAME,
        QUIT_GAME,

        RESUME_GAME,
        PAUSE,

        // GAME RELATED

        VALID_STARTING_UNIT_SELECTION,

        MOVE_UP,
        MOVE_DOWN,
        MOVE_LEFT,
        MOVE_RIGHT,

        SELECT_MULTIPLE
    };

    /// @brief classic SDL_Event object
    SDL_Event e;

    Event();
    ~Event();

    /// @brief set the owner window pointer
    /// @param w
    void linkTo(Window* w);

    /// @brief handle user's keyboard inputs
    void handleKeyboardInputs();

    /// @brief check for a mouse left click
    /// @param clickType format = [SDL_MOUSEBUTTONUP, SDL_MOUSEBUTTONDOWN]
    /// @return
    bool mouseClickLeft(const SDL_EventType clickType = SDL_MOUSEBUTTONUP);

    /// @brief check for a mouse right click
    /// @return
    bool mouseClickRight();

    /// @brief check wether a specific event been raised or not
    bool raised(const Event::ID eid);

    /// @brief raise a specific event
    /// @param id 
    void raise(const Event::ID id);

private:
    void handleMainMenuEvents();
    void handleOptionsMenuEvents();
    void handleCreditsEvents();

    void handleGameEvents();
    void handlePauseMenuEvents();
};

std::string to_string(const Event::ID eid);
