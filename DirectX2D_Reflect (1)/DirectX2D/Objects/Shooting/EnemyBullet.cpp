#include "Framework.h"
#include "EnemyBullet.h"

EnemyBullet::EnemyBullet() : Quad(L"Textures/Shooting/triEnemy.png")
{
    isActive = false; // ���� ������

    collider = new RectCollider(texture->GetSize());    // �׸� ������ ũ�Ⱑ �� ������ ũ��
    collider->SetParent(this);  // �浹ü�� �θ� ������ �ڱ� �ڽ����� = �浹ü�� �ڽ��� ����ٴϰ�!
}

EnemyBullet::~EnemyBullet()
{
    delete collider;
}

void EnemyBullet::Update()
{
    if (!isActive) return;

    // �Ѿ˷μ� �����̱�
    Pos() += direction * speed * DELTA; // �־��� ������ �����̱� (��� ����)

    // �Ѿ��� Ȱ��ȭ�� ���� �ʴ� ���� = 1. ���� �� ���� ��. 2. �¾��� ��. (<-���߿�)
    if (Pos().x < 0 || Pos().x > WIN_WIDTH) isActive = false;
    if (Pos().y < 0 || Pos().y > WIN_HEIGHT) isActive = false;

    // ���� �� ��ü�μ� �����θ� ����
    GameObject::Update();
    collider->UpdateWorld();    // �浹ü ��� ����
}

void EnemyBullet::Render()
{
    if (!isActive) return;
    Quad::Render();
    collider->Render(); // �浹ü ���
}

void EnemyBullet::Fire(Vector2 pos, Vector2 direction)
{
    isActive = true;    // Ȱ��ȭ�� �Ƶ� �� �Ƶ� ������ ���⼭ Ȱ��ȭ Ȯ��

    Pos() = pos;    // �Ű������� �ڽſ��� ���� (��ġ ����)
    this->direction = direction;    // ���� ����

    // ���� ���⿡ ���߾ �ڱ� �׸� ������ ����
    Rot().z = direction.Angle(); // ź��Ʈ ���� �Ἥ ���� ���, DX�� y�� - �ʿ� ����
}
