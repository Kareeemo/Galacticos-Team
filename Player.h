#ifndef PLAYER_H
#define PLAYER_H

#include "gameglobale.h"
#include <SFML/Graphics.hpp>

void playerInit(Player& p, int index);
void playerReadInputForIndex(Player& p, int index);
void playerUpdate(Player& p, float dt);

#endif
