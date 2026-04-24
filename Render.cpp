#include "Render.h"
#include <cmath>

using namespace sf;

static void drawStickFigure(RenderWindow& window, Player& p, int playerIndex) {
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

void drawPlayer(RenderWindow& window, Player& p, int playerIndex, float dt) {
    static Texture runTexture;
    static bool triedLoadRunTexture = false;
    static bool runTextureLoaded = false;
    static float runAnimTimer = 0.f;
    static int runFrame = 0;

    if (!triedLoadRunTexture) {
        runTextureLoaded = runTexture.loadFromFile("assets/Sprites/RUN.png");
        if (!runTextureLoaded) {
            runTextureLoaded = runTexture.loadFromFile("assets/sprites/RUN.png");
        }
        triedLoadRunTexture = true;
    }

    if (playerIndex == 0) {
        const float frameDuration = 0.06f;
        runAnimTimer += dt;
        while (runAnimTimer >= frameDuration) {
            runAnimTimer -= frameDuration;
            runFrame = (runFrame + 1) % 16;
        }
    }

    const bool isRunning = p.isAlive && std::abs(p.velocity.x) > 20.f;
    if (!runTextureLoaded || !isRunning) {
        drawStickFigure(window, p, playerIndex);
        return;
    }

    Sprite runSprite(runTexture);
    runSprite.setTextureRect(IntRect({runFrame * 96, 0}, {96, 96}));
    runSprite.setPosition({p.pos.x - 33.f, p.pos.y - 25.f});

    if (p.facingRight) {
        runSprite.setScale({1.2f, 1.2f});
    } else {
        runSprite.setOrigin({48.f, 0.f});
        runSprite.setPosition({p.pos.x + 15.f, p.pos.y - 25.f});
        runSprite.setScale({-1.2f, 1.2f});
    }

    window.draw(runSprite);
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
