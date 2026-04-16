#include "gameglobale.h"
void drawPlayer(RenderWindow& window, Player& p) {
    CircleShape head(20);
    head.setFillColor(Color::White);
   head.setPosition(sf::Vector2f(p.x, p.y));
    window.draw(head);

    RectangleShape body(Vector2f(4, 50));
    body.setFillColor(Color::White);
   body.setPosition(sf::Vector2f(p.x + 18, p.y + 40));
    window.draw(body);

    RectangleShape leg1(Vector2f(4, 35));
    leg1.setFillColor(Color::White);
    leg1.setPosition(sf::Vector2f(p.x + 18, p.y + 90));
   leg1.setRotation(sf::degrees(20));
    window.draw(leg1);

 RectangleShape leg2(Vector2f(4, 35));
    leg2.setFillColor(Color::White);
    leg2.setPosition(sf::Vector2f(p.x + 18, p.y + 90));
  leg2.setRotation(sf::degrees(-20));
    window.draw(leg2);


}

 void drawHealthBar(sf::RenderWindow& window, Player& p) {
    sf::RectangleShape bgBar(sf::Vector2f(60, 8));
    bgBar.setFillColor(sf::Color::Red);
    bgBar.setPosition(sf::Vector2f(p.x - 10, p.y - 20));
    window.draw(bgBar);

    sf::RectangleShape healthBar(sf::Vector2f(p.health * 0.6f, 8));
    healthBar.setFillColor(sf::Color::Green);
    healthBar.setPosition(sf::Vector2f(p.x - 10, p.y - 20));
    window.draw(healthBar);
}
void drawBackground(sf::RenderWindow& window) {
    sf::RectangleShape bg(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
    bg.setFillColor(sf::Color(30, 30, 30));
    window.draw(bg);