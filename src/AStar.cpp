#include "include/Game/Components/AStar.h"
#include <algorithm>

using namespace std::placeholders;

/* ----- NODE ----- */
AStar::Node::Node(Vector2D coordinates_, Node *parent_) {
    parent = parent_;
    coordinates = coordinates_;
    G = H = 0;
}

uint AStar::Node::getScore() {
    return G + H;
}

/* ----- GENERATOR ----- */

AStar::Generator::Generator() {
    setDiagonalMovement(false);
    setHeuristic(&Heuristic::manhattan);
    direction = {
        { 0, 1 }, { 1, 0 }, { 0, -1 }, { -1, 0 },
        { -1, -1 }, { 1, 1 }, { -1, 1 }, { 1, -1 }
    };
}

void AStar::Generator::setWorldSize(Vector2D worldSize_) {
    worldSize = worldSize_;
}

void AStar::Generator::setDiagonalMovement(bool enable_) {
    directions = (enable_ ? 8 : 4);
}

void AStar::Generator::setHeuristic(HeuristicFunction heuristic_) {
    heuristic = std::bind(heuristic_, _1, _2);
}

void AStar::Generator::addCollision(Vector2D coordinates_) {
    walls.push_back(coordinates_);
}

void AStar::Generator::removeCollision(Vector2D coordinates_) {
    auto it = std::find(walls.begin(), walls.end(), coordinates_);
    if (it != walls.end())
        walls.erase(it);
}

void AStar::Generator::clearCollisions() {
    walls.clear();
}

bool AStar::Generator::hasCollision(Vector2D pos) {
    auto it = std::find_if(walls.begin(), walls.end(), [&pos](const Vector2D& w) {
        return pos == w;
    });

    return it == walls.end();
}

AStar::CoordinateList AStar::Generator::findPath(Vector2D source_, Vector2D target_) {
    Node* current = nullptr;
    NodeSet openSet, closedSet;
    openSet.reserve(100);
    closedSet.reserve(100);
    openSet.push_back(new Node(source_));

    while (!openSet.empty()) {
        auto current_it = openSet.begin();
        current = *current_it;

        for (auto it = openSet.begin(); it != openSet.end(); it++) {
            auto node = *it;
            if (node->getScore() < current->getScore()) {
                current = node;
                current_it = it;
            }
        }

        if (current->coordinates == target_) {
            break;
        }

        closedSet.push_back(current);
        openSet.erase(current_it);

        for (uint i = 0; i < directions; i++) {
            Vector2D newCoordinates = current->coordinates + direction[i];
            if (detectCollision(newCoordinates) ||
                findNodeOnList(closedSet, newCoordinates)) {
                continue;
            }

            uint totalCost = current->G + ((i < 4) ? 10 : 14);

            Node* successor = findNodeOnList(openSet, newCoordinates);
            if (successor == nullptr) {
                successor = new Node(newCoordinates, current);
                successor->G = totalCost;
                successor->H = heuristic(successor->coordinates, target_);
                openSet.push_back(successor);
            }
            else if (totalCost < successor->G) {
                successor->parent = current;
                successor->G = totalCost;
            }
        }
    }

    CoordinateList path;
    while (current != nullptr) {
        path.push_back(current->coordinates);
        current = current->parent;
    }

    releaseNodes(openSet);
    releaseNodes(closedSet);

    return path;
}

AStar::Node* AStar::Generator::findNodeOnList(NodeSet& nodes_, Vector2D coordinates_) {
    for (auto node : nodes_) {
        if (node->coordinates == coordinates_) {
            return node;
        }
    }
    return nullptr;
}

void AStar::Generator::releaseNodes(NodeSet& nodes_) {
    for (auto it = nodes_.begin(); it != nodes_.end();) {
        delete *it;
        it = nodes_.erase(it);
    }
}

bool AStar::Generator::detectCollision(Vector2D coordinates_) {
    if (coordinates_.x < 0 || coordinates_.x >= worldSize.x ||
        coordinates_.y < 0 || coordinates_.y >= worldSize.y ||
        std::find(walls.begin(), walls.end(), coordinates_) != walls.end()) {
        return true;
    }
    return false;
}
