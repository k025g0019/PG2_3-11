#include <Novice.h>
#include "Enemy.h"
#include "Player.h"

const char kWindowTitle[] = "学籍番号";

int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {
    Novice::Initialize(kWindowTitle, 1280, 720);

    char keys[256] = { 0 };
    char preKeys[256] = { 0 };

    // 初期化
    Enemy::Initialize();
    Player::Initialize();

    while (Novice::ProcessMessage() == 0) {
        Novice::BeginFrame();

        memcpy(preKeys, keys, 256);
        Novice::GetHitKeyStateAll(keys);

        // Update
        Enemy::Update(keys);
        Player::Update(keys);
        Player::BulletUpdate(keys);

        // Draw
        Enemy::Draw();
        Player::Draw();
        Player::BulletDraw();

        Novice::EndFrame();

        if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
            break;
        }
    }

    Novice::Finalize();
    return 0;
}
