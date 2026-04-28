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

enum GameState { COUNTDOWN, PLAYING, PAUSED, GAME_OVER };

int main() {
    sf::RenderWindow window(sf::VideoMode({(unsigned int)WINDOW_WIDTH, (unsigned int)WINDOW_HEIGHT}), "Stick Fight - Galacticos");
    window.setFramerateLimit(60);

    GameState currentState = COUNTDOWN;
    float countdownTimer = 3.9f; 
    int winnerIndex = -1;

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
            if (auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                if (keyPressed->code == sf::Keyboard::Key::Escape && currentState == PLAYING) {
                    currentState = PAUSED;
                } else if (keyPressed->code == sf::Keyboard::Key::Escape && currentState == PAUSED) {
                    currentState = PLAYING;
                }
                if (keyPressed->code == sf::Keyboard::Key::R && currentState == GAME_OVER) {
                    playerInit(players[0], 0, currentLevel);
                    playerInit(players[1], 1, currentLevel);
                    players[0].pos.x = 300.f;
                    players[1].pos.x = 1300.f;
                    countdownTimer = 3.9f;
                    currentState = COUNTDOWN;
                }
            }
        }

        if (currentState == COUNTDOWN) {
            countdownTimer -= dt;
            if (countdownTimer <= 0.f) currentState = PLAYING;
        } 
        else if (currentState == PLAYING) {
            playerReadInputForIndex(players[0], 0);
            playerReadInputForIndex(players[1], 1);

            playerUpdate(players[0], dt);
            playerUpdate(players[1], dt);

            physicsUpdate(players[0], dt);
            physicsUpdate(players[1], dt);

            resolvePlayerCollision(players[0], players[1]);
            handleCombat(players[0], players[1]);
            handleCombat(players[1], players[0]);

            if (!players[0].isAlive) { 
                winnerIndex = 1; 
                currentState = GAME_OVER; 
            }
            else if (!players[1].isAlive) { 
                winnerIndex = 0; 
                currentState = GAME_OVER; 
            }
        }

        window.clear(sf::Color::Black);
        
        drawBackground(window);
        drawLevel(window, currentLevel);
        drawPlayer(window, players[0], 0, dt);
        drawPlayer(window, players[1], 1, dt);

        window.setView(window.getDefaultView());

        drawHealthBars(window, players);

        if (currentState == COUNTDOWN) {
            drawCountdown(window, (int)countdownTimer);
        } else if (currentState == PAUSED) {
            drawPauseScreen(window);
        } else if (currentState == GAME_OVER) {
            drawWinScreen(window, winnerIndex);
        }

        window.display();
    }

    return 0;
}