#include "Framework.h"

Bullet::Bullet()
    : Quad(L"Textures/Shooting/playerBullet2.png")
{
    // �ϴ��� �׸� ���� ��, ���
    // + ��Ȱ��ȭ (�����ڸ��� ����Ǵ� ���� ���� ����)

    isActive = false;

    collider = new RectCollider(texture->GetSize());    // �׸� ������ ũ�Ⱑ �� ������ ũ��
    collider->SetParent(this);  // �浹ü�� �θ� ������ �ڱ� �ڽ����� = �浹ü�� �ڽ��� ����ٴϰ�!
}

Bullet::~Bullet()
{
    delete collider;
}

void Bullet::Update()
{
    // Ȱ��ȭ ���� ��, Ȱ��ȭ�� �ƴϸ� ���� ����
    if (!isActive) return;

    // �Ѿ˷μ� �����̱�
    Pos() += direction * speed * DELTA; // �־��� ������ �����̱� (��� ����)

    // �Ѿ��� Ȱ��ȭ�� ���� �ʴ� ���� = 1. ���� �� ���� ��. 2. �¾��� ��. (<-���߿�)
    if (Pos().x < 0 || Pos().x > WIN_WIDTH) isActive = false;
    if (Pos().y < 0 || Pos().y > WIN_HEIGHT) isActive = false;

    // ���� �� ��ü�μ� �����θ� ����
    GameObject::Update();
    collider->UpdateWorld();
}

void Bullet::Render()
{
    if (!isActive) return;
    Quad::Render();
    collider->Render();
}

void Bullet::Fire(Vector2 pos, Vector2 direction)
{
    isActive = true;    // Ȱ��ȭ�� �Ƶ� �� �Ƶ� ������ ���⼭ Ȱ��ȭ Ȯ��

    Pos() = pos;    // �Ű������� �ڽſ��� ���� (��ġ ����)
    this->direction = direction;    // ���� ����

    // ���� ���⿡ ���߾ �ڱ� �׸� ������ ����
    Rot().z = direction.Angle(); // ź��Ʈ ���� �Ἥ ���� ���, DX�� y�� - �ʿ� ����
}
