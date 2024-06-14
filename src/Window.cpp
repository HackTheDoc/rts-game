#include "include/Window.h"

#include "include/Save.h"
#include "include/WindowStates/WindowStates.h"

#include <iostream>

SDL_Window* Window::window = nullptr;

const std::string Window::TITLE = "RTS Game";
bool Window::isRunning = false;
bool Window::fullscreen = false;

SDL_Renderer* Window::renderer = nullptr;
SDL_Rect Window::screen = { 0, 0, 1280, 720 };

Manager* Window::manager = nullptr;
Event Window::event;

Window::Window() {}

Window::~Window() {}

int Window::init() {
    // init sdl
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        return -1;

    if (IMG_Init(IMG_INIT_PNG) == 0)
        return -1;

    if (TTF_Init() != 0)
        return -1;

    // init window
    window = SDL_CreateWindow(
        TITLE.c_str(),
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        screen.w,
        screen.h,
        SDL_WINDOW_SHOWN // | SDL_WINDOW_FULLSCREEN
    );
    if (!window)
        return -2;

    // init renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer)
        return -3;

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    Manager::SetRenderDrawColor(hue::background);

    // load config
    
    const Struct::Config config = Save::LoadConfig();

    SetWindowMode(config.window_mode);

    Save::Auto = config.autosave;

    //KeyMap::Key = config.controls;

    // init components

    manager = new Manager();

    openMainMenu();

    isRunning = true;

    return true;
}

void Window::update() {
    manager->updateCurrentWindowState();
}

void Window::render() {
    SDL_RenderClear(renderer);

    manager->renderCurrentWindowState();

    SDL_RenderPresent(renderer);
}

void Window::handleEvents() {
    SDL_PollEvent(&event.e);

    switch (event.e.type) {
    case SDL_QUIT:
        isRunning = false;
        break;
    default:
        event.handleKeyboardInputs();
        break;
    }
}

void Window::kill() {
    delete manager;
    manager = nullptr;

    SDL_DestroyRenderer(renderer);
    renderer = nullptr;

    SDL_DestroyWindow(window);
    window = nullptr;

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

/* ----- MAIN ----- */

void Window::openMainMenu() {
    manager->clearWindowStates();

    manager->addWindowState(WindowState::Type::MAIN, new MainMenu());
    manager->setCurrentWindowState(WindowState::Type::MAIN);
}

void Window::openGame() {
    manager->addWindowState(WindowState::Type::GAME, new Game());
    manager->setCurrentWindowState(WindowState::Type::GAME);
}

/* ----- OPTIONS ----- */

void Window::openOptionsMenu() {
    manager->addWindowState(WindowState::Type::OPTIONS_MENU, new OptionsMenu());
    manager->setCurrentWindowState(WindowState::Type::OPTIONS_MENU);
}

void Window::openGeneralOptions() {
    WindowState* ws = manager->getCurrentState();
    OptionsMenu* om = static_cast<OptionsMenu*>(ws);

    om->usePage("general");
}

void Window::openControlsOptions() {
    WindowState* ws = manager->getCurrentState();
    OptionsMenu* om = static_cast<OptionsMenu*>(ws);

    om->usePage("controls");
}

/* ----- CREDITS ----- */

void Window::openCredits() {
    manager->addWindowState(WindowState::Type::CREDITS, new Credits());
    manager->setCurrentWindowState(WindowState::Type::CREDITS);
}

/* ----- OTHER ----- */

void Window::SetWindowMode(const Uint32 mode) {
    SDL_SetWindowFullscreen(window, mode);
    SDL_GetWindowSize(window, &screen.w, &screen.h);

    fullscreen = (mode == SDL_WINDOW_FULLSCREEN_DESKTOP);

    if (!fullscreen)
        screen = { 0, 0, 1280, 720 };

    if (!Window::isRunning)
        return;

    manager->reloadFonts();

    WindowState* ws = manager->getCurrentState();
    OptionsMenu* om = static_cast<OptionsMenu*>(ws);
    om->reload();

    Save::SaveConfig();
}
