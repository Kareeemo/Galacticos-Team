#include "Render.h"

using namespace sf;

void drawPlayer(RenderWindow& window, Player& p, int playerIndex) {
    Color playerColors[2] = {
        Color(70, 130, 255),
        Color(220, 60, 60)
    };
    Color col = playerColors[playerIndex % 2];

    CircleShape head(20);
    head.setFillColor(col);
    head.setPosition(Vector2f(p.pos.x, p.pos.y));
    window.draw(head);

    RectangleShape body(Vector2f(4, 50));
    body.setFillColor(col);
    body.setPosition(Vector2f(p.pos.x + 18, p.pos.y + 40));
    window.draw(body);

    RectangleShape leg1(Vector2f(4, 35));
    leg1.setFillColor(col);
    leg1.setPosition(Vector2f(p.pos.x + 18, p.pos.y + 90));
    leg1.setRotation(degrees(20));
    window.draw(leg1);

    RectangleShape leg2(Vector2f(4, 35));
    leg2.setFillColor(col);
    leg2.setPosition(Vector2f(p.pos.x + 18, p.pos.y + 90));
    leg2.setRotation(degrees(-20));
    window.draw(leg2);
}

void drawHealthBar(RenderWindow& window, Player& p, int playerIndex) {
    const float barWidth = 200.f;
    const float barHeight = 20.f;
    const float padding = 15.f;
    const float x = (playerIndex == 0) ? padding : WINDOW_WIDTH - barWidth - padding;
    const float y = padding;

    RectangleShape bgBar(Vector2f(barWidth, barHeight));
    bgBar.setPosition(Vector2f(x, y));
    bgBar.setFillColor(Color(60, 60, 60));
    window.draw(bgBar);

    RectangleShape healthBar(Vector2f((p.health / (float)p.maxHealth) * barWidth, barHeight));
    healthBar.setPosition(Vector2f(x, y));
    healthBar.setFillColor(p.health > 50 ? Color(80, 200, 80) : Color(220, 60, 60));
    window.draw(healthBar);

    RectangleShape outline(Vector2f(barWidth, barHeight));
    outline.setPosition(Vector2f(x, y));
    outline.setFillColor(Color::Transparent);
    outline.setOutlineColor(Color::White);
    outline.setOutlineThickness(2.f);
    window.draw(outline);
}

void drawBackground(RenderWindow& window) {
    static Texture backgroundTexture;
    static bool textureLoaded = backgroundTexture.loadFromFile("assets/hero.png");

    if (textureLoaded) {
        Sprite background(backgroundTexture);
        const Vector2u textureSize = backgroundTexture.getSize();
        if (textureSize.x > 0 && textureSize.y > 0) {
            background.setScale(Vector2f(
                static_cast<float>(WINDOW_WIDTH) / static_cast<float>(textureSize.x),
                static_cast<float>(WINDOW_HEIGHT) / static_cast<float>(textureSize.y)
            ));
        }
        window.draw(background);
        return;
    }

    RectangleShape bg(Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
    bg.setFillColor(Color(30, 30, 30));
    window.draw(bg);
}
