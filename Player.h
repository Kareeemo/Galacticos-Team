#ifndef PLAYER_H
#define PLAYER_H

#include "gameglobale.h"
#include <SFML/Graphics.hpp>

void playerInit(Player& player, int index, const Level& level);
void playerReadInputForIndex(Player& player, int index);
void playerUpdate(Player& player, float dt);

#endif
