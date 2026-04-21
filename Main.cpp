#include <SFML/Graphics.hpp>
#include "gameglobale.h"

int score = 0;
std::vector<Level> levels;

int main() {
    sf::RenderWindow window(
        sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
        "Stick Fight - Galacticos Team"
    );
    window.setFramerateLimit(60);

    while (window.isOpen()) {
        while (const auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
        }
        window.clear(sf::Color::Black);
        // هنا هنرسم لاحقاً
        window.display();
    }
    return 0;
}