#include "Framework.h"

BulletManager::BulletManager()
{
    // ����� ���� ���� �Ѿ� ������ ���⿡�� �ٽ� �ۼ��ϸ� �ȴ� (���� ���Ϳ��� �Ѿ� �ۼ�)
    bullets.resize(30); // �� Ŭ������ ���� �����ι��� ���� �ϳ��� �ƴ� �� �����Ƿ� �˳��ϰ� �����͸� �غ�

    for (Bullet*& bullet : bullets) // bullets ���Ϳ� �ִ� ��� ���Ҹ� bullet���� �ӽ� ��Ī�ϰ�
        bullet = new Bullet();      // �� bullet�� �� �ν��Ͻ��� ���� ��ü�� �Ҵ�

    // ���� �Ѿ˵� ����
    enemyBullets.resize(50);
    for (EnemyBullet*& bullet : enemyBullets) // �ӽ� �̸��̶� ���� �̸��� �̹����� bullet
        bullet = new EnemyBullet();

}

BulletManager::~BulletManager()
{
    for (Bullet* bullet : bullets)  // ������ ��� ���Ҹ� ���� bullet���� ��Ī�ϰ�
        delete bullet;              // ������ ��ġ ���� (Ȥ�� ����)

    for (EnemyBullet* bullet : enemyBullets)
        delete bullet;
}

void BulletManager::Update()
{
    for (Bullet* bullet : bullets)  // ������ ��� ���Ҹ� ���� bullet���� ��Ī�ϰ�
        bullet->Update();           // �� ���Ҹ� ������Ʈ

    //�� �Ѿ˵� ������Ʈ
    for (EnemyBullet* bullet : enemyBullets)
        bullet->Update();
}

void BulletManager::Render()
{
    for (Bullet* bullet : bullets)
        bullet->Render();           // ��� ���� ���� �Ѿ� ���

    for (EnemyBullet* bullet : enemyBullets)
        bullet->Render();
}

void BulletManager::Fire(Vector2 pos, Vector2 direction)
{
    // �Ѿ� �߻� �κи� �����ͼ� ���⼭ �ݺ�
    // -> �Ѿ� �� 1�� (=1����) �װŸ� ���� �ϹǷ� �� ������ �ǵ帱 �� ����
    //    (���� �Ѿ˿� �����ϴ� �Լ��� �ʿ��� ���, ������ �ϳ� �� ������)

    for (Bullet* bullet : bullets) // ��� �Ѿ��� �˻��ؼ�
    {
        if (!bullet->Active()) // ���� �߻� �� �� �Ѿ� �߿� ù ��°�� ã�Ƽ�
        {
            bullet->Fire(pos, direction);   // �߻��Ѵ�. (�׸��� �Լ��� ���� �Ű����� pos, dir��
                                            // �Ѿ˿� �״�� �������ش�)
            return;                         // �׸��� �Լ� ���� (���� �� �߻���� �ʰ�!)
        }
    }
}

void BulletManager::EnemyFire(Vector2 pos, Vector2 direction)
{
    // ���� �Ѿ� �߻�� �Լ�. EnemyBullet Ŭ������ ������� �Ѵ�
    // �̷��� ����� �Ѿ� �Ŵ����� ���� ����⿡��, �����Ե� ������ ��ģ��

    for (EnemyBullet* bullet : enemyBullets)
    {
        if (!bullet->Active()) // ���� �߻� �� �� �Ѿ� �߿� ù ��°�� ã�Ƽ�
        {
            bullet->Fire(pos, direction);   // �߻��Ѵ�. (�׸��� �Լ��� ���� �Ű����� pos, dir��
            // �Ѿ˿� �״�� �������ش�)
            return;                         // �׸��� �Լ� ���� (���� �� �߻���� �ʰ�!)
        }
    }
}

