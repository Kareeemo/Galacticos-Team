#include "gameglobale.h"
#include "Level.h"
#include <SFML/Graphics.hpp>

using namespace sf;

namespace {
constexpr float SPEED = 250.f;
constexpr float JUMP_VELOCITY = -650.f;
constexpr float ATTACK_BOX_WIDTH = 120.f;
constexpr float ATTACK_BOX_HEIGHT = 80.f;
}

void playerInit(Player& player, int index, const Level& level) {
    player.pos = getSpawnPoint(level, index);
    player.velocity = {0.f, 0.f};
    player.width = 30.f;
    player.height = 60.f;
    player.health = 100;
    player.maxHealth = 100;
    player.isAlive = true;
    player.onGround = false;
    player.facingRight = (index % 2 == 0);
    player.attackCooldown = 0.4f;
    player.attackTimer = 0.f;
    player.isAttacking = false;
    player.score = 0;
    player.inputLeft = false;
    player.inputRight = false;
    player.inputJump = false;
    player.inputAttack = false;
    player.attackBox = FloatRect({player.pos.x, player.pos.y}, {0.f, 0.f});
}

void playerReadInputForIndex(Player& player, int index) {
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
        Keyboard::Key::C,
        Keyboard::Key::N,
    };

    if (index < 0 || index >= MAX_PLAYERS) {
        player.inputLeft = false;
        player.inputRight = false;
        player.inputJump = false;
        player.inputAttack = false;
        return;
    }

    player.inputLeft = Keyboard::isKeyPressed(LEFT_KEYS[index]);
    player.inputRight = Keyboard::isKeyPressed(RIGHT_KEYS[index]);
    player.inputJump = Keyboard::isKeyPressed(JUMP_KEYS[index]);
    player.inputAttack = Keyboard::isKeyPressed(ATTACK_KEYS[index]);
}

void playerUpdate(Player& player, float dt) {
    if (!player.isAlive) {
        player.isAttacking = false;
        player.attackBox = FloatRect({player.pos.x, player.pos.y}, {0.f, 0.f});
        return;
    }

    if (player.inputLeft && !player.inputRight) {
        player.velocity.x = -SPEED;
        player.facingRight = false;
    } else if (player.inputRight && !player.inputLeft) {
        player.velocity.x = SPEED;
        player.facingRight = true;

    } else if (player.inputLeft && player.inputRight && !player.onGround) {
        player.velocity.x = (player.facingRight ? 1.f : -1.f) * SPEED * 2.0f;
        
    } else {
        player.velocity.x *= 0.75f;
    }

    if (player.inputJump && player.onGround) {
        player.velocity.y = JUMP_VELOCITY;
        player.onGround = false;
    }

    if (player.attackTimer > 0.f) {
        player.attackTimer -= dt;
    }

    if (player.inputAttack && player.attackTimer <= 0.f) {
        const float attackX = player.facingRight
            ? player.pos.x + player.width
            : player.pos.x - ATTACK_BOX_WIDTH;
        const float attackY = player.pos.y + (player.height - ATTACK_BOX_HEIGHT) * 0.5f;

        player.isAttacking = true;
        player.attackTimer = player.attackCooldown;
        player.attackBox = FloatRect({attackX, attackY}, {ATTACK_BOX_WIDTH, ATTACK_BOX_HEIGHT});
    } else {
        player.isAttacking = false;
        player.attackBox = FloatRect({player.pos.x, player.pos.y}, {0.f, 0.f});
    }
}
