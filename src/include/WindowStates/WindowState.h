#pragma once

class WindowState {
public:
    enum Type {
        UNKNOWN,

        MAIN,
        
        PLAY_MENU,
        OPTIONS_MENU,
        CREDITS,
        
        GAME,
        PAUSE_MENU,
        UNITS_SELECTION_MENU,
    };

    WindowState() {}
    ~WindowState() {}

    virtual void init() {}
    virtual void update() {}
    virtual void render() {}
    virtual void clean() {}

    virtual void reload() {}
};
