#include "Framework.h"

Collider::Collider()
{
    // vertexBuffer; // �̰� ���̴� + ������ �������ε�
                     // ���̴��� : �ؿ��� �������
                     // ������???? ���� ��絵 �� ��������ϱ� (�� �ڽ� Ŭ�������� ���� ��� ����)

    // �� Ŭ������ ���� ��ü�� � ������� ������ �ϴ��� �����ϴ� �ڵ� (���̴� ����)
    vertexShader = Shader::AddVS(L"VertexPos.hlsl"); // ������� ���� VertexPos�� ���缭
    pixelShader = Shader::AddPS(L"PixelPos.hlsl");  // VertexPos : ��ġ �߽��� ���� ������
                                                    // (��ġ�� �߿��� ���� ��� � �� ��)

    worldBuffer = new MatrixBuffer();   // �������� ���� ���� (�⺻��)
    colorBuffer = new ColorBuffer();    // �� ������ ����

    //�� �⺻�� ���ϱ�
    colorBuffer->Get() = { 0.0f, 1.0f, 0.0f, 1.0f }; // �ʷϻ�. { 0, 1, 0, 1 } ����
                                                     // ������ ���ڴ� ���ü�(alpha)
}

Collider::~Collider()
{
    delete vertexBuffer;
    
    // delete vertexShader; // <- �̱��ϰ� ����ϰ�, �ٸ� ������ �����ǰ� �������� ���
    // delete pixelShader;
    
    delete worldBuffer;
    delete colorBuffer;
}

void Collider::Render()
{
    if (!isActive) return; // Ʈ���������ν� ��Ȱ��ȭ �� ���� ���� (�� �׸�)

    //���ӿ�����Ʈó�� �浹ü�� �ڱ� ������ �����ϰ� ����ϸ� �ȴ�
    worldBuffer->Set(world);    // ��� ������ �ʿ��� �����͸� ���� ���� �����ͷ� �Է� (=Ʈ������)
    worldBuffer->SetVS(0);      // �� ��ü�� ����� ��, ���̴��� ���� �� ��° ������ ������ (��ġ)
    colorBuffer->SetPS(0);      // (=Ʈ������, ���ӿ�����Ʈ) (��Ʈ�� �������)

    vertexBuffer->Set(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);
    // ���� ��� ����� ���̷�Ʈ X�� �ɼ� �߿��� ��� ����
    // �̹��� ����� �ɼ� : PRIMITIVE_TOPOLOGY_LINESTRIP, "�� ǥ�ÿ� ���� �⺻ ���� ���"
    // PRIMITIVE : �����͸� �⺻ ������ ���� ����� ����մϴ�.
    // TOPOLOGY : ��ġ�� ��ǥ�� ���� ����, ��������� �ǹ� (���� �߿��� ū �ǹ̴� ����. �⺻���� ��½� �ʿ��ϴٰ� ��)
    // LINESTRIP : �ܰ��� ǥ�ø� �߽����� �Ѵٴ� ��

    vertexShader->Set();    // ���̴� ���� (�غ�)
    pixelShader->Set();     // ����->�ȼ� ��

    DC->Draw(vertices.size(), 0); // ����Ͱ� �� ������ �׸����� ����
                                  // vertices.size() : ���� �����͸�, �ö� ũ�⸸ŭ (=���� ��)
                                  // 0 : 0��° ���Һ��� (= �׷��ϱ�, ���� ��)
}

bool Collider::IsCollision(Collider* collider)
{
    // �浹 ������ ����

    // �� �� �浹�� �ʿ��� (Ȱ��ȭ�� ��������) ����
    if (!Active()) return false;
    if (!collider->Active()) return false;

    // �������� ���ǹ����� ����� �����غ���
    switch (collider->type) // �ε�ģ ����� ������ ����
    {
    case Collider::Type::RECT:  // �� Ŭ������, enum clss "����"��, �簢���̶�� (enum class ȣ��)
                                // Collider:: ���� ȣ���ϴ� ���� �ٸ� �ڽ� Ŭ���������� �񱳽�Ű����

        return IsRectCollision((RectCollider*)collider); // �������̽� �Ϻο��� �浹ü�� ������ �ڽ� Ŭ������ ����ȯ
        
        // break; // ���ٿ��� return�� �����ϸ� ������� ��ǻ�Ͱ� �� ���� ����
        
        // -> �̷ν� �簢�� �浹 ���θ� ���� �Լ��� �Ǻ��ϰ� �� ����� �״�� ȣ���� ������ ��ȯ���ش�

    case Collider::Type::CIRCLE:
        return IsCircleCollision((CircleCollider*)collider); // ���� ���

    }

    // ������� �Դٸ� ������ ���� �ϳ���
    // collider�� �������� type �����Ͱ� ���� -> �츮�� �ǵ��� ������ �ƴϴ�

    return false;   // �׷��Ƿ� �浹 ���δ� ������� �ʴ´�
}
