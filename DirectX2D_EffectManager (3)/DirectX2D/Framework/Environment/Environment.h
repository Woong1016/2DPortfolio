#pragma once

class Environment : public Singleton<Environment>
{
private:
    friend class Singleton;

    Environment();
    ~Environment();

public:
    void SetAlphaBlend();
    void SetAdditiveBlend();

    void SetViewport(UINT width = WIN_WIDTH, UINT height = WIN_HEIGHT);
    void SetProjection();

    Camera* GetMainCamera() { return mainCamera; }

private:
    void CreateProjection();
    void CreateSamplerState();
    void CreateBlendState();
    void CreateRasterizerState();

private:
    MatrixBuffer* projectionBuffer;

    ID3D11SamplerState* samplerState;
    ID3D11BlendState* alphaBlendState;
    ID3D11BlendState* additiveBlendState;
    ID3D11RasterizerState* rasterizerState;

    Camera* mainCamera; // 환경설정에서 이제 카메라 1대가 기본으로 설정되어 있다
                        // -> 시야 데이터가 이제 카메라로 분담된 것

    D3D11_VIEWPORT viewport;
};