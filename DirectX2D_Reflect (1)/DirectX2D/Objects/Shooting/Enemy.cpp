#include "Framework.h"

Enemy::Enemy() : Quad(L"Textures/Shooting/player.png")
{
    Pos() = { CENTER_X / 2, CENTER_Y }; // �ణ ���ʿ� ����

    canFire = false;    // ���� ���Ŀ��� ���� �� ��� �ɷ�
    fireTime = 0;       // �� ���� ��� �ɸ� �ð� ����


}

Enemy::~Enemy()
{
}

void Enemy::Update()
{
    Cooldown(); // �߻� ��� �ð� �Ǻ���

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
    // �ӽ� ����
}

void Enemy::Rotate()
{
    // �ӽ� ����

    Rot().z += DELTA;   // <- ����� ȸ�� �ڵ�
}

void Enemy::Fire()
{
    // �Է��� �ʿ� ����, ������ �� �� ������ �ٷ� ���

    if (canFire)
    {
        BulletManager::Get()->EnemyFire(Pos(), Right());
        canFire = false; // ������� �ʰ�
    }
}

void Enemy::Cooldown()
{
    // ���� ��� �ð� (��) ���� �Լ�

    if (!canFire) // �� �� ���� ���� ���
    {
        fireTime += DELTA;  // ����� �ð���ŭ �ð� ������ ���� = ��� �ð� ���

        if (fireTime >= fireDelay) // ��� �ð��� ������ ���� �ð��� �Ѿ��
        {
            canFire = true; // �ٽ� �� �� �ְ�
            fireTime = 0;   // ����ð� 0����
        }
        // �̰��� ���ӿ��� ���� ���� ���� ���ð� (��ٿ�) �⺻ �˰���
    }
}
