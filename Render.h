#ifndef RENDER_H
#define RENDER_H

#include <SFML/Graphics.hpp>
#include "gameglobale.h"

void drawPlayer(sf::RenderWindow& window, Player& p, int playerIndex, float dt);
void drawBackground(sf::RenderWindow& window);

#endif
