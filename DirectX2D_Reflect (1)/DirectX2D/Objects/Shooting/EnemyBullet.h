#pragma once
class EnemyBullet : public Quad
{

public:

    EnemyBullet();
    ~EnemyBullet();

    void Update();
    void Render();

    void Fire(Vector2 pos, Vector2 direction);

    Collider* GetCollider() { return collider; } // �浹ü �ܺ� ������ ����

private:
    float speed = 300.0f;
    Vector2 direction;

    // �浹ü �Ẹ��
    Collider* collider; //�浹ü! (�������̽�)
};

