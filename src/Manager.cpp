#include "include/Manager.h"

#include "include/Window.h"

#include "include/Game/Components/Vector2D.h"
#include "include/Game/Map/Tile.h"

#include <vector>
#include <sstream>
#include <iostream>

Manager::Manager() {
    // Fonts
    loadFonts();

    // Window States
    currentWindowState = WindowState::Type::UNKNOWN;
}

Manager::~Manager() {
    clearFonts();
    clearGameTextures();
    clearWindowStates();
}

SDL_Color Manager::SetRenderDrawColor(const SDL_Color& c) {
    SDL_Color t;
    SDL_GetRenderDrawColor(Window::renderer, &t.r, &t.g, &t.b, &t.a);

    SDL_SetRenderDrawColor(Window::renderer, c.r, c.g, c.b, c.a);

    return t;
}

void Manager::SetViewport(const SDL_Rect* v) {
    SDL_RenderSetViewport(Window::renderer, v);
}

void Manager::SetScale(const float sw, const float sh) {
    SDL_RenderSetScale(Window::renderer, sw, sh);
}

/* ---------- FONT MANAGER ---------- */

TTF_Font* Manager::getFont(const std::string& id) {
    if (fonts.count(id) == 0)
        return nullptr;
    return fonts[id];
}

void Manager::loadFonts() {
    if (Window::fullscreen) {
        float sc = (float)Window::screen.w / 1280.0;

        fonts["h1"] = TTF_OpenFont("./assets/font/Oxanium-Regular.ttf", 160 * sc);
        fonts["h2"] = TTF_OpenFont("./assets/font/Oxanium-Regular.ttf", 120 * sc);
        fonts["h2 bold"] = TTF_OpenFont("./assets/font/Oxanium-Bold.ttf", 120 * sc);
        fonts["h3"] = TTF_OpenFont("./assets/font/Oxanium-Regular.ttf", 76 * sc);
        fonts["h3 bold"] = TTF_OpenFont("./assets/font/Oxanium-Bold.ttf", 76 * sc);
        fonts["h4"] = TTF_OpenFont("./assets/font/Oxanium-Regular.ttf", 64 * sc);
        fonts["h4 bold"] = TTF_OpenFont("./assets/font/Oxanium-Bold.ttf", 64 * sc);

        fonts["big"] = TTF_OpenFont("./assets/font/Oxanium-Regular.ttf", 48 * sc);
        fonts["big bold"] = TTF_OpenFont("./assets/font/Oxanium-Bold.ttf", 48 * sc);
        fonts["default"] = TTF_OpenFont("./assets/font/Oxanium-Regular.ttf", 32 * sc);
        fonts["default bold"] = TTF_OpenFont("./assets/font/Oxanium-Bold.ttf", 32 * sc);
        fonts["small"] = TTF_OpenFont("./assets/font/Oxanium-Regular.ttf", 16 * sc);
    }
    else {
        fonts["h1"] = TTF_OpenFont("./assets/font/Oxanium-Regular.ttf", 160);
        fonts["h2"] = TTF_OpenFont("./assets/font/Oxanium-Regular.ttf", 120);
        fonts["h2 bold"] = TTF_OpenFont("./assets/font/Oxanium-Bold.ttf", 120);
        fonts["h3"] = TTF_OpenFont("./assets/font/Oxanium-Regular.ttf", 76);
        fonts["h3 bold"] = TTF_OpenFont("./assets/font/Oxanium-Bold.ttf", 76);
        fonts["h4"] = TTF_OpenFont("./assets/font/Oxanium-Regular.ttf", 64);
        fonts["h4 bold"] = TTF_OpenFont("./assets/font/Oxanium-Bold.ttf", 64);

        fonts["big"] = TTF_OpenFont("./assets/font/Oxanium-Regular.ttf", 48);
        fonts["big bold"] = TTF_OpenFont("./assets/font/Oxanium-Bold.ttf", 48);
        fonts["default"] = TTF_OpenFont("./assets/font/Oxanium-Regular.ttf", 32);
        fonts["default bold"] = TTF_OpenFont("./assets/font/Oxanium-Bold.ttf", 32);
        fonts["small"] = TTF_OpenFont("./assets/font/Oxanium-Regular.ttf", 16);
    }
}

void Manager::clearFonts() {
    for (auto f : fonts)
        TTF_CloseFont(f.second);
    fonts.clear();
}

void Manager::reloadFonts() {
    clearFonts();
    loadFonts();
}

/* ---------- TEXTURE MANAGER ---------- */

SDL_Texture* Manager::getTexture(const std::string& id) {
    if (textures.count(id) == 0)
        return nullptr;
    return textures[id];
}

