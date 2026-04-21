#include <SFML/Graphics.hpp>
#include "Physics.h"
#include "Render.h"
#include "Player.h"
#include "gameglobale.h"

int score = 0;
std::vector<Level> levels;

int main() {
    Player players[2];
    playerInit(players[0], 0);
    playerInit(players[1], 1);

    sf::RenderWindow window(
        sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
        "Stick Fight - Galacticos Team"
    );
    window.setFramerateLimit(60);
    sf::Clock clock;

    while (window.isOpen()) {
        float dt = clock.restart().asSeconds();
        if (dt > 0.05f) dt = 0.05f;

        while (const auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
        }
        for (int i = 0; i < 2; i++) {
            playerReadInputForIndex(players[i], i);
            playerUpdate(players[i], dt);
            physicsUpdate(players[i], dt);
        }
        window.clear(sf::Color::Black);
        drawBackground(window);
        for (int i = 0; i < 2; i++)
            drawPlayer(window, players[i], i);
        window.display();
    }
    return 0;
}
