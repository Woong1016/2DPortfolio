#pragma once

class EffectManager : public Singleton<EffectManager>
{
private:
    friend class Singleton; // �θ� Ŭ������ private ����

    EffectManager() = default;  // �̱����̴ϱ� �����ڰ� ������ ������ ������ ������ �δ�
    ~EffectManager();

public:
    // ������ (���� '���') �Լ�
    void Update();
    void Render();

    // ����Ʈ ���� �Լ�

    void Add(string key, UINT poolSize, wstring textureFile, float maxFrameX, float maxFrameY,
        float speed = 1.0f, bool isAdditive = false); // ����Ʈ �߰�
    // ���� ���� �Ű����� �� speed : �ӵ� ��� (�ӵ�����ŭ ���� FPS�� ����)
    // isAdditive : ȭ�Ҹ� ������ ���ΰ� (�������� ��, �ش� ���� ���ؼ� ��������, ������ ��������)

    void Play(string key, Vector2 position);    // ����Ʈ ����ϱ�
    void SetColor(string key, float r, float g, float b, float a = 1); // ���� �޶����� �� ��� �����ϴ� �Լ�
                                                                       // = '�ȷ� ����'

private:
    
    // �Ʒ� �� �� �ڵ�� �⺻ ��� ����
    //vector<Effect*> effects; // ������ �������� �ʼ��� �ƴ�
    //unordered_map<string, vector<Effect*>> totalEffects; // ����Ʈ ��ü ������ ����

    //�� �ڵ带 ���� ���·� ���� ��
    typedef vector<Effect*> Effects;    //vector<Effect*>�� ���ݺ��� Effects��� ö�ڷ� ���
    unordered_map<string, Effects> totalEffect; // <- ȣ�⵵, ��뵵 ����������
};

