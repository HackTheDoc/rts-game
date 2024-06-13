#pragma once

#include "Manager.h"
#include "Event.h"
#include "Text.h"

class Window {
public:
    static const std::string TITLE;
    static bool isRunning;
    static bool fullscreen;

    static SDL_Renderer* renderer;
    static SDL_Rect screen;

    static Manager* manager;
    static Event event;

    Window();
    ~Window();

    int init();
    void update();
    void render();
    void handleEvents();
    void kill();

    /* ----- MAIN ----- */

    void openMainMenu();

    /* ----- GAME ----- */

    void openGame();

    /* ----- OPTIONS ----- */

    void openOptionsMenu();

    /* ----- CREDITS ----- */

    void openCredits();

private:
    /// @brief the actual window
    static SDL_Window *window;
};
