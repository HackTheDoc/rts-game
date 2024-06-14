#pragma once

#include "Components/Vector2D.h"

class Camera {
public:

    Vector2D pos;
    int width;
    int height;
    float zoom;

    Camera();
    ~Camera();

    void update();

    void applyZoom(const int s);

    void reset();

private:
    static const float SPEED;
    static const float ZOOM_SPEED;
    static const float ZOOM_MARGIN;
    static const float ZOOM_MIN;
    static const float ZOOM_MAX;
};
