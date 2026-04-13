#include "gameglobale.h"
#include "Level.h"

static void addPlatform(Level& level, float x, float y, float width, float height, sf::Color color) {
    int i = level.platformCount;
    level.platforms[i].position = {x, y};
    level.platforms[i].size     = {width, height};
    level.platforms[i].color    = color;
    level.platformCount++;
}

void loadLevel(Level& level, int levelId) {
    level.platformCount = 0;
    // level.width  = 1280.f;
    // level.height = 720.f;

    sf::Color ground = sf::Color(80,  80,  90);
    sf::Color mid    = sf::Color(100, 110, 130);

    if (levelId == 1) {
        addPlatform(level, 0,    680, 1280, 40, ground); // floor
        addPlatform(level, 0,    0,   20,  720, ground); // left wall
        addPlatform(level, 1260, 0,   20,  720, ground); // right wall
        addPlatform(level, 490,  400, 300, 20,  mid);    // center
        addPlatform(level, 150,  520, 200, 20,  mid);    // left mid
        addPlatform(level, 930,  520, 200, 20,  mid);    // right mid
        addPlatform(level, 200,  280, 160, 20,  mid);    // high left
        addPlatform(level, 920,  280, 160, 20,  mid);    // high right

        level.spawnPoints[0] = {120.f,  620.f};
        level.spawnPoints[1] = {400.f,  620.f};
        level.spawnPoints[2] = {780.f,  620.f};
        level.spawnPoints[3] = {1060.f, 620.f};
    }
}

void resetLevel(Level& level, int levelId) {
    loadLevel(level, levelId);
}

Vec2 getSpawnPoint(const Level& level, int playerId) {
    if (playerId >= 0 && playerId < 4)
        return level.spawnPoints[playerId];
    return {640.f, 300.f};
}