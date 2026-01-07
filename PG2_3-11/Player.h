#pragma once

class Player {
public:
    struct PlayerStatus {
        float posX;
        float posY;
        float speed;
        int hp;
    };

    struct BulletStatus {
        float posX;
        float posY;
        float speed;
        bool isActive;
    };

    static void Initialize();
    static void Update(const char* keys);
    static void Draw();

    static void BulletUpdate(const char* keys);
    static void BulletDraw();
public:
    static const BulletStatus& GetBullet();
    static void DeactivateBullet();

private:
    static PlayerStatus playerStatus_;
    static BulletStatus bulletStatus_;
};
