#pragma once

#include "Components/Vector2D.h"

namespace Struct {
    struct Camera;
} // namespace Struct

class Building;

class Camera {
public:
    float zoom;
    Vector2D pos;
    int width;
    int height;

    Camera();
    ~Camera();

    void load(const Struct::Camera& c);

    void update();

    void applyZoom(const int s);

    void reset();

    void centerOn(Building* b);

    Struct::Camera getStructure();

private:
    static const float SPEED;
    static const float ZOOM_SPEED;
    static const float ZOOM_MARGIN;
    static const float ZOOM_MIN;
    static const float ZOOM_MAX;
};
