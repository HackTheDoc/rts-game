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

        //      FREE

        MOVE_CAMERA_UP,
        MOVE_CAMERA_DOWN,
        MOVE_CAMERA_LEFT,
        MOVE_CAMERA_RIGHT,
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
    /// @return
    bool mouseClickLeft();

    /// @brief check for a mouse right click
    /// @return
    bool mouseClickRight();

    /// @brief check wether a specific event been raised or not
    /// @param id
    /// @return
    bool raised(const Event::ID id);

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
