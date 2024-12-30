#pragma once

class GameObject : public Transform // 게임오브젝트 (트랜스폼 상속)
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

    // 공간 (없어도 만들고 있으면 받을)
    MatrixBuffer* worldBuffer;
        
    vector<Vertex> vertices;
    vector<UINT> indices;
};