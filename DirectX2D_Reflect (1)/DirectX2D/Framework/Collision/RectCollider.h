#pragma once

// �簢�� �浹ü

class RectCollider : public Collider
{
public: // ������

    struct ObbDesc  // ���� �簢�� ������ ��ġ ���踦 ��Ÿ�� �� ����ϴ� �߰� ������ (����ü)
                    // O(��) + BB(����, ����) ���� �ε�ģ ��Ȳ�� ���� ����(Description)
    {
        Vector2 position;   // ��ġ
        Vector2 axis[2];    // ���� ���� (�ε�ģ �簢�� �ʿ��� X, Y ��ǥ�� ��� �����̳�)
        Vector2 halfSize;   // �ε�ģ ������ ���� ũ�� (��ġ, �� ��� � ���δ�)
    };

public: // ���

    RectCollider(Vector2 size);
    ~RectCollider() = default;

    // �浹 �Լ� �Ǳ��� �غ�
    virtual bool IsPointCollision(Vector2 point) override;
    virtual bool IsRectCollision(class RectCollider* rect, Vector2* overlap = nullptr) override;
    virtual bool IsCircleCollision(class CircleCollider* circle) override;

    // ������ �ܺ� ������
    Vector2 Size() { return size * GlobalScale(); } // �� �ݶ��̴��� ����� ��ü�� ũ����� �ݿ��� ����ũ��
    Vector2 Half() { return Size() * 0.5f; }    // �� �Լ� ����� ����

    // ������ ������
    Vector2 LeftTop();
    Vector2 LeftBottom();
    Vector2 RightTop();
    Vector2 RightBottom();

    // �� ��ġ (����)
    float L();
    float R();
    float T();
    float B();

    // OBB Ȯ�ο�
    ObbDesc GetObb();

private: // ���

    // �߰� �Ǻ��� �Լ��� �ʿ� : ���� �簢���� �� Ȯ��. �׷���...
    // ���ϰ� �ε�ģ ���°� �簢���ΰ�? �ƴϸ� ���ΰ�? �� �Ǻ��� �ʿ䰡 �ִ�

    bool IsAABB(RectCollider* rect, Vector2* overlap);  // AA(���μ��ΰ� �ִ� ���簢��) ��
                                                        // BB(���� ���簢��)���� ǥ�� ������ �����ΰ�?

    bool IsOBB(RectCollider* rect);                     // O + BB, ���� ���簢�� ������ �����ΰ�?

    bool IsSeperate(Vector2 seperateAxis, ObbDesc box1, ObbDesc box2);
                                                        // ���� �簢���� ��Ծ��� ���� ��,
                                                        // �ٸ� �� ������ �������� ������ �ִ���
                                                        // = �밢���� ���� �浹�� �������� �ִ���
                                                        // �Ǻ��ϱ� ���� 2���� ����� ���� �Լ�

private: // ������

    Vector2 size;   // �浹ü�� ũ�� (Ȥ�� "��𼭺��� �������� ��ü�ΰ�?"�� ���� ���� ����)

    ObbDesc obbDesc;    // ����ü �ǹ� ������

};

