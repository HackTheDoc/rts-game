#include "include/Game/Buildings/Mine.h"

#include "include/Game/Game.h"
#include "include/Window.h"
#include "include/struct.h"

constexpr int GOLD_GATHERING_SPEED = 60 * 5;
constexpr int GOLD_GATHERING_AMOUNT = 5;

const int Mine::MAX_CAPACITY = 1000;

Mine::Mine(const Vector2D& pos) {
    type = MINE;
    
    position = pos;
    
    width = 3;
    height = 2;

    freeSpace = 0;

    miner = nullptr;
    isMinerWorking = false;

    entryPosition = pos + Vector2D{1,1};

    capacity = MAX_CAPACITY;

    texture = Window::manager->getTexture("mine inactive");

    level = new UILevelBar(GOLD_GATHERING_SPEED, 0, 256);
    
    lbl_capacity = new UILabel();

    addColliders();
}

Mine::~Mine() {}

void Mine::update() {
    Building::update();

    const std::string cstring = "Capacity: " + std::to_string(capacity) + "/" + std::to_string(Mine::MAX_CAPACITY);
    lbl_capacity->setText(cstring, "default bold", hue::font);
    lbl_capacity->place(
        rect.x + (rect.w - lbl_capacity->width()) / 2,
        rect.y
    );

    if (miner) updateWithMiner();
    else updateWithoutMiner();    

    if (!Cursor::enable) return;
    
    if (Builder::active) return;
    
    if (Game::CountSelectedEntities() > 0) return;

    if (!Game::cursor.inRect(&rect)) return;

    if (!Window::event.mouseClickLeft()) return;

    freeMiner();
}

void Mine::draw() {
    Building::draw();

    lbl_capacity->draw();

    if (!isMinerWorking) return;

    level->draw();
}

void Mine::freeMiner() {
    if (!miner) return;

    Vector2D pos = miner->position;

    if (isMinerWorking) {
        pos = entryPosition * Tile::SIZE;

        if (Game::IsTileOccupied(pos)) {
            std::cout << "tile " << pos << " occupied" << std::endl;
            return;
        }

        miner->placeAt(pos);
    
        miner->setState(Entity::State::FREE);
    
        Game::AddEntity(miner);

        isMinerWorking = false;
    }
    else miner->stopMovement();

    miner = nullptr;
}

void Mine::destroy() {
    if (miner && isMinerWorking)
        miner->kill();
    
    Building::destroy();
}

Struct::Building Mine::getStructure() {
    return {Struct::Mine{position}};
}

void Mine::updateWithMiner() {
    if (isMinerWorking) {
        texture = Window::manager->getTexture("mine active");

        level->update();
        level->place(
            rect.x + (rect.w - level->width()) / 2,
            rect.y + rect.h - Map::TileSize() / 3
        );
        
        if (level->isFinished()) {
            Game::playerFaction.storeGold(GOLD_GATHERING_AMOUNT, entryPosition);
            capacity -= GOLD_GATHERING_AMOUNT;
            level->setCurrentLevel(0);
        }
    }
    else if (miner->reachedDestination()) {
        if (miner->position == entryPosition*Tile::SIZE) {
            miner->setState(Entity::State::MINING);
            Game::RemoveEntity(miner);
            
            isMinerWorking = true;
            level->setCurrentLevel(0);
            level->active = true;
        }
        else miner = nullptr;
    }
    else if (miner->destination() != entryPosition) {
        miner = nullptr;
    }
}

void Mine::updateWithoutMiner() {
    texture = Window::manager->getTexture("mine inactive");
    
    if (Builder::active) return;

    if (Game::CountSelectedEntities() != 1) return;

    if (Game::GetSelectedEntity()->type != Entity::Type::PAWN) return;
    
    if (!Game::cursor.inRect(&rect)) return;
    
    if (!Window::event.mouseClickRight()) return;

    miner = Game::GetSelectedEntity();
    
    miner->goTo(entryPosition);

    isMinerWorking = false;
}
