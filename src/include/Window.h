#pragma once

#include "Manager.h"
#include "Event.h"

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
    void openGeneralOptions();
    void openControlsOptions();

    /* ----- CREDITS ----- */

    void openCredits();

    /* ----- OTHER ----- */

    static void SetWindowMode(const Uint32 mode);

private:
    /// @brief the actual window
    static SDL_Window *window;
};
