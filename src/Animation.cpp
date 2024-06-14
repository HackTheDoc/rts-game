#include "include/Game/Components/Animation.h"
 
const int Animation::SPEED = 100; // 100 ms = 10 fps

Animation::Animation() : index(0), frames(0) {}

Animation::Animation(const int i, const int f) : index(i), frames(f) {}

Animation::~Animation() {}
