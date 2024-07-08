#include <iostream>

#include "include/Window.h"

Window window;

void run_window() {
    const int FPS = 60;
    const int FRAME_DELAY = 1000 / FPS;

    Uint32 frameStart;
    int frameTime;

    if (window.init() < 0)
        exit(EXIT_FAILURE);

    while (Window::isRunning) {
        frameStart = SDL_GetTicks();

        window.handleEvents();
        window.update();
        window.render();

        frameTime = SDL_GetTicks() - frameStart;
        if (frameTime < FRAME_DELAY)
            SDL_Delay(FRAME_DELAY - frameTime);
    }

    window.kill();

    exit(EXIT_SUCCESS);
}

#ifdef _WIN32

#include <windows.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    run_window();
    return 0;
}

#else

int main() {
    run_window();
    return 0;
}

#endif
