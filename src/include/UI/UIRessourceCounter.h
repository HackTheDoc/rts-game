#pragma once

#include "UIElement.h"
#include "UILabel.h"
#include "UIIcon.h"

class UIRessourceCounter : public UIElement {
public: 
    static const int WIDTH = 128;

    UIRessourceCounter(const std::string& r);
    ~UIRessourceCounter();

    void draw() override;
    void update() override;
    void destroy() override;

    void place(const int x, const int y);

private:
    int* ressource;

    UILabel* lbl;
    UIIcon* ico;
};