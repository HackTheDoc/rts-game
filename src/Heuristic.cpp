#include "include/Game/Components/Heuristic.h"

#include <math.h>

Vector2D Heuristic::getDelta(Vector2D source_, Vector2D target_) {
    return{ abs(source_.x - target_.x),  abs(source_.y - target_.y) };
}

uint Heuristic::manhattan(Vector2D source_, Vector2D target_) {
    auto delta = std::move(getDelta(source_, target_));
    return static_cast<uint>(10 * (delta.x + delta.y));
}

uint Heuristic::euclidean(Vector2D source_, Vector2D target_) {
    auto delta = std::move(getDelta(source_, target_));
    return static_cast<uint>(10 * sqrt(pow(delta.x, 2) + pow(delta.y, 2)));
}

uint Heuristic::octagonal(Vector2D source_, Vector2D target_) {
    auto delta = std::move(getDelta(source_, target_));
    return 10 * (delta.x + delta.y) + (-6) * std::min(delta.x, delta.y);
}
