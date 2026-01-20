#include "Enemy.h"
#include <Novice.h>

#include "Player.h"
#include <cmath>

Enemy::EnemyStatus Enemy::enemyStatus_[Enemy::kEnemyCount_] = {};

void Enemy::Initialize() {
    for (int i = 0; i < kEnemyCount_; ++i) {
        enemyStatus_[i].posX = 100.0f * static_cast<float>(i + 1);
        enemyStatus_[i].posY = 100.0f * static_cast<float>(i + 1);
        enemyStatus_[i].speed = 5.0f + static_cast<float>(i);
        enemyStatus_[i].hp = 1;
    }
}

void Enemy::Update(const char* keys) {
    // 移動
    for (int i = 0; i < kEnemyCount_; ++i) {
        enemyStatus_[i].posX += enemyStatus_[i].speed;

        const bool outRight = (enemyStatus_[i].posX > 1280.0f);
        const bool outLeft = (enemyStatus_[i].posX < 0.0f);
        if (outRight || outLeft) {
            enemyStatus_[i].speed *= -1.0f;
        }
    }

    const Player::BulletStatus& b = Player::GetBullet();
    if (b.isActive) {
        const float bulletRadius = 10.0f; 
        const float enemyRadius = 20.0f;

        for (int i = 0; i < kEnemyCount_; ++i) {


            const float dx = b.posX - enemyStatus_[i].posX;
            const float dy = b.posY - enemyStatus_[i].posY;
            const float r = bulletRadius + enemyRadius;


            const float dist2 = dx * dx + dy * dy;
            const float r2 = r * r;

            if (dist2 <= r2) {

                for (int j = 0; j < 2; j++) {
                    enemyStatus_[j].hp--;
                    Player::DeactivateBullet();


                    if (enemyStatus_[j].hp <= 0) {
                        ResetEnemy(j);
                    }
                }


             
            }
        }
    }


    if (keys[DIK_R]) {
        for (int i = 0; i < kEnemyCount_; ++i) {
            ResetEnemy(i);
        }
    }
}


void Enemy::Draw() {
    for (int i = 0; i < kEnemyCount_; ++i) {
        Novice::DrawEllipse(
            static_cast<int>(enemyStatus_[i].posX),
            static_cast<int>(enemyStatus_[i].posY),
            20, 20, 0.0f, 0xFF0000FF, kFillModeSolid
        );
    }
}

void Enemy::ResetEnemy(int index) {
    if (index < 0 || index >= kEnemyCount_) {
        return;
    }
    enemyStatus_[index].posX = 100.0f * static_cast<float>(index + 1);
    enemyStatus_[index].posY = 100.0f * static_cast<float>(index + 1);
    enemyStatus_[index].speed = 5.0f + static_cast<float>(index);
    enemyStatus_[index].hp = 1;
}

