#pragma once

// �Ѿ� ���� Ŭ����

class BulletManager : public Singleton<BulletManager> // �� Ŭ������ ���Ϲ����ϰ�
{
private:
    friend class Singleton; // friend class : "�� �̸����� ������ Ŭ������ ���ϰ� ģ���Դϴ�"
                            //                -> �ش� Ŭ������ private �����͸� �� �� �ְ� ���ش�

    BulletManager();
    ~BulletManager();

public:
    void Update();
    void Render();

    void Fire(Vector2 pos, Vector2 direction); // ������� �߻� �Լ�
                                               // (������� �Ѿ� ���� ����� ������Ų ��)
    void EnemyFire(Vector2 pos, Vector2 direction); // ���� �߻�

    // Get() �� �̱��� ��ü�μ� �־�� �� �Լ��� �̱��� Ŭ���� ���� �̹� ���� (�װ� ���� friend)

    void CollisionBullets();    // �Ѿ˰� �ٸ� �Ѿ� ������ �浹 ���� (���� ����)
                                // ���� �ִ� �����ͳ����� �� �״� ��� ��ȯ ���ʿ�
    bool CollisionBulletToOther(Collider* collider);  // �Ѿ�(��)�� �ٸ� ��ü�� �ε�ġ��?

private:

    vector<Bullet*> bullets; // �Ѿ� (�����ι��� ������ ���ӿ� ��ϵ� ������)
    vector<EnemyBullet*> enemyBullets; // ���� �Ѿ�

    // �ٸ� �Ѿ��� �ʿ��ϸ� ���� ���⼭ ���� �ۼ� �Ŀ� ȣ���ϸ� ��

};

