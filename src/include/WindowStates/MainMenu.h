#pragma once

#include "WindowState.h"

#include "../UI/UIElements.h"

class MainMenu : public WindowState {
public:
    MainMenu();
    ~MainMenu();

    void init() override;
    void update() override;
    void render() override;
    void clean() override;

private:
    UILabel* lbl_title;
    UILabel* lbl_version;

    UIButton* btn_play;
    UIButton* btn_options;
    UIButton* btn_credits;
    UIButton* btn_quit;
};
