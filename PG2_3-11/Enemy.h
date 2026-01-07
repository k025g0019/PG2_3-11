#pragma once

class Enemy {
public:
    struct EnemyStatus {
        float posX;
        float posY;
        float speed;
        int hp;
    };

    static void Initialize();
    static void Update(const char* keys);
    static void Draw();
	static void ResetEnemy(int index);

private:
    static constexpr int kEnemyCount_ = 2;
    static EnemyStatus enemyStatus_[kEnemyCount_];
};
