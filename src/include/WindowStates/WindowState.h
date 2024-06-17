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
        STARTING_UNIT_SELECTION,
    };

    WindowState() {}
    ~WindowState() {}

    virtual void init() {}
    virtual void update() {}
    virtual void render() {}
    virtual void clean() {}

    virtual void reload() {}
};
