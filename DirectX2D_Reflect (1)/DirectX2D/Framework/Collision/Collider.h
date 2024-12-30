#pragma once

// �浹ü (�浹�� ����) : �����ͷ� �����ϴ� �� ��ü�� ��Ÿ�� ������ ������
//                       (��ü�� ���� �ְ�, �ƹ�ư ���� �ε�ĥ ���� �ְ�)
//                       �� ������ ��𼭺��� ���������� ��Ÿ���� �Ѱ� ���� Ŭ����

class Collider : public Transform // ���� �����Ϳ� �ϳ��� ������ ���ϹǷ� �� ���� �׳� ��� ����� ����
{
protected:
    // �浹ü�� ���� ������ ������
    // enum Type
    enum class Type // enum class : �������� ���� Ŭ���� �����θ� ����ϰ� �����ϴ� ��
    {
        RECT,   // �簢��
        CIRCLE, // ��
    };

    // �������� enum class�� �����ϸ� ����� ��, ���� ������ Ŭ���������� ��� �ϴ� ������ �ٴ´�
    // (������ �������̽���� ���� �ȴ�) �� ���, Ŭ��������� �־�� �ϹǷ� ���� �ߺ��� Ȯ���� �ſ� ��������
    // Type::RECT; // <- ȣ�⿹��

public:

    Collider();
    ~Collider();

    void Render(); // �浹ü ������ ���� ���̵��� ������ֱ� (�����ڿ�)

    bool IsCollision(Collider* collider);

    // ������ � ������� �� ���鼭 �浹 ����� �õ��ϴ� ������ ���� �Լ� (�������̽�)
    // * �Ű������� class�� class ���� ������ �Ű� ���� �ȿ��� ��ġ�� ��.
    //   �� Ŭ���� �ۿ��� 'class RectCollider'��� ������ �Ͱ� ȿ���� ����. (=������ �̰͵� ������ �Ѵ�)
    virtual bool IsPointCollision(Vector2 point) = 0;
    virtual bool IsRectCollision(class RectCollider* rect, Vector2* overlap = nullptr) = 0;
    virtual bool IsCircleCollision(class CircleCollider* circle) = 0;

    // �����ڿ� ���� ǥ�ÿ��� ���� �ٲ� �ʿ䰡 �ִٸ�
    Float4& GetColor() { return colorBuffer->Get(); }

protected:
    Type type; // �浹ü�� ����

    //�浹ü�� ����
    VertexBuffer* vertexBuffer; // ������� �������� �޸𸮿� ��ϵǾ� �ֵ��� ����� ���� (�Ҵ��)
    vector<VertexPos> vertices; // ���� �����͵� (�����)

private:

    // ���� ����� ȭ��� �������� ����Ǳ� ���� �ڷ��
    
    // ���� ���̰� �ϴ� �� (=���̴�)
    VertexShader* vertexShader; // �����͸� ��ġ�� �������ش�
    PixelShader* pixelShader;   // ������� ��ġ �����͸� ��Ʈ�� �ٲ��ش�

    // ���� ������ (+ ��)
    MatrixBuffer* worldBuffer;  // ���� �����͸� �޸𸮿� �ø� ��
    ColorBuffer* colorBuffer;   // �� �����͵� �޸𸮿� �÷��ּ� �Ź� �����ϴ� ���� �����

};

