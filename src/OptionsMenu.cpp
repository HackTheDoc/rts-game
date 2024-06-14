#include "include/WindowStates/OptionsMenu.h"

#include "include/Save.h"
#include "include/Window.h"

OptionsMenu::OptionsMenu() {}

OptionsMenu::~OptionsMenu() {}

void OptionsMenu::createGeneralPage() {
    UIWindowModeSelector* wms = new UIWindowModeSelector();
    wms->place(
        (Window::screen.w - wms->width()) / 2,
        border.y + 32 * (Window::fullscreen + 1)
    );

    UIActivator* sma = new UIActivator("Save Mode:", &Save::Auto);
    sma->place(
        (Window::screen.w - sma->width()) / 2,
        wms->y() + wms->height() + 32 * (Window::fullscreen + 1)
    );

    page["general"] = {
        {"wms", wms},
        {"sma", sma},
    };
}

void OptionsMenu::reloadGeneralPage() {
    UIWindowModeSelector* wms = static_cast<UIWindowModeSelector*>(page["general"]["wms"]);
    wms->reload();
    wms->place(
        (Window::screen.w - wms->width()) / 2,
        border.y + 32 * (Window::fullscreen + 1)
    );

    UIActivator* sma = static_cast<UIActivator*>(page["general"]["sma"]);
    sma->reload();
    sma->place(
        (Window::screen.w - sma->width()) / 2,
        wms->y() + wms->height() + 32 * (Window::fullscreen + 1)
    );
}

void OptionsMenu::createControlsPage() {

}

void OptionsMenu::reloadControlsPage() {

}

void OptionsMenu::init() {
    btn_generalSection = new UIButton("GENERAL", Event::ID::OPEN_GENERAL_SETTINGS, "h3", hue::font);
    btn_generalSection->place(
        (Window::screen.w / 2 - btn_generalSection->width()) / 2,
        8 * (Window::fullscreen + 1)
    );

    btn_controlsSection = new UIButton("CONTROLS", Event::ID::OPEN_CONTROLS_SETTINGS, "h3", hue::font);
    btn_controlsSection->place(
        (3 * Window::screen.w / 2 - btn_controlsSection->width()) / 2,
        8 * (Window::fullscreen + 1)
    );

    btn_quit = new UIButton("X", Event::ID::OPEN_MAIN_MENU, "h3", hue::font);
    btn_quit->place(
        Window::screen.w - btn_quit->width() - 8 * (Window::fullscreen + 1),
        8 * (Window::fullscreen + 1)
    );

    border = {
        0,
        8 * (Window::fullscreen + 1) + std::max(btn_generalSection->height(), btn_controlsSection->height()),
        Window::screen.w,
        3 * (Window::fullscreen + 1)
    };

    createGeneralPage();
    createControlsPage();

    usePage("general");
}

void OptionsMenu::update() {
    btn_generalSection->update();
    btn_controlsSection->update();
    btn_quit->update();

    for (const auto& elt : page[currentPage])
        elt.second->update();
}

void OptionsMenu::render() {
    Manager::DrawFilledRect(&Window::screen, hue::background);

    btn_generalSection->draw();
    btn_controlsSection->draw();
    btn_quit->draw();

    Manager::DrawFilledRect(&border, hue::border);

    for (const auto& elt : page[currentPage])
        elt.second->draw();
}

void OptionsMenu::clean() {
    btn_generalSection->destroy();
    btn_controlsSection->destroy();
    btn_quit->destroy();

    for (auto p : page) {
        for (auto elt : p.second)
            elt.second->destroy();
        p.second.clear();
    }
    page.clear();
}

void OptionsMenu::reload() {
    btn_generalSection->setText("GENERAL", "h3", hue::white);
    btn_generalSection->place(
        (Window::screen.w / 2 - btn_generalSection->width()) / 2,
        8 * (Window::fullscreen + 1)
    );

    btn_controlsSection->setText("CONTROLS", "h3", hue::white);
    btn_controlsSection->place(
        (3 * Window::screen.w / 2 - btn_controlsSection->width()) / 2,
        8 * (Window::fullscreen + 1)
    );

    btn_quit->setText("X", "h3", hue::white);
    btn_quit->place(
        Window::screen.w - btn_quit->width() - 8 * (Window::fullscreen + 1),
        8 * (Window::fullscreen + 1)
    );

    border = {
        0,
        8 * (Window::fullscreen + 1) + std::max(btn_generalSection->height(), btn_controlsSection->height()),
        Window::screen.w,
        3 * (Window::fullscreen + 1)
    };

    reloadGeneralPage();
    reloadControlsPage();
}

void OptionsMenu::usePage(const std::string& p) {
    currentPage = p;
}