void Manager::loadGameTextures() {
    /* ----- TILESETS ----- */

    textures["foam"] = LoadTexture("assets/terrain/foam.png");

    textures["ground"] = LoadTexture("assets/terrain/ground_tilesheet.png");
    textures["stone"] = LoadTexture("assets/terrain/stone_tilesheet.png");

    /* ----- SPRITESHEETS ----- */

    textures["sheep"] = LoadTexture("assets/ressources/food/sheep_spritesheet.png");
    textures["tree"] = LoadTexture("assets/ressources/wood/tree.png");

    textures["white pawn"] = LoadTexture("assets/troops/white/pawn.png");
    textures["white warrior"] = LoadTexture("assets/troops/white/warrior.png");
    textures["white archer"] = LoadTexture("assets/troops/white/archer.png");

    textures["blue pawn"] = LoadTexture("assets/troops/blue/pawn.png");
    textures["blue warrior"] = LoadTexture("assets/troops/blue/warrior.png");
    textures["blue archer"] = LoadTexture("assets/troops/blue/archer.png");
    
    textures["red pawn"] = LoadTexture("assets/troops/red/pawn.png");
    textures["red warrior"] = LoadTexture("assets/troops/red/warrior.png");
    textures["red archer"] = LoadTexture("assets/troops/red/archer.png");
    
    textures["yellow pawn"] = LoadTexture("assets/troops/yellow/pawn.png");
    textures["yellow warrior"] = LoadTexture("assets/troops/yellow/warrior.png");
    textures["yellow archer"] = LoadTexture("assets/troops/yellow/archer.png");
    
    textures["purple pawn"] = LoadTexture("assets/troops/purple/pawn.png");
    textures["purple warrior"] = LoadTexture("assets/troops/purple/warrior.png");
    textures["purple archer"] = LoadTexture("assets/troops/purple/archer.png");

    /* ----- BUILDINGS ----- */
    
    textures["unit selector indicator"] = LoadTexture("assets/buildings/unit_selector_indicator.png");
    
    textures["white castle"] = LoadTexture("assets/buildings/white/castle.png");
    textures["white tower"] = LoadTexture("assets/buildings/white/tower.png");
    textures["white house"] = LoadTexture("assets/buildings/white/house.png");

    textures["construction castle"] = LoadTexture("assets/buildings/construction/castle.png");
    textures["construction tower"] = LoadTexture("assets/buildings/construction/tower.png");
    textures["construction house"] = LoadTexture("assets/buildings/construction/house.png");

    textures["mine active"] = LoadTexture("assets/ressources/gold/active.png");
    textures["mine inactive"] = LoadTexture("assets/ressources/gold/inactive.png");
    textures["mine destroyed"] = LoadTexture("assets/ressources/gold/destroyed.png");

    /* ----- ICONS ----- */

    textures["unit icons"] = LoadTexture("assets/icons/troops.png");
    textures["buildings icons"] = LoadTexture("assets/icons/buildings.png");
    textures["ressources icons"] = LoadTexture("assets/icons/ressources.png");
}

void Manager::clearGameTextures() {
    for (auto t : textures)
        SDL_DestroyTexture(t.second);
    textures.clear();
}

SDL_Texture* Manager::LoadTexture(const char* filepath) {
    SDL_Surface* tmpSurface = IMG_Load(filepath);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(Window::renderer, tmpSurface);
    SDL_FreeSurface(tmpSurface);

    return texture;
}

SDL_Texture* Manager::GenerateText(const std::string& text, const std::string& font, const SDL_Color& color, const int length, const bool centered) {
    if (centered)
        return GenerateCenterAnchoredText(text, font, color, length);
    else
        return GenerateLeftAnchoredText(text, font, color, length);
}

SDL_Texture* Manager::GenerateLeftAnchoredText(const std::string& text, const std::string& font, const SDL_Color& color, const int length) {
    TTF_Font* f = Window::manager->getFont(font);

    if (f == nullptr) return nullptr;

    SDL_Surface* tmpSurface = TTF_RenderUTF8_Blended_Wrapped(f, text.c_str(), color, length);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(Window::renderer, tmpSurface);
    SDL_FreeSurface(tmpSurface);
    return texture;
}

