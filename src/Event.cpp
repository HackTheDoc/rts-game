#include "include/Event.h"

#include "include/WindowStates/UnitsSelectionMenu.h"
#include "include/Game/Game.h"
#include "include/Window.h"
#include "include/Save.h"

Event::Event() {}

Event::~Event() {}

void Event::linkTo(Window* w) {
    window = w;
}

void Event::handleKeyboardInputs() {
    switch (Window::manager->getCurrentStateID()) {
    case WindowState::Type::MAIN:
        handleMainMenuEvents();
        break;
    case WindowState::Type::OPTIONS_MENU:
        handleOptionsMenuEvents();
        break;
    case WindowState::Type::CREDITS:
        handleCreditsEvents();
        break;
    case WindowState::Type::GAME:
        handleGameEvents();
        break;
    case WindowState::Type::UNITS_SELECTION_MENU:
        handleUnitsSelectionMenuEvents();
        break;
    case WindowState::Type::PAUSE_MENU:
        handlePauseMenuEvents();
        break;
    case WindowState::Type::UNKNOWN:
    default:
        break;
    }
}

bool Event::mouseClickLeft(const SDL_EventType clickType) {
    return e.type == clickType && e.button.button == SDL_BUTTON_LEFT;
}

bool Event::mouseClickRight() {
    return e.type == SDL_MOUSEBUTTONUP && e.button.button == SDL_BUTTON_RIGHT;
}

bool Event::raised(const Event::ID eid) {
    const Uint8* kstate = SDL_GetKeyboardState(NULL);
    return kstate[Window::controls[eid]];
}

void Event::raise(const Event::ID id) {
    switch (id) {
    case SET_WINDOW_TO_FULLSCREEN:
        Window::SetWindowMode(SDL_WINDOW_FULLSCREEN_DESKTOP);
        break;
    case SET_WINDOW_TO_DEFAULT:
        Window::SetWindowMode(0);
        break;
    case QUIT:
        Window::isRunning = false;
        break;
    
    case OPEN_MAIN_MENU:
        window->openMainMenu();
        break;
    
    case OPEN_GAME:
        window->openGame();
        break;  
    case SELECT_UNITS:
        window->openUnitsSelectionMenu();
        break;
    case VALID_UNITS_SELECTION:
        window->endUnitsSelection();
        break;

    case SELECT_HOUSE_SCHEMATIC:   
        Game::ActiveBuilder(Building::Type::HOUSE);
        break;
    case SELECT_TOWER_SCHEMATIC:
        Game::ActiveBuilder(Building::Type::TOWER);
        break;
    case SELECT_CASTLE_SCHEMATIC:
        Game::ActiveBuilder(Building::Type::CASTLE);
        break;

    case QUIT_GAME:
        window->quitGame();
        break; 

    case OPEN_OPTIONS:
        window->openOptionsMenu();
        break;
    case OPEN_GENERAL_SETTINGS:
        window->openGeneralOptions();
        break;
    case OPEN_CONTROLS_SETTINGS:
        window->openControlsOptions();
        break;
    
    case OPEN_CREDITS:
        window->openCredits();
        break;
    
    case RESUME_GAME:
        window->resumeGame();
        break;
    case SAVE_GAME:
        Save::Update();
        break;
    case PAUSE_GAME:
        window->pauseGame();
        break;
    default:
        break;
    }
}

void Event::handleMainMenuEvents() {
    if (e.type != SDL_KEYUP || !(SDL_GetModState() & KMOD_CTRL))
        return;

    switch (e.key.keysym.sym) {
    case SDLK_q:
        raise(QUIT);
        break;
    case SDLK_r:
        raise(OPEN_MAIN_MENU);
        break;
    case SDLK_g:
        raise(OPEN_GAME);
        break;
    case SDLK_o:
        raise(OPEN_OPTIONS);
        break;
    case SDLK_c:
        raise(OPEN_CREDITS);
        break;
    default:
        break;
    }
}

void Event::handleOptionsMenuEvents() {
    if (e.type != SDL_KEYUP || !(SDL_GetModState() & KMOD_CTRL))
        return;

    switch (e.key.keysym.sym) {
    case SDLK_q:
        raise(OPEN_MAIN_MENU);
        break;
    case SDLK_g:
        raise(OPEN_GENERAL_SETTINGS);
        break;
    case SDLK_c:
        raise(OPEN_CONTROLS_SETTINGS);
        break;
    default:
        break;
    }
}

void Event::handleCreditsEvents() {
    if (e.type != SDL_KEYUP || !(SDL_GetModState() & KMOD_CTRL))
        return;

    switch (e.key.keysym.sym) {
    case SDLK_q:
        raise(OPEN_MAIN_MENU);
        break;
    default:
        break;
    }
}

void Event::handleGameEvents() {
    if (e.type == SDL_MOUSEWHEEL) {
        if (e.wheel.y > 0)
            Game::camera.applyZoom(1);
        else if (e.wheel.y < 0)
            Game::camera.applyZoom(-1);
    }

    if (e.type == SDL_KEYUP) {
        switch (e.key.keysym.sym) {
        case SDLK_q:
            if (SDL_GetModState() & KMOD_CTRL)
                raise(QUIT_GAME);
            break;
        case SDLK_SPACE:
            Game::camera.centerOn(Game::playerFaction.getNearestCastle(Game::camera.pos / Tile::SIZE));
            break;
        case SDLK_ESCAPE:
            raise(PAUSE_GAME);
            break;
        default:
            break;
        }    
    }
}

void Event::handlePauseMenuEvents() {
    if (e.type != SDL_KEYUP)
        return;

    switch (e.key.keysym.sym) {
    case SDLK_ESCAPE:
        raise(RESUME_GAME);
        break;
    case SDLK_s:
        if (SDL_GetModState() & KMOD_CTRL)
            raise(SAVE_GAME);
        break;
    case SDLK_q:
        if (SDL_GetModState() & KMOD_CTRL)
            raise(QUIT_GAME);
        break;
    default:
        break;
    }
}

void Event::handleUnitsSelectionMenuEvents() {
    if (e.type != SDL_KEYUP) return;

    switch (e.key.keysym.sym) {
    case SDLK_ESCAPE:
        UnitsSelectionMenu::pawnSelector->count = 0;
        UnitsSelectionMenu::warriorSelector->count = 0;
        UnitsSelectionMenu::archerSelector->count = 0;
        raise(VALID_UNITS_SELECTION);
        break;
    case SDLK_RETURN:
        raise(VALID_UNITS_SELECTION);
    default:
        break;
    }
}
