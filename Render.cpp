#include "Render.h"
#include <cmath>

using namespace sf;

namespace {
constexpr float FRAME_WIDTH = 96.f;
constexpr float FRAME_HEIGHT = 96.f;
constexpr float SPRITE_SCALE = 3.0f;
constexpr float SPRITE_CENTER_X = FRAME_WIDTH * 0.5f;
constexpr float SPRITE_FEET_Y = FRAME_HEIGHT;
constexpr float FEET_OFFSET_Y = 8.f;
}

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

static void drawAnimatedSprite(RenderWindow& window, Texture& texture, int frame, Player& p) {
    Sprite sprite(texture);
    sprite.setTextureRect(IntRect({frame * static_cast<int>(FRAME_WIDTH), 0}, {static_cast<int>(FRAME_WIDTH), static_cast<int>(FRAME_HEIGHT)}));
    const float PLAYER_CENTER_X = p.pos.x + (p.width * 0.5f);
    const float PLAYER_FEET_Y = p.pos.y + p.height;

    sprite.setOrigin({SPRITE_CENTER_X, SPRITE_FEET_Y});
    sprite.setPosition({PLAYER_CENTER_X, PLAYER_FEET_Y + FEET_OFFSET_Y});
    if (p.facingRight) {
        sprite.setScale({SPRITE_SCALE, SPRITE_SCALE});
    } else {
        sprite.setScale({-SPRITE_SCALE, SPRITE_SCALE});
    }

    window.draw(sprite);
}

void drawPlayer(RenderWindow& window, Player& p, int playerIndex, float dt) {
    static Texture runTexture;
    static bool triedLoadRunTexture = false;
    static bool runTextureLoaded = false;
    static Texture idleTexture;
    static bool triedLoadIdleTexture = false;
    static bool idleTextureLoaded = false;
    static Texture attackTexture;
    static bool triedLoadAttackTexture = false;
    static bool attackTextureLoaded = false;
    static float runAnimTimer = 0.f;
    static int runFrame = 0;
    static float idleAnimTimer = 0.f;
    static int idleFrame = 0;
    static float attackAnimTimer = 0.f;
    static int attackFrame = 0;
    static int drawCallsThisFrame = 0;
    static bool attackUpdatedThisFrame = false;

    if (!triedLoadRunTexture) {
        runTextureLoaded = runTexture.loadFromFile("assets/Sprites/RUN.png");
        if (!runTextureLoaded) {
            runTextureLoaded = runTexture.loadFromFile("assets/sprites/RUN.png");
        }
        triedLoadRunTexture = true;
    }

    if (!triedLoadIdleTexture) {
        idleTextureLoaded = idleTexture.loadFromFile("assets/Sprites/IDLE.png");
        if (!idleTextureLoaded) {
            idleTextureLoaded = idleTexture.loadFromFile("assets/sprites/IDLE.png");
        }
        triedLoadIdleTexture = true;
    }

    if (!triedLoadAttackTexture) {
        attackTextureLoaded = attackTexture.loadFromFile("assets/Sprites/ATTACK 1.png");
        if (!attackTextureLoaded) {
            attackTextureLoaded = attackTexture.loadFromFile("assets/sprites/ATTACK 1.png");
        }
        triedLoadAttackTexture = true;
    }

    if (drawCallsThisFrame == 0) {
        const float runFrameDuration = 0.06f;
        const float idleFrameDuration = 0.10f;
        runAnimTimer += dt;
        idleAnimTimer += dt;
        while (runAnimTimer >= runFrameDuration) {
            runAnimTimer -= runFrameDuration;
            runFrame = (runFrame + 1) % 16;
        }
        while (idleAnimTimer >= idleFrameDuration) {
            idleAnimTimer -= idleFrameDuration;
            idleFrame = (idleFrame + 1) % 10;
        }
        attackUpdatedThisFrame = false;
    }

    if (p.isAttacking && !attackUpdatedThisFrame) {
        const float attackFrameDuration = 0.05f;
        int attackFrameCount = 7;
        if (attackTextureLoaded) {
            const unsigned int textureWidth = attackTexture.getSize().x;
            if (textureWidth >= static_cast<unsigned int>(FRAME_WIDTH)) {
                attackFrameCount = static_cast<int>(textureWidth / static_cast<unsigned int>(FRAME_WIDTH));
            }
        }

        attackAnimTimer += dt;
        while (attackAnimTimer >= attackFrameDuration) {
            attackAnimTimer -= attackFrameDuration;
            attackFrame = (attackFrame + 1) % attackFrameCount;
        }
        attackUpdatedThisFrame = true;
    }

    if (!p.isAlive) {
        drawStickFigure(window, p, playerIndex);
    } else if (p.isAttacking) {
        if (attackTextureLoaded) {
            drawAnimatedSprite(window, attackTexture, attackFrame, p);
        } else {
            drawStickFigure(window, p, playerIndex);
        }
    } else if (std::abs(p.velocity.x) > 20.f) {
        if (runTextureLoaded) {
            drawAnimatedSprite(window, runTexture, runFrame, p);
        } else {
            drawStickFigure(window, p, playerIndex);
        }
    } else {
        if (idleTextureLoaded) {
            drawAnimatedSprite(window, idleTexture, idleFrame, p);
        } else {
            drawStickFigure(window, p, playerIndex);
        }
    }

    drawCallsThisFrame++;
    if (drawCallsThisFrame >= MAX_PLAYERS) {
        drawCallsThisFrame = 0;
    }
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
