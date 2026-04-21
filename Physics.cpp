#include "Physics.h"

using namespace sf;

namespace {
const float GRAVITY = 1200.f;
}

void physicsUpdate(Player& p, float dt) {
    if (!p.isAlive) {
        return;
    }

    p.velocity.y += GRAVITY * dt;

    p.pos.x += p.velocity.x * dt;
    p.pos.y += p.velocity.y * dt;

    if (p.pos.y + p.height >= 650.f) {
        p.pos.y = 650.f - p.height;
        p.velocity.y = 0.f;
        p.onGround = true;
    } else {
        p.onGround = false;
    }

    if (p.pos.x < 0.f) {
        p.pos.x = 0.f;
    }
    if (p.pos.x + p.width > WINDOW_WIDTH) {
        p.pos.x = WINDOW_WIDTH - p.width;
    }
}
