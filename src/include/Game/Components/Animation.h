#pragma once

class Animation {
public:
    static const int SPEED;
    
    int index;
    int frames;

    Animation();
    Animation(const int i, const int f);
    ~Animation();
};
    