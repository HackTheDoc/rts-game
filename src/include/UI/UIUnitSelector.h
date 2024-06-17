#pragma once

#include "UIElement.h"
#include "../Game/Entities/Entity.h"

#include "UIIcon.h"
#include "UILabel.h"
#include "UITextBox.h"

class UIUnitSelector : public UIElement {
public:
    int count;

    UIUnitSelector(const Entity::Type etype, int* available);
    ~UIUnitSelector();
    
    virtual void draw();
    virtual void update();
    virtual void destroy();

    void place(const int x, const int y);

private:
    UIIcon* ico;
    UILabel* lbl;
    UITextBox* minus;
    UITextBox* plus;

    int* available;

    void decreaseCounter();
    void increaseCounter();
};
