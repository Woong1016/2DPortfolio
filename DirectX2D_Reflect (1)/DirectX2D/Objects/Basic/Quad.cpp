#include "Framework.h"

Quad::Quad(Vector2 size, Vector2 pos)
{
    // �⺻ �簢�� ����� (�׸� ����)
    CreateMesh(size, pos); // ũ��, ��ġ ������ �簢�� �����
}

Quad::Quad(wstring file, Vector2 pos)
{
    // �׸� �ִ� �簢�� ����� (���� ���� ����)

    SetTexture(file); // �׸� ������ �Լ��� �ҷ��� ���� �׸� ����
    size = texture->GetSize();  // �ؽ�ó�� ��ϵ� �����Ϳ���, DX�� �ִ� ����� �Ἥ, �̹��� ũ�� Ȯ��
    CreateMesh(size, pos);     // �簢�� ��� �����
}

Quad::~Quad()
{
    // �ؽ�ó�� ������ �Ѵ�. ������ (�����ʹϱ�)
    // -> �ؽ�ó�� ���, ���� �����Ͷ� ���⼭ �� ����ٰ� ���� �� �� �ִ� (�ٸ� ������ �׸��� ���ٵ簡)
    // -> ���� ������ ���� �����͸� �� ����� ������ ��� �ִ� : �׷��� �ؽ�ó�� ������
}

void Quad::Render()
{
    texture->PSSet();   // "�׸��� �׷���"��� ȣ���� ���� (������ �ؽ�ó Ŭ�������� Ȯ��)

    // ������ ���� �繰�μ��� �����͵� ��� ������ ���ָ� �ȴ�
    GameObject::Render(); // �θ� Ŭ������ ���� �̸� �Լ�
}

void Quad::SetTexture(wstring file)
{
    // �ؽ�ó ������ ������ �Ҵ� + �� �޸𸮿� �̹��� ���
    texture = Texture::Add(file); // Ŭ������ �̹����� ����ϰ�, ��ȯ�� �̹����� ������ ������ ��.
}

void Quad::CreateMesh(Vector2 size, Vector2 pos)
{

     // ��ġ�� �߽������� ��Ƽ� �� ������ �����

    float left = pos.x - size.x * 0.5f; // �߽ɿ���, �־��� ũ���� �ݸ�ŭ, �������� ���� �´�
    float right = pos.x + size.x * 0.5f;    // ���
    float top = pos.y + size.y * 0.5f;  // ��� (DX�ϱ� +- ������ �ʿ� ����)
    float bottom = pos.y - size.y * 0.5f; // �ϴ�

    // �� �������� ���۵Ǵ� ������ �����͸� ���Ϳ� ����ִ´�
    // * ���� ������ �޸� ������ �����Ϳ� ���� ���� ������ ������ ���� �ٸ���
    // * 'emplace_back' : ������ push_back�� ����ѵ�, �޸𸮸� ������ �������� �� �ű�� �Լ�
    vertices.emplace_back(left, top, 0, 0);
    vertices.emplace_back(right, top, 1, 0);
    vertices.emplace_back(left, bottom, 0, 1);
    vertices.emplace_back(right, bottom, 1, 1);

    // ���� ���� �߰����� ���� ���� �Ű����� ({0, 0}, {1, 0} ��)....
    // -> �̰��� UV��ǥ. ������ �������� (left+top ��) �׸����� ġ�� ������� �����ϴ� ��.
    //    UV ��ǥ�� 0�� �ּ�, 1�� �ִ� ����....
    // vertices.emplace_back(left, top, 0, 0) <- ���⼭ 0, 0�� �� �׸��� �ְ� ���� ����� ��
    // vertices.emplace_back(right, bottom, 1, 1) <- ���⼭ 1, 1�� �׸��� �ְ� ������ �Ʒ���� ��

    // �� �������� ȭ���� ����ϵ��� 3���� ������ �������ָ� �ȴ� (�ﰢ�� + �ﰢ��)

    indices = { 0, 1, 2, 2, 1, 3 }; // 012 �ﰢ�� + 213 �ﰢ��

    // �� ���� ���� �����Ϳ� ����(���� �� ����) �����͸� �޸𸮿� ����ϸ� ��
    vertexBuffer = new VertexBuffer(vertices.data(), sizeof(Vertex), vertices.size());
    // ������ �����͸�, ���Ͷ�� �ڷ��� ũ�⸦ ��������, ���� �� ���� ������ŭ �޸𸮿� ����Ѵٴ� ��
    indexBuffer = new IndexBuffer(indices.data(), indices.size()); // int�� ���� ����
}
