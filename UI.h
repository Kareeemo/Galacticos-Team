#pragma once
#include <SFML/Graphics.hpp>
#include "gameglobale.h"

void drawHealthBars(sf::RenderWindow& window, Player players[]);
void drawWinScreen(sf::RenderWindow& window, int winnerIndex);
void drawPauseScreen(sf::RenderWindow& window);
void drawCountdown(sf::RenderWindow& window, int count);