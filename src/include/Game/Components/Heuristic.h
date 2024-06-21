#pragma once

#include <functional>

#include "Vector2D.h"

using uint = unsigned int;
using HeuristicFunction = std::function<uint(Vector2D, Vector2D)>;

class Heuristic {
public:
    static uint manhattan(Vector2D source_, Vector2D target_);
    static uint euclidean(Vector2D source_, Vector2D target_);
    static uint octagonal(Vector2D source_, Vector2D target_);

private:
    static Vector2D getDelta(Vector2D source_, Vector2D target_);
};