SDL_Texture* Manager::GenerateCenterAnchoredText(const std::string& text, const std::string& f, const SDL_Color& color, const int length) {
    TTF_Font* font = Window::manager->getFont(f);

    if (font == nullptr) return nullptr;

    // add new line where needed
    const int fontHeight = TTF_FontHeight(font);
    int spaceWidth;
    TTF_GlyphMetrics(font, ' ', nullptr, nullptr, nullptr, nullptr, &spaceWidth);

    int totalWidth = 0;
    int totalHeight = 0;
    int currWidth = 0;
    std::stringstream ss;

    std::stringstream rawss(text);
    std::string l;
    while (std::getline(rawss, l, '\n')) {
        std::stringstream lss(l);
        std::string w;
        while (std::getline(lss, w, ' ')) {
            currWidth += spaceWidth;

            int wordWidth;
            TTF_SizeText(font, w.c_str(), &wordWidth, nullptr);

            if (currWidth + wordWidth > length) {
                totalWidth = std::max(totalWidth, currWidth);
                totalHeight += fontHeight;
                ss << '\n';
                currWidth = 0;
            }

            ss << w << ' ';
            currWidth += wordWidth;
        }
        ss << '\n';
    }

    if (currWidth > 0) totalHeight += fontHeight;

    // generate the actual surface
    SDL_Surface* tmpSurface = SDL_CreateRGBSurfaceWithFormat(0, totalWidth+spaceWidth, totalHeight, 32, SDL_PIXELFORMAT_RGBA8888);
    if (tmpSurface == nullptr) return nullptr;
    SDL_SetSurfaceBlendMode(tmpSurface, SDL_BLENDMODE_BLEND);

    int currY = 0;
    ss.clear();
    ss.seekg(0);

    while (std::getline(ss, l, '\n')) {
        SDL_Surface* lSurface = TTF_RenderUTF8_Blended(font, l.c_str(), color);
        if (lSurface == nullptr) continue;

        SDL_Rect r = { (tmpSurface->w - lSurface->w) / 2, currY, lSurface->w, lSurface->h };
        SDL_UpperBlitScaled(lSurface, nullptr, tmpSurface, &r);

        SDL_FreeSurface(lSurface);

        currY += lSurface->h;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(Window::renderer, tmpSurface);
    SDL_FreeSurface(tmpSurface);
    return texture;
}

void Manager::Draw(SDL_Texture* text, const SDL_Rect* src, const SDL_Rect* dest, SDL_RendererFlip flip) {
    if (text == nullptr) return;
    SDL_RenderCopyEx(Window::renderer, text, src, dest, 0, NULL, flip);
}

void Manager::DrawRect(const SDL_Rect* rect, const SDL_Color& color) {
    SDL_Color temp = SetRenderDrawColor(color);

    SDL_RenderDrawRect(Window::renderer, rect);

    SetRenderDrawColor(temp);
}

void Manager::DrawFilledRect(const SDL_Rect* rect, const SDL_Color& color) {
    SDL_Color temp = SetRenderDrawColor(color);

    SDL_RenderFillRect(Window::renderer, rect);

    SetRenderDrawColor(temp);
}

void Manager::DrawLine(const int x1, const int y1, const int x2, const int y2, const SDL_Color& color) {
    SDL_Color temp = SetRenderDrawColor(color);

    SDL_RenderDrawLine(Window::renderer, x1, y1, x2, y2);

    SetRenderDrawColor(temp);
}

/* ---------- WINDOW STATES MANAGER ---------- */

void Manager::addWindowState(const WindowState::Type id, WindowState* ws) {
    windowStates.emplace(id, ws);
    windowStates[id]->init();
    
    if (id == WindowState::Type::GAME)
        windowStates[id]->update();
}

void Manager::removeWindowState(const WindowState::Type id) {
    if (windowStates.count(id) == 0)
        return;

    windowStates[id]->clean();
    windowStates.erase(id);
    currentWindowState = previousWindowState;
}

void Manager::setCurrentWindowState(const WindowState::Type id) {
    previousWindowState = currentWindowState;
    currentWindowState = id;
}

void Manager::updateCurrentWindowState() {
    if (currentWindowState > WindowState::Type::GAME + 1)
        windowStates[WindowState::Type::GAME]->update();
    windowStates[currentWindowState]->update();
}

void Manager::renderCurrentWindowState() {
    if (currentWindowState > WindowState::Type::GAME)
        windowStates[WindowState::Type::GAME]->render();
    windowStates[currentWindowState]->render();
}

void Manager::clearWindowStates() {
    for (auto ws : windowStates) {
        ws.second->clean();
    }
    windowStates.clear();

    previousWindowState = WindowState::Type::UNKNOWN;
    currentWindowState = WindowState::Type::UNKNOWN;
}

WindowState* Manager::getState(const WindowState::Type id) {
    if (windowStates.count(id) == 0)
        return nullptr;
    return windowStates[id];
}

WindowState* Manager::getCurrentState() {
    return windowStates[currentWindowState];
}

WindowState::Type Manager::getCurrentStateID() {
    return currentWindowState;
}
