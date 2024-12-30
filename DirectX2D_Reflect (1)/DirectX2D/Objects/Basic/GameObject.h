#pragma once

class GameObject : public Transform // ���ӿ�����Ʈ (Ʈ������ ���)
{
public:
    GameObject(wstring shaderFile = L"UV.hlsl");
    ~GameObject();

    virtual void Update();
    virtual void Render();

protected:
    VertexShader* vertexShader;
    PixelShader* pixelShader;
    VertexBuffer* vertexBuffer = nullptr;
    IndexBuffer* indexBuffer = nullptr;

    // ���� (��� ����� ������ ����)
    MatrixBuffer* worldBuffer;
        
    vector<Vertex> vertices;
    vector<UINT> indices;
};