void BulletManager::CollisionBullets()
{
    // �� �Ѿ˸��� ���ư��鼭 �浹 üũ�� �ϸ� �ȴ�
    for (Bullet* b1 : bullets)  // �Ѿ� ���Ϳ� �ִ� �� �Ѿ˸��� ���ư��鼭 b1���� ��Ī
    {
        // ������ ���� �ʴ� ������ ����
        if (!b1->Active()) continue; // continue : �ݺ��� ��, ���� ���� ���, ���� ���� ����

        // ���� ���� �Ѿ˳���
        for (Bullet* b2 : bullets) // �Ѿ� ���Ϳ� �ִ� �� �Ѿ˸��� �ѹ� �� ���ư��鼭 b2�� ��Ī
        {
            // �� �ݺ����� ���� ���� ���� �ϳ��� ���� ���� �ٸ� ��� ���ҿ� �񱳸� �Ѵ�
            // �����ڸ� ������.

            if (!b2->Active()) continue;
            if (b1 == b2) continue; // �� ����� �����ϸ� ���� ��� �� ����

            if (b1->GetCollider()->IsCollision(b2->GetCollider())) // �� �Ѿ��� �浹ü�� ���� �ε�ġ��?
            {
                // TODO : �浹�� ��� ������ ������ ������ OK
            }
        }

        // ������ �ٸ� �Ѿ˰��� �浹 �� ����
        for (EnemyBullet* e1 : enemyBullets)
        {
            if (!e1->Active()) continue;

            if (b1->GetCollider()->IsCollision(e1->GetCollider()))
            {
                // TODO : �� �Ѿ˰� �� �Ѿ��� �ε�ģ ��� �Ͼ ��
                
                // -- ���� : �� �� ��������
                // b1->SetActive(false); // �ݻ縦 ���� �ּ�ȭ
                e1->SetActive(false);
            }

            // �� �Ѿ��� �ε�ĥ ��, �������� ���� ���鼭 �ݻ���� �����ϴ� �ڵ�
            // -> �浹ü �Լ� ��, �� ��° �Ű����� ������ ������ �簢�� �浹 �Լ��� �� ���� �Ẹ��

            Vector2 overlap = { 0, 0 }; // ���������� ����ϱ� ���� �ӽ� ������ (�浹 Ȯ�� ���̹Ƿ� �� ����)

            // �� �浹ü�� �簢�����ν� �� ( + ������ ���� overlap �����Ϳ� ���� �ֱ�)
            if (b1->GetCollider()->IsRectCollision((RectCollider*)e1->GetCollider(), &overlap))
            {
                Vector2 floor; // ���� �ٴ�(�ε�ģ ��)�� ��Ȯ�� ��� �������� ���ϱ� ���� ������

                // ���⼭ �ʿ��� ���� �������� ���
                if (overlap.x > overlap.y) // ���η� ������ ������ = ���� �浹 (���� �Ʒ����� �ε�ħ)
                {
                    // �ٴ��� ����� ����� ���򼱸� �������� �Ѵ�
                    floor  = { ((RectCollider*)e1->GetCollider())->R(), ((RectCollider*)e1->GetCollider())->T() };
                    floor -= { ((RectCollider*)e1->GetCollider())->L(), ((RectCollider*)e1->GetCollider())->T() };

                    // ������� ���� �ε�ģ ��(������ e1)�� �¿츦 �� ��-�Ʒ� ���� ���� ������ ��´�
                }
                else // ���� �浹 (�����̳� �����ʿ��� �ε�ħ)
                {
                    // �ٴ��� ����� ����� �������� �������� �Ѵ�
                    floor  = { ((RectCollider*)e1->GetCollider())->L(), ((RectCollider*)e1->GetCollider())->B() };
                    floor -= { ((RectCollider*)e1->GetCollider())->L(), ((RectCollider*)e1->GetCollider())->T() };
                }

                // �� ��������, �ƹ�ư, �ٴ�(Ȥ�� "�ε�ģ �ݻ��")�� ���� ��

                // �� �ݻ���� �������� ����� �ݻ�� ������ ����

                Vector2 reflect = floor.Normal(); // �ٴ��� ���� ���� (x, y ��ǥ ������ �ϳ��� ������ ����� ���� ����)
                reflect = reflect.GetNormalized();  // ����ȭ�ϱ� (���̰� 1�� �ǵ���!)

                // �� ����ȭ�� ���� (ƨ�� �ö� ������) ...�� �Ի��� �Ѿ��� �̵��¸�ŭ�� ���� �������ָ� �ݻ�

                // �Ѿ��� �ݻ�鿡 ���� ��(������ ��)�� �˱� ���� ����(����)�� ����
                float ratio = b1->GetDir().Dot(reflect);

                // �� ��(����)�� ���� ���Ϳ� �ǵ���ϸ� -> �� ���̸�ŭ ���Ͱ� �þ�� ���� ���ͷ� �ۿ�
                reflect = reflect * ratio; // ���ο� ���� ����
                reflect = reflect * -1;    // �������� �������� �ٲٱ�

                reflect = reflect * 2;     // ���� ���͸� �� ���ؼ� �ݻ��ϴ� ������

                // �� ������� �ݻ��ϴ� ���� ������ �Ի� ���Ϳ� �����ϸ� �ݻ� ���ͷ� ����� �ȴ�

                b1->GetDir() = b1->GetDir() + reflect; // ���ο� ������ ���������

                // (�ɼ�) ���ο� ���⿡ �°� ȸ��
                b1->Rot().z = b1->GetDir().Angle(); // ���ο� ������ ������ ȸ��

                // ������� ���� �� �Ѿ��� ���� ����� ������.
                // ��� �Ѿ��� �� ������ �ѹ� �� ���� (TODO!!!! ���� ��������)

            }
        }

        // ������� ���� �� �Ѿ˿� �ʿ��� �񱳴� �� �ߴ�
    }

    // �� �Ѿ˿� �浹�� �ִٸ�
    for (EnemyBullet* e1 : enemyBullets)
    {
        if (!e1->Active()) continue;

        // ���� �Ѿ��� �� �Ѿ˰� ���� �ʿ�� ������ ���� : ���� �� �س���
        // ���� �Ѿ˿� ���� �ʿ��� �浹 �񱳴� : ���� ��������
        for (EnemyBullet* e2 : enemyBullets)
        {
            if (!e2->Active()) continue;
            if (e1 == e2) continue;

            if (e1->GetCollider()->IsCollision(e2->GetCollider()))
            {
                // �� �Ѿ��� �ε�ġ�� �Ͼ ���� �ۼ�

                //-- ���� : �� �Ѿ��� �ε�ġ�� ���� �ٲ� �� �ִ��� ����
                e1->GetCollider()->GetColor() = { 1, 1, 1, 1 }; // ���
                e2->GetCollider()->GetColor() = { 1, 1, 0, 1 }; // ���

                // �� �Ѿ��� �ε����� ��, �ݴ�� ƨ�ܳ�������???
            }
        }
    }
}

bool BulletManager::CollisionBulletToOther(Collider* collider)
{
    return false;

    // TODO : ������ �غ��ô�!! (�Ѿ˰� �ٸ� ��ü�� �浹!!)
}
