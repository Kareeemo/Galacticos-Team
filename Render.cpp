#include "Render.h"

using namespace sf;

#define pos position

void drawPlayer(RenderWindow& window, Player& p) {
    CircleShape head(20);
    head.setFillColor(Color::White);
    head.setPosition(Vector2f(p.pos.x, p.pos.y));
    window.draw(head);

    RectangleShape body(Vector2f(4, 50));
    body.setFillColor(Color::White);
    body.setPosition(Vector2f(p.pos.x + 18, p.pos.y + 40));
    window.draw(body);

    RectangleShape leg1(Vector2f(4, 35));
    leg1.setFillColor(Color::White);
    leg1.setPosition(Vector2f(p.pos.x + 18, p.pos.y + 90));
    leg1.setRotation(degrees(20));
    window.draw(leg1);

    RectangleShape leg2(Vector2f(4, 35));
    leg2.setFillColor(Color::White);
    leg2.setPosition(Vector2f(p.pos.x + 18, p.pos.y + 90));
    leg2.setRotation(degrees(-20));
    window.draw(leg2);
}

void drawHealthBar(RenderWindow& window, Player& p) {
    RectangleShape bgBar(Vector2f(60.f, 8.f));
    bgBar.setFillColor(Color::Red);
    bgBar.setPosition(Vector2f(p.pos.x - 10.f, p.pos.y - 20.f));
    window.draw(bgBar);

    RectangleShape healthBar(Vector2f((p.health / (float)p.maxHealth) * 60.f, 8.f));
    healthBar.setFillColor(Color::Green);
    healthBar.setPosition(Vector2f(p.pos.x - 10.f, p.pos.y - 20.f));
    window.draw(healthBar);
}

void drawBackground(RenderWindow& window) {
    RectangleShape bg(Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
    bg.setFillColor(Color(30, 30, 30));
    window.draw(bg);
}

#undef pos
