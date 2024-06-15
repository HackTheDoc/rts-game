#include "include/Game/Components/Sprite.h"

#include "include/Window.h"
#include "include/Game/Game.h"

Sprite::Sprite(Entity* o) {
    linkTo(o);
    texture = nullptr;
    spriteFlip = SDL_FLIP_NONE;
    srcRect = destRect = { 0,0,0,0 };
    frames = animationIndex = 0;
}

Sprite::~Sprite() {}

void Sprite::init(const std::string& tag, const int numberOfAnimations) {
    srcRect = { 0, 0, 192, 192 };

    destRect.w = owner->width;
    destRect.h = owner->height;

    setSprite(tag);

    if (numberOfAnimations < 0) {
        animated = false;
        return;
    }

    animated = true;
    Animation animation;
    for (int i = 0; i < numberOfAnimations; i++) {
        switch (i) {
        case 0: // idle
            animation = Animation(0, 6);
            animations.emplace("idle", animation);
            break;
        case 1: // walk
            animation = Animation(1, 6);
            animations.emplace("walk", animation);
            break;
        case 2: // building
            animation = Animation(2, 6);
            animations.emplace("build", animation);
            break;
        case 3: // cutting wood
            animation = Animation(3, 6);
            animations.emplace("attack", animation);
            break;
        case 4: // holding idle
            animation = Animation(4, 6);
            animations.emplace("holding idle", animation);
            break;
        case 5: // holding walk
            animation = Animation(5, 6);
            animations.emplace("holding walk", animation);
            break;
        default:
            break;
        }
    }

    play("idle");
}

void Sprite::update() {
    if (animated) {
        int currentFrame = (int)((SDL_GetTicks64() / Animation::SPEED) % frames);
        srcRect.x = srcRect.w * currentFrame + owner->selected * frames * srcRect.w;
        srcRect.y = animationIndex * srcRect.h;
    }

    destRect.x = (owner->position.x - Tile::SIZE) * Game::camera.zoom - Game::camera.pos.x;
    destRect.y = (owner->position.y - Tile::SIZE) * Game::camera.zoom - Game::camera.pos.y;

    destRect.w = owner->width * Game::camera.zoom;
    destRect.h = owner->height * Game::camera.zoom;
}

void Sprite::draw() {
    Manager::Draw(texture, &srcRect, &destRect, spriteFlip);
}

void Sprite::destroy() {
    texture = nullptr;
}

void Sprite::setSprite(const std::string& tag) {
    texture = Window::manager->getTexture(tag);
}

void Sprite::play(const std::string& animationName) {
    if (!animated) return;

    currentAnimation = animationName;
    frames = animations[animationName].frames;
    animationIndex = animations[animationName].index;
}

void Sprite::linkTo(Entity* o) {
    owner = o;
}

void Sprite::useFrame(const int y, const int x) {
    srcRect.x = srcRect.w * x;
    srcRect.y = srcRect.h * y;
}

void Sprite::drawSelection() {
    SDL_Texture* t = Window::manager->getTexture("selection");
    Manager::Draw(t, nullptr, &destRect);
}
