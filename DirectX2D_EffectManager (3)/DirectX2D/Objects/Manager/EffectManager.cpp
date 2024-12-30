#include "Framework.h"

EffectManager::~EffectManager()
{
    // �� �ӿ� ���Ͱ�, ������ ���ҷμ� �����Ͱ� �־����Ƿ� �����

    for (pair<string, Effects> effects : totalEffect)    // ������ �̸��� typedef�� �ٿ��� ���� ȣ�� ����
    {
        for (Effect* effect : effects.second) // �� ����� �� �����͸� ���� ����Ʈ ������ ����
        {
            delete effect;  // ������ �����
        }
    }
}

void EffectManager::Update()
{
    for (pair<string, Effects> effects : totalEffect) // ���� �����ϴ� �� �� ����
    {
        for (Effect* effect : effects.second)   // ���� ���� �����͸� �����ϴ� ����Ʈ�� ����
        {
            effect->Update();   // ����Ʈ ����
        }
    }
    // �̷��� ���� ���鼭 �ȿ� �ִ� ����Ʈ ���� ����
}

void EffectManager::Render()
{
    for (pair<string, Effects> effects : totalEffect) // ���� �����ϴ� �� �� ����
    {
        for (Effect* effect : effects.second)   // ���� ���� �����͸� �����ϴ� ����Ʈ�� ����
        {
            effect->Render();
        }
    }
}

void EffectManager::Add(string key, UINT poolSize, wstring textureFile, float maxFrameX, float maxFrameY, float speed, bool isAdditive)
{
    // �ߺ� �����Ͱ� �ִ��� �˻�
    // 1. �����͸� ã�Ƽ�, �����ϸ� (find �Լ� ���)
    // 2. �ش� �����Ϳ� ���ϴ� ����� 1�� �̻��̸� (=�̷��� ������ �ִٴ� �Ҹ�) : �Ʒ� �ڵ�
    if (totalEffect.count(key) > 0) // �����Ϳ� �´� ����� 1�� �̻�!
        return;                     // �̹� �ִ� ������ ("���� �̸����� �� ����Ʈ�� �̹� �����մϴ�~") -> ����

    // * ���� ������ �ߺ� �����͸� �߰������� ������... �׷��� �̷��� ������ ��Ű�� �ð��� �� ���� ����

    // -> �ߺ��� ������ ��¥ �߰� ������ ����

    Effects effects(poolSize);  // -> vector�� poolSize��ŭ ����� ����

    for (Effect*& effect : effects) // ���� �� ��� ���ҿ� ���� �����ͷμ� ����
    {

        effect = new Effect(textureFile, Vector2(maxFrameX, maxFrameY), speed, isAdditive);
    }

    // -> ������� ���� �� ����Ʈ 'effects'�� �ϼ�
    // -> �� �����͸� key�� �Բ� �ʿ� ������ ��

    totalEffect[key] = effects; // �ʿ� �� key�� value(=effects) �߰�
}

void EffectManager::Play(string key, Vector2 position)
{
    // �����Ͱ� �����ϴ��� Ȯ���ϰ�... "�����Ͱ� ������ ����."
    if (totalEffect.count(key) == 0) return; // ����ôµ� 0���� ���ٴ� �̾߱�

    for (Effect* effect : totalEffect[key]) // key�� ��ϵ� ����Ʈ�� ����
    {
        if (!effect->Active()) // �ִϸ��̼��̴ϱ�, "Ʈ������" ���� + ���� ���� �Ǻ� ��
        {
            effect->Play(position); // ���� ���� ���� �ƴϾ����� ������ ��ġ���� �����ϱ�
            return;                 // ���� ���ð� �̹� �������Ƿ�, ���ø� ���� �� ����
        }
    }
}

void EffectManager::SetColor(string key, float r, float g, float b, float a)
{
    // �����Ͱ� �����ϴ��� Ȯ��
    if (totalEffect.count(key) == 0) return;

    for (Effect* effect : totalEffect[key]) // key�� ��ϵ� ����Ʈ�� ����
        effect->GetColor() = { r, g, b, a };    // �Ű������� ���� �� ���� �����ϱ�

}
