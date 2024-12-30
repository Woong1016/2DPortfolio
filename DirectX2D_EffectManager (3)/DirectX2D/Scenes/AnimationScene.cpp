#include "Framework.h"
#include "AnimationScene.h"

AnimationScene::AnimationScene()
{
    background = new Quad(L"Textures/ETC/Kitties.jpg");
    background->Pos() = { CENTER_X, CENTER_Y };
    background->Scale() = { 0.5f, 0.5f };
    background->UpdateWorld(); // ������Ʈ ������ ���൵ ������.. ������ �� ������ �Ŷ�...

    BulletManager::Get();

    ninja = new Ninja();

    // ī�޶� ������ ����
    //Environment::Get()->GetMainCamera()->SetDevMode(true);  // ȯ�漳������ ȣ��
    CAM->SetDevMode(true);
    
    // ī�޶� ���� ����� �����ϱ� (ī�޶� ���ڸ� ���󰡰�)
    // CAM->SetTarget(ninja);


    // ����Ʈ�� (�̱�������) �Ẹ��

    // ����Ʈ �߰�
    EffectManager::Get()->Add("Explosion1", // ����Ʈ�� �츮�� �ο��ϴ� �̸� (�������)
        10,                                 // �ۿ��� ����Ʈ�� �� �� ��ϵ��� (������ �����ϸ�, ������� ������ ��)
        L"Textures/Effect/Explosion1.png",  // ���� ���
        4,                                  // ���� �� �׸��� ���� ����
        4);                                 // ���� �� �׸��� ���� ����

    // ���� �� �߰� (���� ���� ������, �ٸ� key)
    EffectManager::Get()->Add("Explosion1A", 10, L"Textures/Effect/Explosion1.png", 4, 4);
    EffectManager::Get()->SetColor("Explosion1A", 1, 0, 0); // ���� ���� ������ (�����̴ϱ�!)

    // �ٸ� ���ϵ� �߰�
    EffectManager::Get()->Add("Explosion2", 10, L"Textures/Effect/Explosion2.png", 4, 2, // ���� �׸� ���� �ݿ�
        0.8f,       // �ӵ� ���
        true);      // ȭ�� ���� ����
}

AnimationScene::~AnimationScene()
{
    delete ninja;

    BulletManager::Delete();
}

void AnimationScene::Update()
{
    // Ű�� 123���� ������ ����Ʈ�� ���� �ϳ��� ����ǰ�
    if (KEY_DOWN('1'))
        EffectManager::Get()->Play("Explosion1", mousePos); // �����ġ = ���콺 Ŀ�� ��ġ
    if (KEY_DOWN('2'))
        EffectManager::Get()->Play("Explosion1A", mousePos);
    if (KEY_DOWN('3'))
        EffectManager::Get()->Play("Explosion2", mousePos);


    // background->UpdateWorld(); // �� ������ �ǵ�

    ninja->Update();

    BulletManager::Get()->Update();

    // ī�޶� ���� ������ ��� (Ŭ���� �ȿ� �ֱ� ������ Ȯ����)
    // -> ȭ��ǥŰ�� ī�޶� ����������
    if (KEY_PRESS(VK_LEFT))
        CAM->Pos().x -= DELTA * 100;

    if (KEY_PRESS(VK_RIGHT))
        CAM->Pos().x += DELTA * 100;

    EffectManager::Get()->Update(); // ����Ʈ ����
}

void AnimationScene::Render()
{
    background->Render();

    ninja->Render();

    BulletManager::Get()->Render();
    EffectManager::Get()->Render(); // ����Ʈ ���
}

void AnimationScene::PostRender()
{    
    ninja->PostRender();
}
