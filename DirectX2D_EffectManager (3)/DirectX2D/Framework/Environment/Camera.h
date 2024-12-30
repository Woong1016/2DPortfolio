#pragma once

// ī�޶� Ŭ���� : �þ� ������ ������ ���� ������ ��� ���� ���̿�
//                �ǵ����� ��ġ ����ġ�� ���� ��������� �þ߰� �̵��ϴ� ȿ���� �����ϴ� ���� �������� �� Ŭ����

class Camera : public Transform
{
public:
    Camera();
    ~Camera();

    void Update();
    void SetView();

    // Ʈ�������� ������ ���� ���� �� ��κ� ������ �ִ� (Ư�� ��Ʈ, ����)
    void SetTarget(Transform* target) { this->target = target; }
    void SetOffset(float x, float y) { targetOffset = { x, y }; }
    void SetLeftBottom(float x, float y) { leftBottom = { x, y }; }
    void SetRightTop(float x, float y) { rightTop = { x, y }; }
    void SetDeviceSize(float x, float y) { deviceSize = { x, y }; } // ��� ��� ������ ũ��

    Vector2 ScreenToWorld(Vector2 pos);
    Vector2 WorldToScreen(Vector2 pos);

    void SetDevMode(bool value) { isDevMode = value; }  // ���� ������ ��带 on/off
                                                        // ������ ��� : �ӽ� ���� ���
                                                        // ��ɿ��� ������ �Ѱ踦 �����ϰ� 100% �������� ī�޶� ����

private:
    // ���� ���� ��� ���� (�ܺο��� ������ �Ұ���, ī�޶� ����ٴ� ǥ���� �����ϸ� �ڵ����� ���� ����)
    // -> ǥ���� �����Ǹ� �ش� ǥ�� ��ü�� �Ѿƴٴϰ�, �׷��� ������ ���� ���� ���°� �ȴ�
    void FreeMode();            // ǥ���� ���� ��
    void FollowMode();          // ǥ���� ���� ��

    void FixPosition(Vector2& position);    // ǥ���� �ֵ� ���� ������ ��ġ�� �ڴ�� ����� �ʰ� �����ϴ� ����
                                            // (�ܺο��� �Ű� �� �ᵵ ����)

private:

    // ī�޶� ������ �ٽ� ���̵��
    MatrixBuffer* viewBuffer;
    Matrix view;

    float speed = 100.0f;
    bool isDevMode = false;

    // ī�޶� ���� ������ �ٽ� : ���� ���
    Transform* target = nullptr;

    // Ʈ������ �����͵�
    Vector2 targetOffset = { CENTER_X, CENTER_Y };
    Vector2 leftBottom;
    Vector2 rightTop = { WIN_WIDTH, WIN_HEIGHT };
    Vector2 deviceSize = { WIN_WIDTH, WIN_HEIGHT };
};