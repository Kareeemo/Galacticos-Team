#include "gameglobale.h"
#include <SFML/Graphics.hpp>

using namespace sf;

namespace {
constexpr float SPEED = 250.f;
constexpr float JUMP_VELOCITY = -550.f;
constexpr float ATTACK_BOX_WIDTH = 40.f;
constexpr float ATTACK_BOX_HEIGHT = 20.f;
}

void playerInit(Player& p, int index) {
    p.position = {200.f + index * 300.f, 300.f};
    p.velocity = {0.f, 0.f};
    p.width = 30.f;
    p.height = 60.f;
    p.health = 100;
    p.maxHealth = 100;
    p.isAlive = true;
    p.onGround = false;
    p.facingRight = (index % 2 == 0);
    p.attackCooldown = 0.4f;
    p.attackTimer = 0.f;
    p.isAttacking = false;
    p.score = 0;
    p.inputLeft = false;
    p.inputRight = false;
    p.inputJump = false;
    p.inputAttack = false;
    p.attackBox = FloatRect({p.position.x, p.position.y}, {0.f, 0.f});
}

void playerReadInputForIndex(Player& p, int index) {
    static const Keyboard::Key LEFT_KEYS[MAX_PLAYERS] = {
        Keyboard::Key::A,
        Keyboard::Key::Left,
    };
    static const Keyboard::Key RIGHT_KEYS[MAX_PLAYERS] = {
        Keyboard::Key::D,
        Keyboard::Key::Right,
    };
    static const Keyboard::Key JUMP_KEYS[MAX_PLAYERS] = {
        Keyboard::Key::W,
        Keyboard::Key::Up,
    };
    static const Keyboard::Key ATTACK_KEYS[MAX_PLAYERS] = {
        Keyboard::Key::Space,
        Keyboard::Key::Enter,
    };

    if (index < 0 || index >= MAX_PLAYERS) {
        p.inputLeft = false;
        p.inputRight = false;
        p.inputJump = false;
        p.inputAttack = false;
        return;
    }

    p.inputLeft = Keyboard::isKeyPressed(LEFT_KEYS[index]);
    p.inputRight = Keyboard::isKeyPressed(RIGHT_KEYS[index]);
    p.inputJump = Keyboard::isKeyPressed(JUMP_KEYS[index]);
    p.inputAttack = Keyboard::isKeyPressed(ATTACK_KEYS[index]);
}

void playerUpdate(Player& p, float dt) {
    if (!p.isAlive) {
        return;
    }

    if (p.inputLeft && !p.inputRight) {
        p.velocity.x = -SPEED;
        p.facingRight = false;
    } else if (p.inputRight && !p.inputLeft) {
        p.velocity.x = SPEED;
        p.facingRight = true;
    } else {
        p.velocity.x *= 0.75f;
    }

    if (p.inputJump && p.onGround) {
        p.velocity.y = JUMP_VELOCITY;
        p.onGround = false;
    }

    p.attackTimer -= dt;
    if (p.inputAttack && p.attackTimer <= 0.f) {
        const float attackX = p.facingRight
            ? p.position.x + p.width
            : p.position.x - ATTACK_BOX_WIDTH;
        const float attackY = p.position.y + (p.height - ATTACK_BOX_HEIGHT) * 0.5f;

        p.isAttacking = true;
        p.attackTimer = p.attackCooldown;
        p.attackBox = FloatRect({attackX, attackY}, {ATTACK_BOX_WIDTH, ATTACK_BOX_HEIGHT});
    } else {
        p.isAttacking = false;
    }
}
