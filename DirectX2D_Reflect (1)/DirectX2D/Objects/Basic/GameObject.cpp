#include "Framework.h"

GameObject::GameObject(wstring shaderFile)
{
    vertexShader = Shader::AddVS(L"Vertex" + shaderFile);
    pixelShader = Shader::AddPS(L"Pixel" + shaderFile);

    worldBuffer = new MatrixBuffer(); // ��� ������ �ϴ� ����� �α� (���� ������ ������ ����)
}

GameObject::~GameObject()
{
    if (vertexBuffer)
        delete vertexBuffer;

    if (indexBuffer)
        delete indexBuffer;

    delete worldBuffer; // ��ü�� (=Ʈ��������) �� ���� ����
}

void GameObject::Update()
{
    // Ʈ������ �����͸� �����ؼ� ��ġ�� ������ �ο�
    UpdateWorld(); // �θ� Ŭ������ �Լ� ����
}

void GameObject::Render()
{    
    // DX�μ� ���̴��� ��ġ�Ƿ�, �������� ���̴��� ��� �Ѵ�
    // -> �� ���, ���̴��� ����� ��Ʈ(�ȼ�)�� �ƴ϶� ���� ������ ��(������)�� �ȴ�
    //    "�� �����Ͱ� ���� ���� ��� ��ġ�� ������ ���� �����ϰ�, 3D ��� ��, ����Ϳ� ����ؾ� �ϴ°�?"

    // -> �̷��� ����Ǵ� ���� �׷��� ���̴��� "������ ���̴�(Vertex Shader)"��� �Ѵ�

    worldBuffer->Set(world);  // �θ� Ŭ�������� �޴� wolrd �����͸� ������ �ִ´�
    worldBuffer->SetVS(0);    // VS (���ؽ� ���̴�) ���� ���� (���̴� ������ �ؽ�ó Ŭ���� Ȯ��)

    // -> �� �繰�� ������ ���� ��� �ӿ��� ��� ����Ǵ��� ��ǻ�Ͱ� �˰�, �װ� ������� �� �ִ�

    // �� ���� �Ŀ�, �繰�� ���� ���� �����͸� ������ָ� �ȴ�

    //---------------------------------------------------------------------------

    if (vertexBuffer)
        vertexBuffer->Set();
    if (indexBuffer)
        indexBuffer->Set();
    
    vertexShader->Set();
    pixelShader->Set();

    DC->DrawIndexed(indices.size(), 0, 0);
}
