#pragma once

#include "Heuristic.h"

#include <vector>
#include <set>

namespace AStar {
    using CoordinateList = std::vector<Vector2D>;

    struct Node {
        uint G, H;
        Vector2D coordinates;
        Node* parent;

        Node(Vector2D coord_, Node *parent_ = nullptr);
        uint getScore();
    };

    using NodeSet = std::vector<Node*>;

    class Generator {
    public:
        Generator();
        void setWorldSize(Vector2D worldSize_);
        void setDiagonalMovement(bool enable_);
        void setHeuristic(HeuristicFunction heuristic_);
        CoordinateList findPath(Vector2D source_, Vector2D target_);
        void addCollision(Vector2D coordinates_);
        bool detectCollision(Vector2D coordinates_);
        void removeCollision(Vector2D coordinates_);
        void clearCollisions();
        bool hasCollision(Vector2D pos);

    private:
        HeuristicFunction heuristic;
        CoordinateList direction, walls;
        Vector2D worldSize;
        uint directions;

        Node* findNodeOnList(NodeSet& nodes_, Vector2D coordinates_);
        void releaseNodes(NodeSet& nodes_);
    };
}
