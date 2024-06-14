#include "include/Event.h"

#include "include/Window.h"
#include <iostream>

std::string to_string(const Event::ID eid) {
    /*
    switch (KeyMap::GetKeyCode(eid)) {
    case SDLK_a:
        return "A";
    case SDLK_b:
        return "B";
    case SDLK_c:
        return "C";
    case SDLK_d:
        return "D";
    case SDLK_e:
        return "E";
    case SDLK_f:
        return "F";
    case SDLK_g:
        return "G";
    case SDLK_h:
        return "H";
    case SDLK_i:
        return "I";
    case SDLK_j:
        return "J";
    case SDLK_k:
        return "K";
    case SDLK_l:
        return "L";
    case SDLK_m:
        return "M";
    case SDLK_n:
        return "N";
    case SDLK_o:
        return "O";
    case SDLK_p:
        return "P";
    case SDLK_q:
        return "Q";
    case SDLK_r:
        return "R";
    case SDLK_s:
        return "S";
    case SDLK_t:
        return "T";
    case SDLK_u:
        return "U";
    case SDLK_v:
        return "V";
    case SDLK_w:
        return "W";
    case SDLK_x:
        return "X";
    case SDLK_y:
        return "Y";
    case SDLK_z:
        return "Z";

    case SDLK_UP:
        return Text::Get("UP");
    case SDLK_DOWN:
        return Text::Get("DOWN");
    case SDLK_LEFT:
        return Text::Get("LEFT");
    case SDLK_RIGHT:
        return Text::Get("RIGHT");

    case SDLK_RALT:
    case SDLK_LALT:
        return "ALT";
    case SDLK_ESCAPE:
        return "ESC";
    case SDLK_RETURN:
        return Text::Get("ENTER");
    case SDLK_RCTRL:
        return "RCTRL";
    case SDLK_LCTRL:
        return "LCTRL";
    case SDLK_RSHIFT:
        return "RSHIFT";
    case SDLK_LSHIFT:
        return "LSHIFT";
    case SDLK_CAPSLOCK:
        return "CAPS";
    case SDLK_TAB:
        return "TAB";

    case SDLK_0:
        return "0";
    case SDLK_1:
        return "1";
    case SDLK_2:
        return "2";
    case SDLK_3:
        return "3";
    case SDLK_4:
        return "4";
    case SDLK_5:
        return "5";
    case SDLK_6:
        return "6";
    case SDLK_7:
        return "7";
    case SDLK_8:
        return "8";
    case SDLK_9:
        return "9";
    default:
        return "";
    }
    */
   return "";
}

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
    case WindowState::Type::PAUSE_MENU:
        handlePauseMenuEvents();
        break;
    case WindowState::Type::UNKNOWN:
    default:
        break;
    }
}

bool Event::mouseClickLeft() {
    return e.type == SDL_MOUSEBUTTONUP && e.button.button == SDL_BUTTON_LEFT;
}

bool Event::mouseClickRight() {
    return e.type == SDL_MOUSEBUTTONUP && e.button.button == SDL_BUTTON_RIGHT;
}

bool Event::raised(const Event::ID id) {
    return false; // KeyMap::Key[k] == id;
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
        //window->resumeGame();
        break;
    case PAUSE:
        //window->pauseGame();
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

void Event::handlePauseMenuEvents() {
    
}
