#pragma once
class EnemyBullet : public Quad
{

public:

    EnemyBullet();
    ~EnemyBullet();

    void Update();
    void Render();

    void Fire(Vector2 pos, Vector2 direction);

    Collider* GetCollider() { return collider; } // 충돌체 외부 참조용 겟터

private:
    float speed = 300.0f;
    Vector2 direction;

    // 충돌체 써보기
    Collider* collider; //충돌체! (인터페이스)
};

