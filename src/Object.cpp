#include "include/Game/Components/Object.h"

#include "include/struct.h"

Object::Object() {
    type = Type::UNKNOWN;
    position.Zero();
    width = 0;
    height = 0;
}

Object::~Object() {}

void Object::update() {}

void Object::draw() {}

void Object::destroy() {}

Struct::Object Object::getStructure() {
    return Struct::Object{Struct::UnknownObject{}};
}
