#include "gameglobale.h"

int main() 
{
    RenderWindow window(VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Stick Fight");

    while (window.isOpen())
    {
        while (const auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear();
        window.display();
    }

    return 0;
}
