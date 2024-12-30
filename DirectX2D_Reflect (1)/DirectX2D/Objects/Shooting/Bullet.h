#pragma once
class Bullet : public Quad
{

public:

    Bullet();
    ~Bullet();

    void Update();
    void Render(); // ������� ���� ����

    void Fire(Vector2 pos, Vector2 direction); // �߻簡 �Ǹ� �Ͼ�� ��

    Collider* GetCollider() { return collider; } // �浹ü �ܺ� ������ ����
    Vector2& GetDir() { return direction; }      // �ӵ�(����)�� ��� ���� ����

    // ���⼭ �ٽ�
    // &�� *

    // & : ���𿡼� ����ϸ�, �������� ��ü�� ���� �ٷ�ٴ� ��. ȣ�⿡�� ����ϸ�, �����Ͱ� �ִ� ��(����)
    // * : ���𿡼� ����ϸ�, �����Ͱ� �ִ� ��(�ּ�), ȣ�⿡�� ����ϸ�, ȣ��� �ּҿ� �ִ� ������(������)

private:
    // ���� �Լ� ���ʿ� = ������Ʈ���� �� �Ѵ�
    // �Ѿ��� �����ϰ� �������� �ʴ´� = �׳� ���ư���, �ε�ġ�� xxx�Ѵ�

    // �ӷ��� �ʿ�!
    float speed = 300.0f;

    // ����
    Vector2 direction;

    // �浹ü �Ẹ��
    Collider* collider; //�浹ü! (�������̽�)
};

