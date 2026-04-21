#ifndef RENDER_H
#define RENDER_H

#include <SFML/Graphics.hpp>
#include "gameglobale.h"

void drawPlayer(sf::RenderWindow& window, Player& p);
void drawHealthBar(sf::RenderWindow& window, Player& p);
void drawBackground(sf::RenderWindow& window);

#endif
