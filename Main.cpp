#include <SFML/Graphics.hpp>
#include <vector>
#include <optional>
#include "gameglobale.h"
#include "Level.h"
#include "Player.h"
#include "Physics.h"
#include "Render.h"
#include "UI.h"

int score = 0;
std::vector<Level> levels;

int main() {
    sf::RenderWindow window(sf::VideoMode({(unsigned int)WINDOW_WIDTH, (unsigned int)WINDOW_HEIGHT}), "Stick Fight - Galacticos");
    window.setFramerateLimit(60);

    Level currentLevel;
    int currentLevelId = 0;
    loadLevel(currentLevel, currentLevelId);

    Player players[MAX_PLAYERS];
    playerInit(players[0], 0, currentLevel);
    playerInit(players[1], 1, currentLevel);

    sf::Clock clock;

    while (window.isOpen()) {
        float dt = clock.restart().asSeconds();

        while (std::optional<sf::Event> event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        playerReadInputForIndex(players[0], 0);
        playerReadInputForIndex(players[1], 1);

        playerUpdate(players[0], dt);
        playerUpdate(players[1], dt);

        physicsUpdate(players[0], dt);
        physicsUpdate(players[1], dt);

        resolvePlayerCollision(players[0], players[1]);

        handleCombat(players[0], players[1]);
        handleCombat(players[1], players[0]);

        window.clear(sf::Color::Black);

        drawBackground(window);
        drawLevel(window, currentLevel);

        drawPlayer(window, players[0], 0, dt);
        drawPlayer(window, players[1], 1, dt);

        window.setView(window.getDefaultView());

        drawHealthBars(window, players);

        window.display();
    }

    return 0;
}