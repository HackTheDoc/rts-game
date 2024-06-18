#include "include/Game/Game.h"

#include "include/Window.h"
#include "include/Save.h"

AStar::Generator Game::generator;

Camera Game::camera;
Cursor Game::cursor;

UI* Game::ui = nullptr;

Faction Game::playerFaction;

Map* Game::map = nullptr;
std::vector<Entity*> Game::selectedEntities{};

Game::Game() {}

Game::~Game() {}

void Game::init() {
    Window::manager->loadGameTextures();

    Manager::SetRenderDrawColor(hue::water);

    camera.width = Window::screen.w;
    camera.height = Window::screen.h;

    const Struct::Game g = Save::Load();

    playerFaction = Faction(g.faction.name, g.faction.food, g.faction.gold, g.faction.wood);

    camera.load(g.camera);

    map = new Map();
    map->init(g.map);

    // init pathfinder generator
    generator.setHeuristic(&AStar::Heuristic::euclidean);
    generator.setDiagonalMovement(true);
    generator.setWorldSize({map->width(), map->height()});
    
    std::vector<std::vector<bool>> col_map = map->getCollisionMap();
    for (int y = 0; y < map->height(); y++) {
        for (int x = 0; x < map->width(); x++) {
            std::cout << col_map[y][x];
            if (col_map[y][x] == true)
                generator.addCollision(Vector2D{x,y});
            }
        std::cout << std::endl;
    }

    ui = new UI();
    ui->init();

    if (Save::New)
        camera.centerOn(playerFaction.castles[0]);
}

void Game::update() {
    camera.update();
    cursor.update();

    map->update();

    ui->update();
}

void Game::render() {
    map->render();
    cursor.draw();

    ui->display();
}

void Game::clean() {
    camera.reset();
    cursor.reset();
    
    map->destroy();
    delete map;
    map = nullptr;

    ui->destroy();
    delete ui;
    ui = nullptr;

    Window::manager->clearGameTextures();

    Manager::SetRenderDrawColor(hue::background);
}

void Game::ReleaseSelectedEntities() {
    for (Entity* e : selectedEntities)
        e->selected = false;
    selectedEntities.clear();
}

void Game::SelectEntities() {
    if (!Window::event.raised(Event::ID::SELECT_MULTIPLE))
        Game::ReleaseSelectedEntities();

    // format selection rect
    SDL_Rect r = cursor.selectionRect;
    if (cursor.selectionRect.w < 0) {
        r.x = cursor.selectionRect.x + cursor.selectionRect.w;
        r.w = -cursor.selectionRect.w;
    }
    if (cursor.selectionRect.h < 0) {
        r.y = cursor.selectionRect.y + cursor.selectionRect.h;
        r.h = -cursor.selectionRect.h;
    }
        
    std::vector<Entity*> newlySelectedEntities = map->getEntitiesInRect(r);
    for (Entity* e :  newlySelectedEntities) {
        e->selected = true;
        selectedEntities.push_back(e);
    }
}

void Game::SelectEntityAt(const Vector2D* pos) {
    if (!Window::event.raised(Event::ID::SELECT_MULTIPLE))
        Game::ReleaseSelectedEntities();

    std::optional<Entity*> e = map->getEntitiesAt(pos);
    
    if (e.has_value()) {
        e.value()->selected = true;
        selectedEntities.push_back(e.value());
    }

}

void Game::AddStartingEntities(const int pawnCount, const int warriorCount, const int archerCount) {
    const Vector2D castlePos = playerFaction.castles[0]->getPosition();
    const std::array<Vector2D, 4> pos{
        castlePos + Vector2D{1*Tile::SIZE, 3*Tile::SIZE},
        castlePos + Vector2D{3*Tile::SIZE, 3*Tile::SIZE},
        castlePos + Vector2D{0*Tile::SIZE, 3*Tile::SIZE},
        castlePos + Vector2D{4*Tile::SIZE, 3*Tile::SIZE}
    };

    int i = 0;

    while (i < pawnCount) {
        map->addPawn(playerFaction.name, pos[i]);
        i++;
    }
    
    while (i < pawnCount+warriorCount) {
        map->addWarrior(playerFaction.name, pos[i]);
        i++;
    }
    
    while (i < pawnCount+warriorCount+archerCount) {
        map->addArcher(playerFaction.name, pos[i]);
        i++;
    }
}

Struct::Game Game::GetStructure() {
    return {camera.getStructure(), map->getStructure(), playerFaction.getstructure()};
}

std::vector<Vector2D> Game::FindPath(const Vector2D& start, const Vector2D& end) {
    auto path = generator.findPath(start, end);
    std::cout << "from" << start << " to " << end << std::endl;
    for(auto& coordinate : path)
        std::cout << coordinate << std::endl;
    return path;
}
