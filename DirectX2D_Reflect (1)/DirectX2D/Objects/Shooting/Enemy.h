#pragma once

// �� (�ӽ�) Ŭ���� : ������ ������ ������ �÷��̾� ���۸� ����

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

    void Cooldown(); // ���� ��� �ð� ����

private:

    float speed = 100.0f;
    // Quad* turret; // ��ž�� ���� ������ ����

    // �Ѿ� ���ʿ� (�Ѿ� �Ŵ����� ���� �����ϱ�)

    // ��� �ɷ¸� ����
    bool canFire;   // �� �� �ִ°�?
    float fireTime; // ��� �� �ɸ� �ð�
    float fireDelay = 0.75f; // ���� ���� �ð�

};

