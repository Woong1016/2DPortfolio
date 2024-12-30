#pragma once

// 적 (임시) 클래스 : 비행기와 동등한 구성에 플레이어 조작만 없게

class Bullet;

class Enemy : public Quad
{
public:
    Enemy();
    ~Enemy();

    void Update();
    void Render();

private:

    void Move();
    void Rotate();
    void Fire();

    void Cooldown(); // 재사용 대기 시간 연산

private:

    float speed = 100.0f;
    // Quad* turret; // 포탑은 따로 만들지 않음

    // 총알 불필요 (총알 매니저가 이제 있으니까)

    // 쏘는 능력만 제시
    bool canFire;   // 쏠 수 있는가?
    float fireTime; // 사격 후 걸린 시간
    float fireDelay = 0.75f; // 연사 지연 시간

};

