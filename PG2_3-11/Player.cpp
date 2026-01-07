#include "Player.h"
#include <Novice.h>

Player::PlayerStatus Player::playerStatus_ = {};
Player::BulletStatus Player::bulletStatus_ = {};

void Player::Initialize() {
    playerStatus_.posX = 640.0f;
    playerStatus_.posY = 360.0f;
    playerStatus_.speed = 5.0f;
    playerStatus_.hp = 10;

    bulletStatus_.posX = 0.0f;
    bulletStatus_.posY = 0.0f;
    bulletStatus_.speed = 0.0f;
    bulletStatus_.isActive = false;
}

void Player::Update(const char* keys) {
    if (keys[DIK_W]) {
        playerStatus_.posY -= playerStatus_.speed;
    }
    if (keys[DIK_S]) {
        playerStatus_.posY += playerStatus_.speed;
    }
    if (keys[DIK_A]) {
        playerStatus_.posX -= playerStatus_.speed;
    }
    if (keys[DIK_D]) {
        playerStatus_.posX += playerStatus_.speed;
    }
}

void Player::Draw() {
    Novice::DrawEllipse(
        static_cast<int>(playerStatus_.posX),
        static_cast<int>(playerStatus_.posY),
        20, 20, 0.0f, 0xFFFFFFFF, kFillModeSolid
    );
}

void Player::BulletUpdate(const char* keys) {
    const bool shoot = (keys[DIK_SPACE] != 0);

    if (shoot && !bulletStatus_.isActive) {
        bulletStatus_.isActive = true;
        bulletStatus_.posX = playerStatus_.posX;
        bulletStatus_.posY = playerStatus_.posY;
        bulletStatus_.speed = 10.0f;
    }

    if (bulletStatus_.isActive) {
        bulletStatus_.posY -= bulletStatus_.speed;
        if (bulletStatus_.posY < 0.0f) {
            bulletStatus_.isActive = false;
        }
    }
}

void Player::BulletDraw() {
    if (!bulletStatus_.isActive) {
        return;
    }

    Novice::DrawEllipse(
        static_cast<int>(bulletStatus_.posX - 5.0f),
        static_cast<int>(bulletStatus_.posY - 5.0f),
        10, 10, 0.0f, 0xFFFFFFFF, kFillModeSolid
    );
}
const Player::BulletStatus& Player::GetBullet() {
    return bulletStatus_;
}

void Player::DeactivateBullet() {
    bulletStatus_.isActive = false;
}
