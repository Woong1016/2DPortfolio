#include "Framework.h"
#include "TextureScene.h"

TextureScene::TextureScene()
{
    /* ���۰� ���� �̷� ǥ�ð� ������
    ���̿� �ִ� ��� �ؽ�Ʈ�� �ּ� */

    /* 
    // rect = new Rect({}, {}); // <- ����.
    plane = new Quad(
        L"Textures/Shooting/airplane.png",
        { CENTER_X, CENTER_Y }
    );
    */

    // -----------------------------

    // 2�� �̻� ��ü�� �����ϰ�, �� �������� �ʿ��� �̱����� �ִٸ�?
    // -> ��ü�� �ƴ� ���� �ش� �̱����� �����ϴ� �� �� ȿ������ ����.
    BulletManager::Get();   // Ư�� Ŭ�������� �ƴ�, ������ �ٷ� �̱��� ��ü�� ������.

    //�׷��� ���� ��¥ �����ι����� ������ �Ѵ�.
    plane = new Plane();    // ����� �׳� ���� (�ʿ��� ������ Ŭ�������� �̹� ��)
    plane->Pos() = { CENTER_X, CENTER_Y };  // ��ġ�� �ٽ� ����

    enemy = new Enemy();
    enemy->Pos() = { CENTER_X / 2, CENTER_Y };  // Ȯ�� ��� ��ġ ����

    enemy2 = new Enemy();
    enemy2->Pos() = { CENTER_X * 3 / 2, CENTER_Y }; // ���� 3/4 ��ġ�� ����

}

TextureScene::~TextureScene()
{
    delete plane;
    delete enemy;
    delete enemy2;

    BulletManager::Delete();    // ���������� ���� �̱����̴�, ���������� ���� �� �ִ�
                                // (�����ڸ� "�� ���� �ƴϸ� �Ѿ˸Ŵ��� ���� �ٸ� ����� ���� ������?")
                                //  ....���� �ٸ� �������� �̱����� ����, �� �ڵ�� �ٽ� ��������...
}

void TextureScene::Update()
{
    /* ������ �ٸ� ������...
    if (KEY_PRESS(VK_LEFT))
        plane->Rot().z += DELTA;

    if (KEY_PRESS(VK_UP))
        plane->Pos() += plane->Right();
    */

    // ------------
    // �ݻ翡 ���� �Ͼ ���� �ڵ�� ȣ��
    // * �Ѿ˳����� �ۼ��ϸ� �Ѿ� �Ŵ����� �ո��� (�Ѿ� �����Ͱ� �ִ� ��)
    //   �׷��� ���� �÷��̾� �����ͱ��� ������� ���� �� ��� �����ι��� �ִ� ���� ����

    CheckCollision(); // �浹 Ȯ�� �� �� ���Ŀ� �Ͼ �� �ۼ�

    // ------------

    plane->Update(); // ���� ������ ����, ��¸� ����
    enemy->Update();
    enemy2->Update();

    BulletManager::Get()->Update();
    // -> �����͵�, ������ ���еǴ� �Ѿ� �Ŵ��� ���� ��� �����Ͱ� (= �Ѿ˵���)
    //    ������ ���� �ڱ� �����ʹ�� ����ǰ� �� �׷�����
}

void TextureScene::Render()
{
    plane->Render();
    enemy->Render();
    enemy2->Render();

    BulletManager::Get()->Render();
}

void TextureScene::PostRender()
{
}

void TextureScene::CheckCollision()
{
    // �浹 Ȯ�� ���ǹ�

    //if (BulletManager::Get()->CollisionBulletToOther(�÷��̾��浹ü))
    //{
    //      // �÷��̾�� ��ȣ�ۿ�
    //}

    BulletManager::Get()->CollisionBullets();   // �Ѿ˳��� �Ͼ�� �浹 ����
}
