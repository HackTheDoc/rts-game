#pragma once

#include "Manager.h"
#include "Event.h"

#include <random>

using KeyMap = std::map<Event::ID, SDL_Scancode>;

class Window {
public:
    static const std::string TITLE;
    static bool isRunning;
    static bool fullscreen;

    static SDL_Renderer* renderer;
    static SDL_Rect screen;

    static KeyMap controls;
    static Manager* manager;
    static Event event;

    static std::default_random_engine randomEngine;

    static float deltaTime;

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

    void openUnitsSelectionMenu();
    void endUnitsSelection();

    void pauseGame();
    void resumeGame();

    void quitGame();

    /* ----- OPTIONS ----- */

    void openOptionsMenu();
    void openGeneralOptions();
    void openControlsOptions();

    /* ----- CREDITS ----- */

    void openCredits();

    /* ----- OTHER ----- */

    static void SetWindowMode(const Uint32 mode);

private:
    static Uint32 lastTick;

    /// @brief the actual window
    static SDL_Window *window;
};
