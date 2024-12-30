#pragma once

class TextureScene : public Scene
{
public:
    TextureScene();
    ~TextureScene();
        
    virtual void Update() override;
    virtual void Render() override;
    virtual void PostRender() override;

private:    // �� �������� ���̴� ���ο� �Լ�

    void CheckCollision();

private:

    //Rect* rect; // DX�� ���ѱ� "��Ʈ"�� �̸�... ���ڱ� ��?
                  // �̹� �����ӿ�ũ������ �� �Ϲ�����, ��ȭ�� DX�� ���� �ֱ� ����!
                  // (���̺귯�� ������ �׸� ����, �ؽ�ó�� �����ϴ� DX-Tex ����� �߰���)

    // ���� rect�� �ƴ�, ���ο� �̸�����, �� ���� ����� ����� �ϰ�...... �� �� �ִ�!

    // �ٽ� ����, �츮�� ���� ���̷�ƮX�� �׸��� ǥ���� �� �ִ�.


    // �׸��� ���� �簢�� ���....�� �غ���

    //Quad* plane;

    Plane* plane;   // �ڱ� Ŭ������ ���� �ִ� ������
    
    Enemy* enemy;   // ���� �� ����!
    Enemy* enemy2;   // ��2�� ����!
};