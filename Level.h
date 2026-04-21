#ifndef LEVEL_H
#define LEVEL_H

#include "gameglobale.h"

void loadLevel(Level& level, int levelId);
void resetLevel(Level& level, int levelId);
Vec2 getSpawnPoint(const Level& level, int playerId);

#endif
