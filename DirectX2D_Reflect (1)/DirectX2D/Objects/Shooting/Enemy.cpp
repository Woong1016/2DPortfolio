#include "Framework.h"

Enemy::Enemy() : Quad(L"Textures/Shooting/player.png")
{
    Pos() = { CENTER_X / 2, CENTER_Y }; // 약간 왼쪽에 생성

    canFire = false;    // 등장 직후에는 아직 안 쏘는 걸로
    fireTime = 0;       // 쏜 적이 없어서 걸린 시간 없음


}

Enemy::~Enemy()
{
}

void Enemy::Update()
{
    Cooldown(); // 발사 대기 시간 판별용

    // -------------------------------
    Move();
    Rotate();
    Fire();

    GameObject::Update();
}

void Enemy::Render()
{
    Quad::Render();
}

void Enemy::Move()
{
    // 임시 공백
}

void Enemy::Rotate()
{
    // 임시 공백

    Rot().z += DELTA;   // <- 시험용 회전 코드
}

void Enemy::Fire()
{
    // 입력은 필요 없고, 스스로 쏠 수 있으면 바로 쏘게

    if (canFire)
    {
        BulletManager::Get()->EnemyFire(Pos(), Right());
        canFire = false; // 연사되지 않게
    }
}

void Enemy::Cooldown()
{
    // 재사용 대기 시간 (쿨) 계산용 함수

    if (!canFire) // 쏠 수 없을 때만 계산
    {
        fireTime += DELTA;  // 경과한 시간만큼 시간 변수에 누적 = 경과 시간 기록

        if (fireTime >= fireDelay) // 경과 시간이 정해진 지연 시간을 넘어서면
        {
            canFire = true; // 다시 쏠 수 있게
            fireTime = 0;   // 경과시간 0으로
        }
        // 이것이 게임에서 흔히 보는 재사용 대기시간 (쿨다운) 기본 알고리즘
    }
}
